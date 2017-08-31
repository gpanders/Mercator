#include <cmath>
#include <iostream>
#include <unordered_map>

#include <ceres/ceres.h>

#include <Eigen/Core>
#include <Eigen/Eigenvalues>

#include "util/colmap.h"
#include "util/config.h"

#include "mercator.h"
#include "bundle_adjustment.h"
#include "cost_functions.h"

using namespace mercator;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
    return 1;
  }

  const std::string config_file = "config.ini";

  ConfigManager config;

  if (!config.ReadConfigFile(config_file))
  {
    std::cerr << "Failed to read config file: " << config_file << std::endl;
    return 1;
  }

  const std::string path = argv[1];

  BundleAdjustment::Options ba_options;

  ColmapReader reader;

  if (reader.Read(path))
  {
    auto& cameras = reader.Cameras();
    if (cameras.size() > 1)
    {
      std::cout << "WARNING: More than one camera given! Defaulting to the "
                << "first." << std::endl;
    }

    Camera& camera = cameras.begin()->second;

    // This information is not provided by COLMAP so the user must supply it
    camera.SetPixelSize(config.camera_pixel_size);

    // Iterate over each point
    for (auto& point : reader.Points())
    {
      const Eigen::Vector3d& xyz = point.second.Coords();
      const size_t num_cameras = point.second.ImageIds().size();
      
      // If the maximum eigenvalue of the covariance matrix is less than the
      // threshold specified by the user, skip this point
      Eigen::EigenSolver<Eigen::Matrix3d> es(point.second.Covariance(), true);
      const auto& eigenvals = es.eigenvalues().real();
      if (eigenvals.maxCoeff() < config.uncertainty_threshold
          && num_cameras >= config.min_cameras)
      {
        point.second.SetCovered(true);
        continue;
      }

      // Otherwise, prepare for a new bundle adjustment
      BundleAdjustment ba(ba_options);
      ba.AddCamera(camera);
      ba.AddPoint(point.second);

      // Find quaternion that aligns the vector [0, 0, 1] with the minimum
      // eigenvector
      const auto& eigenvecs = es.eigenvectors().real();

      Eigen::Vector3d::Index idx;
      eigenvals.minCoeff(&idx);
      const auto& min_eigenvec = eigenvecs.col(idx);

      const double gsd_desired = config.min_ground_sampling_distance;
      double distance = CalculateDistanceForGSD(camera.PixelSize(),
          camera.Params()[0],
          gsd_desired);

      // Normalized minimum eigenvector
      auto v = min_eigenvec.normalized();

      // If following this vector the requisite distance puts us below ground
      // level then move in the other direction
      if ((xyz + distance * v)(2) <= 0)
      {
        std::cout << "Flipping eigenvector." << std::endl;
        v *= -1;
      }

      const Eigen::AngleAxisd aa(
          std::acos(v.dot(Eigen::Vector3d::UnitZ())),
          v.cross(Eigen::Vector3d::UnitZ()).normalized());

      // q is the quaternion representation of the rotation from the world 
      // frame to the camera frame
      Eigen::Quaterniond q(aa);
      q.normalize();

      const Eigen::Vector3d T = q * (-xyz + distance * v);

      Image new_image;

      new_image.SetCameraId(camera.CameraId());
      new_image.SetRotation(q);
      new_image.SetTranslation(T);

      Eigen::Vector3d xyz_local = new_image.Transform(xyz);

      Point2d point2d;
      Camera::WorldToImage(camera.Params().data(), xyz_local.data(),
          point2d.Coords().data());

      new_image.Points2d().push_back(point2d);
      new_image.NumPoints3d() += 1;

      for (const auto& other_point : reader.Points())
      {
        if (other_point.second.Point3dId() == point.second.Point3dId())
        {
          continue;
        }

        const Eigen::Vector3d& other_xyz = other_point.second.Coords();

        Point2d point2d;
        Eigen::Vector3d other_point_local = new_image.Transform(other_xyz);
        Camera::WorldToImage(camera.Params().data(),
            other_point_local.data(),
            point2d.Coords().data());

        if (point2d.X() < 0 || point2d.X() > camera.Width()
            || point2d.Y() < 0 || point2d.Y() > camera.Height())
        {
          // Skip points that don't fit in the camera frame
          continue;
        }

        ba.AddPoint(other_point.second);
        point2d.SetPoint3dId(other_point.second.Point3dId());
        new_image.Points2d().push_back(point2d);
        new_image.NumPoints3d() += 1;
      }

      break;
    }
  }
  else
  {
    std::cout << "Something went wrong." << std::endl;
    return 1;
  }

  return 0;
}

double CalculateGroundSamplingDistance(const double pixel_size_mm,
                                       const double focal_length_mm,
                                       const double distance_m)
{
  return (pixel_size_mm * (distance_m * 1000) / focal_length_mm) / 10;
}

double CalculateDistanceForGSD(const double pixel_size_mm,
                               const double focal_length_mm,
                               const double gsd_cm)
{
  return (((gsd_cm * 10) * focal_length_mm) / pixel_size_mm) / 1000;
}
