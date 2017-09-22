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

#ifndef MERCATOR_LOGGER_H
#define MERCATOR_LOGGER_H

#include <iostream>
#include <memory>
#include <string>

namespace mercator {

class Logger {
 public:
  enum class LogLevel
  {
    DEBUG,
    INFO,
    WARN,
    ERROR
  };

  Logger(const LogLevel level = LogLevel::WARN);
  Logger(std::ostream& os = std::cout, const LogLevel level = LogLevel::WARN);

  void SetLogLevel(const LogLevel level);

  std::ostream& Debug() const;
  std::ostream& Debug(const std::string& msg) const;

  std::ostream& Info() const;
  std::ostream& Info(const std::string& msg) const;

  std::ostream& Warn() const;
  std::ostream& Warn(const std::string& msg) const;

  std::ostream& Error() const;
  std::ostream& Error(const std::string& msg) const;

 private:
  class NullBuffer : public std::streambuf {
   public:
    inline int overflow(int c);
  };

  class NullStream : public std::ostream {
   public:
    NullStream() : std::ostream(&m_sb) {}
   private:
    NullBuffer m_sb;
  };

  LogLevel level_;
  mutable NullStream null_;
  std::ostream& os_;
};

int Logger::NullBuffer::overflow(int c) { return c; }

} // namespace mercator

#endif /* MERCATOR_LOGGER_H */
