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
    ceres::LossFunction* loss_function;

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
      loss_function = new ceres::TrivialLoss();

      solver_options.function_tolerance = 0.0;
      solver_options.gradient_tolerance = 0.0;
      solver_options.parameter_tolerance = 0.0;
      solver_options.minimizer_progress_to_stdout = false;
      solver_options.max_num_iterations = 100;
      solver_options.max_linear_solver_iterations = 200;
      solver_options.max_num_consecutive_invalid_steps = 10;
      solver_options.max_consecutive_nonmonotonic_steps = 10;
      solver_options.linear_solver_type = ceres::DENSE_SCHUR;
      solver_options.num_threads = -1;
      solver_options.num_linear_solver_threads = -1;

      covariance_options.num_threads = -1;
      // covariance_options.algorithm_type = ceres::DENSE_SVD;
      // covariance_options.null_space_rank = 1;
    }
  };

  BundleAdjustment(const Options& options);

  void AddCamera(const Camera& camera);

  void AddImage(const Image& image);

  void AddPoint(const Point3d& point3d);

  bool HasCamera(const uint32_t camera_id) const;

  bool HasImage(const uint32_t image_id) const;

  bool HasPoint(const uint64_t point3d_id) const;

  const std::unordered_map<uint32_t, Camera>& Cameras() const;

  const std::unordered_map<uint32_t, Image>& Images() const;

  const std::unordered_map<uint64_t, Point3d>& Points() const;

  void Run();

  void ComputeCovariance(std::vector<Point3d>* points);

  void PrintSummary(const bool print_full_report);

  const ceres::Solver::Summary& Summary() const;

 private:
  std::unique_ptr<ceres::Problem> problem_;
  ceres::Solver::Summary summary_;
  const Options options_;

  std::unordered_map<uint32_t, Camera> cameras_;
  std::unordered_map<uint32_t, Image> images_;
  std::unordered_map<uint64_t, Point3d> points3d_;

};

} // namespace mercator

#endif // MERCATOR_BUNDLE_ADJUSTMENT_H_
