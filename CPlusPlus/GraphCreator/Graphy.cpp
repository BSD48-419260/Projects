#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;


struct node{
 public:
  node(){
    for(int i=0; i<16; i++){
      name[i] = '\0';
    }
    lowestFromRoute = nullptr;
    connectionNum =0;
    conVal = nullptr;
    connections = nullptr;
  }
  
  char* getName(){
    return name;
  }
  
  void setName(char* newName){
    for(int i=0; i<16; i++){
      name[i]='\0';
    }
    strncpy(name, newName, 15);
  }
  
  node* getLowest(){
    return lowestFromRoute;
  }
  
  void setLowest(node* newLowest){
    lowestFromRoute = newLowest;
  }

  void addConnection(int newVal, node* newConnect, bool check = true){
    if(check){
      if(connectionNum!=0){
	for(int i=0; i<connectionNum; i++){
	  if(connections[i] == newConnect){
	    conVal[i] = newVal;
	    return;
	  }
	}
      }
    }
    if(connectionNum!=0){
      int* newConVals= new int[connectionNum+1];
      node** newCons = new node*[connectionNum+1];
      for(int i=0; i<connectionNum; i++){
	newConVals[i] = conVal[i];
	newCons[i] = connections[i];
      }
      newConVals[connectionNum] = newVal;
      newCons[connectionNum] = newConnect;
      delete[] conVal;
      delete[] connections;
      conVal = newConVals;
      connections = newCons;
      connectionNum++;
    }else{
      conVal = new int[1];
      connections = new node*[1];
      conVal[0] = newVal;
      connections[0] = newConnect;
      connectionNum=1;
    }
    return;
  }

  bool isConnected(node* toTest){
    for(int i=0; i<connectionNum; i++){
      if(connections[i]=toTest){
	return true;
      }
    }
    return false;
  }
  
 private:
  char* name = new char[21];
  node* lowestFromRoute = nullptr;
  int connectionNum =0;
  int* conVal = nullptr;
  node** connections = nullptr;
};


//function signatures
void getStringFromInput(char* inpstring);
void printConnections(node* box);
int lengthOfStr(char* stringy);
void addNode(node* box);

//main.
int main(){
  /*
  srand(time(0));
  node* box = new node[20];
  for(int i=0; i<20; i++){
    box[i]=nullptr;
  }
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
  char inpstring[16];
  char gremlin[16];
  //primary loop
  while(notQuit){
    try{
      //robust-ish command handler.
      cout<<"Please input a command. (Valid commands: ADD, ADDFILE, DELETE, SEARCH, PRINT, QUIT)"<<endl;
      for(int i=0; i<16; i++){
	inpstring[i]='\0';
      }
      cin.getline(gremlin, sizeof(gremlin), '\n');
      strncpy(inpstring, gremlin, 16);
      if(cin.fail()){
	cout<<"Something went wrong. Please try again."<<endl;
	cin.clear();
	cin.ignore(100000,'\n');
      }else if (strcmp(inpstring,"ADD")==0){
	
      }else if (strcmp(inpstring,"DELETE")==0){
	
      }else if (strcmp(inpstring,"SEARCH")==0){
        
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
  cout<<"Have a wonderful day."<<endl;
  */
  node* box = new node[20];
  for(int i=0; i<20; i++){
    box[i]=nullptr;
  }
  
  return 0; 
}

//string getter. techically only needed once but I just really like having it.
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

void printConnections(node* box){
  int lastindex = -1;
  for(int i=0; i<20; i++){
    if(box[i] == nullptr){
      lastindex = i;
      i=21;
    }
    lastindex=20;
  }
  if(lastindex==0){
    cout<<"There are no nodes.";
    return;
  }
  cout<<"     |";
  for(int i=0; i<lastindex; i++){
    for(int j=0; j<5; j++){
      if(box[i]->getName()[j]!='\0'){
	cout<<box[i]->getName()[j];
      }else{ 
	cout<<" ";
      }
    }
    cout<<"|";
  }
  cout<<endl;
  for(int i=0; i<lastindex; i++){
    for(int j=0; j<5; j++){
      if(box[i]->getName()[j]!='\0'){
	cout<<box[i]->getName()[j];
      }else{ 
	cout<<" ";
      }
    }
    cout<<"|";

    cout<<endl;
  }
  
  
}

int lengthOfStr(char* stringy){
  for(int i=0; i<15; i++){
    if(stringy[i]=='\0'){
      return i;
    }
  }
  return 15;
}

void addNode(node* box){
  node* theodore = new node();
  
}
