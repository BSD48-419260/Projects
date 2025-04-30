#include <iostream>
#include "node.h"

using namespace std;

Node::Node(Student* argdata) {
    data = argdata;
}

Node::~Node() {
    delete data;
    data = nullptr;
}

Node* Node::getNext() {
    return link;
}

Student* Node::getStudent() {
    return data;

}

void Node::setNext(Node* arglink) {
   link = arglink; 
}
