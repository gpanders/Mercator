#ifndef MERCATOR_POINT_H_
#define MERCATOR_POINT_H_

#include <Eigen/Core>

#include "util/types.h"

namespace mercator {

class Point {
 public:
  Point();

  Eigen::Vector3d& Coords();
  const Eigen::Vector3d Coords() const;
  double& Coords(const size_t idx);
  const double Coords(const size_t idx) const;
  void SetCoords(const Eigen::Vector3d& coords);

  Eigen::Vector3ub& Color();
  const Eigen::Vector3ub Color() const;
  uint8_t& Color(const size_t idx);
  const uint8_t Color(const size_t idx) const;
  void SetColor(const Eigen::Vector3ub& color);

  const double Uncertainty() const;
  void SetUncertainty(const double uncertainty);

  const uint64_t Cameras() const;
  void SetCameras(const uint64_t cameras);

  const bool Covered() const;
  void SetCovered(const bool covered);

 private:
  Eigen::Vector3d coords_;
  Eigen::Vector3ub color_;
  double uncertainty_;
  uint64_t cameras_;
  bool covered_;
};

}

#endif // MERCATOR_POINT_H_
