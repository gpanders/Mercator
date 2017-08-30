#include <iostream>
#include <numeric>

#include "util/colmap.h"
#include "util/config.h"

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  // const std::string config_file = "config.ini";

  // mercator::ConfigManager config;

  // if (!config.ReadConfigFile(config_file))
  // {
  //   std::cerr << "Failed to read config file: " << config_file << std::endl;
  //   return 1;
  // }

  const std::string path = argv[1];

  mercator::ColmapReader reader;

  if (reader.Read(path))
  {
    auto& points = reader.Points();
    auto& cameras = reader.Cameras();
    auto& images = reader.Images();
    std::cout << "There are " << points.size() << " 3d points and "
              << images.size() << " images." << std::endl;
  }
  else
  {
    std::cout << "Something went wrong." << std::endl;
    return 1;
  }

  return 0;
}
