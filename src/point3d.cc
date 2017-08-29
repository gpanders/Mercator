#include "point3d.h"

namespace mercator {

Point3d::Point3d() : coords_(0.0, 0.0, 0.0), 
                     color_(0, 0, 0),
                     uncertainty_(-1.0), 
                     cameras_(0), 
                     covered_(false) {}

Eigen::Vector3d& Point3d::Coords() { return coords_; }

const Eigen::Vector3d& Point3d::Coords() const { return coords_; }

double& Point3d::Coords(const size_t idx) { return coords_(idx); }

double Point3d::Coords(const size_t idx) const { return coords_(idx); }

void Point3d::SetCoords(const Eigen::Vector3d& coords) { coords_ = coords; }

Eigen::Vector3ub& Point3d::Color() { return color_; }

const Eigen::Vector3ub& Point3d::Color() const { return color_; }

uint8_t& Point3d::Color(const size_t idx) { return color_(idx); }

uint8_t Point3d::Color(const size_t idx) const { return color_(idx); }

void Point3d::SetColor(const Eigen::Vector3ub& color) { color_ = color; }

const Eigen::Matrix3d& Point3d::Covariance() const { return covariance_; }

Eigen::Matrix3d& Point3d::Covariance() { return covariance_; }

void Point3d::SetCovariance(const Eigen::Matrix3d& covariance)
{
  covariance_ = covariance;
}

const std::vector<Camera>& Point3d::Cameras() const { return cameras_; }

std::vector<Camera>& Point3d::Cameras() { return cameras_; }

void Point3d::SetCameras(const std::vector<Camera>& cameras)
{
  cameras_ = cameras;
}

bool Point3d::Covered() const { return covered_; }

void Point3d::SetCovered(const bool covered) { covered_ = covered; }

} // namespace mercator
