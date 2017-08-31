#ifndef MERCATOR_H_
#define MERCATOR_H_

double CalculateGroundSamplingDistance(const double pixel_size_mm,
                                       const double focal_length_mm,
                                       const double distance);

double CalculateDistanceForGSD(const double pixel_size_mm,
                               const double focal_length_mm,
                               const double gsd);

#endif // MERCATOR_H_
