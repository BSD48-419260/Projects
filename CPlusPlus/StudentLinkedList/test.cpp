#include "Node.cpp"
#include "Node.h"
#include "Student.h"
#include<iostream>
#include<cstring>
using namespace std;

void printall(Node*);

//Here is a test of the functions I have made.
int main(){
  Student* Alice = new Student((char*)"Alice\0");
  Student* Bob = new Student((char*)"Bob\0");
  Student* Charles = new Student((char*)"Charles\0");
  Student* Debra = new Student((char*)"Debra\0");
  //node constructor beign demonstrated.
  Node* fourthnode = new Node(Debra);
  Node* thirdnode = new Node();
  thirdnode->setStudent(Charles);
  thirdnode->setNext(fourthnode);
  Node* secondnode = new Node(Bob);
  //ensuring setNext works.
  secondnode->setNext(thirdnode);
  Node* firstnode = new Node(Alice, secondnode);
  //ensuring structure works
  printall(firstnode);
  //showing delete ~Node() working
  cout<<"crud"<<endl;
  delete fourthnode;
  thirdnode->setNext(nullptr);
  printall(firstnode);
  return 0;
}

//demonstrating getStudent and getNext working
void printall(Node* currentNode){
  if (currentNode->getNext()==nullptr){
    cout<<currentNode->getStudent()->name<<endl;
    return;
  }
  cout<<currentNode->getStudent()->name<<endl;
  printall(currentNode->getNext());
  cout<<"reachedend"<<endl;
}
