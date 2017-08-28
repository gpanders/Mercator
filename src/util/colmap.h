#ifndef MERCATOR_COLMAP_H_
#define MERCATOR_COLMAP_H_

#include <string>
#include <vector>

#include "camera.h"
#include "point.h"

namespace mercator {

bool ReadCOLMAP(const std::string& path,
                std::vector<Point>* points, std::vector<Camera>* cameras);

} // namespace mercator

#endif // MERCATOR_COLMAP_H_
