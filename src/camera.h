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

#ifndef MERCATOR_CAMERA_H_
#define MERCATOR_CAMERA_H_

#include <vector>

#include <Eigen/Core>

namespace mercator {

// Represents a physical camera (not an actual image)
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
  // This camera's unique id
  uint32_t camera_id_;

  // Width of the camera frame in pixels
  uint64_t width_;

  // Height of the camera frame in pixels
  uint64_t height_;

  // Physical size of each pixel of the camera in mm
  double pixel_size_; // mm

  // Focal length, principal point, radial distortion, etc.
  std::vector<double> params_;

};

// Project a 3D point onto a 2D image plane using a given camera model. The
// inputs are the intrinsic parameters of the camera and the coordinates of the
// 3D world point. A pointer to an array representing the 2D coordinates of the
// image point is given and is populated with the result of the function.
//
// Note that this function is templated in order to work with Ceres. The input
// parameters must also be pointers to the underlying data structure.
//
// Currently this function assumes a radial distortion model. This function can
// (and probably should) be further abstracted to work with other distortion
// models.
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
