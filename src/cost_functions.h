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

#ifndef MERCATOR_COST_FUNCTIONS_H_
#define MERCATOR_COST_FUNCTIONS_H_

#include <vector>

#include <ceres/ceres.h>
#include <ceres/rotation.h>

#include <Eigen/Core>
#include <Eigen/Geometry>

#include "camera.h"
#include "point2d.h"

namespace mercator {

// Cost function to use with Ceres. Calculates the residuals between the
// projected position of 3D points onto the camera frame and the corresponding
// image points
class ReprojectionCostFunction {
 public:
  ReprojectionCostFunction(const Camera& camera,
                           const Eigen::Quaterniond& rot,
                           const Eigen::Vector3d& trans,
                           const Point2d& point2d)
    : params_(camera.Params()),
      qw_(rot.w()), qx_(rot.x()), qy_(rot.y()), qz_(rot.z()),
      tx_(trans(0)), ty_(trans(1)), tz_(trans(2)),
      x_(point2d.X()),
      y_(point2d.Y()) {}

  template<typename T>
  bool operator()(const T* const world, T* residuals) const
  {
    const T quat[4] = { T(qw_), T(qx_), T(qy_), T(qz_) };

    T world_local[3];
    ceres::QuaternionRotatePoint(quat, world, world_local);

    // camera[3,4,5] are the translation
    world_local[0] += T(tx_);
    world_local[1] += T(ty_);
    world_local[2] += T(tz_);

    T image[2];
    const std::vector<T> params(params_.begin(), params_.end());
    Camera::WorldToImage(params.data(), world_local, image);

    // Compute residuals
    residuals[0] = image[0] - T(x_);
    residuals[1] = image[0] - T(y_);

    return true;
  }

  static ceres::CostFunction* Create(const Camera& camera,
                                     const Eigen::Quaterniond& rot,
                                     const Eigen::Vector3d& trans,
                                     const Point2d& point2d)
  {
    return (new ceres::AutoDiffCostFunction<ReprojectionCostFunction, 2, 3>(
          new ReprojectionCostFunction(camera, rot, trans, point2d)));
  }

 private:
  const double qw_;
  const double qx_;
  const double qy_;
  const double qz_;
  const double tx_;
  const double ty_;
  const double tz_;
  const double x_;
  const double y_;

  const std::vector<double> params_;
};

} // namespace mercator

#endif // MERCATOR_COST_FUNCTIONS_H_
