/*
11/6/2024
made by Elliott VanOrman for Jason Galbraith's C++ class
This is the cpp file that contains all the actual functions for the 'Movie' class.
 */
#include <iostream>
#include <cstring>
#include "Movie.h"

using namespace std;

Movie::Movie(){
  type='O';

  delete title;
  title = new char[16];

  delete director;
  director = new char[16];

  delete rating;
  rating = new char[16];
}

Movie::Movie(char* newtitle, char* newdirector, int newyear, int newduration, char* newrating){
  type='O';

  delete title;
  title = new char[16];
  strcpy(title,newtitle);
  
  delete director;
  director = new char[16];
  strcpy(director,newdirector);

  year=newyear;

  duration=newduration;

  delete rating;
  rating = new char[16];
  strcpy(rating,newrating);
}

char* Movie::getDirector(){
  return director;
}
void Movie::setDirector(char* newdirector){
  delete director;
  director = new char[16];
  strcpy(director,newdirector);
}
int Movie::getDuration(){
  return duration;
}
void Movie::setDuration(int newduration){
  duration=newduration;
}
char* Movie::getRating(){
  return rating;
}
void Movie::setRating(char* newrating){
  delete rating;
  rating = new char[16];
  strcpy(rating,newrating);
}
