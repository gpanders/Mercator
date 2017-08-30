#ifndef MERCATOR_POINT3D_H_
#define MERCATOR_POINT3D_H_

#include <vector>

#include <Eigen/Core>

#include "image.h"
#include "util/types.h"

namespace mercator {

class Point3d {
 public:
  Point3d();

  uint64_t Point3dId() const;
  void SetPoint3dId(const uint64_t point3d_id);

  Eigen::Vector3d& Coords();
  const Eigen::Vector3d& Coords() const;
  double& Coords(const size_t idx);
  double Coords(const size_t idx) const;
  void SetCoords(const Eigen::Vector3d& coords);

  double X() const;
  double& X();
  double Y() const;
  double& Y();
  double Z() const;
  double& Z();

  Eigen::Vector3ub& Color();
  const Eigen::Vector3ub& Color() const;
  uint8_t& Color(const size_t idx);
  uint8_t Color(const size_t idx) const;
  void SetColor(const Eigen::Vector3ub& color);

  const Eigen::Matrix3d& Covariance() const;
  Eigen::Matrix3d& Covariance();
  void SetCovariance(const Eigen::Matrix3d& covariance);

  const std::vector<Image>& Images() const;
  std::vector<Image>& Images();
  void SetImages(const std::vector<Image>& images);

  bool Covered() const;
  void SetCovered(const bool covered);

 private:
  uint64_t point3d_id_;
  Eigen::Vector3d coords_;
  Eigen::Vector3ub color_;
  Eigen::Matrix3d covariance_;
  std::vector<Image> images_;
  bool covered_;
};

}

#endif // MERCATOR_POINT3D_H_
