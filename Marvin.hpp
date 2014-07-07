//
// Marvin.hpp for marvin in /home/zellou_i/LibBomberman_linux_x64
//
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
//
// Started on  Wed Jun  4 22:10:55 2014 ilyas zelloufi
// Last update Sun Jun 15 14:58:45 2014 Jean Luc TANG
//

#ifndef		MARVIN_HPP_
# define	MARVIN_HPP_

# include	<Model.hh>
# include	"Map.hpp"

enum	eDirection
  {
    UP = 1,
    RIGHT = 2,
    LEFT = 3,
    DOWN = 4,
  };

class Marvin : public AObject
{
private:
  gdl::Texture		_texture;
  gdl::Model		_model;
  float			_speed;
  double		_x;
  double		_z;
  eDirection		_dir;
  int			_player;
public:
  Marvin(std::vector<std::vector<AObject*> > const &map, std::vector<AObject*> const &personnage, int const player)
  {
    if (!this->find_place(map, personnage))
      {
	std::cout << "cannot find a place for the player" << std::endl;
	return ;
      }
    scale(glm::vec3(0.0025, 0.0025, 0.0025));
    translate(glm::vec3(_x + 0.5, 0, _z + 0.5));
    _speed = 5.0;
    _player = player;
    _dir = DOWN;
  }

  bool check_place(std::vector<AObject *> const &perso, int const x, int const z)
  {
    for (size_t i = 0; i < perso.size(); ++i)
      {
	if (perso[i] && perso[i]->getX() == x && perso[i]->getZ() == z)
	  return (false);
      }
    return (true);
  }

  bool	find_place(std::vector<std::vector<AObject*> > const &map, std::vector<AObject*> const &personnage)
  {
    unsigned int	z;
    unsigned int	x;

    for (z = 0; z < map.size(); ++z)
      {
	for (x = 0; x < map[z].size(); ++x)
	  {
	    int		count_freecase = 0;

	    if (x > 0 && !map[z][x - 1] && check_place(personnage, x - 1, z))
	      count_freecase += 1;
	    if (x < map[z].size() && !map[z][x + 1] && check_place(personnage, x + 1, z))
	      count_freecase += 1;
	    if (z > 0 && !map[z - 1][x] && check_place(personnage, x, z - 1))
	      count_freecase += 1;
	    if (z < map.size() && !map[z + 1][x] && check_place(personnage, x, z + 1))
	      count_freecase += 1;
	    if (count_freecase >= 2 && !map[z][x] && check_place(personnage, x, z))
	      {
		_x = x;
		_z = z;
		return (true);
	      }
	  }
      }
    return (false);
  }

  virtual	~Marvin() {}
  double	getX() {return (this->_x);}
  double	getZ() {return (this->_z);}
  void		setX(double const &x) {this->_x = x;}
  void		setZ(double const &z) {this->_z = z;}
  bool		initialize()
  {
    if (_model.load("./assets/marvin.fbx") == false)
      {
	std::cout << "Cannot load the marvin model" << std::endl;
	return (false);
      }
    _model.setCurrentAnim(0);
    return (true);
  }

  int		getAngle(eDirection const current_dir, eDirection const next_dir)
  {
    switch (current_dir)
      {
      case UP:
	{
	  if (next_dir == RIGHT)
	    return (-90);
	  else if (next_dir == DOWN)
	    return (180);
	  else if (next_dir == LEFT)
	    return (90);
	}
      case RIGHT:
	{
	  if (next_dir == UP)
	    return (90);
	  else if (next_dir == DOWN)
	    return (-90);
	  else if (next_dir == LEFT)
	    return (180);
	}
      case DOWN:
	{
	  if (next_dir == UP)
	    return (180);
	  else if (next_dir == RIGHT)
	    return (90);
	  else if (next_dir == LEFT)
	    return (-90);
	}
      case LEFT:
	{
	  if (next_dir == UP)
	    return (-90);
	  else if (next_dir == DOWN)
	    return (90);
	  else if (next_dir == RIGHT)
	    return (180);
	}
      }
    return (0);
  }

  virtual bool          update(gdl::Clock const &clock, gdl::Input &input)
  {
    int		up;
    int		down;
    int		right;
    int		left;

    up = (_player == 1) ? SDLK_KP_5 : SDLK_z;
    down = (_player == 1) ? SDLK_KP_2 : SDLK_s;
    right = (_player == 1) ? SDLK_KP_3 : SDLK_d;
    left = (_player == 1) ? SDLK_KP_1 : SDLK_q;
    if (input.getKey(up))
      {
	if (_dir != UP)
	  {
	    rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, UP));
	    _dir = UP;
	  }
	this->setZ(this->_z - (static_cast<float>(clock.getElapsed()) * _speed));
	translate(glm::vec3(0, 0, -1) * static_cast<float>(clock.getElapsed()) * _speed);
      }
    if (input.getKey(down))
      {
	if (_dir != DOWN)
	  {
	    rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, DOWN));
	    _dir = DOWN;
	  }
	this->setZ(this->_z + (static_cast<float>(clock.getElapsed()) * _speed));
	translate(glm::vec3(0, 0, 1) * static_cast<float>(clock.getElapsed()) * _speed);
      }
    if (input.getKey(left))
      {
	if (_dir != LEFT)
	  {
	    rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, LEFT));
	    _dir = LEFT;
	  }
	this->setX(this->_x - (static_cast<float>(clock.getElapsed()) * _speed));
	translate(glm::vec3(-1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
      }
    if (input.getKey(right))
      {
	if (_dir != RIGHT)
	  {
	    rotate(glm::vec3(0, 1, 0), this->getAngle(_dir, RIGHT));
	    _dir = RIGHT;
	  }
	this->setX(this->_x + (static_cast<float>(clock.getElapsed()) * _speed));
	translate(glm::vec3(1, 0, 0) * static_cast<float>(clock.getElapsed()) * _speed);
      }
    return (true);
  }
  
  void          draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    _model.draw(shader, getTransformation(), clock.getElapsed());
  }

  int	getPlayer() const
  {
    return (this->_player);
  }
};

#endif		/* MARVIN_HPP_ */
