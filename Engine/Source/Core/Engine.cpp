#include "Engine.h"
#include "Log/log.h"
#include <format>

using namespace LifeExe;

Engine::Engine()
{
  //  std::cout << "Initializing Life Exe Engine, version: " << version() << std::endl;
    Log::GetInstance().log(LifeExe::LogVerbosity::Display,        
       std::format("Initializing Life Exe Engine, version: {}",version()));
  Log::GetInstance().log(LifeExe::LogVerbosity::Warning, "some Warning example");
  Log::GetInstance().log(LifeExe::LogVerbosity::Error, "some Error example");
  Log::GetInstance().log(LifeExe::LogVerbosity::NoLogging, "you should not see this");
    
    
}
