//
// Menu.hpp for bomberman in /home/tang_j/tmp
// 
// Made by Jean Luc TANG
// Login   <tang_j@epitech.net>
// 
// Started on  Fri Jun 13 19:38:08 2014 Jean Luc TANG
// Last update Sat Jun 14 23:43:56 2014 Jean Luc TANG
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
