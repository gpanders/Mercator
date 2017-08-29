#ifndef MERCATOR_POINT_H_
#define MERCATOR_POINT_H_

#include "<vector>"

#include <Eigen/Core>

#include "camera.h"
#include "util/types.h"

namespace mercator {

class Point3d {
 public:
  Point3d();

  Eigen::Vector3d& Coords();
  const Eigen::Vector3d& Coords() const;
  double& Coords(const size_t idx);
  double Coords(const size_t idx) const;
  void SetCoords(const Eigen::Vector3d& coords);

  Eigen::Vector3ub& Color();
  const Eigen::Vector3ub& Color() const;
  uint8_t& Color(const size_t idx);
  uint8_t Color(const size_t idx) const;
  void SetColor(const Eigen::Vector3ub& color);

  const Eigen::Matrix3d& Covariance() const;
  Eigen::Matrix3d& Covariance();
  void SetCovariance(const Eigen::Matrix3d& covariance);

  const std::vector<Camera>& Cameras() const;
  std::vector<Camera>& Cameras();
  void SetCameras(const std::vector<Camera>& cameras);

  bool Covered() const;
  void SetCovered(const bool covered);

 private:
  Eigen::Vector3d coords_;
  Eigen::Vector3ub color_;
  Eigen::Matrix3d covariance_;
  std::vector<Camera> cameras_;
  bool covered_;
};

}

#endif // MERCATOR_POINT_H_
