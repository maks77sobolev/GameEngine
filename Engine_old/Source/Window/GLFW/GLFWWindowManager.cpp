#include "GLFWWindowManager.h"
#include "Log/log.h"
#include "GLFW/glfw3.h"
using namespace LifeExe;
DEFINE_LOG_CATEGORY_STATIC(LogGLFWWindowManager);

GLFWWindowManager::GLFWWindowManager() 
 {
    glfwSetErrorCallback([](int errorCode, const char* description)
        {
        LE_LOG(LogGLFWWindowManager, Error, "GLFW error code {}: description:{}",errorCode,description);
        }
    );
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
    {
        LE_LOG(LogGLFWWindowManager, Error, "GLFW intialization failed");
    };       
    m_initialized = true;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        LE_LOG(LogGLFWWindowManager, Display, "GLFW intialization succeded");
    if (!window)
    {
        glfwTerminate();
        LE_LOG(LogGLFWWindowManager, Error, "GLFW Window creation failed");
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

  
 }

 GLFWWindowManager::~GLFWWindowManager() {
     if (m_initialized)
     {
         glfwTerminate();
         m_initialized = false;
         LE_LOG(LogGLFWWindowManager, Display, "GLFW Window successfully termintated");
     }; 
 }
