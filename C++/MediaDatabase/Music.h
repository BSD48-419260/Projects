/*
11/6/2024
made by Elliott VanOrman for Jason Galbraith's C++ class
This is the header file for the 'Music' class.
 */

#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>
#include <cstring>
#include "Media.h"

using namespace std;

class Music:public Media{
 public:
  Music();
  Music(char*,char*,int,int,char*);
  char* getArtist();
  void setArtist(char*);
  int getDuration();
  void setDuration(int);
  char* getPublisher();
  void setPublisher(char*);
};
#endif
