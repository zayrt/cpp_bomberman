//
// Core.cpp for Core in /home/zellou_i/rendu/cpp_bomberman
// 
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
// 
// Started on  Mon Jul  7 12:39:16 2014 ilyas zelloufi
// Last update Mon Jul  7 12:39:18 2014 ilyas zelloufi
//

#include "Core.hpp"

Core::Core()
{
  _speed = 5.0f;
}

Core::~Core()
{
  while (_personnage.size() > 0)
    _personnage.erase(_personnage.begin());
  while (_bomb.size() > 0)
    _bomb.erase(_bomb.begin());
  for (size_t i = 0; i < _map.size(); ++i)
    {
      while (_map[i].size() > 0)
        _map[i].erase(_map[i].begin());
    }
  while (_map.size() > 0)
    _map.erase(_map.begin());
}

void	Core::cleanVector()
{
  while (_personnage.size() > 0)
    _personnage.erase(_personnage.begin());
  while (_bomb.size() > 0)
    _bomb.erase(_bomb.begin());
  for (size_t i = 0; i < _map.size(); ++i)
    {
      while (_map[i].size() > 0)
	_map[i].erase(_map[i].begin());
    }
  while (_map.size() > 0)
    _map.erase(_map.begin());
}

bool	Core::begin()
{
  Menu	*menu = new Menu(_shader, _clock, _input, _context);
  if (menu->initialize() == false)
    return (false);
  while (menu->update() == true)
    menu->draw();
  std::string	map = menu->getMap();
  int		mode = menu->getMode();
  if (map == "" || mode == 0)
    {
      delete (menu);
      return (false);
    }
  delete (menu);

  CoreMap	m(map);
  if (!m.loadmap())
    return (false);
  _zmax = m.getZ();
  _xmax = m.getX();
  _surface = new Map(_xmax, _zmax);
  if (_surface->initialize() == false)
    return (false);
  _map = m.getMap();

  AObject *p = new Marvin(_map, _personnage, 1);
  if (p->initialize() == false)
    return (false);
  _personnage.push_back(p);

  AObject *p2 = new Marvin(_map,  _personnage, 2);
  if (p2->initialize() == false)
    return (false);
  _personnage.push_back(p2);

  glm::mat4 projection;
  glm::mat4 transformation;
  double	x = p->getX();
  double	z = p->getZ();

  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(x, 10, z + 8), glm::vec3(x, 0, z), glm::vec3(0, 1, 0));

  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);
  return (true);
}

bool	Core::initialize()
{
  if (!_context.start(800, 600, "Bomberman!"))
    return false;
  glEnable(GL_DEPTH_TEST);
  if (!_shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER) || !_shader.load("./shaders/basic.vp", GL_VERTEX_SHADER) || !_shader.build())
    return (false);
  if (this->begin() == false)
    return (false);
  return (true);
}

bool	Core::collision(AObject *perso, int const dir, int const dir2) const
{
  double	x;
  double	z;
  double	xp;
  double	zp;
  double	elapse;

  xp = perso->getX();
  zp = perso->getZ();
  for (size_t j = 0; j < _map.size(); ++j)
    {
      for (size_t i = 0; i < _map[j].size(); ++i)
	{
	  elapse = static_cast<float>(_clock.getElapsed()) * _speed;
	  if (_map[j][i])
	    {
	      x = i;
	      z = j;
	      if (dir != 0)
		{
		  elapse = elapse * dir;
		  if (xp + 0.20 >= x && xp + 0.20 <= x + 1)
		    {
		      if ((zp + elapse + 0.20 > z && zp + elapse + 0.20 < z + 1)
			  || (zp + 0.80 + elapse > z && zp + elapse + 0.80 < z + 1))
			return (false);
		    }
		  else if (xp + 0.80 >= x && xp + 0.80 <= x + 1)
		    {
		      if ((zp + elapse + 0.20 > z && zp + 0.20 + elapse < z + 1)
			  || (zp + 0.80 + elapse > z && zp + elapse + 0.80 < z + 1))
			return (false);
		    }
		}
	      else if (dir2 != 0)
		{
		  elapse = elapse * dir2;
		  if (zp + 0.20 >= z && zp + 0.20 <= z + 1)
		    {
		      if ((xp + elapse + 0.20 > x && xp + elapse + 0.20 < x + 1)
			  || (xp + 0.80 + elapse > x && xp + elapse + 0.80 < x + 1))
			return (false);
		    }
		  if (zp + 0.80 >= z && zp + 0.80 <= z + 1)
		    {
		      if ((xp + elapse  + 0.20 > x && xp + elapse + 0.20 < x + 1) ||
			  (xp + 0.80 + elapse > x && xp + elapse + 0.80 < x + 1))
			return (false);
		    }
		}
	    }
	}
    }
  return (true);
}

bool	Core::putBomb()
{
  for(size_t i = 0; i < _personnage.size(); ++i)
    {
      int x = _personnage[i]->getX() + 0.5;
      int z = _personnage[i]->getZ() + 0.5;
      if ((_input.getKey(SDLK_KP_0) && _personnage[i]->getPlayer() == 1) ||
	  (_input.getKey(SDLK_SPACE) && _personnage[i]->getPlayer() == 2))
	{
	  AObject *b = new Bomb(x, z);
	  if (b->initialize() == false)
	    return (false);
	  _bomb.push_back(b);
	}
    }
  return (true);
}

