#include <glad/glad.h>
#include "mb_window.h"
#include <glm/gtc/matrix_transform.hpp>

Window::Window(int width, int height, std::string title , mb_logger& console)
  :m_Width(width),m_Height(height),m_Title(title),m_Console(console)
{
  if(!glfwInit())
  {
    m_Console.log(LogType::ERROR, "failed to init GLFW ...");
    return;
  }
  m_Console.log(LogType::INFO, "initializing GLFW ...");

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT , GLFW_TRUE);
  #endif
  m_Window = glfwCreateWindow(width , height , title.c_str() , NULL, NULL);
  if(!m_Window)
  {
    m_Console.log(LogType::ERROR, "failed to create a window ...");
    return;
  }
  m_Console.log(LogType::INFO, "created a window ... | title: ",m_Title," | width: ",width , " | height: ",height);

  glfwMakeContextCurrent(m_Window);
}
void Window::update()
{
  glfwGetFramebufferSize(m_Window,&m_Width,&m_Height);
  m_Console.log(LogType::INFO, "window | title: ",m_Title," | width: ",m_Width , " | height: ",m_Width);
  m_ProjectionMatrix = glm::perspective(m_FOV,(float)m_Width/m_Height,0.01f,100.0f);
  glViewport(0,0,m_Width,m_Height);

  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

Window::~Window()
{
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}
