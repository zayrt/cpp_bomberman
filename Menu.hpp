//
// Menu.hpp for  in /home/zellou_i/rendu/cpp_bomberman
// 
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
// 
// Started on  Mon Jul  7 12:41:37 2014 ilyas zelloufi
// Last update Mon Jul  7 12:41:39 2014 ilyas zelloufi
//

#ifndef		MENU_HPP_
#define		MENU_HPP_

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
#include	"Marvin.hpp"
#include	"Menu.hpp"
#include	"Icon.hpp"

class	Menu : public gdl::Game
{
private:
  gdl::Clock            _clock;
  gdl::Input            _input;
  gdl::BasicShader      _shader;
  gdl::SdlContext	_context;
  std::vector<AObject*> _menu;
  std::string		_map;
  int			_mode;

public:
  Menu(gdl::BasicShader const &, gdl::Clock const &, gdl::Input const &, gdl::SdlContext const &);
  virtual ~Menu();
  bool	initialize();
  bool	update();
  void	draw();
  std::string	getMap() const;
  int		getMode() const;
};

#endif		/* MENU_HPP_ */
