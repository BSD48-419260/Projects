#include <iostream>
#include "Node.h"

using namespace std;

Node::Node(Student* argdata) {
    data = argdata;
    link = nullptr;
}

Node::~Node() {
    delete data;
    link = nullptr;
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
