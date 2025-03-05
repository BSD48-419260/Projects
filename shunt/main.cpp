/*
  Main.cpp for Shunting Yard Algorithim Project.
  Made by Elliott VanOrman for Jason Galbraith's C++/Data Structures class.

  Takes in a formula in Infix, Translates it into Postifx, then restructures it into a binary expression tree that can be expressed as any of Prefix, Infix, and Postfix

*/
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
void removeLast(Node* Head);
void printList(Node* Head);
int precedence(char toTest);
void infixToPostfix(Node * & inQueue);
void PostfixToTree(Node * & inQueue);
Node* getStackFromInput();
int length(Node* Head, int Size);
void RecPrintInf(Node* tree);
void RecPrintPre(Node* tree);
void RecPrintPos(Node* tree);

//main. 
int main(){

  cout<<"======================================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<"_____   ___________    ____            "<<endl;
  cout<<"\   /   \___   ___/   / __ \           "<<endl;
  cout<<" | |        | |      / /  \ \          "<<endl;
  cout<<" | |        | |     / /____\ \         "<<endl;
  cout<<" | |        | |    / ________ \        "<<endl;
  cout<<" | |        | |    | |      | |        "<<endl;
  cout<<" | |        | |    | |      | |        "<<endl;
  cout<<"/___\ nfix /___\o /___\    /___\llfixes"<<endl;
  cout<<"(To avoid confusion, Allfixes means all of prefix,infix, and postfix)"<<endl;
  //getting formula
  Node* mathLinkedList=getStackFromInput();
  //confirming formula is correct
  cout<<"Currrent List:"<<endl;
  printList(mathLinkedList);
  //converting formula to postfix, confirming again.
  cout<<endl<<"Postfixed:"<<endl;
  infixToPostfix(mathLinkedList);
  printList(mathLinkedList);
  cout<<endl;
  //converting formula to Tree, printing results 
  PostfixToTree(mathLinkedList);
  cout<<"Converted to tree!"<<endl<<"Infix:"<<endl;
  RecPrintInf(mathLinkedList);
  cout<<endl<<"Prefix:"<<endl;
  RecPrintPre(mathLinkedList);
  cout<<endl<<"Postfix:"<<endl;
  RecPrintPos(mathLinkedList);
  cout<<endl;
  return 0; 
}

//input getter
void getStringFromInput(char* inpstring){
  char bufferarray [101];
  //make sure it works
  bool acin=false;
  for(int i=0;i<101;i++){
    bufferarray[i]='\0';
  }
  while(acin==false){
    cout<<"100 characters or less, please."<<endl;
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
  strncpy(inpstring, bufferarray, 100);
  inpstring[100]='\0';
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

//treats Head like a stack and Peeks. Functionally speaking this is completely useless but it's meant for readability.
Node* peek(Node* & Head){
  return Head;
}

//treats Head like a queue and Enqueues. Functionally indistinguisable from Push but again, readability.
void enqueue(Node* & Head, Node* ToAdd){
  ToAdd->setNext(Head);
  Head=ToAdd;
}

//treats Head like a stack and Dequeues.
Node* dequeue(Node* & Head){
  //a while ago I realized it would be much easier for me to handle getting the last node and removing the last node seprately, so here I do just that.
  Node* last= getLast(Head);
  if(Head->getNext()==nullptr){
    Head=nullptr;
    return last;
  }
  removeLast(Head);
  return last;
}

//gets the last node in a LinkedList. for dequeue.
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

//removes the last node in a list. also for dequeue.
void removeLast(Node* Head){
  if (Head==nullptr){
    return;
  }if (Head->getNext()->getNext()==nullptr){
    Head->setNext(nullptr);
  }else{
    removeLast(Head->getNext());
  }
}

//linkedlist printer. does it both backwards and forwards because normally queues are printed in reverse for it.
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
    cout<<Head->getChar();
    cout<<", ";
    return;
  }
  cout<<Head->getChar();
  cout<<", ";
}


//checks if a character is an operator and returns it's precedence based on that. if called on a number, returns 0. technically means most letters can be used in place of numbers.
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

