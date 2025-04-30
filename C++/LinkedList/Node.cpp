#include "Student.h"
#include "Node.h"

Node::Node(){
  refrencedStudent=nullptr;
  next=nullptr;
}

Node::Node(Student* newkid){
  refrencedStudent=newkid;
  next=nullptr;
}

Node::Node(Student* newkid, Node*& newNext){
  refrencedStudent=newkid;
  next=newNext;
}

Node::~Node(){
  delete refrencedStudent;
}

Node* Node::getNext(){
  return next;
}

void Node::setNext(Node* newNext){
  next=newNext;
}

Student* Node::getStudent(){
  return refrencedStudent;
}

void Node::setStudent(Student* newStudent){
  refrencedStudent=newStudent;
}
