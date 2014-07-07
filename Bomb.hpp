//
// Bomb.hpp for Bomb in /home/zellou_i/LibBomberman_linux_x64
//
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
//
// Started on  Tue Jun 10 14:53:42 2014 ilyas zelloufi
// Last update Mon Jul  7 12:38:39 2014 ilyas zelloufi
//

#ifndef		BOMB_HPP_
# define	BOMB_HPP_

#include	<Model.hh>
#include	"Cube.hpp"
#include	"CoreMap.hpp"

class Bomb : public AObject
{
private:
  gdl::Texture		_texture;
  gdl::Model		_model;
  gdl::Geometry		_geometry;
  float			_timeout;
  int			_x;
  int			_z;
  bool			_explose;
  AObject		*_fire;
  AObject		*_fire2;
  AObject		*_fire3;
  AObject		*_fire4;
  AObject		*_fire5;

public:
  Bomb(int const x, int const z)
  {
    _timeout = 0.0f;
    scale(glm::vec3(5, 5, 5));
    translate(glm::vec3(x + 0.5, 0, z + 0.5));
    _x = x;
    _z = z;
    _explose = false;
  }

  virtual ~Bomb() {}

  bool		initialize()
  {
    if (!_model.load("./assets/bomb.fbx"))
      {
	std::cout << "Cannot load the bomb model" << std::endl;
	return (false);
      }
    return (true);
  }

  bool          update(gdl::Clock const &clock, gdl::Input &input)
  {
    (void)input;

    _timeout +=  static_cast<float>(clock.getElapsed());
    if (_explose)
      return (false);
    if (_timeout > 3.0f && !_explose)
      {
	_fire =  new Cube(_x, _z, "./assets/lava.tga", FIRE);
	if (!_fire->initialize())
	  return (false);
	_fire2 =  new Cube(_x + 1, _z, "./assets/lava.tga", FIRE);
	if (!_fire2->initialize())
	  return (false);
	_fire3 =  new Cube(_x - 1, _z, "./assets/lava.tga", FIRE);
	if (!_fire3->initialize())
	  return (false);
	_fire4 =  new Cube(_x, _z - 1, "./assets/lava.tga", FIRE);
	if (!_fire4->initialize())
	  return (false);
	_fire5 =  new Cube(_x, _z + 1, "./assets/lava.tga", FIRE);
	if (!_fire5->initialize())
	  return (false);
	_explose = true;
	_timeout = 0;
      }
    return (true);
  }

  void          draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    if (_explose)
      {
	_fire->draw(shader, clock);
	_fire2->draw(shader, clock);
	_fire3->draw(shader, clock);
	_fire4->draw(shader, clock);
	_fire5->draw(shader, clock);
      }
    else
      _model.draw(shader, getTransformation(), clock.getElapsed());
  }

  int        getx() const {return (this->_x);}
  int        getz() const {return (this->_z);}
  float	     getTime() const {return (this->_timeout);}
};

#endif
