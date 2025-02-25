#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "node.cpp"
using namespace std;

//function signatures
void getStringFromInput(char* inpstring);
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
  Node* warmaster_horus=getStackFromInput();
  return 0; 
}

void getStringFromInput(char* inpstring){
  char bufferarray [16];
  //make sure it works
  bool acin=false;
  for(int i=0;i<16;i++){
    bufferarray[i]='\0';
  }
  while(acin==false){
    cout<<"15 characters or less, please."<<endl;
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
  strncpy(inpstring, bufferarray, 15);
  inpstring[15]='\0';
  cout<<endl;
  return;
}

//treats Head like a stack and Pushes.
void push(Node* & Head, char* ToAdd){
  Node* newNode = new Node(ToAdd);
  if(Head->getChar()!=nullptr){
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
  return mychar;
}

//treats Head like a stack and Peeks.
char* peek(Node* & Head){
  return Head->getChar();
}

//treats Head like a queue and Enqueues. Yes, it is indistinguisable from Push but the name helps me remember.
void enqueue(Node* & Head, char* ToAdd){
  Node* newNode = new Node(ToAdd);
  if(Head->getChar()!=nullptr){
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
      char* box=pop(shuntStack);
      delete box;
      delete currentChar;
    }else{
      while ((*peek(shuntStack)!='(')&&((precedence(peek(shuntStack))>precedence(currentChar))||((precedence(peek(shuntStack))==precedence(currentChar))&&(*currentChar!='^')))){
	enqueue(outQueue,pop(shuntStack));
      }
      push(shuntStack,currentChar);
    }
  }
  while(peek(shuntStack)!=nullptr){
    enqueue(outQueue,pop(shuntStack));
  }
  inQueue=outQueue;
  delete shuntStack;
  delete currentChar;
  
}

Node* getStackFromInput(){
  Node* buffer;
  char* inputbuffer = new char[16];
  getStringFromInput(inputbuffer);
  for(int i=0; i<16; i++){
    if(inputbuffer[i]=='\0'){
      cout<<" \\0";
    }else{
      cout<<inputbuffer[i];
    }
  }
  return buffer;
}
