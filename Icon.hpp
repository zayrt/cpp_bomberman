//
// Icon.hpp for  in /home/zellou_i/rendu/cpp_bomberman
// 
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
// 
// Started on  Mon Jul  7 12:41:51 2014 ilyas zelloufi
// Last update Mon Jul  7 12:41:54 2014 ilyas zelloufi
//

#ifndef			ICON_HPP_
# define		ICON_HPP_

#include	"Cube.hpp"

class Icon : public AObject
{
private:
  gdl::Texture _texture;
  gdl::Geometry _geometry;
  
  double	_x;
  double	_y;
  std::string	_path;
  double	_time;
  bool		_down;
  int		_step;
  std::string	_map;
  int		_mode;
public:
  Icon(double const &x, double const &y, std::string const &path, int const step)
  {
    _path = path;
    _x = x;
    _y = y;
    _down = false;
    _step = step;
    _map = "";
    _mode = 0;
  }
  virtual	~Icon() { }
  int		getStep() const {return (this->_step);}
  double	getX() const {return (this->_x);}
  double	getY() const {return (this->_y);}
  std::string	getMap() {return (this->_map);}
  int		getMode() const {return (this->_mode);}
  void		setX(double const &dir) {this->_x = this->_x + dir;}
  void		setY(double const &dir) {this->_y = this->_y + dir;}
  void	setMap()
  {
    if (this->_down == true)
      _map = "./map2";
    else
      _map = "./map1";
  }

  void	setMode()
  {
    if (this->_down == true)
      _mode = 2;
    else
      _mode = 1;
  }

  bool initialize()
  {
    _time = 0.00;

    if (_texture.load(_path) == false)
      {
	std::cerr << "Cannot load icon" << _path << std::endl;
	return (false);
      }
    _geometry.pushVertex(glm::vec3(this->_x, this->_y, 21));
    _geometry.pushVertex(glm::vec3(this->_x + 0.75, this->_y, 21));
    _geometry.pushVertex(glm::vec3(this->_x + 0.75, this->_y + 0.5, 21));
    _geometry.pushVertex(glm::vec3(this->_x, this->_y + 0.5, 21));

    _geometry.pushUv(glm::vec2(0.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 0.0f));
    _geometry.pushUv(glm::vec2(1.0f, 1.0f));
    _geometry.pushUv(glm::vec2(0.0f, 1.0f));
    _geometry.build();
    return (true);
  }
  
  void	exit()
  {
    _step = 0;    
  }
  
  bool update(gdl::Clock const &clock, gdl::Input &input)
  {
    if (_time <= 0.00)
      {
	if (input.getKey(SDLK_UP))
	  {
	    if (_down == false)
	      {
		this->setY(this->_y - 0.5);
		translate(glm::vec3(0, -1, 0) * 0.72f);
		_down = true;
	      }
	    else
	      {
		this->setY(this->_y + 0.5);
		translate(glm::vec3(0, 1, 0) * 0.72f);
		_down = false;
	      }
	    _time = 0.1;
	  }
	if (input.getKey(SDLK_DOWN))
	  {
	    if (_down == true)
	      {
		this->setY(this->_y + 0.5);
		translate(glm::vec3(0, 1, 0) * 0.72f);
		_down = false;
	      }
	    else
	      {
		this->setY(this->_y - 0.5);
		translate(glm::vec3(0, -1, 0) * 0.72f);
		_down = true;
	      }
	    _time = 0.1;
	  }
	if (input.getKey(SDLK_SPACE))
	  {
	    _time = 0.1;
	    _step = _step + 1;
	    if (_step == 3)
	      this->setMap();
	    else if (_step == 4)
	      this->setMode();
	    if ((_down == true && _step == 2) || (_step >= 4))
	      this->exit();
	  }
      }
    if (input.getKey(SDLK_BACKSPACE))
      {
	if (_step > 1)
	  {
	    _time = 0.1;
	    _step = _step - 1;
	  }
      }
    else
      _time = _time - static_cast<double>(clock.getElapsed());
    return (true);
  }

  void draw(gdl::AShader &shader, gdl::Clock const &clock)
  {
    (void)clock;
    _texture.bind();
    _geometry.draw(shader, getTransformation(), GL_QUADS);
  }
};

#endif		/* ICON_HPP_ */
