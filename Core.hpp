//
// Core.hpp for Core in /home/zellou_i/rendu/cpp_bomberman
// 
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
// 
// Started on  Mon Jul  7 12:39:34 2014 ilyas zelloufi
// Last update Mon Jul  7 12:39:38 2014 ilyas zelloufi
//

#ifndef		CORE_HPP_
#define		CORE_HPP_

#include	<glm/glm.hpp>
#include	<glm/gtc/matrix_transform.hpp>
#include	<iostream>
#include	<BasicShader.hh>
#include	<vector>
#include	<new>
#include	<Geometry.hh>
#include	<Texture.hh>
#include	<Game.hh>
#include	<SdlContext.hh>
#include	"Bomb.hpp"
#include	"Map.hpp"
#include	"Marvin.hpp"
#include	"CoreMap.hpp"
#include	"Menu.hpp"
#include	"Icon.hpp"

class	Core : public gdl::Game
{
private:
  gdl::Clock				_clock;
  gdl::Input				_input;
  gdl::SdlContext			_context;
  gdl::BasicShader			_shader;
  AObject				*_surface;
  std::vector<std::vector<AObject*> >	 _map;
  std::vector<AObject*>			_personnage;
  std::vector<AObject*>			_bomb;
  int					_zmax;
  int					_xmax;
  float					_speed;
public:
  Core();
  virtual ~Core();
  virtual bool	initialize();
  virtual bool	update();
  virtual void	draw();
  bool	collision(AObject *perso, int const, int const) const;
  bool	putBomb();
  bool	begin();
  void	cleanVector();
  void	explosion();
  bool	end(std::string const &);
};

#endif		/* CORE_HPP_ */
