#pragma once
#include <string>
#include <functional>
#include "Window/IWindow.h"
#include "Core/Utility.h"
#include  <Event/event.h>
#include  <Event/inputevent.h>
class GLFWwindow;

namespace LifeExe
{

class GLFWWindow final : public IWindow, public NonCopyable
{
public:
    GLFWWindow(WindowId id,const WindowSettings& settings);
    ~GLFWWindow() override;

    void setTitle(const std::string& title) override;
    bool isValid() const override;
    bool shouldClose() const override;

private:
    GLFWwindow* m_window{nullptr};
   const  WindowId m_id;
    Event<const InputEvent&> m_windowEvent;
};

}  // namespace LifeExe