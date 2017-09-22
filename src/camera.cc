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
