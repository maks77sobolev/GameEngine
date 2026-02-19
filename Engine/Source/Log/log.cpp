#include "log.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
using namespace LifeExe;
namespace
{
const std::unordered_map<LogVerbosity, spdlog::level::level_enum> c_verbocityMap
{
    {LogVerbosity::NoLogging, spdlog::level::off},
    {LogVerbosity::Display, spdlog::level::info},
    {LogVerbosity::Warning, spdlog::level::warn},
    {LogVerbosity::Error, spdlog::level::err},
    {LogVerbosity::Fatal  , spdlog::level::critical}
};

};  // namespace
//pImpl
class Log::Impl
{
public:
    Impl() {
        const auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        m_consoleLogger = std::make_unique<spdlog::logger>("console", consoleSink);
    
    };
    void log(LogVerbosity verbosity, const std::string& message) const
    {
        if (verbosity == LogVerbosity::NoLogging) return;

        
        const auto verbocity = c_verbocityMap.find(verbosity);  // searching through map
        if (verbocity != c_verbocityMap.end())                  // if "find" found some key-value pair
        {
            m_consoleLogger->log(verbocity->second, message);  // from "find" selecting second field-value
        }
    
    }
private:
    std::unique_ptr<spdlog::logger> m_consoleLogger;

};

//interface
void Log::log(LogVerbosity verbosity, const std::string& message) const 
{
    m_pImpl->log(verbosity, message);
};

Log::Log() : m_pImpl(std::make_unique<Impl>()) {}
Log::~Log() = default;

