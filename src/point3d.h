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

#ifndef MERCATOR_POINT3D_H_
#define MERCATOR_POINT3D_H_

#include <vector>

#include <Eigen/Core>

#include "util/types.h"

namespace mercator {

class Point3d {
 public:
  Point3d();

  uint64_t Point3dId() const;
  void SetPoint3dId(const uint64_t point3d_id);

  Eigen::Vector3d& Coords();
  const Eigen::Vector3d& Coords() const;
  double& Coords(const size_t idx);
  double Coords(const size_t idx) const;
  void SetCoords(const Eigen::Vector3d& coords);

  double X() const;
  double& X();
  double Y() const;
  double& Y();
  double Z() const;
  double& Z();

  Eigen::Vector3ub& Color();
  const Eigen::Vector3ub& Color() const;
  uint8_t& Color(const size_t idx);
  uint8_t Color(const size_t idx) const;
  void SetColor(const Eigen::Vector3ub& color);

  const Eigen::Matrix3d& Covariance() const;
  Eigen::Matrix3d& Covariance();
  void SetCovariance(const Eigen::Matrix3d& covariance);

  double Uncertainty() const;
  double& Uncertainty();
  void SetUncertainty(const double uncertainty);

  const std::vector<uint32_t>& ImageIds() const;
  std::vector<uint32_t>& ImageIds();
  void SetImageIds(const std::vector<uint32_t>& image_ids);

  bool Covered() const;
  void SetCovered(const bool covered);

 private:
  uint64_t point3d_id_;
  Eigen::Vector3d coords_;
  Eigen::Vector3ub color_;
  Eigen::Matrix3d covariance_;
  double uncertainty_;
  std::vector<uint32_t> image_ids_;
  bool covered_;
};

} // namespace mercator

#endif // MERCATOR_POINT3D_H_
