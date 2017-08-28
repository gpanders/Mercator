#include "point.h"

namespace mercator {

Point::Point() : coords_(0.0, 0.0, 0.0), 
                 color_(0, 0, 0),
                 uncertainty_(-1.0), 
                 cameras_(0), 
                 covered_(false) {}

Eigen::Vector3d& Point::Coords() { return coords_; }

const Eigen::Vector3d Point::Coords() const { return coords_; }

double& Point::Coords(const size_t idx) { return coords_(idx); }

const double Point::Coords(const size_t idx) const { return coords_(idx); }

void Point::SetCoords(const Eigen::Vector3d& coords) { coords_ = coords; }

Eigen::Vector3ub& Point::Color() { return color_; }

const Eigen::Vector3ub Point::Color() const { return color_; }

uint8_t& Point::Color(const size_t idx) { return color_(idx); }

const uint8_t Point::Color(const size_t idx) const { return color_(idx); }

void Point::SetColor(const Eigen::Vector3ub& color) { color_ = color; }

const double Point::Uncertainty() const { return uncertainty_; }

void Point::SetUncertainty(const double uncertainty) { uncertainty_ = uncertainty; }

const uint64_t Point::Cameras() const { return cameras_; }

void Point::SetCameras(const uint64_t cameras) { cameras_ = cameras; }

const bool Point::Covered() const { return covered_; }

void Point::SetCovered(const bool covered) { covered_ = covered; }

} // namespace mercator
