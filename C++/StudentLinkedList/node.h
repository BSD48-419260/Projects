//Note: this code was programmed by one Sriram Subramanian, for use in mr Galbraith's c++ class
#ifndef NODE_H
#define NODE_H
#include "student.h"

class Node {
    public:
        Node(Student* data); //Node constructor
        ~Node(); //Node destructor
        Node* getNext(); //Getter for link
        Student* getStudent(); //Getter for data
        void setNext(Node* arglink);
    private: //The node has two things, the link (what it goes to next), and the data
        Student* data;
        Node* link;

};

#endif
