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

#ifndef MERCATOR_UTIL_CONFIG_H_
#define MERCATOR_UTIL_CONFIG_H_

#include <boost/program_options.hpp>
#include <string>

namespace mercator {

class ConfigManager {
 public:
  ConfigManager(); 

  bool ReadConfigFile(const std::string&);

  const std::string PrintOptions() const;

  double uncertainty_threshold;
  double camera_pixel_size;
  double min_ground_sampling_distance;
  uint64_t min_cameras;
  short print_ba_summary;

 private:
  boost::program_options::options_description desc_;
  boost::program_options::variables_map vmap_;

};

} // namespace mercator

#endif // MERCATOR_UTIL_CONFIG_H_
