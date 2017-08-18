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

bool ReadCOLMAP(const std::string& fname, std::vector<Point> *points)
{
  std::ifstream file(fname, std::ios::binary);
  if (!file.is_open())
  {
    std::cerr << "Could not open file " << fname << std::endl;
    return false;
  }

  const auto num_points = ReadBinary<uint64_t>(&file);

  if (!points->empty())
  {
    std::cerr << "Reading COLMAP file failed: input vector must be empty."
              << std::endl;
    return false;
  }

  try
  {
    for (size_t i = 0; i < num_points; i++)
    {
      Point point;
      ReadBinary<uint64_t>(&file); // point3d_id
      // The first three values are the X, Y, Z coordinates of the point
      point.Coords(0) = ReadBinary<double>(&file); // x
      point.Coords(1) = ReadBinary<double>(&file); // y
      point.Coords(2) = ReadBinary<double>(&file); // z

      // The next 3 values are the colors of the 3d point, which we are
      // not concerned with
      point.Color(0) = ReadBinary<uint8_t>(&file); // color[0] (r)
      point.Color(1) = ReadBinary<uint8_t>(&file); // color[1] (g)
      point.Color(2) = ReadBinary<uint8_t>(&file); // color[2] (b)

      // Next is the reprojection error
      ReadBinary<double>(&file); // error

      // And finally the uncertainty
      point.SetUncertainty(ReadBinary<double>(&file)); // uncertainty

      // Next are the tracks
      const auto track_length = ReadBinary<uint64_t>(&file);
      for (size_t j = 0; j < track_length; j++)
      {
        ReadBinary<uint32_t>(&file); // image_id
        ReadBinary<uint32_t>(&file); // point2d_idx
      }

      point.SetCameras(track_length);

      points->push_back(point);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Reading COLMAP file failed. Caught exception: "
              << e.what() << std::endl;
    return false;
  }

  return true;
}

} // namespace mercator
