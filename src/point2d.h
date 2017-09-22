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

#ifndef MERCATOR_POINT2D_H_
#define MERCATOR_POINT2D_H_

#include <Eigen/Core>

namespace mercator {

class Point2d {
 public:
  Point2d();
  Point2d(const double x, const double y);

  const Eigen::Vector2d& Coords() const;
  Eigen::Vector2d& Coords();
  double Coords(const size_t idx) const;
  double& Coords(const size_t idx);
  void SetCoords(const Eigen::Vector2d& coords);

  double X() const;
  double& X();

  double Y() const;
  double& Y();

  uint64_t Point3dId() const;
  bool HasPoint3d() const;
  void SetPoint3dId(const uint64_t point3d_id);

 private:
  // Image coordinates of this point
  Eigen::Vector2d coords_;

  // The unique ID of the 3D point corresponding to this point
  uint64_t point3d_id_;

};

} // namespace mercator

#endif // MERCATOR_POINT2D_H_
