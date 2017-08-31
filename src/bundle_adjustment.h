#ifndef MERCATOR_BUNDLE_ADJUSTMENT_H_
#define MERCATOR_BUNDLE_ADJUSTMENT_H_

#include <memory>
#include <unordered_map>
#include <vector>

#include <ceres/ceres.h>

#include <Eigen/Core>

#include "cost_functions.h"
#include "image.h"
#include "point2d.h"
#include "point3d.h"

namespace mercator {

class BundleAdjustment {
 public:
  struct Options {
    // Type of loss function to use. If NULL, ceres will default to a squared
    // loss function
    ceres::LossFunction* loss_function = nullptr;

    // Ceres specific options
    ceres::Solver::Options solver_options;

    ceres::Covariance::Options covariance_options;

    // Whether or not to print the summary of the bundle adjustment after
    // completion
    bool print_summary = false;

    // If print_summary is true, whether or not to print the FullReport or the
    // BriefReport
    bool print_full_report = false;

    Options()
    {
      solver_options.linear_solver_type = ceres::DENSE_SCHUR;
      solver_options.num_threads = -1;

      covariance_options.num_threads = -1;
      // covariance_options.algorithm_type = ceres::DENSE_SVD;
      // covariance_options.null_space_rank = 1;
    }
  };

  BundleAdjustment(const Options& options);

  void AddCamera(const Camera& camera);

  void AddImage(const Image& image);

  void AddPoint(const Point3d& point3d);

  void Run();

  void ComputeCovariance(std::vector<Point3d>* points);

  void PrintSummary(const bool print_full_report);

  const ceres::Solver::Summary Summary() const;
 private:
  std::unique_ptr<ceres::Problem> problem_;
  std::unique_ptr<ceres::Solver::Summary> summary_;

  std::unordered_map<uint32_t, Camera> cameras_;
  std::unordered_map<uint32_t, Image> images_;
  std::unordered_map<uint64_t, Point3d> points3d_;

  const Options options_;
};

}

#endif // MERCATOR_BUNDLE_ADJUSTMENT_H_
