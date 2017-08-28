#ifndef MERCATOR_CAMERA_H_
#define MERCATOR_CAMERA_H_

#include <vector>

#include <Eigen/Core>

namespace mercator {

class Camera {
 public:
  Camera();

  const uint32_t CameraId() const;
  void SetCameraId(const uint32_t camera_id);

  const uint64_t Width() const;
  void SetWidth(const uint64_t width);

  const uint64_t Height() const;
  void SetHeight(const uint64_t height);

  const std::vector<double> Params() const;
  std::vector<double>& Params();
  void SetParams(const std::vector<double>& params);

  void WorldToImage(const Eigen::Vector3d world, Eigen::Vector2d* image);

 private:
  uint32_t camera_id_;
  uint64_t width_;
  uint64_t height_;
  std::vector<double> params_;

};

} // namespace mercator

#endif // MERCATOR_CAMERA_H_
