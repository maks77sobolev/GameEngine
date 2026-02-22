#include "Engine.h"
#include "Log/log.h"
#include <format>
using namespace LifeExe;
DEFINE_LOG_CATEGORY_STATIC(LogEngine);
DEFINE_LOG_CATEGORY_STATIC(Bullshit);
Engine::Engine()
{
    
  //  std::cout << "Initializing Life Exe Engine, version: " << version() << std::endl;
    Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Display,        
       std::format("Initializing Life Exe Engine, version: {}",version()),true);
  Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Warning, "some Warning example",true);
    Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Error, "some Error example",true);
  Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Log, "you should not see this",true);
 // Log::GetInstance().log(LogEngine, LifeExe::LogVerbosity::Fatal, "Here comes debug break");
  LE_LOG(Bullshit, Warning, "some nasty message");
  
    
}
