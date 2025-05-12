#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "node.cpp"
using namespace std;

//function signatures
void getStringFromInput(char* inpstring);
void printList(Node* Head);
void RecPrint(int depth, Node* Head);
void PrintFromEldest(Node* Head);
Node* getGrandparent(Node* Head);
Node* getUncle(Node* Head);
Node* getSibling(Node* Head);
bool isLeft(Node* Head);
bool isRight(Node* Head);
bool isRed(Node* Check);
void addNode(Node* & Head, int ToAdd);
void addNodeRecursive(Node* & Head, Node* Cur, Node* ToAdd);
void handleAddingRedBlack(Node* & Head, Node* ToAdd);
int numberOfKids(Node* check);
/*
Node* removeNode(Node* Head, int nodeVal);
Node* deleteoncefound(Node* toDelete);
Node* stepTwo(Node* Head);
*/
void transplant(Node* & Head, Node* Original, Node* New);

Node* findNode(Node* Head, int nodeVal);
void removeNode(Node* & Head, Node* ToDelete);
void normDelete(Node* & Head, Node* toDelete, Node* Replacement);
void twokidDelete(Node* & Head, Node* toDelete, Node* Replacement);
void figDelete(Node* & Head, Node* toDelete, Node* Replacement, Node* x);
void NullWipedown(Node* & Head, Node* Replacment, Node* x);
void stepTwo(Node* & Head, Node* toDelete, Node* Replacement, Node* x);
void doFixup(Node* & Head, Node* x);

void ShiftTillLast(Node* Head);
void RecolorLineage(Node* Head);
void SwapCol(Node* Head);
void SwapNodes(Node* One, Node* Two);
Node* GetSuccessor(Node* Cur);
Node* getLastLeft(Node* Cur);
int getInt();
void DetectNumb(Node* Cur, int Check, int Depth);
int getDepth(Node* Cur, int & depth);
void addFromFile(Node* & head);
void rotLeft(Node* & Head, Node* Cur);
void rotRight(Node* & Head, Node* Cur);

