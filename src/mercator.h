/**
 *  @file   mercator.h
 *  @author Greg Anders
 *  @date   8/31/2017
 *
 *  @brief  Declaration of functions used in main program
 */
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
