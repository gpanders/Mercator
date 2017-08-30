#ifndef MERCATOR_IMAGE_H_
#define MERCATOR_IMAGE_H_

#include <vector>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "camera.h"
#include "point2d.h"

namespace mercator {

class Image {
 public:
  Image();

  uint32_t ImageId() const;
  void SetImageId(const uint32_t image_id);

  const std::string& Name() const;
  std::string& Name();
  void SetName(const std::string& name);

  const class Camera& Camera() const;
  class Camera& Camera();
  void SetCamera(const class Camera& camera);

  uint32_t NumPoints3d() const;
  void SetNumPoints3d(const uint32_t num_points_3d);

  const Eigen::Quaterniond& Rotation() const;
  Eigen::Quaterniond& Rotation();
  void SetRotation(const Eigen::Quaterniond& rotation);

  const Eigen::Vector3d& Translation() const;
  Eigen::Vector3d& Translation();
  void SetTranslation(const Eigen::Vector3d& translation);

  const std::vector<Point2d>& Points2d() const;
  std::vector<Point2d>& Points2d();
  void SetPoints2d(const std::vector<Point2d>& points2d);
  uint32_t NumPoints2d() const;

  void SetPoint3dForPoint2d(const uint32_t point2d_idx,
                            const uint64_t point3d_id);

 private:
  uint32_t image_id_;

  std::string name_;

  class Camera camera_;

  uint32_t num_points3d_;

  Eigen::Quaterniond rotation_;

  Eigen::Vector3d translation_;

  std::vector<Point2d> points2d_;
};

} // namespace mercator

#endif // MERCATOR_IMAGE_H_
