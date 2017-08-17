#ifndef MERCATOR_COLMAP_H_
#define MERCATOR_COLMAP_H_

#include <string>
#include <vector>

#include "point.h"

namespace mercator {

bool ReadCOLMAP(const std::string& fname, std::vector<Point> *points); 

} // namespace mercator

#endif // MERCATOR_COLMAP_H_
