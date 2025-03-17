#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
#include "node.cpp"
using namespace std;

//function signatures
void getStringFromInput(char* inpstring);
void RecPrint(int depth, Node* Head);
void printList(Node* Head);
void addNode(Node* & Head, int ToAdd);
void addNodeRecursive(Node* Cur, Node* ToAdd);
Node* removeNode(Node* Head, int nodeVal);
void ShiftTillLast(Node* Head);
void SwapInts(Node* One, Node* Two);
Node* GetSucessor(Node* Cur);
Node* getLastLeft(Node* Cur);
int getInt();
void DetectNumb(Node* Cur, int Check, int Depth);
int getDepth(Node* Cur, int & depth);
void addFromFile(Node* & head);

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
	cout<<"WORKING ON THIS STILL"<<endl;
      }else if (strcmp(inpstring,"DELETE")==0){
	cout<<"To Cancel, Input the number 0"<<endl;
	Head=removeNode(Head, getInt());
      }else if (strcmp(inpstring,"SEARCH")==0){
        DetectNumb(Head, getInt(), 0);
      }else if (strcmp(inpstring,"PRINT")==0){
	RecPrint(0, Head);
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
	  addNodeRecursive(Head, new Node(new int(Integ)));
	}else{
	  Head = new Node(new int(Integ));
	}
	acin=true;
      }
    }
  }
}


//actual adder function.
void addNodeRecursive(Node* Cur, Node* ToAdd){
  if(Cur==nullptr){
    Cur=ToAdd;
  }else if(*(ToAdd->getInt())<*(Cur->getInt())){
    if(Cur->getLeft()==nullptr){
      Cur->setLeft(ToAdd);
    }else{
      addNodeRecursive(Cur->getLeft(),ToAdd);
    }
  }else if(*(ToAdd->getInt())>*(Cur->getInt())){
    if(Cur->getRight()==nullptr){
      Cur->setRight(ToAdd);
    }else{
      addNodeRecursive(Cur->getRight(),ToAdd);
    }
  }else{
    if(Cur->getNext()==nullptr){
      Cur->setNext(ToAdd);
    }else{
      addNodeRecursive(Cur->getNext(),ToAdd);
    }
  }
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
	  addNodeRecursive(head, new Node(new int(got)));
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
