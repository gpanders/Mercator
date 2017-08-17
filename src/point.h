#ifndef MERCATOR_POINT_H_
#define MERCATOR_POINT_H_

#include <Eigen/Core>

#include "util/types.h"

namespace mercator {

class Point {
    public:

    Point();

    inline Eigen::Vector3d& Coords();
    inline const Eigen::Vector3d Coords() const;
    inline double& Coords(const size_t idx);
    inline const double Coords(const size_t idx) const;
    inline void SetCoords(const Eigen::Vector3d& coords);

    inline Eigen::Vector3ub& Color();
    inline const Eigen::Vector3ub Color() const;
    inline uint8_t& Color(const size_t idx);
    inline const uint8_t Color(const size_t idx) const;
    inline void SetColor(const Eigen::Vector3ub& color);

    inline const double Uncertainty() const;
    inline void SetUncertainty(const double uncertainty);

    inline const uint64_t Cameras() const;
    inline void SetCameras(const uint64_t cameras);

    inline const double Score() const;

    private:

    Eigen::Vector3d coords_;
    Eigen::Vector3ub color_;
    double uncertainty_;
    uint64_t cameras_;
    double score_;
};

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

const double Point::Score() const { return score_; }

}

#endif // MERCATOR_POINT_H_
