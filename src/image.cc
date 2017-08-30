#include "image.h"

namespace mercator {

Image::Image()
  : image_id_(-1), num_points3d_(0) {}

uint32_t Image::ImageId() const { return image_id_; }

void Image::SetImageId(const uint32_t image_id) { image_id_ = image_id; }

const std::string& Image::Name() const { return name_; }

std::string& Image::Name() { return name_; }

void Image::SetName(const std::string& name) { name_ = name; }

const class Camera& Image::Camera() const { return camera_; }

class Camera& Image::Camera() { return camera_; }

void Image::SetCamera(const class Camera& camera) { camera_ = camera; }

uint32_t Image::NumPoints3d() const { return num_points3d_; }

void Image::SetNumPoints3d(const uint32_t num_points_3d) { num_points3d_ = num_points_3d; }

const Eigen::Quaterniond& Image::Rotation() const { return rotation_; }

Eigen::Quaterniond& Image::Rotation() { return rotation_; }

void Image::SetRotation(const Eigen::Quaterniond& rotation) { rotation_ = rotation; }

const Eigen::Vector3d& Image::Translation() const { return translation_; }

Eigen::Vector3d& Image::Translation() { return translation_; }

void Image::SetTranslation(const Eigen::Vector3d& translation) { translation_ = translation; }

const std::vector<Point2d>& Image::Points2d() const { return points2d_; }

std::vector<Point2d>& Image::Points2d() { return points2d_; }

void Image::SetPoints2d(const std::vector<Point2d>& points2d) { points2d_ = points2d; }

uint32_t Image::NumPoints2d() const { return points2d_.size(); }

void Image::SetPoint3dForPoint2d(const uint32_t point2d_idx,
                                 const uint64_t point3d_id)
{
  Point2d& point2d = points2d_.at(point2d_idx);
  if (!point2d.HasPoint3d()) {
    num_points3d_ += 1;
  }
  point2d.SetPoint3dId(point3d_id);
}

}