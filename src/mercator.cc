#include <iostream>
#include <pcl/io/ply_io.h>
#include <pcl/PolygonMesh.h>

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

  const std::string ply_fname = argv[1];

  pcl::PolygonMesh mesh;
  pcl::PLYReader ply_reader;
  auto ret_val = ply_reader.read(ply_fname, mesh);

  std::cout << "ret_val = " << ret_val << std::endl;

  //std::cout << mesh << std::endl;

  /*
  std::vector<mercator::Point> points;
  if (mercator::ReadCOLMAP(fname, &points))
  {
    std::vector<mercator::Point> bad_points;  // need a better name for this
    for (const auto& point : points)
    {
      if (point.Uncertainty() > config.uncertainty_threshold ||
          point.Cameras() < config.min_cameras)
      {
        bad_points.push_back(point);
      }
    }

    std::cout << "This file has " << points.size() << " points, "
              << bad_points.size() << " of which do not meet the specified "
              << "criteria." << std::endl;

    std::vector<double> uncertainty_vec(points.size());
    std::transform(points.begin(), points.end(), uncertainty_vec.begin(),
        [](const mercator::Point& p) { return p.Uncertainty(); });

    auto uncertainty_vec_sum = std::accumulate(uncertainty_vec.begin(),
                                               uncertainty_vec.end(), 0.0);
    auto uncertainty_vec_avg = uncertainty_vec_sum / uncertainty_vec.size();

    auto uncertainty_vec_minmax = std::minmax_element(uncertainty_vec.begin(),
                                                      uncertainty_vec.end());

    std::vector<uint64_t> camera_vec(points.size());
    std::transform(points.begin(), points.end(), camera_vec.begin(),
        [](const mercator::Point& p) { return p.Cameras(); });

    auto camera_vec_sum = std::accumulate(camera_vec.begin(),
                                          camera_vec.end(), 0.0);
    auto camera_vec_avg = camera_vec_sum / camera_vec.size();

    auto camera_vec_minmax = std::minmax_element(camera_vec.begin(),
                                                 camera_vec.end());

    std::cout << "The average uncertainty is "
              << uncertainty_vec_avg << std::endl;
    std::cout << "The min uncertainty is "
              << *uncertainty_vec_minmax.first << std::endl;
    std::cout << "The max uncertainty is "
              << *uncertainty_vec_minmax.second << std::endl;

    std::cout << "The average number of cameras per point is "
              << camera_vec_avg << std::endl;
    std::cout << "The minimum number of cameras per point is "
              << *camera_vec_minmax.first << std::endl;
    std::cout << "The maximum number of cameras per point is "
              << *camera_vec_minmax.second << std::endl;
  }
  else
  {
    std::cout << "Something went wrong." << std::endl;
    return 1;
  }
  */

  return 0;
}
