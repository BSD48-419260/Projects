#include <iostream>
#include "node.h"

using namespace std;
/*
  For comments, please see the .h fie.
 */

Node::Node(int* argdata) {
  integ = argdata;
  next = nullptr;
  left = nullptr;
  right = nullptr;
}

Node::~Node() {
  delete integ;
  next = nullptr;
  left = nullptr;
  right = nullptr;
}

int* Node::getInt() {
  return integ;
}

Node* Node::getNext() {
  return next;
}

void Node::setNext(Node* arglink) {
  next = arglink;
}

Node* Node::getLeft() {
  return left;
}

void Node::setLeft(Node* arglink) {
  left = arglink;
}

Node* Node::getRight() {
  return right;
}

void Node::setRight(Node* arglink) {
  right = arglink;
}
