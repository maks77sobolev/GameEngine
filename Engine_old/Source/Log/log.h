#pragma once
#include "Core/Utility.h"
#include <memory>
#include <concepts>
#include <format>
#include <string>
#include <string_view>
#include <source_location>
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
    void log(const LogCategory& category, LogVerbosity verbocity, const std::string& message, bool showLocation=false,
        const std::source_location location = std::source_location::current()) const;

private:
    Log();
    ~Log();
class Impl;
std::unique_ptr<Impl> m_pImpl;
};
constexpr LogVerbosity c_minVerbosity = LogVerbosity::Display;
constexpr LogVerbosity c_maxVerbosity = LogVerbosity::Fatal;

// concepts
template <typename T>
concept ValidLogCategory = std::constructible_from<LogCategory, T>;

template <typename T>
concept LoggableMessage = std::convertible_to<T, std::string> || std::convertible_to<T, std::string_view>;

template <LogVerbosity V>
concept ValidVerbosityLevel = V == LogVerbosity::NoLogging   //
                              || V == LogVerbosity::Display  //
                              || V == LogVerbosity::Warning  //
                              || V == LogVerbosity::Error    //
                              || V == LogVerbosity::Log      //
                              || V == LogVerbosity::Fatal;


}
#define DEFINE_LOG_CATEGORY_STATIC(logName)   \
     namespace                                  \
    {                                           \
        LifeExe::LogCategory logName(#logName);\
    }
#define LE_LOG_IMPL(categoryName, verbosity, showLocation, formatStr, ...)                                                        \
    do                                                                                                                            \
    {                                                                                                                             \
        if constexpr (LifeExe::LogVerbosity::verbosity >= LifeExe::c_minVerbosity &&                                              \
                      LifeExe::LogVerbosity::verbosity <= LifeExe::c_maxVerbosity)                                                \
        {                                                                                                                         \
            static_assert(LifeExe::ValidVerbosityLevel<LifeExe::LogVerbosity::verbosity>,                                         \
                "Verbosity must be one of: NoLogging, Display, Warning, Error, Log, Fatal");                                      \
            static_assert(LifeExe::ValidLogCategory<decltype(categoryName)>, "Category must be of type LogCategory");             \
            static_assert(                                                                                                        \
                LifeExe::LoggableMessage<decltype(formatStr)>, "Message must be convertible to std::string or std::string_view"); \
            LifeExe::Log::GetInstance().log(                                                                                      \
                categoryName, LifeExe::LogVerbosity::verbosity, std::format(formatStr __VA_OPT__(, ) __VA_ARGS__), showLocation); \
        }                                                                                                                         \
    } while (0)

#define LE_LOG(categoryName, verbosity, formatStr, ...) LE_LOG_IMPL(categoryName, verbosity, false, formatStr, __VA_ARGS__)
#define LE_LOG_DEBUG(categoryName, verbosity, formatStr, ...) LE_LOG_IMPL(categoryName, verbosity, true, formatStr, __VA_ARGS__)