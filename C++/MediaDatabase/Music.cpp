/*
11/6/2024
made by Elliott VanOrman for Jason Galbraith's C++ class
This is the cpp file that contains all the actual functions for the 'Music' class.
 */
#include <iostream>
#include <cstring>
#include "Music.h"

using namespace std;

Music::Music(){
  type='U';

  delete title;
  title = new char[16];

  delete artist;
  artist = new char[16];

  delete publisher;
  publisher = new char[16];
}

Music::Music(char* newtitle, char* newartist, int newyear, int newduration, char* newpublisher){
  type='U';

  delete title;
  title = new char[16];
  strcpy(title,newtitle);
  
  delete artist;
  artist = new char[16];
  strcpy(artist,newartist);

  year=newyear;

  duration=newduration;
  
  delete publisher;
  publisher = new char[16];
  strcpy(publisher,newpublisher);
}

char* Music::getArtist(){
  return artist;
}
void Music::setArtist(char* newartist){
  delete artist;
  artist = new char[16];
  strcpy(artist,newartist);
}
int Music::getDuration(){
  return duration;
}
void Music::setDuration(int newduration){
  duration=newduration;
}
char* Music::getPublisher(){
  return publisher;
}
void Music::setPublisher(char* newpublisher){
  delete publisher;
  publisher = new char[16];
  strcpy(publisher,newpublisher);
}
