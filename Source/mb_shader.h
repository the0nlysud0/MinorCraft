#pragma once
#include <glad/glad.h>
#include <iostream>

#include "mb_logger.h"

class mb_shader
{
private:
  unsigned int m_ShaderID;
  mb_logger& m_Console;
public:
  mb_shader(mb_logger& p_Console);
  bool create_shader(std::string path,GLenum type);
  bool link_program();
  void use() const;
  // uniforms
  void set_int(std::string uniformName, int uniform);
  ~mb_shader();
};