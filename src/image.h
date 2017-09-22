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

  uint32_t CameraId() const;
  uint32_t& CameraId();
  void SetCameraId(const uint32_t camera_id);

  uint32_t NumPoints3d() const;
  uint32_t& NumPoints3d();
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

  Eigen::Vector3d Transform(const Eigen::Vector3d& point3d);
  void SetPoint3dForPoint2d(const uint32_t point2d_idx,
                            const uint64_t point3d_id);

 private:
  // The unique ID of this image
  uint32_t image_id_;

  // The file name associated with this image
  std::string name_;

  // The unique camera ID of the camera that took this image
  uint32_t camera_id_;

  // How many 3D world points this image observes
  uint32_t num_points3d_;

  // Rotation from the world frame to the image frame
  Eigen::Quaterniond rotation_;

  // Translation from the world frame to the image frame
  Eigen::Vector3d translation_;

  // List of image points
  std::vector<Point2d> points2d_;
};

} // namespace mercator

#endif // MERCATOR_IMAGE_H_
