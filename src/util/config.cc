/**
 *  @file   config.cc
 *  @author Greg Anders
 *  @date   9/11/2017
 *
 *  @brief  Implementation of config manager
 */
#include <fstream>
#include <sstream>

#include "util/config.h"

namespace mercator {

namespace po = boost::program_options;

ConfigManager::ConfigManager()
{
  desc_.add_options()("uncertainty_threshold",
                     po::value<double>(&uncertainty_threshold)->required(),
                     "Maximum allowed uncertainty of the point")
                     ("min_cameras",
                     po::value<uint64_t>(&min_cameras)->required(),
                     "Minimum number of cameras that see the point")
                     ("camera_pixel_size",
                     po::value<double>(&camera_pixel_size)->required(),
                     "Size (in mm) of each camera pixel")
                     ("min_ground_sampling_distance",
                     po::value<double>(&min_ground_sampling_distance)->required(),
                     "Ground sampling distance requirement")
                     ("print_ba_summary",
                     po::value<short>(&print_ba_summary),
                     "Print a summary of the bundle adjustment (0, 1, or 2)");
}

bool ConfigManager::ReadConfigFile(const std::string& path)
{
  std::ifstream config_file(path);
  if (!config_file.is_open())
  {
    return false;
  }

  po::store(po::parse_config_file(config_file, desc_), vmap_);
  po::notify(vmap_);

  return true;
}

const std::string ConfigManager::PrintOptions() const
{
  std::ostringstream ss;
  ss << "Using configuration:\n"
    << "uncertainty_threshold = " << uncertainty_threshold << "\n"
    << "min_cameras = " << min_cameras << "\n"
    << "camera_pixel_size = " << camera_pixel_size << "\n"
    << "min_ground_sampling_distance = " << min_ground_sampling_distance << "\n"
    << "print_ba_summary = " << print_ba_summary << "\n";
  return ss.str();
}

} // namespace mercator
