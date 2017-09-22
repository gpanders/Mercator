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

#include "point2d.h"
#include "util/types.h"

namespace mercator {

Point2d::Point2d()
  : coords_(Eigen::Vector2d::Zero()), point3d_id_(-1) {}

Point2d::Point2d(const double x, const double y)
  : coords_(x, y), point3d_id_(-1) {}

const Eigen::Vector2d& Point2d::Coords() const { return coords_; }

Eigen::Vector2d& Point2d::Coords() { return coords_; }

double Point2d::Coords(const size_t idx) const { return coords_(idx); }

double& Point2d::Coords(const size_t idx) { return coords_(idx); }

void Point2d::SetCoords(const Eigen::Vector2d& coords) { coords_ = coords; }

double Point2d::X() const { return coords_(0); }

double& Point2d::X() { return coords_(0); }

double Point2d::Y() const { return coords_(1); }

double& Point2d::Y() { return coords_(1); }

uint64_t Point2d::Point3dId() const { return point3d_id_; }

bool Point2d::HasPoint3d() const { return point3d_id_ != kInvalidPoint3dId; }

void Point2d::SetPoint3dId(const uint64_t point3d_id)
{
  point3d_id_ = point3d_id;
}

} // namespace mercator
