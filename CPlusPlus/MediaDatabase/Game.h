/*
11/6/2024
made by Elliott VanOrman for Jason Galbraith's C++ class
This is the header file for the 'Game' class.
 */
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstring>
#include "Media.h"

using namespace std;

class Game : public Media{
 public:
  Game();
  Game(char*, int, char*, char*);
  char* getPublisher();
  void setPublisher(char*);
  char* getRating();
  void setRating(char*);
};
#endif
