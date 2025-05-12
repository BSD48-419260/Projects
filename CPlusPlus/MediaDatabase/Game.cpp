/*
11/6/2024
made by Elliott VanOrman for Jason Galbraith's C++ class
This is the cpp file that contains all the actual functions for the 'Game' class.
 */
#include <iostream>
#include <cstring>
#include "Game.h"

using namespace std;

Game::Game(){
  type='G';

  delete title;
  title = new char[16];

  delete publisher;
  publisher = new char[16];

  delete rating;
  rating = new char[16];
}
Game::Game(char* newtitle, int newyear, char* newpublisher, char* newrating){
  type='G';

  title = new char[16];
  strcpy(title,newtitle);

  year=newyear;

  publisher = new char[16];
  strcpy(publisher,newpublisher);

  rating = new char[16];
  strcpy(rating,newrating);
}
char* Game::getPublisher(){
  return publisher;
}
void Game::setPublisher(char* newpublisher){
  delete publisher;
  publisher = new char[16];
  strcpy(publisher,newpublisher);
  return;
}
char* Game::getRating(){
  return rating;
}
void Game::setRating(char* newrating){
  delete rating;
  rating = new char[16];
  strcpy(rating,newrating);
  return;
}
