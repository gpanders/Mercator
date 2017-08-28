#include "camera.h"

namespace mercator {

Camera::Camera() : camera_id_(-1), width_(0), height_(0) {}

const uint32_t Camera::CameraId() const { return camera_id_; }

void Camera::SetCameraId(const uint32_t camera_id) { camera_id_ = camera_id; }

const uint64_t Camera::Width() const { return width_; }

void Camera::SetWidth(const uint64_t width) { width_ = width; }

const uint64_t Camera::Height() const { return height_; }

void Camera::SetHeight(const uint64_t height) { height_ = height; }

const Eigen::Quaterniond& Camera::Rotation() const { return rotation_; }

Eigen::Quaterniond& Camera::Rotation() { return rotation_; }

void Camera::SetRotation(const Eigen::Quaterniond& rotation)
{
  rotation_ = rotation;
}

const Eigen::Vector3d& Camera::Translation() const { return translation_; }

Eigen::Vector3d& Camera::Translation() { return translation_; }

void Camera::SetTranslation(const Eigen::Vector3d& translation)
{
  translation_ = translation;
}

const std::vector<double> Camera::Params() const { return params_; }

std::vector<double>& Camera::Params() { return params_; }

void Camera::SetParams(const std::vector<double>& params) { params_ = params; }

void Camera::WorldToImage(const Eigen::Vector3d& world, Eigen::Vector2d* image)
{
  // Put world point in camera's reference frame
  // TODO: Not sure if the translation should be + or -
  const Eigen::Vector3d world_local = rotation_ * (world + translation_);

  // Get params from params vector
  // These could change based on the camera model being used
  const double focal_length = params_[0];
  const double cx = params_[1];
  const double cy = params_[2];
  const double radial_distortion = params_[3];

  // Normalize to image plane
  const double X = world_local(0) / world_local(2);
  const double Y = world_local(1) / world_local(2);

  // Calculate radial distortion
  const double r2 = X*X + Y*Y;
  const double radial = radial_distortion * r2;

  // Calculate image coordinates relative
  const double x = X * (1 + radial);
  const double y = Y * (1 + radial);

  (*image)(0) = focal_length * x + cx;
  (*image)(1) = focal_length * y + cy;
}

} // namespace mercator
