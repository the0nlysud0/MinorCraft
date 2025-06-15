#pragma once
#include <GLFW/glfw3.h>
#include "mb_logger.h"
#include <glm/glm.hpp>

class Window
{
private:
  int m_Width;
  int m_Height;
  std::string m_Title;
  GLFWwindow* m_Window=nullptr;
  glm::mat4 m_ProjectionMatrix;
  float m_FOV=90.0f;
  mb_logger& m_Console;
public:
  Window(int width, int height, std::string title , mb_logger& console);
  bool is_running() {return !glfwWindowShouldClose(m_Window);}
  glm::mat4 getProjection() const {return m_ProjectionMatrix;}
  void update();
  ~Window();
};