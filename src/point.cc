#include "point.h"

namespace mercator {

Point::Point() : coords_(0.0, 0.0, 0.0), 
                 color_(0, 0, 0),
                 uncertainty_(-1.0), 
                 cameras_(0), 
                 score_(0.0) {}

} // namespace mercator
