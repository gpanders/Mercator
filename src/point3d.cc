#include <Eigen/EigenSolver>

#include "point3d.h"

namespace mercator {

Point3d::Point3d() : point3d_id_(-1),
                     coords_(Eigen::Vector3d::Zero()),
                     color_(Eigen::Vector3ub::Zero()),
                     uncertainty_(-1.0),
                     covered_(false) {}

uint64_t Point3d::Point3dId() const { return point3d_id_; }

void Point3d::SetPoint3dId(const uint64_t point3d_id)
{
  point3d_id_ = point3d_id;
}

Eigen::Vector3d& Point3d::Coords() { return coords_; }

const Eigen::Vector3d& Point3d::Coords() const { return coords_; }

double& Point3d::Coords(const size_t idx) { return coords_(idx); }

double Point3d::Coords(const size_t idx) const { return coords_(idx); }

void Point3d::SetCoords(const Eigen::Vector3d& coords) { coords_ = coords; }

double Point3d::X() const { return coords_(0); }

double& Point3d::X() { return coords_(0); }

double Point3d::Y() const { return coords_(1); }

double& Point3d::Y() { return coords_(1); }

double Point3d::Z() const { return coords_(2); }

double& Point3d::Z() { return coords_(2); }

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
  uncertainty_ = covariance.eigenvalues().real().maxCoeff();
}

double Point3d::Uncertainty() const { return uncertainty_; }

double& Point3d::Uncertainty() { return uncertainty_; }

void Point3d::SetUncertainty(const double uncertainty)
{
  uncertainty_ = uncertainty;
}

const std::vector<uint32_t>& Point3d::ImageIds() const { return image_ids_; }

std::vector<uint32_t>& Point3d::ImageIds() { return image_ids_; }

void Point3d::SetImageIds(const std::vector<uint32_t>& image_ids)
{
  image_ids_ = image_ids;
}

bool Point3d::Covered() const { return covered_; }

void Point3d::SetCovered(const bool covered) { covered_ = covered; }

} // namespace mercator
