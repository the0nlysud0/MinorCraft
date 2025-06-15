#include "mb_texture.h"
#include <memory>
#include <cstring>
#include <algorithm>
#include "stb_image_write.h"

TextureMGR::TextureMGR(mb_shader &shader,mb_logger &Console):m_Console(Console),m_Shader(shader)
{}

void TextureMGR::attatch_texture(std::string texture_name)
{
  TextureData tex;
  tex.TextureID++;
  std::string file_path = "assets/Textures/"+texture_name;
  tex.data = stbi_load(file_path.c_str(),&tex.width,&tex.height,&tex.nrchannels,STBI_rgb_alpha);
  if(!tex.data) m_Console.log(LogType::ERROR,"failed to load texture ", texture_name);
  else m_Console.log(LogType::INFO,"loaded texture ", texture_name);
  m_Textures2D.push_back(tex);

}

void TextureMGR::make_atlas()
{
  if(m_Textures2D.empty())
  {
    m_Console.log(LogType::WARNING, "no textures will be loaded to the atlas");
    return;
  }
  int tile_size = m_Textures2D[0].width;

  for (auto& tex : m_Textures2D) {
  // if (tex.width != tile_size && tex.height != tile_size) {
    // m_Console.log(LogType::ERROR, "Texture size mismatch. All textures must be the same size.");
    // return;
    // }
  }
  int tile_width = m_Textures2D[0].width;
  int tile_height = m_Textures2D[0].height;
  int atlas_width = 0;
  for(auto tex:m_Textures2D)
  {
    atlas_width+= tex.width;
  }
  int atlas_height = tile_height; // assume same height for now 
  for(auto s:m_Textures2D) atlas_height = std::max(atlas_height,s.height);
  int atlas_channels = 4;

  unsigned char* atlas_data = new unsigned char[atlas_width * atlas_height * atlas_channels];
  std::memset(atlas_data, 0, atlas_width * atlas_height * atlas_channels);
  for (size_t i = 0; i < m_Textures2D.size(); ++i)
  {
  TextureData& tex = m_Textures2D[i];
  int x_offset = i * tile_size; // horizontal shift per texture

  for (int row = 0; row < tex.height; ++row)
  {
    unsigned char* src = tex.data + row * tex.width * atlas_channels;
    unsigned char* dst = atlas_data + (row * atlas_width + x_offset) * atlas_channels;

    std::memcpy(dst, src, tex.width * atlas_channels);
  }

  float minU = (float)(x_offset) / atlas_width;
  float maxU = (float)(x_offset + tile_size) / atlas_width;
  m_RowsUV.emplace_back(minU, 0.0f, maxU, 1.0f);
  stbi_image_free(tex.data);
}


  glGenTextures(1,&m_AtlasID);
  glBindTexture(GL_TEXTURE_2D,m_AtlasID);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, atlas_width, atlas_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, atlas_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_write_png("debug_atlas.png", atlas_width, atlas_height, 4, atlas_data, atlas_width * 4);
  delete [] atlas_data;
  m_Console.log(LogType::INFO,"created texture atlas :",atlas_width," , ",atlas_height);
}

glm::vec4 TextureMGR::getUV(int index)
{
  return m_RowsUV[index];
}

TextureMGR::~TextureMGR()
{
}

void TextureMGR::use(unsigned int index)
{
  glActiveTexture(GL_TEXTURE0+index);
  glBindTexture(GL_TEXTURE_2D,m_AtlasID);
  m_Shader.use();
  m_Shader.set_int("u_Texture",index);
}
