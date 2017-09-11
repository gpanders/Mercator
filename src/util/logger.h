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
