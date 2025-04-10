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
void addNode(Node* & Head, int ToAdd);
void addNodeRecursive(Node* & Head, Node* Cur, Node* ToAdd);
void handleAddingRedBlack(Node* & Head, Node* ToAdd);
void repairTree(Node* & Head, Node* Cur);
Node* removeNode(Node* Head, int nodeVal);
void ShiftTillLast(Node* Head);
void RecolorLineage(Node* Head);
void SwapCol(Node* Head);
void SwapInts(Node* One, Node* Two);
Node* GetSucessor(Node* Cur);
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
  cout<<"_____     ___________"<<endl;
  cout<<"\\    \\    \\___   ___/"<<endl;
  cout<<" | |\\ \\       | |"<<endl;
  cout<<" | |/ /       | |"<<endl;
  cout<<" |   |        | |"<<endl;
  cout<<" | |\\ \\       | |"<<endl;
  cout<<" | |/ /       | |"<<endl;
  cout<<"/____/ inary /___\\ree "<<endl;
  bool notQuit=true;
  char inpstring[10];
  //primary loop
  while(notQuit){
    try{
      //robust command handler.
      cout<<"Please input a command. (Valid commands: ADD, ADDFILE, DELETE, SEARCH, PRINT, QUIT)"<<endl;
      for(int i=0; i<10; i++){
	inpstring[i]='\0';
      }
      cin >> inpstring;
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
	Head=removeNode(Head, getInt());
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
  for(int i=0; i<depth;i++){
    cout<<"\t";
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

//Adder function preamble
void addNode(Node* & Head, int ToAdd){
  int Integ;
  for(int i=0; i<ToAdd; i++){
    bool acin=false;
    while (acin==false){
      cin>>Integ;
      if(cin.fail()){
	cout<<"I think you did something wrong. please try again."<<endl;
	  cin.clear();
	  cin.ignore(100000,'\n');
      }else{
	if(Head!=nullptr){
	  addNodeRecursive(Head, Head, new Node(new int(Integ)));
	}else{
	  Head = new Node(new int(Integ));
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
  cout<<"----------------"<<endl;
  RecPrint(0,Head);
  cout<<"----------------"<<endl;
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
	// ((ToAdd->getParent()->getLeft()==ToAdd)&&(getGrandparent(ToAdd)->getRight()==ToAdd->getParent()))
	//                                                                                                    ((ToAdd->getParent()->getRight()==ToAdd)&&(getGrandparent(ToAdd)->getLeft()==ToAdd->getParent()))
	if(((ToAdd->getParent()->getLeft()==ToAdd)&&(getGrandparent(ToAdd)->getRight()==ToAdd->getParent()))||((ToAdd->getParent()->getRight()==ToAdd)&&(getGrandparent(ToAdd)->getLeft()==ToAdd->getParent()))){
	  if(ToAdd->getParent()->getLeft()==ToAdd){
	    rotRight(Head, ToAdd->getParent());
	    //SwapCol(ToAdd->getRight());
	    handleAddingRedBlack(Head,ToAdd->getRight());
	  }else{
 	    rotLeft(Head, ToAdd->getParent());
	    //SwapCol(ToAdd->getLeft());
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
	  //SwapCol(ToAdd->getRight());
	  handleAddingRedBlack(Head,ToAdd->getRight());
	}else{
	  rotLeft(Head, ToAdd->getParent());
	  //SwapCol(ToAdd->getLeft());
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
  cout<<"----------------"<<endl;
  RecPrint(0,Head);
  cout<<"----------------"<<endl;
}

void repairTree(Node* & Head, Node* Cur){
  
}

//recursive node remover
Node* removeNode(Node* Head,int nodeVal){
  if(Head==nullptr){
    cout<<"ERROR! Head may be empty"<<endl;
    return nullptr;
  }else if((*(Head->getInt()))==nodeVal){
    if(Head->getNext()!=nullptr){
      ShiftTillLast(Head);
    }else{
      if(Head->getLeft()==nullptr){
	Node* box = Head->getRight();
	delete Head;
	return box;
      }else if (Head->getRight()==nullptr){
	Node* box = Head->getLeft();
	delete Head;
	return box;
      }else{
	Node* box = GetSucessor(Head);
	SwapInts(Head, box);
	Head->setRight(removeNode(Head->getRight(),nodeVal));
      }
    }
  }else if((*(Head->getInt()))<nodeVal){
    if(Head->getRight()!=nullptr){
      Head->setRight(removeNode(Head->getRight(), nodeVal));
    }else{
      cout<<"There is no Node with that value."<<endl;
    }
  }else if((*(Head->getInt()))>nodeVal){
    if(Head->getLeft()!=nullptr){
      Head->setLeft(removeNode(Head->getLeft(), nodeVal));
    }else{
      cout<<"There is no Node with that value."<<endl;
    }
  }else{
    cout<<"Something Went Wrong. Please try again."<<endl;
  }
  return Head;
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

//Swaps out the contents of two Nodes. suprisingly useful.
void SwapInts(Node* One, Node* Two){
  int holder = *(One->getInt());
  *(One->getInt()) = *(Two->getInt());
  *(Two->getInt()) = holder;
  Node* nodholder = One->getNext();
  One->setNext(Two->getNext());
  Two->setNext(nodholder);
}

//Successor Getter
Node* GetSucessor(Node* Cur){
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
      cout<<"That number appears in the tree! it appears only once."<<endl;
      cout<<"It's parent node was ";
    }else{
      int Dep = 0;
      cout<<"That number appears in the tree! it appears "<<getDepth(Cur,Dep)<<" times."<<endl;
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
  cout<<"a node containing the number "<<(*(Cur->getInt()));
  if(Depth!=0){
    cout<<", Child of ";
  }else{
    cout<<", Which is the root node.";
  }
  cout<<endl;
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
      cout<<"Something Went Wrong. You are strongly advised to use PRINT to check the structure of the Binary Tree as data may have been corrupted"<<endl;
    }
    
  }else{
    cout<<"ERROR! NO VALID FILE!"<<endl;
    return;
  }
  myFile.close();
}

void rotLeft(Node* & Head,Node* Cur){
  cout<<"I Am Alpharius: "<<*(Cur->getInt())<<endl;
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
  cout<<"I Am Omegon: "<<*(Cur->getInt())<<endl;
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
