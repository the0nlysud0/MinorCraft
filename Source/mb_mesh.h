#pragma once 
#include "mb_texture.h"
#include "mb_shader.h"

class mb_block
{
private:
  unsigned int m_VAO,m_VBO,m_InstanceVBO;
public:
  mb_block();
  ~mb_block();
};