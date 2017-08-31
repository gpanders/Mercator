#ifndef MERCATOR_CAMERA_H_
#define MERCATOR_CAMERA_H_

#include <vector>

#include <Eigen/Core>

namespace mercator {

class Camera {
 public:
  Camera();

  uint32_t CameraId() const;
  uint32_t& CameraId();
  void SetCameraId(const uint32_t camera_id);

  uint64_t Width() const;
  uint64_t& Width();
  void SetWidth(const uint64_t width);

  uint64_t Height() const;
  uint64_t& Height();
  void SetHeight(const uint64_t height);

  double PixelSize() const;
  double& PixelSize();
  void SetPixelSize(const double pixel_size);

  const std::vector<double> Params() const;
  std::vector<double>& Params();
  void SetParams(const std::vector<double>& params);

  template<typename T>
  static void WorldToImage(const T* const params, const T* const world,
                           T* image);

  static void WorldToImage(const std::vector<double> params,
                           const Eigen::Vector3d& world,
                           Eigen::Vector2d* image);

 private:
  uint32_t camera_id_;
  uint64_t width_; // px
  uint64_t height_; // px
  double pixel_size_; // mm

  // Focal length, principal point, radial distortion, etc.
  std::vector<double> params_;

};

template<typename T>
void Camera::WorldToImage(const T* const params, const T* const world,
                          T* image)
{
  // Get params from params vector
  // These could change based on the camera model being used
  const T& focal_length = params[0];
  const T& cx = params[1];
  const T& cy = params[2];
  const T& radial_distortion = params[3];

  // Normalize to image plane
  const T xp = world[0] / world[2];
  const T yp = world[1] / world[2];

  // Calculate radial distortion
  const T r2 = xp*xp + yp*yp;
  const T distortion = 1.0 + r2 * radial_distortion;

  image[0] = focal_length * distortion * xp + cx;
  image[1] = focal_length * distortion * yp + cy;
}

} // namespace mercator

#endif // MERCATOR_CAMERA_H_
