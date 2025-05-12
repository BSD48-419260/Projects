#include <iostream>
#include <cmath>
#include <fstream>
#include <cstring>
using namespace std;

//function signatures
int parentIndex(int index);
int leftIndex(int index);
int rightIndex(int index);
int earliestOpenIndex(int* heapofints, int sizeofarray);
int getInt();
void addNode(int*& heapofints, int sizeofarray, int toadd);
void deleteNode(int*& heapofints, int sizeofarray, int index);
void bubbleTo(int*& heapofints, int index);
void swap(int& one, int& two);
void printStraight(int* heapofints,int addon,int sizeofarray,bool shownum);
void RecPrint(int pos, int depth, int sizeofarray,int* heapofints);
void addFromFile(int* heapofints, int sizeofarray);

int main(){
  //oh boy
  int* heapofints = new int[255];
  int sizeofarray=255;
  for(int i=0; i<sizeofarray; i++){
    heapofints[i]=-1;
  }
  
  
  cout<<"==========================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<"_____    _____ _____"<<endl;
  cout<<"\\   /    \\   / \\   /"<<endl;
  cout<<" | |      | |   | |"<<endl;
  cout<<" | |      | |___| |"<<endl;
  cout<<" | |      | _____ |"<<endl;
  cout<<" | |      | |   | |"<<endl;
  cout<<" | |      | |   | |"<<endl;
  cout<<"/___\\ nt /___\\ /___\\eap"<<endl;
  bool notQuit=true;
  char inpstring[10];
  //primary loop
  while(notQuit){
    try{
      //robust command handler.
      cout<<"Please input a command. (Valid commands: ADD, ADDFILE, DELETE, DELETEALL, PRINT, QUIT)"<<endl;
      for(int i=0; i<10; i++){
	inpstring[i]='\0';
      }
      cin >> inpstring;
      if(cin.fail()){
	cout<<"Something went wrong. Please try again."<<endl;
	cin.clear();
	cin.ignore(100000,'\n');
      }else if (strcmp(inpstring,"ADD")==0){
	addNode(heapofints, sizeofarray,getInt());
      }else if (strcmp(inpstring,"ADDFILE")==0){
	addFromFile(heapofints, sizeofarray);
      }else if (strcmp(inpstring,"DELETE")==0){
	cout<<"top of heap:"<<heapofints[0]<<endl;
	deleteNode(heapofints,sizeofarray,0);
      }else if (strcmp(inpstring,"DELETEALL")==0){
        while(heapofints[0]!=-1){
	  cout<<"top of heap:"<<heapofints[0]<<endl;
	  deleteNode(heapofints,sizeofarray,0);
	}
      }else if (strcmp(inpstring,"PRINT")==0){
	cout<<"Heap as picture:"<<endl;
	RecPrint(0,0,sizeofarray,heapofints);
	cout<<"Heap as array with indexes to assist identification:"<<endl;
	printStraight(heapofints,0,sizeofarray,true);
      }else if (strcmp(inpstring,"QUIT")==0){
	notQuit=false;
	//no command needed, just quit the loop.
      }else{
	cout<<"Invalid Command."<<endl;
      }
    }catch(...){
      //sometimes accidentally pressing the arrow keys can throw the input system for a loop, so I put this here to correct the error
      //(That was an idiom. Despite how much it sounds like technobabble, the pun was fully unintended)
      cout<<"Something went wrong. Please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }
  }
  cout<<"Have a nice day."<<endl;
  
  return 0;
  
}

//heap traversal commands
int parentIndex(int index){
  return floor((index-1)/2);
}

int leftIndex(int index){
  return (index*2)+1;
}

int rightIndex(int index){
  return (index+1)*2;
}

//returns what it's name is
int earliestOpenIndex(int* heapofints, int sizeofarray){
  for(int i=0; i<sizeofarray; i++){
    if(heapofints[i]==-1){
      return i;
    }
  }
  return -1;
}


//for getting Ints from the user.
int getInt(){
  bool acin=false;
  int Integ;
  while (acin==false){
    cout<<"Please Enter Positive Integer: "<<endl;
    cin>>Integ;
    if((cin.fail())||(Integ<0)){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  return Integ;
}

//Just adds a node. calls the bubbleTofunction, which contains recursive sorting.
void addNode(int*& heapofints, int sizeofarray, int toadd){
  int addindex = earliestOpenIndex(heapofints,sizeofarray);
  if(addindex==-1){
    cout<<"ERROR! HEAP FULL!"<<endl;
    return;
  }
  heapofints[addindex] = toadd;
  bubbleTo(heapofints, addindex);
  return;
}

//deletes a node
void deleteNode(int*& heapofints, int sizeofarray, int index){
  if((rightIndex(index)>=sizeofarray)||(leftIndex(index)>=sizeofarray)){
    heapofints[index]=-1;
  }else if(heapofints[rightIndex(index)]>heapofints[leftIndex(index)]){
    swap(heapofints[rightIndex(index)],heapofints[index]);
    deleteNode(heapofints, sizeofarray, rightIndex(index));
  }else{
    swap(heapofints[leftIndex(index)],heapofints[index]);
    deleteNode(heapofints, sizeofarray, leftIndex(index));
  }
  
  return;
}

//contains recursive sorting logic.
void bubbleTo(int*& heapofints,int index){
  if(parentIndex(index)==-1){
    cout<<heapofints[index]<<" reached top at "<<index<<endl;
    return;
  }
  if(heapofints[parentIndex(index)]<heapofints[index]){
    swap(heapofints[parentIndex(index)] , heapofints[index]);
    bubbleTo(heapofints, parentIndex(index));
  }
  return;
}

//swaps two ints. Suprisingly useful.
void swap(int& one, int& two){
  int buff=one;
  one=two;
  two=buff;
  return;
}

//prints the Heap as an array
void printStraight(int* heapofints, int addon, int sizeofarray,bool shownum){
  cout<<"[";
  if(shownum){
    for(int i=addon; i<sizeofarray+addon; i++){
      cout<<i<<":";
      if(heapofints[i]!=-1){
        if((int)log10(heapofints[i])==0){
	  cout<<" "<<heapofints[i]<<" ";
	}else if((int)log10(heapofints[i])==1){
	  cout<<heapofints[i]<<" ";
	}else {
	  cout<<heapofints[i];
	}
      }else{
	cout<<"    ";
      }
      if(i!=sizeofarray+addon-1){
	cout<<",";
      }
    }
  }else{
    for(int i=addon; i<sizeofarray+addon; i++){
      if(heapofints[i]!=-1){
	if((int)log10(heapofints[i])==0){
	  cout<<" "<<heapofints[i]<<" ";
	}else if((int)log10(heapofints[i])==1){
	  cout<<heapofints[i]<<" ";
	}else {
	  cout<<heapofints[i];
	}
      }else{
	cout<<" ";
      }
      if(i!=sizeofarray+addon-1){
	cout<<",";
      }
    }
  }
  cout<<"]"<<endl;
  return;
}

//prints the heap as a heap
void RecPrint(int pos, int depth, int sizeofarray,int* heapofints)
{
  if(heapofints[pos]==-1){
    return;
  }
  if(rightIndex(pos)<sizeofarray){
    RecPrint(rightIndex(pos), depth+1, sizeofarray, heapofints);
  }
  for(int i=0; i<depth;i++){
    cout<<"\t";
  }
  cout<<heapofints[pos]<<endl;
  if(leftIndex(pos)<sizeofarray){
    RecPrint(leftIndex(pos), depth+1, sizeofarray, heapofints);
  }
}

void addFromFile(int* heapofints, int sizeofarray){
  ifstream myFile;
  myFile.open("ints.txt");
  if(myFile.is_open()){
    int got;
    int earl = earliestOpenIndex(heapofints, sizeofarray);
    int remains;
    if(earl<0){
      cout<<"ERROR! HEAP FULL!"<<endl;
      return;
    }else{
      remains = sizeofarray-earl;
    }
    while((remains>0)&&(myFile>>got)){
      addNode(heapofints, sizeofarray, got);
      remains--;
    }
  }else{
    cout<<"ERROR! NO VALID ints.txt FILE!"<<endl;
    return;
  }
  myFile.close();
}
