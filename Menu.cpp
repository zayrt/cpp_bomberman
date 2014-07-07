//
// Menu.cpp for bomberman in /home/tang_j/tmp
// 
// Made by Jean Luc TANG
// Login   <tang_j@epitech.net>
// 
// Started on  Fri Jun 13 19:42:07 2014 Jean Luc TANG
// Last update Sat Jun 14 23:44:06 2014 Jean Luc TANG
//

#include "Menu.hpp"

Menu::Menu(gdl::BasicShader const &shader, gdl::Clock const &clock, gdl::Input const &input, gdl::SdlContext const &context)
{
  this->_shader = shader;
  this->_clock = clock;
  this->_input = input;
  this->_context = context;
  this->_map = "";
  this->_mode = 0;
}

Menu::~Menu()
{
  for (size_t i = 0; i < _menu.size(); ++i)
    delete (_menu[i]);
}

bool	Menu::initialize()
{
  glm::mat4 projection;
  glm::mat4 transformation;

  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(10, 20, 25), glm::vec3(10, 20, 0), glm::vec3(0, 1, 0));

  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);
  AObject *arrow = new Icon(10.75, 18.75, "./assets/arrow.tga", 1);
  if (arrow->initialize() == false)
    return (false);
  _menu.push_back(arrow);
  AObject *exit = new Icon(11.75, 18, "./assets/exit.tga", 1);
  if (exit->initialize() == false)
    return (false);
  _menu.push_back(exit);
  AObject *start = new Icon(11.75, 18.75, "./assets/start.tga", 1);
  if (start->initialize() == false)
    return (false);
  _menu.push_back(start);
  AObject *map2 = new Icon(11.75, 18, "./assets/map2.tga", 2);
  if (map2->initialize() == false)
    return (false);
  _menu.push_back(map2);
  AObject *map1 = new Icon(11.75, 18.75, "./assets/map1.tga", 2);
  if (map1->initialize() == false)
    return (false);
  _menu.push_back(map1);
  AObject *ia = new Icon(11.75, 18, "./assets/ia.tga", 3);
  if (ia->initialize() == false)
    return (false);
  _menu.push_back(ia);
  AObject *player = new Icon(11.75, 18.75, "./assets/player.tga", 3);
  if (player->initialize() == false)
    return (false);
  _menu.push_back(player);
  return (true);
}

bool	Menu::update()
{
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;
    
  _context.updateClock(_clock);
  _context.updateInputs(_input);

  _menu[0]->update(_clock, _input);
  if (_menu[0]->getStep() == 0)
    {
      _map = _menu[0]->getMap();
      _mode = _menu[0]->getMode();
      return (false);
    }
  return (true);
}

void	Menu::draw()
{
  int	step;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  _shader.bind();

  step = _menu[0]->getStep();
  for (size_t i = 0; i < _menu.size(); ++i)
    {
      if (_menu[i]->getStep() == step)
	_menu[i]->draw(_shader, _clock);
    }
  _context.flush();
}

std::string	Menu::getMap() const
{
  return (this->_map);
}

int	Menu::getMode() const
{
  return (this->_mode);
}
