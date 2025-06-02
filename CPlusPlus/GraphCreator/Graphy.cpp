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
    connectionNum =0;
    conVal = nullptr;
    connections = nullptr;
  }

  ~node(){
    delete name;
    delete[] conVal;
    delete[] connections;
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
      int index = getIndex(toCut);
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

  int getNumberOfConnections(){
    return connectionNum;
  }

  node** getConnections(){
    return connections;
  }

  int* getConnectionValues(){
    return conVal;
  }
 private:
  char* name = new char[21];
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
void findPath(node** box);
void Dijkstra(node** box, node* origin, node* target);
int getIndex(node* toTest, node** box);
void printPath(int* dists, int* shortBox, node** box, int target);

//main.
int main(){
  //technically having 20 be a prefined number is unnecesary, but I'm working on a deadline so...
  node** box = new node*[20];
  for(int i=0; i<20; i++){
    box[i]=nullptr;
  }
  
  cout<<"==========================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<" _____            _    _         "<<endl;
  cout<<"/ ___ \\          / \\  / \\        "<<endl;
  cout<<"| | /__\\        / _ \\/ _ \\       "<<endl;
  cout<<"| | ___        / / \\  / \\ \\      "<<endl;
  cout<<"| | \\ |        | |  \\/  | |      "<<endl;
  cout<<"| | | |        | |      | |      "<<endl;
  cout<<"| |_| |        | |      | |      "<<endl;
  cout<<"\\_____/ raph  /___\\    /___\\aker "<<endl;
  bool notQuit=true;
  char inpstring[16];
  char gremlin[16];
  //primary loop
  //*
  while(notQuit){
    try{
      //robust-ish command handler.
      cout<<"Please input a command. (Valid commands: ADD, DELETE, CONNECT, CUT, PATH, PRINT, QUIT)"<<endl;
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
	addNode(box);
      }else if (strcmp(inpstring,"DELETE")==0){
	cutNode(box);
      }else if (strcmp(inpstring,"CONNECT")==0){
	addConnection(box);
      }else if (strcmp(inpstring,"CUT")==0){
        cutConnection(box);
      }else if (strcmp(inpstring,"PATH")==0){
	findPath(box);        
      }else if (strcmp(inpstring,"PRINT")==0){
	cout<<"Names:"<<endl;
	printBox(box);
	cout<<"Connections"<<endl;
	printConnections(box);
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
  cout<<"Have a terrific day."<<endl;
  /*
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
  //*/
  return 0; 
}

//string getter.
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
    cout<<"There are no nodes."<<endl;
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
	  cout<<"OvFlw";
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
      cout<<i+1<<": "<<box[i]->getName()<<endl;
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
      char* namestr = new char[16];
      cout<<"Please input name for new node."<<endl;
      getStringFromInput(namestr);
      for(int j=0; j<20; j++){
	if(box[j]!=nullptr){
	  if(strcmp(box[j]->getName(),namestr)==0){
	    delete[] namestr;
	    cout<<"You cannot have two nodes with the same name!"<<endl;
	    return;
	  }
	}
      }
      node* theodore = new node();
      theodore->setName(namestr);
      delete[] namestr;
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
    if(box[i]!=nullptr){
      if(strcmp(box[i]->getName(),newName)==0){
	origin=box[i];
	i=21;
      }
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
    if(box[i]!=nullptr){
      if(strcmp(box[i]->getName(),newName)==0){
	dest=box[i];
	i=21;
      }
    }
  }
  if(dest==nullptr){
    cout<<"There is no Node by that name."<<endl;
    return;
  }
  if(origin==dest){
    cout<<"You cannot make a connection to yourself."<<endl;
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
  delete[] newName;
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
  cin.ignore(100000,'\n');
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
  int index = -1;
  for(int i=0; i<20; i++){
    if(box[i]!=nullptr){
      if(strcmp(box[i]->getName(),newName)==0){
	deadMeat=box[i];
	index = i;
	i=21;
      }
    }
  }
  if(deadMeat==nullptr){
    cout<<"There is no Node by that name."<<endl;
    return;
  }
  for(int i=0; i<20; i++){
    if(box[i]!=nullptr){
      box[i]->cutConnection(deadMeat,false);
    }
  }
  delete deadMeat;
  box[index]=nullptr;
  for(int i=0; i<19; i++){
    if(box[i]==nullptr){
      if(box[i+1]!=nullptr){
	box[i] = box[i+1];
	box[i+1] = nullptr;
      }
    }
  }
  delete[] newName;
}

void cutConnection(node** box){
  printBox(box);
  char* newName = new char[16];
  for(int i=0; i<16; i++){
    newName[i]='\0';
  }
  cout<<"Please input the name of the node from which the connection is to be cut."<<endl;
  getStringFromInput(newName);
  node* Orig = nullptr;
  for(int i=0; i<20; i++){
    if(box[i]!=nullptr){
      if(strcmp(box[i]->getName(),newName)==0){
	Orig=box[i];
	i=21;
      }
    }
  }
  if(Orig==nullptr){
    cout<<"There is no Node by that name."<<endl;
    return;
  }
  cout<<"Please input the name of the destination node for the cut connection"<<endl;
  getStringFromInput(newName);
  node* Targ = nullptr;
  for(int i=0; i<20; i++){
    if(box[i]!=nullptr){
      if(strcmp(box[i]->getName(),newName)==0){
	Targ=box[i];
	i=21;
      }
    }
  }
  if(Targ==nullptr){
    cout<<"There is no Node by that name."<<endl;
    return;
  }
  Orig->cutConnection(Targ);
  delete[] newName;
}

void findPath(node** box){
  printBox(box);
  char* newName = new char[16];
  for(int i=0; i<16; i++){
    newName[i]='\0';
  }
  cout<<"Please input the name of node to start the path at."<<endl;
  getStringFromInput(newName);
  node* origin = nullptr;
  for(int i=0; i<20; i++){
    if(box[i]!=nullptr){
      if(strcmp(box[i]->getName(),newName)==0){
	origin=box[i];
	i=21;
      }
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
    if(box[i]!=nullptr){
      if(strcmp(box[i]->getName(),newName)==0){
	dest=box[i];
	i=21;
      }
    }
  }
  if(dest==nullptr){
    cout<<"There is no Node by that name."<<endl;
    return;
  }
  delete[] newName;
  Dijkstra(box, origin, dest);
  
}

void Dijkstra(node** box, node* origin, node* target){
  int* dist = new int[20];
  int* shortestPrev = new int[20];
  bool* explored = new bool[20];
  for(int i=0; i<20; i++){
    dist[i]=-1;
    shortestPrev[i] = -1;
    explored[i] = false;
  }
  int originIndex = getIndex(origin, box);
  int targetIndex = getIndex(target, box);
  dist[originIndex]=0;
  bool progress = true;
  while(!explored[targetIndex]){
    if(progress==false){
      cout<<"Looks like there isn't any path between the two."<<endl;
      delete[] dist;
      delete[] shortestPrev;
      delete[] explored;
      return;
    }
    progress=!progress;
    int lowestIndex = -1;
    /*
    for(int i=0; i<20; i++){
      if(box[i]!=nullptr){
	cout<<"Cell: "<<i<<", Name: "<<box[i]->getName()<<", Explored: "<<explored[i]<<", Dist: "<<dist[i]<<", shorestPrev: "<<shortestPrev[i]<<endl;
      }
    }
    */
    for(int i=0; i<20; i++){
      if(box[i]!=nullptr){
	//cout<<i<<", "<<box[i]->getName()<<". "<<(dist[i]<dist[lowestIndex])<<" AND "<<(dist[i]!=-1)<<" AND "<<(explored[i]==false)<<endl;
	if((lowestIndex==-1)&&(dist[i]!=-1)&&(explored[i]==false)){
	  lowestIndex=i;
	}else{
	  if((dist[i]<dist[lowestIndex])&&(dist[i]!=-1)&&(explored[i]==false)){
	    lowestIndex=i;
	  }
	}
      }
    }
    //cout<<"LowestIndex: "<<lowestIndex<<endl;
    if(lowestIndex==-1){
      cout<<"Error! No path found."<<endl;
      delete[] dist;
      delete[] shortestPrev;
      delete[] explored;
    }
    explored[lowestIndex]=true;
    if(lowestIndex==targetIndex){
      cout<<"Path found!"<<endl;
      printPath(dist, shortestPrev, box, targetIndex);
      cout<<"leading to -wait no, that's our destination!"<<endl;
    }else{
      //cout<<"NumberOfCons: "<<box[lowestIndex]->getNumberOfConnections()<<endl;
      for(int i=0; i<box[lowestIndex]->getNumberOfConnections();i++){
	progress=true;
	int conIndex = getIndex(box[lowestIndex]->getConnections()[i],box);
	//cout<<"LowIndex"<<lowestIndex<<", "<<box[lowestIndex]->getName()<<"ConIndex: "<<conIndex<<", "<<box[conIndex]->getName()<<endl;
	if((dist[conIndex]==-1)||(dist[lowestIndex]+box[lowestIndex]->getConnectionValues()[i] < dist[conIndex])){
	    dist[conIndex]=dist[lowestIndex]+box[lowestIndex]->getConnectionValues()[i];
	    shortestPrev[conIndex]=lowestIndex;
	}
      }
    }
  }
  delete[] dist;
  delete[] shortestPrev;
  delete[] explored;
}

int getIndex(node* toTest, node** box){
  for(int i=0; i<20; i++){
    if(box[i]==toTest){
      return i;
    }
  }
  return -1;
}

void printPath(int* dists, int* shortBox,node** box, int target){
  if(target!=-1){
    printPath(dists, shortBox, box, shortBox[target]);
  }else{
    //cout<<"NULL!"<<endl;
    return;
  }
  if(shortBox[target]!=-1){
    cout<<"leading to "<<box[target]->getName()<<", which is "<<dists[target]<<" from the origin, with a path"<< endl;
  }else{
    cout<<box[target]->getName()<<", which is the the origin, has a path "<<endl;
  }
}
