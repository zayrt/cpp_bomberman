//
// CoreMap.hpp for  in /home/zellou_i/rendu/cpp_bomberman
// 
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
// 
// Started on  Mon Jul  7 12:42:33 2014 ilyas zelloufi
// Last update Mon Jul  7 12:42:34 2014 ilyas zelloufi
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
