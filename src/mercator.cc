#include <algorithm>
#include <cmath>
#include <iostream>

#include <Eigen/Core>
#include <Eigen/Eigenvalues>

#include "util/colmap.h"
#include "util/config.h"

#include "mercator.h"
#include "bundle_adjustment.h"

using namespace mercator;

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: " << argv[0] << " <path>" << std::endl;
    return 1;
  }

  const std::string config_file = "config.ini";

  ConfigManager config;

  if (!config.ReadConfigFile(config_file))
  {
    std::cerr << "Failed to read config file: " << config_file << std::endl;
    return 1;
  }

  BundleAdjustment::Options ba_options;

  ColmapReader reader;

  if (reader.Read(argv[1]))
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
      if (point.second.Uncertainty() < config.uncertainty_threshold &&
          num_cameras >= config.min_cameras)
      {
        std::cout << "Point " << point.second.Point3dId()
                  << " is already covered, skipping..." << std::endl;
        point.second.SetCovered(true);
        continue;
      }

      // Otherwise, prepare for a new bundle adjustment
      BundleAdjustment ba(ba_options);
      ba.AddCamera(camera);
      ba.AddPoint(point.second);

      // Add every other image that sees this point
      for (const auto image_id : point.second.ImageIds())
      {
        const Image& image = reader.Image(image_id);
        ba.AddImage(image);
      }

      Image new_image;
      new_image.SetCameraId(camera.CameraId());

      CreateVirtualCameraForPoint(
          point.second,
          camera,
          config.min_ground_sampling_distance,
          0,
          &new_image);

      if (!ProjectPointOntoImage(point.second, camera, &new_image))
      {
        continue;
      }

      for (const auto& other_point : reader.Points())
      {
        if (other_point.second.Point3dId() == point.second.Point3dId())
        {
          continue;
        }

        // If this point is visible in any of the images in the bundle
        // adjustment, add it to the BA
        const auto& image_ids = other_point.second.ImageIds();
        if (std::any_of(image_ids.begin(), image_ids.end(),
              [&ba](uint32_t image_id) { return ba.HasImage(image_id); }))
        {
          ba.AddPoint(other_point.second);
        }
        // Otherwise, if the projection of this point onto our virtual camera
        // exists in the virtual camera's frame, add it to the BA
        else if (ProjectPointOntoImage(other_point.second, camera, &new_image))
        {
          ba.AddPoint(other_point.second);
        }
      }

      // Add our new virtual camera to the bundle adjustment
      ba.AddImage(new_image);

      // Start the bundle adjustment
      ba.Run();

      if (config.print_ba_summary > 0)
      {
        ba.PrintSummary(config.print_ba_summary == 2);
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

/**
 * Calculate the ground sampling distance of an image taken from a given
 * distance
 *
 * @param pixel_size_mm   The physical size of each pixel of the camera, in mm
 * @param focal_length_mm Focal length of the camera, in mm
 * @param distance_m      Camera's distance from the desired object, in m
 *
 * @return                Ground sampling distance, in cm
 */
double CalculateGroundSamplingDistance(const double pixel_size_mm,
                                       const double focal_length_mm,
                                       const double distance_m)
{
  return (pixel_size_mm * (distance_m * 1000) / focal_length_mm) / 10;
}

/**
 * Calculate the maximum distance (or altitude) an image can be while
 * maintaining a desired ground sampling distance.
 *
 * @param pixel_size_mm   The physical size of each pixel of the camera, in mm
 * @param focal_length_mm Focal length of the camera, in mm
 * @param gsd_cm          The minimum ground sampling distance, in cm
 *
 * @return                Maximum distance, in meters
 */
double CalculateDistanceForGSD(const double pixel_size_mm,
                               const double focal_length_mm,
                               const double gsd_cm)
{
  return (((gsd_cm * 10) * focal_length_mm) / pixel_size_mm) / 1000;
}

/**
 * Calculate the rotation and translation of an imaginary camera located along
 * the eigenvector corresponding to the minimum eigenvalue, with an optional
 * angle offset.
 *
 * @param point3d     3D point under consideration
 * @param camera      A Camera object containing intrinsic parameters
 * @param gsd         The minimum ground sampling distance constraint 
 * @param angle       An angle offset (in radians) from the eigenvector axis
 * @param image       Pointer to an Image acting as a virtual camera whose
 *                    Rotation and Translation will be set 
 */
void CreateVirtualCameraForPoint(const Point3d& point3d,
                                 const Camera& camera,
                                 const double gsd,
                                 const double angle,
                                 Image* image)
{
  Eigen::EigenSolver<Eigen::Matrix3d> es(point3d.Covariance(), true);

  // Find eigenvector corresponding to smallest eigenvalue
  const auto& eigenvals = es.eigenvalues().real();
  const auto& eigenvecs = es.eigenvectors().real();

  Eigen::Vector3d::Index idx;
  eigenvals.minCoeff(&idx);
  const Eigen::Vector3d& min_eigenvec = eigenvecs.col(idx);

  // Calculate the maximum distance the camera can be from the point while
  // still meeting the ground sampling distance criteria
  double distance = CalculateDistanceForGSD(camera.PixelSize(),
      camera.Params()[0],
      gsd);

  // Normalized minimum eigenvector
  auto v = min_eigenvec.normalized();

  // If following this vector the requisite distance puts us below ground
  // level then move in the other direction
  if ((point3d.Coords() + distance * v)(2) <= 0)
  {
    v *= -1;
  }

  // Create angle-axis representation of rotation
  const Eigen::AngleAxisd aa(
      std::acos(v.dot(Eigen::Vector3d::UnitZ())) + angle,
      v.cross(Eigen::Vector3d::UnitZ()).normalized());

  // q is the quaternion representation of the rotation from the world
  // frame to the camera frame
  Eigen::Quaterniond q(aa);
  q.normalize();

  const Eigen::Vector3d T = q * (-point3d.Coords() + distance * v);

  image->SetRotation(q);
  image->SetTranslation(T);
}

/**
 * Project a 3D point onto an image
 *
 * @param point3d     The 3D point in the _reference_ frame
 * @param camera      A Camera object containing intrinsic parameters
 * @param image       Pointer to the Image to be projected onto
 *
 * @return            True if the projected point is visible in the camera's
 *                    frame
 */
bool ProjectPointOntoImage(const Point3d& point3d,
                           const Camera& camera,
                           mercator::Image* image)
{
  Eigen::Vector3d point3d_local = image->Transform(point3d.Coords());
  Point2d point2d;
  Camera::WorldToImage(camera.Params(), point3d_local, &point2d.Coords());

  if (point2d.X() >= 0 && point2d.X() <= camera.Width()
      && point2d.Y() >= 0 && point2d.Y() <= camera.Height())
  {
    point2d.SetPoint3dId(point3d.Point3dId());
    image->Points2d().push_back(point2d);
    image->NumPoints3d() += 1;
    return true;
  }

  return false;
}

