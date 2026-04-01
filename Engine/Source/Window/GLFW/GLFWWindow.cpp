#include "GLFWWindow.h"
#include "Log/Log.h"
#include <GLFW/glfw3.h>

using namespace LifeExe;

DEFINE_LOG_CATEGORY_STATIC(LogGLFWWindow);

GLFWWindow::GLFWWindow(WindowId id, const WindowSettings& settings) : m_id(id)
{
    m_window = glfwCreateWindow(settings.width, settings.height, settings.title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        LE_LOG(LogGLFWWindow, Error, "Failed to create GLFW window!");
        return;
    }
   glfwSetWindowUserPointer(m_window, this);  // pass parameter to callback
   
   glfwSetFramebufferSizeCallback(m_window,
        [](GLFWwindow* window, int width, int height)
        {
            GLFWWindow* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            LE_LOG(LogGLFWWindow, Display, "resize:width={},hight={}", width, height);
           InputEvent event;
           event.type = EventType::WindowsResize;
           thisWindow->m_windowEvent.invoke(event);
        }

    );
    glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
           GLFWWindow* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
         //   LE_LOG(LogGLFWWindow, Display, "key pressed :key={},scancode={}", key, scancode); 
        InputEvent event;
           event.type = EventType::KeyPress;
           thisWindow->m_windowEvent.invoke(event);
       });
    glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
        GLFWWindow* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
            InputEvent event;
        event.type = EventType::MouseMove;
            thisWindow->m_windowEvent.invoke(event);
        });
    glfwSetMouseButtonCallback(m_window,
        [](GLFWwindow* window, int button, int action, int mods)
        {
            GLFWWindow* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
         //   LE_LOG(LogGLFWWindow, Display, "mouse button: {} ,action={}", button, action);
            InputEvent event;
            event.type = EventType::MouseButton;
            thisWindow->m_windowEvent.invoke(event);
        });
    glfwSetScrollCallback(m_window,
        [](GLFWwindow* window, double xoffset, double yoffset)
        {
            GLFWWindow* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
         //   LE_LOG(LogGLFWWindow, Display, "mouse scroll: xoffset={},yoffset={}", xoffset, yoffset);
            InputEvent event;
            event.type = EventType::MouseScroll;
            thisWindow->m_windowEvent.invoke(event);
        });
    glfwSetWindowCloseCallback(m_window,
        [](GLFWwindow* window)
        {
            GLFWWindow* thisWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
          //  LE_LOG(LogGLFWWindow, Display, "Window  with id={} has closed !", thisWindow->m_id.value);
            InputEvent event;
            event.type = EventType::WindowsClose;
            thisWindow->m_windowEvent.invoke(event);

        });
    glfwSetWindowPos(m_window, settings.x, settings.y);
}

GLFWWindow::~GLFWWindow()
{
    if (m_window)
    {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

void GLFWWindow::setTitle(const std::string& title)
{
    if (!m_window) return;
    glfwSetWindowTitle(m_window, title.c_str());
}

bool GLFWWindow::isValid() const
{
    return m_window != nullptr;
}

bool GLFWWindow::shouldClose() const
{
    if (!m_window) return true;
    return glfwWindowShouldClose(m_window);
}
