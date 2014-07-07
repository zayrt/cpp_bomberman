//
// CoreMap.cpp for  in /home/zellou_i/rendu/cpp_bomberman
// 
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
// 
// Started on  Mon Jul  7 12:42:41 2014 ilyas zelloufi
// Last update Mon Jul  7 12:42:42 2014 ilyas zelloufi
//

#include "CoreMap.hpp"

CoreMap::CoreMap(const std::string &filename)
{
  _filename = filename;
}

bool			CoreMap::loadmap()
{
  std::ifstream		fichier(_filename.c_str(), std::ios::in);
  std::vector<AObject*>	tmp;
  std::string	       	line;
  unsigned int		size_line;

  if (fichier)
    {
      _z = 0;
      while (getline(fichier, line))
	{
	  if (_z == 0)
	    size_line = line.size();
	  else
	    if (size_line != line.size())
	      {
		std::cout << "Map format incorrect" << std::endl;
		return (false);
	      }
	  for (unsigned int i = 0; i < line.size(); ++i)
	    {
	      if (i != 0 && line.size() != (unsigned int)_x)
		std::cout << "Wrong map" << std::endl;
	      this->_x = line.size();
	      if (line[i] == 'w')
		{
		  AObject *w = new Cube(i, _z, "./assets/wall.tga", WALL);

		  if (!w->initialize())
		    {
		      std::cout << "Draw wall fail" << std::endl;
		      return (false);
		    }
		  tmp.push_back(w);
		}
	      else if (line[i] == 'c')
		{
		  AObject *c = new Cube(i, _z, "./assets/texture-caisse.tga", BOX);

		  if (!c->initialize())
		    {
		      std::cout << "Draw caisse fail" << std::endl;
		      return (false);
		    }
		  tmp.push_back(c);
		}
	      else if (line[i] == '.')
		{
		  tmp.push_back(NULL);
		}
	      else
		std::cout << "Wrong element" << std::endl;
	    }
	  this->_map.push_back(tmp);
	  tmp.clear();
	  line.assign("");
	  _z += 1;
	}
    }
  else
    {
      std::cout << "Map Loading failed" << std::endl;
      return (false);
    }
  return (true);
}

CoreMap::~CoreMap()
{

}

std::vector<std::vector<AObject*> >	CoreMap::getMap() const
{
  return (this->_map);
}

int					CoreMap::getX() const
{
  return (_x);
}

int					CoreMap::getZ() const
{
  return (_z);
}

void					CoreMap::SetX(unsigned int const &x)
{
  this->_x = x;
}

void					CoreMap::SetZ(unsigned int const &z)
{
  this->_z = z;
}

void					CoreMap::SetElement(const unsigned int &x, const unsigned int &y, AObject *value)
{
  this->_map[y][x] = value;
}
