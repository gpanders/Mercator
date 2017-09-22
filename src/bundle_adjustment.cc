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

#include <iostream>
#include <string>

#include "bundle_adjustment.h"

namespace mercator {

BundleAdjustment::BundleAdjustment(const BundleAdjustment::Options& options)
  : options_(options) {}

void BundleAdjustment::AddCamera(const Camera& camera)
{
  cameras_.emplace(camera.CameraId(), camera);
}

void BundleAdjustment::AddImage(const Image& image)
{
  images_.emplace(image.ImageId(), image);
}

void BundleAdjustment::AddPoint(const Point3d& point3d)
{
  points3d_.emplace(point3d.Point3dId(), point3d);
}

bool BundleAdjustment::HasCamera(const uint32_t camera_id) const
{
  return cameras_.count(camera_id) > 0;
}

bool BundleAdjustment::HasImage(const uint32_t image_id) const
{
  return images_.count(image_id) > 0;
}

bool BundleAdjustment::HasPoint(const uint64_t point3d_id) const
{
  return points3d_.count(point3d_id) > 0;
}

const std::unordered_map<uint32_t, Camera>& BundleAdjustment::Cameras() const
{
  return cameras_;
}

const std::unordered_map<uint32_t, Image>& BundleAdjustment::Images() const
{
  return images_;
}

const std::unordered_map<uint64_t, Point3d>& BundleAdjustment::Points() const
{
  return points3d_;
}

void BundleAdjustment::Run()
{
  problem_.reset(new ceres::Problem());

  for (const auto& image : images_)
  {
    const Camera& camera = cameras_.at(image.second.CameraId());
    for (const auto& point2d : image.second.Points2d())
    {
      if (!point2d.HasPoint3d())
      {
        continue;
      }

      try
      {
        Point3d& point3d = points3d_.at(point2d.Point3dId());
        problem_->AddResidualBlock(
            ReprojectionCostFunction::Create(
              camera,
              image.second.Rotation(),
              image.second.Translation(),
              point2d
            ),
            options_.loss_function,
            point3d.Coords().data());
      }
      catch (std::out_of_range& ignored) {}
    }
  }

  if (problem_->NumResiduals() > 0)
  {
    ceres::Solver::Options solver_options = options_.solver_options; 
    if (solver_options.num_threads == -1)
    {
#ifdef OPENMP_ENABLED
      solver_options.num_threads = omp_get_max_threads();
      solver_options.num_linear_solver_threads = omp_get_max_threads();
#else
      solver_options.num_threads = 1;
      solver_options.num_linear_solver_threads = 1;
#endif
    }

    ceres::Solve(solver_options, problem_.get(), &summary_);
  }

}

void BundleAdjustment::ComputeCovariance(std::vector<Point3d>* points)
{
  ceres::Covariance::Options covariance_options = options_.covariance_options;
  if (covariance_options.num_threads == -1)
  {
#ifdef OPENMP_ENABLED
    covariance_options.num_threads = omp_get_max_threads();
#else
    covariance_options.num_threads = 1;
#endif
  }
  ceres::Covariance covariance(covariance_options);

  std::vector< std::pair<const double*, const double*> > covariance_blocks;
  for (const auto& point : *points)
  {
    const double* data = point.Coords().data();
    if (problem_->HasParameterBlock(data))
    {
      covariance_blocks.emplace_back(data, data);
    }
  }

  CHECK(covariance.Compute(covariance_blocks, problem_.get()));

  for (auto& point : *points)
  {
    const double* data = point.Coords().data();
    covariance.GetCovarianceBlock(data, data, point.Covariance().data());
  }
}

void BundleAdjustment::PrintSummary(const bool print_full_report)
{
  const std::string report = print_full_report
    ? summary_.FullReport() : summary_.BriefReport();
  std::cout << report << std::endl;
}

const ceres::Solver::Summary& BundleAdjustment::Summary() const
{
  return summary_;
}

}
