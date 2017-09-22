// Copyright (c) 2017 The University of Texas Radionavigation Lab
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: Greg Anders

#include "image.h"

namespace mercator {

Image::Image() : image_id_(-1),
                 camera_id_(-1),
                 num_points3d_(0) {}

uint32_t Image::ImageId() const { return image_id_; }

void Image::SetImageId(const uint32_t image_id) { image_id_ = image_id; }

const std::string& Image::Name() const { return name_; }

std::string& Image::Name() { return name_; }

void Image::SetName(const std::string& name) { name_ = name; }

uint32_t Image::CameraId() const { return camera_id_; }

uint32_t& Image::CameraId() { return camera_id_; }

void Image::SetCameraId(const uint32_t camera_id) { camera_id_ = camera_id; }

uint32_t Image::NumPoints3d() const { return num_points3d_; }

uint32_t& Image::NumPoints3d() { return num_points3d_; }

void Image::SetNumPoints3d(const uint32_t num_points_3d) { num_points3d_ = num_points_3d; }

const Eigen::Quaterniond& Image::Rotation() const { return rotation_; }

Eigen::Quaterniond& Image::Rotation() { return rotation_; }

void Image::SetRotation(const Eigen::Quaterniond& rotation) { rotation_ = rotation; }

const Eigen::Vector3d& Image::Translation() const { return translation_; }

Eigen::Vector3d& Image::Translation() { return translation_; }

void Image::SetTranslation(const Eigen::Vector3d& translation) { translation_ = translation; }

Eigen::Vector3d Image::Transform(const Eigen::Vector3d& point3d)
{
  return rotation_ * point3d + translation_;
}

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
