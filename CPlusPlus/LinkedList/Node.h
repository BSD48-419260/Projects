#ifndef NODE_H
#define NODE_H
#include "Student.h"
#include<iostream>
using namespace std;

//Node class
class Node{
 public:
  Node(); //empty constructor in case an empty node is needed
  Node(Student*); //constructor with student makes a new node that contains said student
  Node(Student*, Node*&); //constructor with a node built in just in case someone needs it
  ~Node(); //destructor to clear the node.
  Node* getNext(); //gets the poiner to the node this node is pointing to
  void setNext(Node*);  //changes the node this node is pointing to to the node parameter
  Student* getStudent(); //gets the pointer to the student this node contains 
  void setStudent(Student*); //changes the student this node is containing to the student parameter
 private:
  Student* refrencedStudent; //this points to the student 'inside' this node
  Node* next; //this points to the node next in the list after this node.
};


#endif
