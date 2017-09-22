// Copyright (c) 2017 The University of Texas Radionavigation Lab
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: Greg Anders

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
