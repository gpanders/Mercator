/**
 *  @file   camera.cc
 *  @author Greg Anders
 *  @date   8/31/2017
 *
 *  @brief  Class to represent a camera model
 */
#include "camera.h"

namespace mercator {

Camera::Camera() : camera_id_(-1),
                   width_(0),
                   height_(0),
                   pixel_size_(0),
                   params_(4, 0) {}

uint32_t Camera::CameraId() const { return camera_id_; }

uint32_t& Camera::CameraId() { return camera_id_; }

void Camera::SetCameraId(const uint32_t camera_id) { camera_id_ = camera_id; }

uint64_t Camera::Width() const { return width_; }

uint64_t& Camera::Width(){ return width_; }

void Camera::SetWidth(const uint64_t width) { width_ = width; }

uint64_t Camera::Height() const { return height_; }

uint64_t& Camera::Height() { return height_; }

void Camera::SetHeight(const uint64_t height) { height_ = height; }

double Camera::PixelSize() const { return pixel_size_; }

double& Camera::PixelSize() { return pixel_size_; }

void Camera::SetPixelSize(const double pixel_size) { pixel_size_ = pixel_size; }

const std::vector<double> Camera::Params() const { return params_; }

std::vector<double>& Camera::Params() { return params_; }

void Camera::SetParams(const std::vector<double>& params) { params_ = params; }

void Camera::WorldToImage(const std::vector<double> params,
                          const Eigen::Vector3d& world,
                          Eigen::Vector2d* image)
{
  WorldToImage(params.data(), world.data(), image->data());
}

} // namespace mercator
