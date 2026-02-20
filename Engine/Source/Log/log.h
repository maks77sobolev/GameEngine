#pragma once
#include "Core/Utility.h"
#include <memory>

namespace LifeExe
{
enum class LogVerbosity : uint8_t
{
    NoLogging = 0,
    Display,
    Log,
    Warning,
    Error,
    Fatal
};
struct LogCategory
{
    explicit LogCategory(const std::string& name):m_name(name) {}

  std::string  name() const { return m_name; }

private: 
  std::string  m_name;
};

class Log final : public NonCopyable
{
public:
    static Log& GetInstance() 
    { static Log instance;
        return instance;
    }
    void log(const LogCategory& category,LogVerbosity verbocity, const std::string& message) const;

private:
    Log();
    ~Log();
class Impl;
std::unique_ptr<Impl> m_pImpl;
};
#define DEFINE_LOG_CATEGORY_STATIC(logName)   \
     namespace                                  \
    {                                           \
        LifeExe::LogCategory logName(#logName);\
    }

}