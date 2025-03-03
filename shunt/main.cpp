#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "node.cpp"
using namespace std;

//function signatures
void getStringFromInput(char* inpstring);
void push(Node* & Head, Node* ToAdd);
Node* pop(Node* & Head);
Node* peek(Node* & Head);
void enqueue(Node* & Head, Node* ToAdd);
Node* dequeue(Node* & Head);
Node* getLast(Node* Head);
void removeLast(Node* & Head);
void printList(Node* Head);
int precedence(char toTest);
int NodeLength();
void infixToPostfix(Node * & inStack);
Node* getStackFromInput();

int main(){
  Node* warmaster_horus=getStackFromInput();
  printList(warmaster_horus);
  infixToPostfix(warmaster_horus);
  printList(warmaster_horus);
  return 0; 
}

void getStringFromInput(char* inpstring){
  char bufferarray [21];
  //make sure it works
  bool acin=false;
  for(int i=0;i<21;i++){
    bufferarray[i]='\0';
  }
  while(acin==false){
    cout<<"20 characters or less, please."<<endl;
    cin.getline(bufferarray, sizeof(bufferarray),'\n');
    //being robust.
    if(cin.fail()){
      cout<<"I think you did something wrong. Please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  strncpy(inpstring, bufferarray, 20);
  inpstring[20]='\0';
  cout<<endl;
  return;
}

//treats Head like a stack and Pushes.
void push(Node* & Head, Node* ToAdd){
  ToAdd->setNext(Head);
  Head=ToAdd;
}

//treats Head like a stack and Pops.
Node* pop(Node* & Head){
  Node* box = Head;
  Head=Head->getNext();
  return box;
}

//treats Head like a stack and Peeks.
Node* peek(Node* & Head){
  return Head->getNext();
}

//treats Head like a queue and Enqueues. Yes, it is indistinguisable from Push but the name helps me remember.
void enqueue(Node* & Head, Node* ToAdd){
  ToAdd->setNext(Head);
  Head=ToAdd;
}

//treats Head like a stack and Dequeues.
Node* dequeue(Node* & Head){
  Node* last= getLast(Head);
  if(Head->getNext()==nullptr){
    Head=nullptr;
    return last;
  }
  removeLast(Head);
  return last;
}


Node* getLast(Node* Head){
  if(Head==nullptr){
    return nullptr;
  }
  if(Head->getNext()==nullptr){
    return Head;
  }else{
    return getLast(Head->getNext());
  }
}


void removeLast(Node* & Head){
  if (Head==nullptr){
    return;
  }if (Head->getNext()->getNext()==nullptr){
    Head->setNext(nullptr);
  }
}

//linkedlist printer
void printList(Node* Head){
  if(Head==nullptr){
    cout<<"Empty"<<endl;
    return;
  }else if(Head->getChar()==nullptr){
    cout<<"Empty"<<endl;
    return;
  }
  cout<<Head->getChar();
  if(Head->getNext()!=nullptr){
    cout<<", ";
    printList(Head->getNext());
  }else{
    cout<<endl;
    return;
  }
}

//checks if a character is an operator and returns it's precedence based on that. if called on a number, returns 0.
int precedence(char toTest){
  if((toTest=='(')||(toTest==')')){
    return -1;
  }else if(toTest=='^'){
    return 4;
  }else if((toTest=='x')||(toTest=='*')||(toTest=='/')){
    return 3;
  }else if((toTest=='+')||(toTest=='-')){
    return 2;
  }else{
    return 0;
  }
}

//converts infix notation script to postfix notation script. Also known as the 'Shunting Yard' algorithim
void infixToPostfix(Node * & inQueue){
  printList(inQueue);
  Node* outQueue = nullptr;
  Node* shuntStack = nullptr;
  Node* currentNode =nullptr;
  while(inQueue!=nullptr){
    if(currentNode!=nullptr){
      cout<<*(currentNode->getChar())<<endl;
    }
    cout<<"_____________"<<endl;
    currentNode=dequeue(inQueue);
    cout<<*(currentNode->getChar())<<endl;
    printList(inQueue);
    printList(shuntStack);
    printList(outQueue);
    if(precedence(*(currentNode->getChar()))==0){
      cout<<"Curse"<<endl;
      enqueue(outQueue, currentNode);
    }else if(*(currentNode->getChar())=='('){
      cout<<"Sanguine"<<endl;
      push(shuntStack, currentNode);
    }else if(*(currentNode->getChar())==')'){
      cout<<"Ferrus"<<endl;
      while(*(peek(shuntStack)->getChar())!='('){
	cout<<"Mannus"<<endl;
	enqueue(outQueue,pop(shuntStack));
      }
      cout<<"Iron"<<endl;
      Node* box=pop(shuntStack);
      cout<<"Tenth"<<endl;
      delete box;
      delete currentNode;
    }else{
      cout<<"Angry"<<endl;
      while ((*(peek(shuntStack)->getChar())!='(')&&((precedence(*(peek(shuntStack)->getChar()))>precedence(*(currentNode->getChar())))||((precedence(*(peek(shuntStack)->getChar()))==precedence(*(currentNode->getChar())))&&(*(currentNode->getChar())!='^')))){
	enqueue(outQueue,pop(shuntStack));
      }
      cout<<"Rouboute"<<endl;
      push(shuntStack,currentNode);
    }
  }
  while(peek(shuntStack)!=nullptr){
    enqueue(outQueue,pop(shuntStack));
  }
  inQueue=outQueue;
  delete shuntStack;
}

int NodeLength(){
  return 0;
}

Node* getStackFromInput(){
  Node* buffer = nullptr;
  //Node* revbuf = nullptr;
  char* inputbuffer = new char[21];
  getStringFromInput(inputbuffer);
  for(int i=0; i<21; i++){
    if(inputbuffer[i]!='\0'){
      enqueue(buffer,new Node(inputbuffer+i));
    }
  }
  delete[] inputbuffer;
  return buffer;
  //while(buffer!=nullptr){
  //  enqueue(revbuf,pop(buffer));
  //}
  //delete buffer;
  //return revbuf;
}

