/*
11/6/2024
made by Elliott VanOrman for Jason Galbraith's C++ class
This is the header file for the 'Media' class, the base parent class all the others rely on. the other files are useless without this, so don't remove this!
 */
#ifndef MEDIA_H
#define MEDIA_H

#include<iostream>
#include<cstring>

using namespace std;

class Media{
 public:
  //constructors and destructors
  Media();
  Media(char*,int);
  ~Media();
  //void setto(Media);
  //getters and setters
  char* getTitle();
  void setTitle(char*);
  int getYear();
  void setYear(int);
  char getType();
 protected:
  //the reason I have all the names here is partially so I can delete them in the destructor. Well, that and so all the chilren classes need the same memory.
  char* title;
  char* artist;
  int year;
  char* director;
  int duration;
  char* publisher;
  char* rating;
  char type;
};

#endif
