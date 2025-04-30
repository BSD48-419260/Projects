#include<iostream>
using namespace std;

void getStringFromInput(char* inpstring);
int getIndexOfLastNonNullChar(char* inpstring);

int main(){
  char* inpstring = new char[101];
  for(int i=0; i<101; i++){
    inpstring[i]='\0';
  }
  cout<<"Please Insert Hex Code"<<endl;
  //get Hex
  getStringFromInput(inpstring);
  //prepare bindump
  bool* bindump = new bool[403];
  for(int i=0; i<403; i++){
    bindump[i]=0;
  }
  //perform Hex-To-Bin
  for(int i=100; i>=0; i--){
    inpstring[i]
  }

  return 0;  
}


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

int getIndexOfLastNonNullChar(char* inpstring){
  i=0;
  while(true){
    if(inpstring[i]=='\0'){
      return i-1;
    }
    i++;
  }
}
