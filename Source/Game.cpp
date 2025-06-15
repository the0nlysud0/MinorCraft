#include "Game.h"

Game::Game()
{
  m_GameWindow = std::make_shared<Window>(800,600,"MinorGame",Console);
  gladLoadGL();
  m_Basic = std::make_shared<mb_shader>(Console);
  m_Basic->use();
  m_Basic->create_shader("assets/Shaders/basic.vs.glsl",GL_VERTEX_SHADER);
  m_Basic->create_shader("assets/Shaders/basic.fs.glsl",GL_FRAGMENT_SHADER);
  m_Basic->link_program();
  m_Basic->use();
  m_TextureMGR = std::make_shared<TextureMGR>(*m_Basic.get(),Console);
  m_TextureMGR->attatch_texture("dirt.png");
  m_TextureMGR->attatch_texture("grass-face1.png");
  m_TextureMGR->make_atlas();
  // Temp testing shaders / textures
  unsigned int textureVBO;
  glGenVertexArrays(1,&VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER,VBO);
  

  glm::vec4 uv = m_TextureMGR->getUV(0);
  float vertices[] = {
      // pos      // tex coords
      -0.5f, -0.5f,  uv.x, uv.y,
      0.5f, -0.5f,  uv.z, uv.y,
      0.5f,  0.5f,  uv.z, uv.w,

      0.5f,  0.5f,  uv.z, uv.w,
      -0.5f,  0.5f,  uv.x, uv.w,
      -0.5f, -0.5f,  uv.x, uv.y
  };

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),&vertices[0],GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0 ,2 , GL_FLOAT, GL_FALSE , 4*sizeof(float),(void*)0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1 ,2 , GL_FLOAT, GL_FALSE , 4*sizeof(float),(void*)(2*sizeof(float)));

  glBindVertexArray(0);
}

void Game::run()
{
  while(m_GameWindow->is_running())
  {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    m_Basic->use();
    m_TextureMGR->use(0);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0,6);


    m_GameWindow->update();
    Console.update();
  }
}

Game::~Game()
{
}
