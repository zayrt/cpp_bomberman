//
// main.cpp for  in /home/zellou_i/rendu/cpp_bomberman
// 
// Made by ilyas zelloufi
// Login   <zellou_i@epitech.net>
// 
// Started on  Mon Jul  7 12:41:18 2014 ilyas zelloufi
// Last update Mon Jul  7 12:41:19 2014 ilyas zelloufi
//

#include <cstdlib>
#include "Core.hpp"

int main()
{
  Core game;

  if (game.initialize() == false)
    return (-1);
  while (game.update() == true)
    game.draw();
  return (0);
}
