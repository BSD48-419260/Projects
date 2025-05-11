#include<iostream>
#include<cstring>
using namespace std;

void getStringFromInput(char* inpstring);
int getIndexOfLastNonNullChar(char* inpstring, int length);

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

  int lastindex = getIndexOfLastNonNullChar(inpstring, 101);
  //perform Hex-To-Bin
  for(int i=0; i<lastindex+1; i++){
    char hexbit = inpstring[lastindex-i];
    if (hexbit=='0'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='1'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='2'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='3'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='4'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='5'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='6'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='7'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 0;
    }else if (hexbit=='8'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 1;
    }else if (hexbit=='9'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 1;
    }else if (hexbit=='a'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 1;
    }else if (hexbit=='b'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 0;
      bindump [(4*i)+3] = 1;
    }else if (hexbit=='c'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 1;
    }else if (hexbit=='d'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 0;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 1;
    }else if (hexbit=='e'){
      bindump [(4*i)] = 0;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 1;
    }else if (hexbit=='f'){
      bindump [(4*i)] = 1;
      bindump [(4*i)+1] = 1;
      bindump [(4*i)+2] = 1;
      bindump [(4*i)+3] = 1;
    }else{
      cout<<"INVALID INPUT! (Contained non-hexadecimal character)"<<endl;
      exit(1);
    }
  }
  //perform Bin-To-Base
  char* output = new char[68];
  for(int i=0; i<68; i++){
    output[i]='\0';
  }
  char basechars[65] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/','\0'};

  for(int i=0; i<67; i++){
    int bindex=0;
    if(bindump[6*i]){
      bindex=bindex+1;
    }
    if(bindump[6*i+1]){
      bindex=bindex+2;
    }
    if(bindump[6*i+2]){
      bindex=bindex+4;
    }
    if(bindump[6*i+3]){
      bindex=bindex+8;
    }
    if(bindump[6*i+4]){
      bindex=bindex+16;
    }
    if(bindump[6*i+5]){
      bindex=bindex+32;
    }
    output[i]=basechars[bindex];
  }
  for(int i=67; i>=0; i--){
    if((output[i]=='A')||(output[i]=='\0')){
      output[i]='\0';
    }else{
      i=-1;
    }
  }
  
  //cout in reverse
  for(int i=67; i>=0; i--){
    cout<<output[i];
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

int getIndexOfLastNonNullChar(char* inpstring, int length){
  for(int i=0; i<length; i++){
    if(inpstring[i]=='\0'){
      return i-1;
    }
  }
  return -1;
}
