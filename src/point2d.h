/**
 *  @file   point2d.h
 *  @author Greg Anders
 *  @date   8/31/2017
 *
 *  @brief  Class to represent a 2D image point
 */
#ifndef MERCATOR_POINT2D_H_
#define MERCATOR_POINT2D_H_

#include <Eigen/Core>

namespace mercator {

class Point2d {
 public:
  Point2d();
  Point2d(const double x, const double y);

  const Eigen::Vector2d& Coords() const;
  Eigen::Vector2d& Coords();
  double Coords(const size_t idx) const;
  double& Coords(const size_t idx);
  void SetCoords(const Eigen::Vector2d& coords);

  double X() const;
  double& X();

  double Y() const;
  double& Y();

  uint64_t Point3dId() const;
  bool HasPoint3d() const;
  void SetPoint3dId(const uint64_t point3d_id);

 private:
  Eigen::Vector2d coords_;

  uint64_t point3d_id_;

};

}

#endif // MERCATOR_POINT2D_H_
