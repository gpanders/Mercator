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

#ifndef MERCATOR_H_
#define MERCATOR_H_

#include "image.h"
#include "point3d.h"

double CalculateGroundSamplingDistance(const double pixel_size_mm,
                                       const double focal_length_mm,
                                       const double distance);

double CalculateDistanceForGSD(const double pixel_size_mm,
                               const double focal_length_mm,
                               const double gsd);

void CreateVirtualCameraForPoint(const mercator::Point3d& point3d,
                                 const mercator::Camera& camera,
                                 const double gsd,
                                 const double angle,
                                 mercator::Image* image);

bool ProjectPointOntoImage(const mercator::Point3d& point3d,
                           const mercator::Camera& camera,
                           mercator::Image* image);

#endif // MERCATOR_H_
