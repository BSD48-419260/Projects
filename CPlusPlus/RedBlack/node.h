#ifndef NODE_H
#define NODE_H

class Node {
 public:
  Node(int* argdata); //Node constructor
  ~Node(); //Node destructor
  int* getInt(); //Getter for data
  Node* getParent(); //Getter for parent
  void setParent(Node* argLink); //Setter for parent
  Node* getNext(); //Getter for next
  void setNext(Node* argLink); //Setter for next
  void setNextOrphaned(Node* argLink); //Setter for next that does not update the parent node.
  Node* getLeft(); //Getter for left
  void setLeft(Node* argLink); //Setter for left
  void setLeftOrphaned(Node* argLink); //Setter for left that does not update the parent node.
  Node* getRight(); //Getter for right
  void setRight(Node* argLink); //Setter for right
  void setRightOrphaned(Node* argLink); //Setter for right that does not update the parent node.
  int* integ;
  Node* parent;
  Node* next;
  Node* left;
  Node* right;
  bool isRed = false;
};

#endif
