#include <iostream>
#include "node.h"

using namespace std;
/*
  For comments, please see the .h fie.
 */

Node::Node(char* argdata) {
  charac[0] = argdata[0];
  charac[1] = '\0';
  link = nullptr;
  left = nullptr;
  right = nullptr;
}

Node::~Node() {
  delete[] charac;
  link = nullptr;
  left = nullptr;
  right = nullptr;
}

char* Node::getChar() {
  return charac;
}

Node* Node::getNext() {
  return link;
}

void Node::setNext(Node* arglink) {
  link = arglink;
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