//main. 
int main(){
  srand(time(0));
  Node* Head= nullptr;
  Node* buf = nullptr;
  cout<<"==========================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<"\033[31m_____        \033[0m_____      "<<endl;
  cout<<"\033[31m\\    \\       \033[0m\\    \\     "<<endl;
  cout<<"\033[31m | |\\ \\      \033[0m | |\\ \\    "<<endl;
  cout<<"\033[31m | |/ /      \033[0m | |/ /    "<<endl;
  cout<<"\033[31m |   |       \033[0m |   |     "<<endl;
  cout<<"\033[31m | |\\ \\      \033[0m | |\\ \\    "<<endl;
  cout<<"\033[31m | | \\ \\     \033[0m | |/ /    "<<endl;
  cout<<"\033[31m/___\\/__\\ed  \033[0m/____/lack "<<endl;
  bool notQuit=true;
  char inpstring[10];
  char gremlin[21];
  //primary loop
  while(notQuit){
    try{
      //robust-ish command handler.
      cout<<"Please input a command. (Valid commands: ADD, ADDFILE, DELETE, SEARCH, PRINT, QUIT)"<<endl;
      for(int i=0; i<10; i++){
	inpstring[i]='\0';
      }
      cin.getline(gremlin, sizeof(gremlin), '\n');
      strncpy(inpstring, gremlin, 10);
      if(cin.fail()){
	cout<<"Something went wrong. Please try again."<<endl;
	cin.clear();
	cin.ignore(100000,'\n');
      }else if (strcmp(inpstring,"ADD")==0){
        cout<<"How many will you be adding?"<<endl;
	addNode(Head,getInt());
      }else if (strcmp(inpstring,"ADDFILE")==0){
	char bufferarray[10];
	cin.getline(bufferarray, sizeof(bufferarray),'\n');
	addFromFile(Head);
      }else if (strcmp(inpstring,"DELETE")==0){
	cout<<"To Cancel, Input the number 0"<<endl;
        cout<<"SAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAALT"<<endl;
	removeNode(Head, findNode(Head, getInt()));
      }else if (strcmp(inpstring,"SEARCH")==0){
        DetectNumb(Head, getInt(), 0);
      }else if (strcmp(inpstring,"PRINT")==0){
	RecPrint(0, Head);
	cout<<"\033[0m";
      }else if (strcmp(inpstring,"QUIT")==0){
	notQuit=false;
	//no command needed, just quit the loop.
      }else{
	cout<<"Invalid Command."<<endl;
      }
    }catch(...){
      //In case of problems
      cout<<"Something went wrong. Please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }
  }
  cout<<"Have a great day."<<endl;
  return 0; 
}

//string getter. techically only needed once but I just really like having it.
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

//linkedlist printer.
void printList(Node* Head){
  if(Head==nullptr){
    cout<<"Empty"<<endl;
    return;
  }else if(Head->getInt()==nullptr){
    cout<<"Empty"<<endl;
    return;
  }
  if(Head->isRed){
    cout<<"\033[31m";
  }else{
    cout<<"\033[0m";
  }
  cout<<*(Head->getInt());
  if(Head->getNext()!=nullptr){
    cout<<", ";
    printList(Head->getNext());
  }else{
    cout<<"\033[0m";
    return;
  }
}

//tree printer
void RecPrint(int depth,Node* tree)
{
  if(tree==nullptr){
    return;
  }
  if(tree->getRight()!=nullptr){
    RecPrint(depth+1, tree->getRight());
  }
  for(int i=0; i<depth-1;i++){
    cout<<"\t";
  }
  if(isLeft(tree)){
    cout<<"\\-------";
  }else if(isRight(tree)){
    cout<<"/-------";
  }
  printList(tree);
  //cout<<(*(tree->getInt()))<<endl;
  cout<<endl;
  if(tree->getLeft()!=nullptr){
    RecPrint(depth+1, tree->getLeft());
  }
}

//Gets the root of a tree and prints the whole tree. not needed, I just wanted something to test the system I set up was working properly.
void PrintFromEldest(Node* Head){
  if(Head->getParent()!=nullptr){
    PrintFromEldest(Head->getParent());
  }else{
    RecPrint(0,Head);
  }
}

//Gets the grandparent of the current node.
Node* getGrandparent(Node* Head){
  if(Head->getParent()!=nullptr){
    return Head->getParent()->getParent();
  }else{
    return nullptr;
  }
}

//gets the Uncle of the current Node.
Node* getUncle(Node* Head){
  if(getGrandparent(Head)!=nullptr){
    if(getGrandparent(Head)->getLeft()==Head->getParent()){
      return getGrandparent(Head)->getRight();
    }else if(getGrandparent(Head)->getRight()==Head->getParent()){
      return getGrandparent(Head)->getLeft();
    }else{
      cout<<"A BIG MISTAKE HAS OCCURED! WE'RE ALL GOING TO DIE!"<<endl;
      cout<<"Node: "<<*(Head->getInt())<<endl;
      cout<<"Parent: "<<*(Head->getParent()->getInt())<<endl;
      cout<<"Grandparent: "<<*(getGrandparent(Head)->getInt())<<endl;
      cout<<"Grandpa's Kids:"<<endl;
      cout<<*(getGrandparent(Head)->getLeft()->getInt())<<" (Left) "<<endl;
      cout<<*(getGrandparent(Head)->getRight()->getInt())<<" (Right) "<<endl;
      exit(1);
    }
  }else{
    return nullptr;
  }
}

Node* getSibling(Node* Head){
  if(Head->getParent()!=nullptr){
    if(isLeft(Head)){
      return Head->getParent()->getRight();
    }else if (isRight(Head)){
      return Head->getParent()->getLeft();
    }
  }
  return nullptr;
}

bool isLeft(Node* Head){
  if(Head!=nullptr){
    if(Head->getParent()!=nullptr){
      if(Head->getParent()->getLeft()==Head){
	return true;
      }
    }
  }
  return false;
}

bool isRight(Node* Head){
  if(Head!=nullptr){
    if(Head->getParent()!=nullptr){
      if(Head->getParent()->getRight()==Head){
	return true;
      }
    }
  }
  return false;
}

bool isRed(Node* Check){
  if(Check!=nullptr){
    return Check->isRed;
  }
  return false;
}

//Adder function preamble
void addNode(Node* & Head, int ToAdd){
  int Integ;
  for(int i=0; i<ToAdd; i++){
    bool acin=false;
    while (acin==false){
      cout<<"Please insert new entry number "<<i+1<<":"<<endl;
      cin>>Integ;
      if(cin.fail()){
	cout<<"I think you did something wrong. please try again."<<endl;
	  cin.clear();
	  cin.ignore(100000,'\n');
      }else{
	if(Integ!=0){
	  if(Head!=nullptr){
	    addNodeRecursive(Head, Head, new Node(new int(Integ)));
	  }else{
	    Head = new Node(new int(Integ));
	  }
	}else{
	  cout<<"No node may contain 0"<<endl;
	 }
	acin=true;
      }
    }
  }
}


//actual adder function.
void addNodeRecursive(Node* & Head, Node* Cur, Node* ToAdd){
  if(Cur==nullptr){
    Cur=ToAdd;
    handleAddingRedBlack(Head,ToAdd);
  }else if(*(ToAdd->getInt())<*(Cur->getInt())){
    if(Cur->getLeft()==nullptr){
      Cur->setLeft(ToAdd);
      handleAddingRedBlack(Head,ToAdd);
    }else{
      addNodeRecursive(Head, Cur->getLeft(),ToAdd);
    }
  }else if(*(ToAdd->getInt())>*(Cur->getInt())){
    if(Cur->getRight()==nullptr){
      Cur->setRight(ToAdd);
      handleAddingRedBlack(Head,ToAdd);
    }else{
      addNodeRecursive(Head, Cur->getRight(),ToAdd);
    }
  }else{
    if(Cur->getNext()==nullptr){
      Cur->setNext(ToAdd);
      ToAdd->isRed = Cur->isRed;
    }else{
      addNodeRecursive(Head, Cur->getNext(),ToAdd);
    }
  }
}


void handleAddingRedBlack(Node* & Head, Node* ToAdd){
  Head->isRed=false;
  RecolorLineage(Head);
  if(Head!=ToAdd){
    ToAdd->isRed = true;
    RecolorLineage(ToAdd);
    if(!(ToAdd->getParent()->isRed)){
      return;
    }if(getUncle(ToAdd)!=nullptr){
      if(getUncle(ToAdd)->isRed){
	ToAdd->getParent()->isRed=false;
	RecolorLineage(ToAdd->getParent());
	getUncle(ToAdd)->isRed=false; 
        RecolorLineage(getUncle(ToAdd));
	getGrandparent(ToAdd)->isRed=true;
        RecolorLineage(getGrandparent(ToAdd));
	handleAddingRedBlack(Head,getGrandparent(ToAdd));
      }else{
	if(((ToAdd->getParent()->getLeft()==ToAdd)&&(getGrandparent(ToAdd)->getRight()==ToAdd->getParent()))||((ToAdd->getParent()->getRight()==ToAdd)&&(getGrandparent(ToAdd)->getLeft()==ToAdd->getParent()))){
	  if(ToAdd->getParent()->getLeft()==ToAdd){
	    rotRight(Head, ToAdd->getParent());
	    handleAddingRedBlack(Head,ToAdd->getRight());
	  }else{
 	    rotLeft(Head, ToAdd->getParent());
	    handleAddingRedBlack(Head,ToAdd->getLeft());
	  }
	}else{
	  Node* origParent=ToAdd->getParent();
	  Node* origGrandparent=getGrandparent(ToAdd);
	  if(ToAdd->getParent()->getLeft()==ToAdd){
	    rotRight(Head, getGrandparent(ToAdd));
	  }else{
	    rotLeft(Head, getGrandparent(ToAdd));
	  }
	  SwapCol(origParent);
	  RecolorLineage(origParent);
	  SwapCol(origGrandparent);
	  RecolorLineage(origGrandparent);
	}
      }
    }else if(getGrandparent(ToAdd)!=nullptr){
      if(((ToAdd->getParent()->getLeft()==ToAdd)&&(getGrandparent(ToAdd)->getRight()==ToAdd->getParent()))||((ToAdd->getParent()->getRight()==ToAdd)&&(getGrandparent(ToAdd)->getLeft()==ToAdd->getParent()))){
	if(ToAdd->getParent()->getLeft()==ToAdd){
	  rotRight(Head, ToAdd->getParent());
	  handleAddingRedBlack(Head,ToAdd->getRight());
	}else{
	  rotLeft(Head, ToAdd->getParent());
	  handleAddingRedBlack(Head,ToAdd->getLeft());
	}
      }else{
        Node* origParent=ToAdd->getParent();
	Node* origGrandparent=getGrandparent(ToAdd);
	if(ToAdd->getParent()->getLeft()==ToAdd){
	  rotRight(Head, getGrandparent(ToAdd));
	}else{
	  rotLeft(Head, getGrandparent(ToAdd));
	}
	SwapCol(origParent);
	RecolorLineage(origParent);
	SwapCol(origGrandparent);
	RecolorLineage(origGrandparent);
      }
    }
  }
}

int numberOfKids(Node* check){
  if(check==nullptr){
    return -1;
  }
  int num=0;
  if(check->getLeft()!=nullptr){
    num++;
  }
  if(check->getRight()!=nullptr){
    num++;
  }
  return num;
}

void transplant(Node* & Head, Node* Original, Node* New){
  if(Original->getParent()==nullptr){
    Head=New;
  }else if(Original==Original->getParent()->getLeft()){
    Original->getParent()->setLeft(New);
  }else{
    Original->getParent()->setRight(New);
  }
}

Node* findNode(Node* Head, int nodeVal){
  if(Head==nullptr){
    cout<<"ERROR! Head may be empty"<<endl;
    return nullptr;
  }else if((*(Head->getInt()))==nodeVal){
    return Head; 
  }else if((*(Head->getInt()))<nodeVal){
    if(Head->getRight()!=nullptr){
      return findNode(Head->getRight(), nodeVal);
    }else{
      cout<<"There is no Node with that value."<<endl;
      return nullptr;
    }
  }else if((*(Head->getInt()))>nodeVal){
    if(Head->getLeft()!=nullptr){
      return findNode(Head->getLeft(), nodeVal);
    }else{
      cout<<"There is no Node with that value."<<endl;
      return nullptr;
    }
  }else{
    cout<<"Something Went Wrong. Please try again."<<endl;
    return nullptr;
  }
}

void removeNode(Node* & Head, Node* toDelete){
  if(toDelete==nullptr){
    return;
  }
  if(toDelete->getNext()!=nullptr){
    ShiftTillLast(Head);
  }else if(numberOfKids(toDelete)==0){
    toDelete;
    int* tost = new int(0);
    Node* Nulby = new Node(tost);
    if(isLeft(toDelete)){
      toDelete->setLeft(Nulby);
    }else if(isRight(toDelete)){
      toDelete->setRight(Nulby);
    }else{
      Head=nullptr;
      delete toDelete;
      delete Nulby;
      return;
    }
    stepTwo(Head, toDelete, Nulby, Nulby);
  }else if(numberOfKids(toDelete)==1){
    Node* box;
    if(toDelete->getLeft()!=nullptr){
      box = toDelete->getLeft();
    }else if(toDelete->getRight()!=nullptr){
      box = toDelete->getRight();
    }else{
      cout<<"A Major Error Has Occured: 1 child, not left or right."<<endl;
      exit(2);
      return;
    }
    if(!(isLeft(toDelete)||isRight(toDelete))){
	Head=box;
	delete toDelete;
	Head->isRed=false;
	return;
     }
    stepTwo(Head, toDelete, box, box);
  }else if(numberOfKids(toDelete)==2){
    int* tost;
    Node* Nulby =GetSuccessor(toDelete)->getRight();
    bool isNil = false;
    if(Nulby==nullptr){
      tost = new int(0);
      Nulby = new Node(tost);
      GetSuccessor(toDelete)->setRight(Nulby);
    }
    stepTwo(Head, toDelete, GetSuccessor(toDelete), Nulby);
  }else{
    cout<<"A Major Error Has Occured: Number of children not between 0 and 2"<<endl;
    return;
  }
}

void normDelete(Node* & Head, Node* toDelete, Node* Replacement){
  if(isLeft(toDelete)){
    toDelete->getParent()->setLeft(Replacement);
  }else if(isRight(toDelete)){
    toDelete->getParent()->setRight(Replacement);
  }else{
    Head=Replacement;
    //cout<<"Angry Ron"<<endl;
    //cout<<"A Fatal Error has occured (parent mismatch or root)"<<endl;
  }
  delete toDelete;
  return;
}

void twokidDelete(Node* & Head, Node* toDelete, Node* Replacement){ 
  //Handles Replacement's kids to ensure they are safe
  if(isLeft(Replacement)){
    Replacement->getParent()->setLeft(Replacement->getRight());
  }else if(isRight(Replacement)){
    Replacement->getParent()->setRight(Replacement->getRight());
  }else{
    //cout<<"Corn on the Cob"<<endl;
    cout<<"A Fatal Error has occured (parent mismatch or root)"<<endl;
    cout<<"If this program does not crash, it is reccomended that you restart it."<<endl;
  }
  //Makes Replacement take ToDelete's place as ToDelete's parent's kid.
  if(isLeft(toDelete)){
    toDelete->getParent()->setLeft(Replacement);
  }else if(isRight(toDelete)){
    toDelete->getParent()->setRight(Replacement);
  }else{
    Head=Replacement;
    //cout<<"Worldly Eater"<<endl;
    //cout<<"A Fatal Error has occured (parent mismatch or root)"<<endl;
  }
  //Gives Replacement ToDelete's Kids
  Replacement->setLeft(toDelete->getLeft());
  Replacement->setRight(toDelete->getRight());
  //Takes ToDelete out behind the shed and fires a double barrel shotgun into their skull.
  delete toDelete;
  return;
}

//FIGures out which DELETE to use
void figDelete(Node* & Head, Node* toDelete, Node* Replacement, Node* x){
  //cout<<"Pre-Del"<<endl;
  //RecPrint(0,Head);
  if(Replacement==x){
    normDelete(Head, toDelete, Replacement);
  }else{
    twokidDelete(Head, toDelete, Replacement);
  }
  //cout<<"Post-Del"<<endl;
  //RecPrint(0,Head);
}

void NullWipedown(Node* & Head, Node* Replacement, Node* x){
  //cout<<"I AM GOING TO KILL THE QUEEN OF ENGLAND"<<endl;
  //RecPrint(0,Head);
  //cout<<"R: "<<*(Replacement->getInt())<<" x: "<<*(x->getInt())<<endl;
  if(Replacement!=nullptr){
    if(*(Replacement->getInt())==0){
      if(isLeft(Replacement)){
	Replacement->getParent()->setLeft(nullptr);
      }else if(isRight(Replacement)){
	Replacement->getParent()->setRight(nullptr);
      }else{
	Head=nullptr;
      }
      delete Replacement;
    }
  }
  if(*(x->getInt())==0){
    if(isLeft(x)){
      x->getParent()->setLeft(nullptr);
    }else if (isRight(x)){
      x->getParent()->setRight(nullptr);
    }else{
      Head=nullptr;
    }
    delete x;
  }
  //RecPrint(0,Head);
}

void stepTwo(Node* & Head, Node* toDelete, Node* Replacement, Node* x){
  //cout<<"StepTwo"<<endl;
  //RecPrint(0, Head);
  if(toDelete->isRed){
    if((*(Replacement->getInt())==0)||(Replacement->isRed)){
      figDelete(Head, toDelete, Replacement, x);
      NullWipedown(Head, Replacement, x);
      return;
    }else{
      Replacement->isRed = true;
      figDelete(Head, toDelete, Replacement, x);
      doFixup(Head, x);
    }
  }else{
    if(Replacement->isRed){
      Replacement->isRed=false;
      figDelete(Head, toDelete, Replacement, x);
      NullWipedown(Head, Replacement, x);
      return;
    }else{
      if(x==Head){
        figDelete(Head, toDelete, Replacement, x);
        NullWipedown(Head, Replacement, x);
	return;
      }else{
	figDelete(Head, toDelete, Replacement, x);
	doFixup(Head, x);
      }
    }
  }
}

//whoo boy it's time to get COMPLICATED!
void doFixup(Node* & Head, Node* x){
  //cout<<"x: "<<*(x->getInt())<<endl;
  int* tost;
  Node* Nulby;
  //RecPrint(0,Head);
  /*if(x==nullptr){
    return;
  }*/
  if(isRed(x)){ //case 0
    x->isRed=false;
    return;
  }else{
    Node* w=getSibling(x);
    if(w==nullptr){
      tost = new int(0);
      Nulby = new Node(tost);
      if(isLeft(x)){
	x->getParent()->setRight(Nulby);
      }else{
	x->getParent()->setLeft(Nulby);
      }
      w=Nulby;
      //cout<<"FRANK"<<endl;
    }
    while(true){
      //cout<<"Once more, X is "<<*(x->getInt())<<endl;
      //RecPrint(0,Head);
      if(w->isRed){ //case 1
	//cout<<"C1"<<endl;
	w->isRed=false;
	x->getParent()->isRed=true;
	if(isLeft(x)){
	  rotLeft(Head, x->getParent());
	}else{
	  rotRight(Head, x->getParent());
	}
        w=getSibling(x);
	if(w==nullptr){
	  tost = new int(0);
	  Nulby = new Node(tost);
	  if(isLeft(x)){
	    x->getParent()->setRight(Nulby);
	  }else{
	    x->getParent()->setLeft(Nulby);
	  }
	  w=Nulby;
	  //cout<<"TOBIAS"<<endl;
	}
	
      }else{
	int redkidcount=0;
	if(isRed(w->getLeft())){
	  redkidcount++;
	}
	if(isRed(w->getRight())){
	  redkidcount++;
	}
	if(redkidcount==0){ //case 2
	  //cout<<"C2"<<endl;
	  w->isRed=true;
	  if(*(x->getInt())==0){
	    Node* box = x->getParent();
	    if(isLeft(x)){
	      x->getParent()->setLeft(nullptr);
	    }else{
	      x->getParent()->setRight(nullptr);
	    }
	    delete x;
	    x=box;
	  }else{
	    x=x->getParent();
	  }
	  if(x->isRed){
	    x->isRed=false;
	    return;
	  }
	  if(Head==x){
	    return;
	  }
	  w=getSibling(x);
	}else if ((isLeft(x)&isRed(w->getRight()))||(isRight(x)&isRed(w->getLeft()))){ //if it made it this far, one is red. if it's this we go to 4 if not 3. also this is case 4
	  //cout<<"C4"<<endl;
	  //cout<<*(x->getInt())<<endl;
	  w->isRed=x->getParent()->isRed;
	  x->getParent()->isRed=false;
	  if(isLeft(x)){
	    w->getRight()->isRed=false;
	    rotLeft(Head, x->getParent());
	  }else if(isRight(x)){
	    w->getLeft()->isRed=false;
	    rotRight(Head, x->getParent());
	  }else{
	    cout<<"ERROR! SEC: CASE 4 ERR: X IS NOT LEFT OR RIGHT"<<endl;
	    exit(4);
	  }
	  if(*(x->getInt())==0){
	    if(isLeft(x)){
	      x->getParent()->setLeft(nullptr);
	    }else if(isRight(x)){
	      x->getParent()->setRight(nullptr);
	    }else{
	      cout<<"If you're seeing this, you're either reading the code, or something went wrong."<<endl;
	    }
	    delete x;
	  }
	  return;
	}else{ //case 3
	  //cout<<"C3"<<endl;
	  w->isRed=true;
	  if (isLeft(x)){
	    w->getLeft()->isRed=false;
	    rotRight(Head, w);
	    w=getSibling(x);
	  }else if (isRight(x)){
	    w->getRight()->isRed=false;
	    rotLeft(Head, w);
	    w=getSibling(x);
	  }else{
	    cout<<"ERROR! SEC: CASE 3 ERR:X IS ROOT."<<endl;
	    exit(3);
	  }
	}
      }
    }
  }
}

//technically I could just delete the last node in the list and get exactly the same result bcos the only variable we have to chain is an int but that's not how it's supposed to be in real life so...
void ShiftTillLast(Node* Head){
  if (Head==nullptr){
    return;
  }
  *(Head->getInt())=*(Head->getNext()->getInt());
  if (Head->getNext()->getNext()==nullptr){
    Node* box = Head->getNext();
    Head->setNext(nullptr);
    delete box;
  }else{
    ShiftTillLast(Head->getNext());
  }
}

//changes all nodes in a LinkedList to be the same color as the Head.
void RecolorLineage(Node* Head){
  if(Head->getNext()!=nullptr){
    Head->getNext()->isRed = Head->isRed;
    RecolorLineage(Head->getNext());
  }
}

//if a node is Red, it makes it black. if a node is Black, it makes it red.
void SwapCol(Node* Head){
  if(Head!=nullptr){
    Head->isRed=(!(Head->isRed));
  }
}

//Swaps out two Nodes. suprisingly useful.
void SwapNodes(Node* One, Node* Two){
  /*
  bool twoleft=isLeft(Two);
  Node* twoParent=Two->getParent();
  if(isLeft(One)){
    One->getParent->setLeft(Two);
  }else{
    One->getParent->setRight(Two);
  }
  if(twoLeft){
    twoParent->setLeft(One);
  }else{

  }
  */

  int holder = *(One->getInt());
  *(One->getInt()) = *(Two->getInt());
  *(Two->getInt()) = holder;
  Node* nodholder = One->getNext();
  One->setNext(Two->getNext());
  Two->setNext(nodholder);
  
  
  /*
  Node* oneLeft = One->getLeft();
  Node* oneRight = One->getRight();
  Node* twoLeft = Two->getLeft();
  Node* twoRight = Two->getRight();
  Node* parBox = One->getParent()
  Node box = *One;
  *One = *Two;
  *Two = box;
  One->setLeft(twoLeft);
  One->setRight(twoRight);
  Two->setLeft(oneLeft);
  Two->setRight(oneRight);
  
  One->setParent(Two->getParent());
  Two->setParent(parBox);
  */
}

//Successor Getter
Node* GetSuccessor(Node* Cur){
  return getLastLeft(Cur->getRight()); 
}

//returns the deepest leftwards child.
Node* getLastLeft(Node* Cur){
  if(Cur->getLeft()!=nullptr){
    return getLastLeft(Cur->getLeft());
  }else{
    return Cur;
  }
}

//integer Getter
int getInt(){
  bool acin=false;
  int Integ;
  while (acin==false){
    cout<<"Please Enter Integer: "<<endl;
    cin>>Integ;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  return Integ;
}

//Number Searcher
void DetectNumb(Node* Cur, int Check, int Depth){
  if((*(Cur->getInt()))==Check){
    if(Cur->getNext()==nullptr){
      if(Cur->isRed){
	cout<<"\033[31m";
      }else{
	cout<<"\033[0m";
      }
      cout<<"That number appears in the tree! it appears only once."<<endl;
      cout<<"It's parent node was \033[0m";
    }else{
      if(Cur->isRed){
	cout<<"\033[31m";
      }else{
	cout<<"\033[0m";
      }
      int Dep = 0;
      cout<<"That number appears in the tree! it appears "<<getDepth(Cur,Dep)<<" times."<<endl;
      cout<<"It's parent node was \033[0m";
    }
  }else if((*(Cur->getInt()))<Check){
    if(Cur->getRight()!=nullptr){
      DetectNumb(Cur->getRight(),Check,Depth+1);
    }else{
      cout<<"There is no Node with that value."<<endl;
      cout<<"If it were, its parent node would be ";
    }
  }else if((*(Cur->getInt()))>Check){
    if(Cur->getLeft()!=nullptr){
      DetectNumb(Cur->getLeft(),Check,Depth+1);
    }else{
      cout<<"There is no Node with that value."<<endl;
      cout<<"If it were, its parent node would be ";
    }
  }
  if(Cur->isRed){
    cout<<"\033[31m";
  }else{
    cout<<"\033[0m";
  }
  cout<<"a node containing the number "<<(*(Cur->getInt()));
  if(Depth!=0){
    cout<<", Child of ";
  }else{
    cout<<", Which is the root node.";
  }
  cout<<"\033[0m"<<endl;
}

//intended to get the depth of a LinkedList
int getDepth(Node* Cur, int & depth){
  depth=depth+1;
  if(Cur->getNext()!=nullptr){
    return getDepth(Cur->getNext(), depth);
  }else{
    return depth;
  }
}

//Adds numbers to the Head node from a file
void addFromFile(Node* & head){
  ifstream myFile;
  char* filename = new char[101];
  for(int i=0; i<101; i++){
    filename[i]='\0';
  }
  getStringFromInput(filename);
  myFile.open(filename);
  if(myFile.is_open()){
    int got;
    try{
      while(myFile>>got){
	if(head!=nullptr){
	  addNodeRecursive(head,head, new Node(new int(got)));
	}else{
	  head=new Node(new int(got));
	}
      }
    }catch(...){
      cout<<"Something Went Wrong. You are strongly advised to use PRINT to check the structure of the Tree as data may have been corrupted"<<endl;
    }
  }else{
    cout<<"ERROR! NO VALID FILE!"<<endl;
    return;
  }
  delete[] filename;
  myFile.close();
}

void rotLeft(Node* & Head,Node* Cur){
  /*
  if(Cur->isRed){
    cout<<"\033[31m";
  }else{
    cout<<"\033[0m";
  }
  cout<<"I Am Alpharius: "<<*(Cur->getInt())<<"\033[0m"<<endl;
  //*/
  Node* ParBox=Cur->getParent();
  Node* OrigRight = Cur->getRight();
  Cur->setRight(OrigRight->getLeft());
  if (ParBox!=nullptr){
    if(Cur==Cur->getParent()->getLeft()){
      ParBox->setLeft(OrigRight);
    }else{
      ParBox->setRight(OrigRight);
    }
  }else{
    Head=OrigRight;
    Head->setParent(nullptr);
  }
  OrigRight->setLeft(Cur);
}

void rotRight(Node* & Head, Node* Cur){
  /*
  if(Cur->isRed){
    cout<<"\033[31m";
  }else{
    cout<<"\033[0m";
  }
  cout<<"I Am Omegon: "<<*(Cur->getInt())<<"\033[0m"<<endl;
  //*/
  Node* ParBox=Cur->getParent();
  Node* OrigLeft = Cur->getLeft();
  Cur->setLeft(OrigLeft->getRight());
  if (ParBox!=nullptr){
    if(Cur==Cur->getParent()->getRight()){
      ParBox->setRight(OrigLeft);
    }else{
      ParBox->setLeft(OrigLeft);
    }   
  }else{  
    Head=OrigLeft;
    Head->setParent(nullptr);
  }
  OrigLeft->setRight(Cur);
}
