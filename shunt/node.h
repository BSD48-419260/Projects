#ifndef NODE_H
#define NODE_H

class Node {
 public:
  Node(Char* data); //Node constructor
  ~Node(); //Node destructor
  char* getChar(); //Getter for data
  Node* getNext(); //Getter for link
  void setNext(Node* arglink); //Setter for link
  Node* getLeft(); //Getter for left
  void setLeft(Node* arglink); //Setter for left
  Node* getRight(); //Getter for right
  void setRight(Node* arglink); //Setter for right
  char* charac;
  Node* link;
  Node* left;
  Node* right;

};

#endif
