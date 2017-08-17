#ifndef MERCATOR_UTIL_CONFIG_H_
#define MERCATOR_UTIL_CONFIG_H_

#include <boost/program_options.hpp>
#include <string>

namespace mercator {

class ConfigManager {
 public:
  ConfigManager(); 

  bool ReadConfigFile(const std::string&);

  double uncertainty_threshold;
  uint8_t min_cameras;

 private:

  boost::program_options::options_description desc_;
  boost::program_options::variables_map vmap_;

};

}

#endif // MERCATOR_UTIL_CONFIG_H_
