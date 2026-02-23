#include "Engine.h"
#include "Log/log.h"
#include <format>
#include "Window/GLFW/GLFWWindowManager.h"
#include <memory>
using namespace LifeExe;
DEFINE_LOG_CATEGORY_STATIC(LogEngine);

Engine::Engine()
{
    
  m_windowManager = std::make_unique<GLFWWindowManager>();
    
}

Engine::~Engine() = default;
