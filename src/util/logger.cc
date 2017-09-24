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

#include "logger.h"

namespace mercator {

Logger::Logger(const LogLevel level)
  : os_(std::cout), level_(level) {}

Logger::Logger(std::ostream& os, const LogLevel level)
  : os_(os), level_(level) {}

void Logger::SetLogLevel(const Logger::LogLevel level) { level_ = level; }

std::ostream& Logger::Log() const
{
  os_ << "LOG: ";
  return os_;
}

std::ostream& Logger::Log(const std::string& msg) const
{
  os_ << "LOG: " << msg << std::endl;
  return os_;
}

std::ostream& Logger::Debug() const
{
  if (level_ <= Logger::LogLevel::DEBUG)
  {
    os_ << "DEBUG: ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Debug(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::DEBUG)
  {
    os_ << "DEBUG: " << msg << std::endl;
    return os_;
  }
  return null_;
}

std::ostream& Logger::Info() const
{
  if (level_ <= Logger::LogLevel::INFO)
  {
    os_ << "INFO: ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Info(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::INFO)
  {
    os_ << "INFO: " << msg << std::endl;
    return os_;
  }
  return null_;
}

std::ostream& Logger::Warn() const
{
  if (level_ <= Logger::LogLevel::WARN)
  {
    os_ << "WARNING: ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Warn(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::WARN)
  {
    os_ << "WARNING: " << msg << std::endl;
    return os_;
  }
  return null_;
}

std::ostream& Logger::Error() const
{
  if (level_ <= Logger::LogLevel::ERROR)
  {
    os_ << "ERROR: ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Error(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::ERROR)
  {
    os_ << "ERROR: " << msg << std::endl;
    return os_;
  }
  return null_;
}

} // namespace mercator
