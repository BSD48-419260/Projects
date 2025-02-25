#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
using namespace std;

//function signatures
void push(Node* & Head, char* ToAdd);
char* pop(Node* & Head);
char* peek(Node* & Head);
void enqueue(Node* & Head, char* ToAdd);
char* dequeue(Node* Head, bool & secondToLast);
void printList(Node* Head);
int precedence(char* toTest);
int NodeLength();
void infixToPostfix(Node * & inStack);
Node* getStackFromInput();

int main(){
  cout<<"Heck."<<endl;
  return 0; 
}

//treats Head like a stack and Pushes.
void push(Node* & Head, char* ToAdd){
  Node* newNode = new Node(ToAdd);
  if(Head->getChar!=nullptr){
    newNode->setNext(Head);
  }
  Head=newNode;
}

//treats Head like a stack and Pops.
char* pop(Node* & Head){
  char* mychar = Head->getChar();
  Node* box = Head;
  Head=Head->getNext();
  delete box;
  return mychar
  
}

//treats Head like a stack and Peeks.
char* peek(Node* & Head){
  return Head->getChar();
}

//treats Head like a queue and Enqueues. Yes, it is indistinguisable from Push but the name helps me remember.
void enqueue(Node* & Head, char* ToAdd){
  Node* newNode = new Node(ToAdd);
  if(Head->getChar!=nullptr){
    newNode->setNext(Head);
  }
  Head=newNode;
}

//treats Head like a stack and Dequeues.
char* dequeue(Node* Head,bool & nextIsLast){
  if(Head==nullptr){
    return nullptr;
  }
  if(Head->getNext()==nullptr){
    nextIsLast=true;
    return Head->getChar();
  }else{
    bool test = false;
    char* ret = dequeue(Head->getNext(),test);
    if(test){
      delete Head->getNext();
      Head->setNext(nullptr);
    }
    return ret;
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
    printList(Head->getNext());
  }else{
    cout<<endl;
    return;
  }
}

//checks if a character is an operator and returns it's precedence based on that. if called on a number, returns 0.
int precedence(char* toTest){
  if((*toTest=='(')||(*toTest==')')){
    return -1;
  }else if(*toTest=='^'){
    return 4;
  }else if((*toTest=='x')||(*toTest=='*')||(*toTest=='/')||(*toTest=='÷')){
    return 3;
  }else if((*toTest=='+')||(*toTest=='-')){
    return 2;
  }else{
    return 0;
  }
}

//converts infix notation script to postfix notation script. Also known as the 'Shunting Yard' algorithim
void infixToPostfix(Node * & inQueue){
  Node* outQueue;
  Node* shuntStack;
  char* currentChar;
  bool headalone=false;
  while(inQueue!=nullptr){
    if(headalone){
      currentChar=inQueue->getChar();
      delete inQueue;
      inQueue=nullptr;
    }else{
      currentChar= dequeue(inQueue,headalone);
    }
    
    if(precedence(currentChar)==0){
      enqueue(outQueue, currentChar);
    }else if(*currentChar=='('){
      push(shuntStack, currentChar);
    }else if(*currentChar==')'){
      while(*peek(shuntStack)!='('){
	enqueue(outQueue,pop(shuntStack));
      }
      box=pop(shuntStack);
      delete box;
    }else{
      while ((*peek(shuntStack)!='(')&&((precedence(peek(shuntstack))>precedence(currentchar))||((precedence(peek(shuntstack))==precedence(currentchar))&&(*currentChar!='^')))){
	enqueue(outQueue,pop(shuntStack));
      }
      push(shuntStack,currentChar);
    }
  }
  while(peek(shuntStack)!=nullptr){
    enqueue(outQueue,pop(shuntStack));
  }
  inQueue=outQueue;
  delete shuntstack;
  delete currentchar;
  
}

Node* getStackFromInput(){
  Node* buffer;
  char* inputbuffer; 
}
