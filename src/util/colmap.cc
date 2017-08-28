#include <algorithm> // std::reverse
#include <exception>
#include <fstream>
#include <iostream>

#include "util/colmap.h"

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

bool ReadCOLMAP(const std::string& path,
                std::vector<Point>* points, std::vector<Camera>* cameras)
{
  const std::string points_path = path + "/points3D.bin";
  const std::string cameras_path = path + "/cameras.bin";
  std::ifstream points_file(points_path, std::ios::binary);
  std::ifstream cameras_file(cameras_path, std::ios::binary);

  if (!points_file.is_open())
  {
    std::cerr << "Could not open file " << points_path << std::endl;
    return false;
  }

  if (!cameras_file.is_open())
  {
    std::cerr << "Could not open file " << cameras_path << std::endl;
    return false;
  }


  if (!points->empty() || !cameras->empty())
  {
    std::cerr << "Reading COLMAP data failed: input vectors must be empty."
              << std::endl;
    return false;
  }

  // Read points
  const auto num_points = ReadBinary<uint64_t>(&points_file);

  try
  {
    for (size_t i = 0; i < num_points; i++)
    {
      Point point;
      ReadBinary<uint64_t>(&points_file); // point3d_id
      // The first three values are the X, Y, Z coordinates of the point
      point.Coords(0) = ReadBinary<double>(&points_file); // x
      point.Coords(1) = ReadBinary<double>(&points_file); // y
      point.Coords(2) = ReadBinary<double>(&points_file); // z

      // The next 3 values are the colors of the 3d point, which we are
      // not concerned with
      point.Color(0) = ReadBinary<uint8_t>(&points_file); // color[0] (r)
      point.Color(1) = ReadBinary<uint8_t>(&points_file); // color[1] (g)
      point.Color(2) = ReadBinary<uint8_t>(&points_file); // color[2] (b)

      // Next is the reprojection error
      ReadBinary<double>(&points_file); // error

      // And finally the uncertainty
      point.SetUncertainty(ReadBinary<double>(&points_file)); // uncertainty

      // Next are the tracks
      const auto track_length = ReadBinary<uint64_t>(&points_file);
      for (size_t j = 0; j < track_length; j++)
      {
        ReadBinary<uint32_t>(&points_file); // image_id
        ReadBinary<uint32_t>(&points_file); // point2d_idx
      }

      point.SetCameras(track_length);

      points->push_back(point);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Reading COLMAP points file failed. Caught exception: "
              << e.what() << std::endl;
    return false;
  }

  // Read cameras
  const auto num_cameras = ReadBinary<uint64_t>(&cameras_file);
  try
  {
    for (size_t i = 0; i < num_cameras; i++)
    {
      Camera camera;
      camera.SetCameraId(ReadBinary<uint32_t>(&cameras_file));
      ReadBinary<int>(&cameras_file); // model_id
      camera.SetWidth(ReadBinary<uint64_t>(&cameras_file));
      camera.SetHeight(ReadBinary<uint64_t>(&cameras_file));

      for (size_t j = 0; j < camera.Params().size(); j++)
      {
        camera.Params()[j] = ReadBinary<double>(&cameras_file);
      }
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

} // namespace mercator
