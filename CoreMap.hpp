//
// Map.hpp for coremap in /home/benkha_z/bomberman
// 
// Made by zakaria benkhalifa
// Login   <benkha_z@epitech.net>
// 
// Started on  Tue Jun 10 15:47:41 2014 zakaria benkhalifa
// Last update Sat Jun 14 22:43:13 2014 Jean Luc TANG
//

#ifndef COREMAP_HPP_
# define COREMAP_HPP_

# include <vector>
# include <fstream>
# include <iostream>
# include "Core.hpp"

class	CoreMap
{
private:
  std::vector<std::vector<AObject*> >	       	_map;
  int			      			_x;
  int						_z;
  gdl::Texture					_texture;
  gdl::Geometry					_geometry;
  float						_speed;
  std::string					_filename;

public:
  CoreMap(const std::string &);
  ~CoreMap();
  int						getX() const;
  int						getZ() const;
  std::vector<std::vector<AObject*> >		getMap() const;
  void						SetX(unsigned int const &);
  void						SetZ(unsigned int const &);
  void						SetElement(const unsigned int &, const unsigned int &, AObject*);
  bool						loadmap();
};

#endif /* COREMAP_HPP_ */
