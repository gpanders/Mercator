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

  inline const std::map<uint32_t, class Camera>& Cameras() const;
  inline std::map<uint32_t, class Camera>& Cameras();
  inline class Camera& Camera(const uint32_t camera_id);

  inline const std::map<uint32_t, class Image>& Images() const;
  inline std::map<uint32_t, class Image>& Images();
  inline class Image& Image(const uint32_t image_id);

  inline const std::map<uint64_t, Point3d>& Points() const;
  inline std::map<uint64_t, Point3d>& Points();
  inline Point3d& Point(const uint64_t point3d_id);

 private:
  bool ReadCameras(const std::string& path);
  bool ReadImages(const std::string& path);
  bool ReadPoints(const std::string& path);

  std::map<uint32_t, class Camera> cameras_;

  std::map<uint32_t, class Image> images_;

  std::map<uint64_t, Point3d> points3d_;
};

const std::map<uint32_t, class Camera>& ColmapReader::Cameras() const { return cameras_; }

std::map<uint32_t, class Camera>& ColmapReader::Cameras() { return cameras_; }

class Camera& ColmapReader::Camera(const uint32_t camera_id)
{
  return cameras_.at(camera_id);
}

const std::map<uint32_t, class Image>& ColmapReader::Images() const { return images_; }

std::map<uint32_t, class Image>& ColmapReader::Images() { return images_; }

class Image& ColmapReader::Image(const uint32_t image_id)
{
  return images_.at(image_id);
}

const std::map<uint64_t, Point3d>& ColmapReader::Points() const { return points3d_; }

std::map<uint64_t, Point3d>& ColmapReader::Points() { return points3d_; }

Point3d& ColmapReader::Point(const uint64_t point3d_id)
{
  return points3d_.at(point3d_id);
}

} // namespace mercator

#endif // MERCATOR_COLMAP_H_