//converts infix notation fomrulae to postfix notation formulae. Also known as the 'Shunting Yard' algorithim
void infixToPostfix(Node * & inQueue){
  //printList(inQueue);
  Node* outQueue = nullptr;
  Node* shuntStack = nullptr;
  Node* currentNode =nullptr;
  while(inQueue!=nullptr){
    /*
    //this oddly-inserted comment of code is for telemetry. once I finished debugging, I didn't need it but I still like to see it in action so I understand how it works.
    if(currentNode!=nullptr){
      cout<<*(currentNode->getChar())<<endl;
    }
    cout<<"_____________"<<endl;
    //*/
    currentNode=dequeue(inQueue);
    /*
    cout<<*(currentNode->getChar())<<endl;
    printList(inQueue);
    cout<<endl;
    printList(shuntStack);
    cout<<endl;
    printList(outQueue);
    cout<<endl;
    //*/
    if(precedence(*(currentNode->getChar()))==0){
      enqueue(outQueue, currentNode);
    }else if(*(currentNode->getChar())=='('){
      push(shuntStack, currentNode);
    }else if(*(currentNode->getChar())==')'){
      while(*(peek(shuntStack)->getChar())!='('){
	enqueue(outQueue,pop(shuntStack));
      }
      Node* box=pop(shuntStack);
      delete box;
      delete currentNode;
    }else{
      if(shuntStack!=nullptr){
	while ((shuntStack!=nullptr)&&((*(peek(shuntStack)->getChar())!='(')&&((precedence(*(peek(shuntStack)->getChar()))>precedence(*(currentNode->getChar())))||((precedence(*(peek(shuntStack)->getChar()))==precedence(*(currentNode->getChar())))&&(*(currentNode->getChar())!='^'))))){
	  enqueue(outQueue,pop(shuntStack));
	}
      }
      push(shuntStack,currentNode);
    }
  }
  while(peek(shuntStack)!=nullptr){
    enqueue(outQueue,pop(shuntStack));
  }
  inQueue=outQueue;
  delete shuntStack;
}

//converts Postfix notation formulae to a binary expression tree
void PostfixToTree(Node * & inQueue){
  Node* workingStack = nullptr;
  Node* currentNode =nullptr;
  while(length(inQueue,1)!=0){
    currentNode = dequeue(inQueue);
    if (length(workingStack,1)>1){
      if (precedence(*(currentNode->getChar()))!=0){
	currentNode->setLeft(pop(workingStack));
	currentNode->setRight(pop(workingStack));
	push(workingStack,currentNode);
      }else{
	push(workingStack,currentNode);
      }
    }else{
      push(workingStack,currentNode);
    }
  }
  inQueue = workingStack;
}

//takes in user input and converts it to a linkedList containing a formula.
Node* getStackFromInput(){
  Node* buffer = nullptr;
  //Node* revbuf = nullptr;
  char* inputbuffer = new char[101];
  getStringFromInput(inputbuffer);
  for(int i=0; i<101; i++){
    if((inputbuffer[i]!='\0')&&(inputbuffer[i]!=' ')){
      enqueue(buffer,new Node(inputbuffer+i));
    }
  }
  delete[] inputbuffer;
  return buffer;
}
//gets the length of an expression
int length(Node* Head, int Size){
  if(Head==nullptr){
    return 0;
  }
  if(Head->getNext()==nullptr){
    return Size;
  }
  return length(Head->getNext(),Size+1);
}

//Recursive Print Infix. modified version of the heap print code Mr.Galbraith provided.
void RecPrintInf(Node* tree){
  if(tree==nullptr){
    return;
  }
  
  if(tree->getRight()!=nullptr){
    cout<<'(';
    RecPrintInf(tree->getRight());
  }
  cout<<*(tree->getChar())<<' ';
  if(tree->getLeft()!=nullptr){
    RecPrintInf(tree->getLeft());
    cout<<')';
  }
}

//Recursive Print Prefix. modified version of the heap print code Mr.Galbraith provided.
void RecPrintPre(Node* tree){
  if(tree==nullptr){
    return;
  }
  cout<<*(tree->getChar())<<' ';
  if(tree->getRight()!=nullptr){
    RecPrintPre(tree->getRight());
  }
  if(tree->getLeft()!=nullptr){
    RecPrintPre(tree->getLeft());
  }
}

//Recursive Print Postfix. modified version of the heap print code Mr.Galbraith provided.
void RecPrintPos(Node* tree){
  if(tree==nullptr){
    return;
  }
  
  if(tree->getRight()!=nullptr){
    RecPrintPos(tree->getRight());
  }
  if(tree->getLeft()!=nullptr){
    RecPrintPos(tree->getLeft());
  }
  cout<<*(tree->getChar())<<' ';
}