void	Core::explosion()
{
  for (size_t i = 0; i < _bomb.size(); ++i)
    {
      if (!_bomb[i]->update(_clock, _input))
	{
	  int		zb = _bomb[i]->getz();
	  int		xb = _bomb[i]->getx();

	  if (zb < _zmax && _map[zb + 1][xb] && _map[zb + 1][xb]->getType() == BOX)
	    _map[zb + 1][xb] = NULL;
	  if (zb > 0 && _map[zb - 1][xb] && _map[zb - 1][xb]->getType() == BOX)
	    _map[zb - 1][xb] = NULL;
	  if (xb < _xmax && _map[zb][xb + 1] && _map[zb][xb + 1]->getType() == BOX)
	    _map[zb][xb + 1] = NULL;
	  if (xb > 0 && _map[zb][xb - 1] && _map[zb][xb - 1]->getType() == BOX)
	    _map[zb][xb - 1] = NULL;

	  for (size_t j = 0; j < _personnage.size(); ++j)
	    {
	      double	zp = _personnage[j]->getZ();
	      double	xp = _personnage[j]->getX();
	      bool	delet = false;

	      if (xp + 0.21 >= xb - 1 && xp + 0.21 <= xb + 2)
		{
		  if ((zp + 0.21 >= zb && zp + 0.21 <= zb + 1) || (zp + 0.79 >= zb && zp + 0.79 <= zb + 1))
		    {
		      _personnage.erase(_personnage.begin() + j);
		      delet = true;
		    }
		}
	      else if (xp + 0.79 >= xb - 1 && xp + 0.79 <= xb + 2)
		{
		  if ((zp + 0.21 >= zb && zp + 0.21 <= zb + 1) || (zp + 0.79 >= zb && zp + 0.79 <= zb + 1))
		    {
		      _personnage.erase(_personnage.begin() + j);
		      delet = true;
		    }
		}
	      if (delet == false)
		{
		  if (zp + 0.21 >= zb - 1 && zp + 0.21 <= zb + 2)
		    {
		      if ((xp + 0.21 >= xb && xp + 0.21 <= xb + 1) || (xp + 0.79  >= xb && xp  + 1 <= xb + 1))
			_personnage.erase(_personnage.begin() + j);
		    }
		  else if (zp + 0.79 >= zb - 1 && zp + 0.79 <= zb + 2)
		    {
		      if ((xp + 0.21 >= xb && xp + 0.21 <= xb + 1) || (xp + 0.79  >= xb && xp  + 1 <= xb + 1))
			_personnage.erase(_personnage.begin() + j);
		    }
		}
	    }
	  if (_bomb[i]->getTime() > 1.0f)
	    _bomb.erase(_bomb.begin() + i);
	}
    }
}

bool	Core::end(std::string const &path)
{
  glm::mat4 projection;
  glm::mat4 transformation;

  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(10, 20, 25), glm::vec3(10, 20, 0), glm::vec3(0, 1, 0));

  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);

  AObject *end = new Icon(9.5, 20, path, 1);
  if (end->initialize() == false)
    return (false);

  float	timeout = 0.0f;
  while (timeout <= 3.0f)
    {
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      _shader.bind();
      _context.updateClock(_clock);
      timeout +=  static_cast<float>(_clock.getElapsed());
      end->draw(_shader, _clock);
      _context.flush();
    }
  return (true);
}

bool	Core::update()
{
  if (_personnage.size() <= 1)
    {
      if (_personnage[0]->getPlayer() == 1)
	this->end("./assets/p1win.tga");
      else
	this->end("./assets/p2win.tga");
      return (false);
      /*      this->cleanVector();
      if (this->begin() == false)
      return (false);*/
    }
  if (_input.getKey(SDLK_ESCAPE) || _input.getInput(SDL_QUIT))
    return false;

  _context.updateClock(_clock);
  _context.updateInputs(_input);

  int	dir = 0;
  int	dir2 = 0;
  int	dir3 = 0;
  int	dir4 = 0;

  if (_input.getKey(SDLK_KP_5))
    dir = -1;
  if (_input.getKey(SDLK_KP_2))
    dir = 1;
  if (_input.getKey(SDLK_KP_1))
    dir2 = -1;
  if (_input.getKey(SDLK_KP_3))
    dir2 = 1;
  if (_input.getKey(SDLK_z))
    dir3 = -1;
  if (_input.getKey(SDLK_s))
    dir3 = 1;
  if (_input.getKey(SDLK_q))
    dir4 = -1;
  if (_input.getKey(SDLK_d))
    dir4 = 1;

  if (this->putBomb() == false)
    return (false);
  if (this->collision(_personnage[0], dir, dir2) == true && (dir != 0 || dir2 != 0))
    _personnage[0]->update(_clock, _input);
  if (this->collision(_personnage[1], dir3, dir4) == true && (dir3 != 0 || dir4 != 0))
    _personnage[1]->update(_clock, _input);
  this->explosion();
  glm::mat4 projection;
  glm::mat4 transformation;
  double	x = _personnage[0]->getX();
  double	z = _personnage[0]->getZ();

  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
  transformation = glm::lookAt(glm::vec3(x, 10, z + 8), glm::vec3(x, 0, z), glm::vec3(0, 1, 0));

  _shader.bind();
  _shader.setUniform("view", transformation);
  _shader.setUniform("projection", projection);
  return (true);
}

void	Core::draw()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _shader.bind();
  _surface->draw(_shader, _clock);
  for (size_t i = 0; i < _map.size(); ++i)
    {
      for (size_t j = 0; j < _map[i].size(); ++j)
	if (_map[i][j])
	  _map[i][j]->draw(_shader, _clock);
    }
  for (size_t i = 0; i < _personnage.size(); ++i)
    _personnage[i]->draw(_shader, _clock);
  for (size_t i = 0; i < _bomb.size(); ++i)
    _bomb[i]->draw(_shader, _clock);
  _context.flush();
}
