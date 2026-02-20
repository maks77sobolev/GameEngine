#include "log.h"
#include <memory>
#include <string>
#include <filesystem>
#include <chrono>
#include <unordered_map>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
using namespace LifeExe;
namespace fs = std::filesystem;
namespace
{
const std::unordered_map<LogVerbosity, spdlog::level::level_enum> c_verbocityMap
{
    {LogVerbosity::NoLogging, spdlog::level::off},
    {LogVerbosity::Display, spdlog::level::info},
    {LogVerbosity::Log, spdlog::level::info},
    {LogVerbosity::Warning, spdlog::level::warn},
    {LogVerbosity::Error, spdlog::level::err},
    {LogVerbosity::Fatal  , spdlog::level::critical}
};
constexpr const char* c_logPattern = "[%H:%M:%S.%e] [%^%l%$] %v";
constexpr const char* c_timeStampFormat = "{:%Y.%d.%m-%H.%M.%S}";
const fs::path c_directory = fs::path("logs") / "subfolder";
constexpr const char* c_LogFilePrefix = "Life-Exe";
constexpr const char* c_LogFileExtension = "txt";
};  // namespace
//pImpl
class Log::Impl
{
public:
    Impl()
    {
        using namespace spdlog;
        const auto consoleSink = std::make_shared<sinks::stdout_color_sink_mt>();
        m_consoleLogger = std::make_unique<logger>("console", consoleSink);
        m_consoleLogger->set_pattern(c_logPattern);

        const auto fileSink =
            std::make_shared<sinks::basic_file_sink_mt>(makeLogFile().string(), true);  // true - to overwrite file content
        m_fileLogger = std::make_unique<spdlog::logger>("file", fileSink);
        m_fileLogger->set_pattern(c_logPattern);
    };
    void log(LogVerbosity verbosity, const std::string& message) const
    {
        if (verbosity == LogVerbosity::NoLogging) return;

        const auto spdLevelIt = c_verbocityMap.find(verbosity);  // searching through map

        if (spdLevelIt == c_verbocityMap.end()) return;  // if "find" found some key-value pair
        const auto spdLevel = spdLevelIt->second;
        if (verbosity != LogVerbosity::Log) m_consoleLogger->log(spdLevel, message);
        m_fileLogger->log(spdLevel, message);

        if (verbosity == LogVerbosity::Fatal)
        {
            PLATFORM_BREAK();
        }
    }

private:
    std::unique_ptr<spdlog::logger> m_consoleLogger;
    std::unique_ptr<spdlog::logger> m_fileLogger;
    fs::path makeLogFile() const
    {
        fs::create_directory(c_directory);
        
        const auto now = std::chrono::system_clock::now();
        const auto now_seconds = std::chrono::floor<std::chrono::seconds>(now);

        const std::string timestamp = std::format(c_timeStampFormat, now_seconds);
        const std::string LongName = std::format("{}-{}.{}", c_LogFilePrefix,timestamp,c_LogFileExtension);
        
        return c_directory/LongName;
    };
};
    // interface
    void Log::log(const LogCategory& category, LogVerbosity verbosity, const std::string& message) const
    {
        m_pImpl->log(verbosity, std::format("[{}] {}", category.name(), message));
    };

    Log::Log() : m_pImpl(std::make_unique<Impl>()) {}
    Log::~Log() = default;

