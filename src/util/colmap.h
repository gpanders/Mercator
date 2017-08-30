#ifndef MERCATOR_COLMAP_H_
#define MERCATOR_COLMAP_H_

#include <map>
#include <string>

#include "camera.h"
#include "image.h"
#include "point3d.h"

namespace mercator {

class ColmapReader {
 public:
  ColmapReader();

  bool Read(const std::string& path);
  bool ReadCameras(const std::string& path);
  bool ReadImages(const std::string& path);
  bool ReadPoints(const std::string& path);

  inline const std::map<uint32_t, Camera>& Cameras() const;
  inline std::map<uint32_t, Camera>& Cameras();

  inline const std::map<uint32_t, Image>& Images() const;
  inline std::map<uint32_t, Image>& Images();

  inline const std::map<uint64_t, Point3d>& Points() const;
  inline std::map<uint64_t, Point3d>& Points();

 private:
  std::map<uint32_t, Camera> cameras_;

  std::map<uint32_t, Image> images_;

  std::map<uint64_t, Point3d> points3d_;
};

const std::map<uint32_t, Camera>& ColmapReader::Cameras() const { return cameras_; }

std::map<uint32_t, Camera>& ColmapReader::Cameras() { return cameras_; }

const std::map<uint32_t, Image>& ColmapReader::Images() const { return images_; }

std::map<uint32_t, Image>& ColmapReader::Images() { return images_; }

const std::map<uint64_t, Point3d>& ColmapReader::Points() const { return points3d_; }

std::map<uint64_t, Point3d>& ColmapReader::Points() { return points3d_; }

} // namespace mercator

#endif // MERCATOR_COLMAP_H_
