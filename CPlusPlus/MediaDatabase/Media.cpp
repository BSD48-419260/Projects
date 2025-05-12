/*
11/6/2024
made by Elliott VanOrman for Jason Galbraith's C++ class
This is the cpp file that contains all the actual functions for the base 'Media' class.
 */
#include <iostream>
#include <cstring>
#include "Media.h"

using namespace std;

//constructors.
Media::Media(){
  delete title;
  title=new char[16];
}

Media::Media(char* newtitle, int newyear){
  delete title;
  title=new char[16];
  strcpy(title,newtitle);
  year=newyear;
}
//Destructors. fun fact: Calling delete on a child class automatically invokes tha parent's destructor, meaning I can just say 'delete' and the memory gets deallocated.
Media::~Media(){
  delete title;
  delete artist;
  delete director;
  delete publisher;
  delete rating;
}
//ignore this. bad idea I had, completely uncessary.
/*
void Media::setto(Media copiedfrom){
  delete title;
  title=new char[16];
  strcpy(title,copiedfrom.getTitle());

  year=copiedfrom.getYear();

  delete artist;
  artist=new char[16];
  strcpy(artist,copiedfrom.artist);

  delete director;
  director=new char[16];
  strcpy(director,copiedfrom.director);

  duration=copiedfrom.duration;

  delete publisher;
  publisher=new char[16];
  strcpy(publisher,copiedfrom.publisher);

  delete rating;
  rating=new char[16];
  strcpy(rating,copiedfrom.rating);

  type=copiedfrom.type;
}
*/
//getters and setters
char* Media::getTitle(){
  return title;
}

void Media::setTitle(char* newtitle){
  delete title;
  title = new char[16];
  strcpy(title,newtitle);
  return;
}

int Media::getYear(){
  return year;
}

void Media::setYear(int newyear){
  year=newyear;
  return;
}

char Media::getType(){
  return type;
}
