#include "logger.h"

namespace mercator {

Logger::Logger(const LogLevel level)
  : os_(std::cout), level_(level) {}

Logger::Logger(std::ostream& os, const LogLevel level)
  : os_(os), level_(level) {}

void Logger::SetLogLevel(const Logger::LogLevel level) { level_ = level; }

std::ostream& Logger::Debug() const
{
  if (level_ <= Logger::LogLevel::DEBUG)
  {
    os_ << "[DEBUG] ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Debug(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::DEBUG)
  {
    os_ << "[DEBUG] " << msg;
    return os_;
  }
  return null_;
}

std::ostream& Logger::Info() const
{
  if (level_ <= Logger::LogLevel::INFO)
  {
    os_ << "[INFO] ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Info(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::INFO)
  {
    os_ << "[INFO] " << msg;
    return os_;
  }
  return null_;
}

std::ostream& Logger::Warn() const
{
  if (level_ <= Logger::LogLevel::WARN)
  {
    os_ << "[WARN] ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Warn(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::WARN)
  {
    os_ << "[WARN] " << msg;
    return os_;
  }
  return null_;
}

std::ostream& Logger::Error() const
{
  if (level_ <= Logger::LogLevel::ERROR)
  {
    os_ << "[ERROR] ";
    return os_;
  }
  return null_;
}

std::ostream& Logger::Error(const std::string& msg) const
{
  if (level_ <= Logger::LogLevel::ERROR)
  {
    os_ << "[ERROR] " << msg;
    return os_;
  }
  return null_;
}

} /* mercator  */ 
