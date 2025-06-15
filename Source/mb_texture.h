#pragma once
#include "mb_shader.h"
#include "stb_image.h"
#include "mb_logger.h"
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

struct TextureData
{
  int width, height, nrchannels;
  int TextureID=0;
  unsigned char* data;
};

class TextureMGR
{
private:
  mb_logger& m_Console;
  mb_shader& m_Shader;
  std::vector<TextureData> m_Textures2D;
  std::vector<glm::vec4> m_RowsUV;
  unsigned int m_AtlasID;
public:
  TextureMGR(mb_shader& shader, mb_logger& Console);
  void attatch_texture(std::string texture_name);
  void make_atlas();
  glm::vec4 getUV(int index);
  glm::vec4 getUV(std::string texture_name);
  void use(unsigned int index=0);
  ~TextureMGR();
};