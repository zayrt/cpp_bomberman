//
// Map.hpp for bomberman in /home/tang_j/bomberman
//
// Made by Jean Luc TANG
// Login   <tang_j@epitech.net>
//
// Started on  Tue Jun  3 21:06:44 2014 Jean Luc TANG
// Last update Sat Jun 14 23:34:08 2014 Jean Luc TANG
//

#ifndef			MAP_HPP_
# define		MAP_HPP_

#include		"Cube.hpp"

class Map : public AObject
{
private:
  gdl::Texture _texture;
  gdl::Geometry _geometry;
  int	_x;
  int	_z;

public:
  Map(int const x, int const  z)
  {
    this->_x = x;
    this->_z = z;
  }
  virtual	~Map() { }
  bool		initialize()
  {
    if (_texture.load("./assets/herbe.tga") == false)
      {
	std::cerr << "Cannot load the map texture" << std::endl;
	return (false);
      }

    _geometry.pushVertex(glm::vec3(_x, 0, 0));
    _geometry.pushVertex(glm::vec3(_x, 0, _z));
    _geometry.pushVertex(glm::vec3(0, 0, _z));
    _geometry.pushVertex(glm::vec3(0, 0, 0));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));

    _geometry.build();
    return (true);
  }

  void draw(gdl::AShader &shader, gdl::Clock const &clock)
  {

    (void)clock;

    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};

#endif		/* MAP_HPP_ */
