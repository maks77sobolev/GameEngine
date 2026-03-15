#include "Core/Engine.h"
#include "stdlib.h"
#include "Window/GLFW/GLFWWindowManager.h"
using namespace LifeExe;
int main()
{
    auto windowManager = std::make_unique<GLFWWindowManager>();
    Engine engine(std::move(windowManager));
    engine.run();
    return EXIT_SUCCESS;
}