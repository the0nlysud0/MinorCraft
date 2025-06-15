#pragma once
#include "mb_shader.h"
#include "mb_texture.h"
#include "mb_window.h"
#include <memory>

class Game
{
private:
  std::shared_ptr<Window> m_GameWindow;
  std::shared_ptr<mb_shader> m_Basic;
  std::shared_ptr<TextureMGR> m_TextureMGR;
  mb_logger Console;


  unsigned int VAO , VBO;


public:
  Game();
  void run();
  ~Game();
};