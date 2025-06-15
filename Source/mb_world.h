#pragma once

#include "mb_shader.h"
#include "mb_texture.h"

struct Block
{
  glm::vec3 position;
  int texture;
};


class mb_world
{
private:
  std::vector<Block> m_Blocks;
public:
  mb_world(/* args */);
  void render(mb_shader& shader);
  ~mb_world();
};

mb_world::mb_world(/* args */)
{
}

mb_world::~mb_world()
{
}
