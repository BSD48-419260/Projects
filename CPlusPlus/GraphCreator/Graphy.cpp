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

  void cutConnection(node* toCut, bool print=true){
    if(!isConnected(toCut)){
      if(print){
	cout<<"Those nodes are not connected."<<endl;
      }
      return;
    }
    if(connectionNum>1){
      index = getIndex(toCut);
      int* newConVals= new int[connectionNum-1];
      node** newCons = new node*[connectionNum-1];
      bool atIndex=false;
      for(int i=0; i<connectionNum; i++){
	if(atIndex==false){
	  if(i!=index){
	    newConVals[i] = conVal[i];
	    newCons[i] = connections[i];
	  }else{
	    atIndex=true;
	    newConVals[i] = conVal[i+1];
	    newCons[i] = connections[i+1];
	  }
	}else{
	  newConVals[i] = conVal[i+1];
	  newCons[i] = connections[i+1];
	}
      }
      
      newConVals[connectionNum] = newVal;
      newCons[connectionNum] = newConnect;
      delete[] conVal;
      delete[] connections;
      conVal = newConVals;
      connections = newCons;
      connectionNum--;
    }else{
      delete conVal;
      delete connections;
      conVal = nullptr;
      connections = nullptr;
      connectionNum=0;
    }
    return;
  }
  
  bool isConnected(node* toTest){
    for(int i=0; i<connectionNum; i++){
      if(connections[i]==toTest){
	return true;
      }
    }
    return false;
  }

  int getValue(node* toTest){
    for(int i=0; i<connectionNum; i++){
      if(connections[i]==toTest){
	return conVal[i];
      }
    }
    return -1;
  }

  int getIndex(node* toTest){
    for(int i=0; i<connectionNum; i++){
      if(connections[i]==toTest){
	return i;
      }
    }
    return -1;
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
void printConnections(node** box);
void printBox(node** box);
int lengthOfStr(char* stringy);
void addNode(node** box);
void addConnection(node** box);
int getInt();
void cutNode(node** box);
void cutConnection(node** box);

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
  node** box = new node*[20];
  for(int i=0; i<20; i++){
    box[i]=nullptr;
  }
  addNode(box);
  addNode(box);
  addNode(box);
  addNode(box);
  addNode(box);
  addNode(box);
  
  box[0]->addConnection(1, box[1]);
  box[1]->addConnection(10, box[2]);
  box[2]->addConnection(100, box[3]);
  box[3]->addConnection(1000, box[4]);
  box[4]->addConnection(10000, box[5]);
  box[5]->addConnection(100000, box[0]);
  
  printConnections(box);
  printBox(box);
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

void printConnections(node** box){
  int lastindex = -1;
  for(int i=0; i<20; i++){
    if(box[i] == nullptr){
      lastindex = i;
      i=21;
    }
  }
  if(lastindex==-1){
    lastindex=20;
  }
  if(lastindex==0){
    cout<<"There are no nodes.";
    return;
  }
  cout<<"Adj? |";
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
    for(int j=0; j<lastindex; j++){
      if(box[i]==box[j]){
	cout<<"  =  ";
      }else if(box[i]->isConnected(box[j])){
	int value = box[i]->getValue(box[j]);
	if(value<10){
	  cout<<"  "<<value<<"  ";
	}else if(value<100){
	  cout<<" "<<value<<"  ";
	}else if(value<1000){
	  cout<<" "<<value<<" ";
	}else if(value<10000){
	  cout<<value<<" ";
	}else if(value<100000){
	  cout<<value;
	}else{
	  cout<<"OvrFlW";
	}
      }else{
	cout<<"  -  ";
      }
      cout<<'|';
    }
    
    cout<<endl;
  }
}

void printBox(node** box){
  for(int i=0; i<20; i++){
    if(box[i]!=nullptr){
      cout<<i+1<<": "<<box[i]->getName();
    }else{
      return;
    }
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

void addNode(node** box){
  for(int i=0; i<20; i++){
    if(box[i]==nullptr){
      node* theodore = new node();
      char* namestr = new char[16];
      cout<<"Please input name for new node."<<endl;
      getStringFromInput(namestr);
      theodore->setName(namestr);
      delete namestr;
      box[i]=theodore;
      return;
    }
  }
  cout<<"No Open Space!"<<endl;
}

void addConnection(node** box){
  printBox(box);
  char* newName = new char[16];
  for(int i=0; i<16; i++){
    newName[i]='\0';
  }
  cout<<"Please input the name of the node to make a one-way connection from."<<endl;
  getStringFromInput(newName);
  node* origin = nullptr;
  for(int i=0; i<20; i++){
    if(strcmp(box[i],newName)==0){
      origin=box[i];
      i=21;
    }
  }
  if(origin==nullptr){
    cout<<"There is no node by that name."<<endl;
    return;
  }
  cout<<"Please input the name of the destination node."<<endl;
  getStringFromInput(newName);
  node* dest = nullptr;
  for(int i=0; i<20; i++){
    if(strcmp(box[i],newName)==0){
      dest=box[i];
      i=21;
    }
  }
  if(dest==nullptr){
    cout<<"There is no Node by that name."<<endl;
    return;
  }
  cout<<"Please input the distance between the two in generic units."<<endl;
  bool acin=false;
  int value=-1;
  while(!acin){
    value = getInt();
    if(value>=0){
      acin=true;
    }else{
      cout<<"Negative numbers are not allowed."<<endl;
    }
  }
  origin->addConnection(value, dest);
}


int getInt(){
  bool acin=false;
  int Integ;
  while (acin==false){
    cout<<"A positive, whole number, please: "<<endl;
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

void cutNode(node** box){
  printBox(box);
  char* newName = new char[16];
  for(int i=0; i<16; i++){
    newName[i]='\0';
  }
  cout<<"Please input the name of the node to be removed."<<endl;
  getStringFromInput(newName);
  node* deadMeat = nullptr;
  for(int i=0; i<20; i++){
    if(strcmp(box[i],newName)==0){
      deadMeat=box[i];
      i=21;
    }
  }
  if(dest==nullptr){
    cout<<"There is no Node by that name."<<endl;
    return;
  }
  for(int i=0; i<20; i++){
    box[i]->cutConnection();
  }
}

void cutConnection(node** box){

}
