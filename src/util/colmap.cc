#include <algorithm> // std::reverse
#include <exception>
#include <fstream>
#include <iostream>

#include "util/colmap.h"
#include "util/types.h"

namespace mercator {

namespace {

inline bool IsLittleEndian()
{
#ifdef BOOST_BIG_ENDIAN
  return false;
#else
  return true;
#endif
}

inline bool IsBigEndian()
{
#ifdef BOOST_BIG_ENDIAN
  return true;
#else
  return false;
#endif
}

template<typename T>
T ReverseBytes(const T& data)
{
  T data_reversed = data;
  std::reverse(reinterpret_cast<char*>(&data_reversed),
               reinterpret_cast<char*>(&data_reversed) + sizeof(T));
  return data_reversed;
}

template<typename T>
T ReadBinary(std::istream* stream)
{
  T data_little_endian;
  stream->read(reinterpret_cast<char*>(&data_little_endian), sizeof(T));
  return IsLittleEndian() ? data_little_endian : ReverseBytes(data_little_endian);
}

} // namespace

ColmapReader::ColmapReader() {}

bool ColmapReader::Read(const std::string& path)
{
  if (!points3d_.empty() || !cameras_.empty() || !images_.empty())
  {
    std::cerr << "ColmapReader instance is stale. Create a new instance to "
              << "read new data."
              << std::endl;
    return false;
  }

  return ReadCameras(path) && ReadImages(path) && ReadPoints(path);
  

  return true;
}

bool ColmapReader::ReadCameras(const std::string& path)
{
  const std::string cameras_path = path + "/cameras.bin";
  std::ifstream cameras_file(cameras_path, std::ios::binary);

  if (!cameras_file.is_open())
  {
    std::cerr << "Couldn't open file " << cameras_path << std::endl;
    return false;
  }

  // Read cameras
  const auto num_cameras = ReadBinary<uint64_t>(&cameras_file);
  try
  {
    for (size_t i = 0; i < num_cameras; i++)
    {
      class Camera camera;
      camera.SetCameraId(ReadBinary<uint32_t>(&cameras_file));
      ReadBinary<int>(&cameras_file); // model_id
      camera.SetWidth(ReadBinary<uint64_t>(&cameras_file));
      camera.SetHeight(ReadBinary<uint64_t>(&cameras_file));

      for (size_t j = 0; j < camera.Params().size(); j++)
      {
        camera.Params()[j] = ReadBinary<double>(&cameras_file);
      }
      cameras_.emplace(camera.CameraId(), camera);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Reading COLMAP cameras file failed. Caught exception: "
              << e.what() << std::endl;
    return false;
  }

  return true;
}

bool ColmapReader::ReadImages(const std::string& path)
{
  if (cameras_.empty())
  {
    std::cerr << "Cameras must be read before images." << std::endl;
    return false;
  }

  const std::string images_path = path + "/images.bin";
  std::ifstream images_file(images_path, std::ios::binary);

  if (!images_file.is_open())
  {
    std::cerr << "Could not open file " << images_path << std::endl;
    return false;
  }

  // Read images
  const auto num_reg_images = ReadBinary<uint64_t>(&images_file);
  try
  {
    for (size_t i = 0; i < num_reg_images; ++i)
    {
      class Image image;
      image.SetImageId(ReadBinary<uint32_t>(&images_file));

      image.Rotation().w() = ReadBinary<double>(&images_file);
      image.Rotation().x() = ReadBinary<double>(&images_file);
      image.Rotation().y() = ReadBinary<double>(&images_file);
      image.Rotation().z() = ReadBinary<double>(&images_file);
      image.Rotation().normalize();

      image.Translation()(0) = ReadBinary<double>(&images_file);
      image.Translation()(1) = ReadBinary<double>(&images_file);
      image.Translation()(2) = ReadBinary<double>(&images_file);

      image.SetCameraId(ReadBinary<uint32_t>(&images_file));

      char name_char;
      do
      {
        images_file.read(&name_char, 1);
        if (name_char != '\0') {
          image.Name() += name_char;
        }
      } while (name_char != '\0');

      const auto num_points2d = ReadBinary<uint64_t>(&images_file);

      std::vector<Point2d> points2d;
      points2d.reserve(num_points2d);
      std::vector<uint64_t> point3d_ids;
      point3d_ids.reserve(num_points2d);
      for (size_t j = 0; j < num_points2d; j++)
      {
        const auto x = ReadBinary<double>(&images_file);
        const auto y = ReadBinary<double>(&images_file);
        points2d.emplace_back(x, y);
        point3d_ids.push_back(ReadBinary<uint64_t>(&images_file));
      }

      image.SetPoints2d(points2d);

      for (uint32_t point2d_idx = 0; point2d_idx < image.NumPoints2d();
           ++point2d_idx)
      {
        if (point3d_ids[point2d_idx] != kInvalidPoint3DId)
        {
          image.SetPoint3dForPoint2d(point2d_idx, point3d_ids[point2d_idx]);
        }
      }

      images_.emplace(image.ImageId(), image);
    }

    return true;
  }
  catch (std::exception& e)
  {
    std::cerr << "Reading COLMAP images file failed. Caught exception: "
              << e.what() << std::endl;
    return false;
  }
}

bool ColmapReader::ReadPoints(const std::string& path)
{
  if (images_.empty())
  {
    std::cerr << "Images must be read before points." << std::endl;
    return false;
  }

  const std::string points3d_path = path + "/points3D.bin";
  std::ifstream points3d_file(points3d_path, std::ios::binary);

  if (!points3d_file.is_open())
  {
    std::cerr << "Could not open file " << points3d_path << std::endl;
    return false;
  }

  // Read points
  const auto num_points = ReadBinary<uint64_t>(&points3d_file);
  try
  {
    for (size_t i = 0; i < num_points; i++)
    {
      Point3d point;
      point.SetPoint3dId(ReadBinary<uint64_t>(&points3d_file));
      // The first three values are the X, Y, Z coordinates of the point
      point.Coords(0) = ReadBinary<double>(&points3d_file); // x
      point.Coords(1) = ReadBinary<double>(&points3d_file); // y
      point.Coords(2) = ReadBinary<double>(&points3d_file); // z

      // The next 3 values are the colors of the 3d point, which we are
      // not concerned with
      point.Color(0) = ReadBinary<uint8_t>(&points3d_file); // color[0] (r)
      point.Color(1) = ReadBinary<uint8_t>(&points3d_file); // color[1] (g)
      point.Color(2) = ReadBinary<uint8_t>(&points3d_file); // color[2] (b)

      // Next is the reprojection error
      ReadBinary<double>(&points3d_file); // error

      for (size_t j = 0; j < point.Covariance().size(); j++)
      {
        point.Covariance()(j) = ReadBinary<double>(&points3d_file);
      }

      // Next are the tracks
      const auto track_length = ReadBinary<uint64_t>(&points3d_file);
      for (size_t j = 0; j < track_length; j++)
      {
        const auto image_id = ReadBinary<uint32_t>(&points3d_file);
        point.ImageIds().push_back(image_id);
        ReadBinary<uint32_t>(&points3d_file); // point2d_idx
      }

      points3d_.emplace(point.Point3dId(), point);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Reading COLMAP points file failed. Caught exception: "
              << e.what() << std::endl;
    return false;
  }

  return true;
}

} // namespace mercator
