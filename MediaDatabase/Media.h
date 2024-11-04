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
