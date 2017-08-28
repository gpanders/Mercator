#include <iostream>
#include <numeric>

#include "camera.h"
#include "mercator.h"
#include "util/colmap.h"
#include "util/config.h"

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  const std::string config_file = "config.ini";

  mercator::ConfigManager config;

  if (!config.ReadConfigFile(config_file))
  {
    std::cerr << "Failed to read config file: " << config_file << std::endl;
    return 1;
  }

  const std::string path = argv[1];

  std::vector<mercator::Point> points;
  std::vector<mercator::Camera> cameras;
  if (mercator::ReadCOLMAP(path, &points, &cameras))
  {
    for (auto& point : points)
    {
      // Begin iteration through points

      // Check uncertainty threshold
      if (point.Uncertainty() > config.uncertainty_threshold)
      {
        point.SetCovered(false);
      }
      else if (point.Cameras() < config.min_cameras)
      {
        point.SetCovered(false);
      }


    }
  }
  else
  {
    std::cout << "Something went wrong." << std::endl;
    return 1;
  }

  return 0;
}
