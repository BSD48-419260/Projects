#ifndef NODE_H
#define NODE_H

class Node {
 public:
  Node(int* argdata); //Node constructor
  ~Node(); //Node destructor
  int* getInt(); //Getter for data
  Node* getNext(); //Getter for left
  void setNext(Node* argLink); //Setter for left
  Node* getLeft(); //Getter for left
  void setLeft(Node* arglink); //Setter for left
  Node* getRight(); //Getter for right
  void setRight(Node* arglink); //Setter for right
  int* integ;
  Node* next;
  Node* left;
  Node* right;

};

#endif
