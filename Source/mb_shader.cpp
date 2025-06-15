#include "mb_shader.h"
#include "mb_fileIO.h"
#include <glm/gtc/type_ptr.hpp>

mb_shader::mb_shader(mb_logger& p_Console):m_Console(p_Console)
{
  m_Console.log(LogType::INFO,"initialized shader program");
  m_ShaderID = glCreateProgram();
}

bool mb_shader::create_shader(std::string path, GLenum type)
{
  std::string s_type;
  switch (type)
  {
  case GL_VERTEX_SHADER:
    s_type = "vertex";
    break;
  case GL_FRAGMENT_SHADER:
    s_type = "fragment";
    break;
  case GL_GEOMETRY_SHADER:
    s_type = "geometry";
    break;
  default:
    break;
  }
  std::string ShaderSource = ReadFile(path);
  const char* Source = ShaderSource.c_str();
  unsigned int shader = glCreateShader(type);
  glShaderSource(shader , 1, &Source, nullptr);
  glCompileShader(shader);
  int success;
  char infoLog[512];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(shader, 512, nullptr, infoLog);
    m_Console.log(LogType::ERROR,"failed to compile ",s_type," shader\n" ,infoLog);
    return false;
  }
  glAttachShader(m_ShaderID,shader);
  glDeleteShader(shader);
  
  m_Console.log(LogType::INFO,"compiled and attched "+s_type+" shader");
  return true;
}

bool mb_shader::link_program()
{
  int success;
  char infoLog[512];
  glLinkProgram(m_ShaderID);
  glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(m_ShaderID, 512, nullptr, infoLog);
    return false;
  }
  m_Console.log(LogType::INFO,"linked shader program");
  return true;
}

void mb_shader::set_int(std::string uniformName, int uniform)
{
  use();
  unsigned int location = glGetUniformLocation(m_ShaderID,uniformName.c_str());
  glUniform1i(location , uniform);
}

mb_shader::~mb_shader()
{
}

void mb_shader::use() const
{
  glUseProgram(m_ShaderID);
}
