#pragma once
#include "Core/Utility.h"
#include <memory>

namespace LifeExe
{
enum class LogVerbosity : uint8_t
{
    NoLogging = 0,
    Display,
    Warning,
    Error,
    Fatal
};

class Log final : public NonCopyable
{
public:
    static Log& GetInstance() 
    { static Log instance;
        return instance;
    }
    void log(LogVerbosity verbocity,const std::string &message) const;

private:
    Log();
    ~Log();
class Impl;
std::unique_ptr<Impl> m_pImpl;
};
}