#include "Engine.h"
#include "Log/log.h"
#include <format>
using namespace LifeExe;
DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine()
{
  //  std::cout << "Initializing Life Exe Engine, version: " << version() << std::endl;
    Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Display,        
       std::format("Initializing Life Exe Engine, version: {}",version()));
  Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Warning, "some Warning example");
    Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Error, "some Error example");
  Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::NoLogging, "you should not see this");
 // Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Fatal, "Here comes debug break");
    
    
}
