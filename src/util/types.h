#ifndef MERCATOR_TYPES_H_
#define MERCATOR_TYPES_H_

#include <Eigen/Core>

namespace Eigen {

typedef Eigen::Matrix<uint8_t, 3, 1> Vector3ub;

} // namespace Eigen

namespace mercator {

const uint64_t kInvalidPoint3dId = std::numeric_limits<uint64_t>::max();

} // namespace mercator

#endif // MERCATOR_TYPES_H_
