// Copyright (c) 2017 The University of Texas Radionavigation Lab
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: Greg Anders

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
                     po::value<int>(&print_ba_summary)->default_value(1),
                     "Print a summary of the bundle adjustment (0, 1, or 2)")
                     ("log_level",
                     po::value<int>(&log_level)->default_value(2),
                     "Log level (0, 1, 2, 3)");
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
