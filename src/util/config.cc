#include <fstream>

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
                     "Minimum number of cameras that see the point");
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

} // namespace mercator
