//
// main.cpp for bomberman in /home/tang_j/bomberman
// 
// Made by Jean Luc TANG
// Login   <tang_j@epitech.net>
// 
// Started on  Sun Jun 15 02:34:46 2014 Jean Luc TANG
// Last update Sun Jun 15 02:34:55 2014 Jean Luc TANG
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
