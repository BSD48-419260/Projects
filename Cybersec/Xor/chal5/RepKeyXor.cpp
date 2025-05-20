#include<iostream>
#include<cstring>
#include<cctype>
#include<cmath>
#include<cfloat>
using namespace std;

void getBigStringFromInput(char* inpstring);
void getStringFromInput(char* inpstring);
int getIndexOfLastNonNullChar(char* inpstring, int length);
void ASCIIToBin(bool* bindump, bool big);
void BinToHex(bool* bindump, char* hex);
void makeKey(bool* key, int length);
int lastOneInBools(bool* numb, int length);

int main(){
  //prepare bindump
  bool* bindumpA = new bool[1600];  
  bool* xordump = new bool[1600];
  bool* key = new bool[1600];
  
  int g=0;
  //buffer that holds the output sequence
  char* sequence = new char[401];
  cout<<"String. ";
  ASCIIToBin(bindumpA, true);

  int last = lastOneInBools(bindumpA, 1600);
  last = (floor(last/8)+1)*8;
  
  cout<<"Bindump:";
  for(int i=0; i<1600; i++){
    if(i%75==0){
      cout<<endl;
    }
    cout<<bindumpA[i];
  }
  cout<<endl;

  makeKey(key, 1600);

  cout<<"Key:";
  for(int i=0; i<1600; i++){
    if(i%75==0){
      cout<<endl;
    }
    cout<<key[i];
  }
  cout<<endl;
  
  for(int i=0; i<last; i++){
    if(bindumpA[i]==key[i]){
      xordump[i]=0;
    }else{
      xordump[i]=1;
    }
  }

  cout<<"Xordump:";
  for(int i=0; i<1600; i++){
    if(i%75==0){
      cout<<endl;
    }
    cout<<xordump[i];
  }
  cout<<endl;
  
  for(int i=0; i<401; i++){
    sequence[i]='\0';
  }

  BinToHex(xordump, sequence);

  cout<<"Sequence:";
  last = last/4;
  for(int i=0; i<last; i++){
    if(i%75==0){
      cout<<endl;
    }
    cout<<sequence[i];
  }
  cout<<endl;
  return 0;  
}


void getBigStringFromInput(char* inpstring){
  char bufferarray [201];
  //Ensure Valid Input.
  bool acin;
  for(int i=0;i<201;i++){
    inpstring[i]='\0';
  }
  int last=0;
  bool moreLines = true;
  cout<<"200 characters or less, please."<<endl;
  while(moreLines){
    for(int i=0;i<201;i++){
      bufferarray[i]='\0';
    }
    acin=false;
    while(acin==false){
      cout<<"(IAMWHOIAM!)"<<endl;
      cin.getline(bufferarray, sizeof(bufferarray),'\n');
      if(bufferarray[0]=='\0'){
	moreLines=false;
      }
      //being robust.
      if(cin.fail()){
	cout<<"I think you did something wrong. Please try again."<<endl;
	cin.clear();
	cin.ignore(100000,'\n');
      }else{
	acin=true;
      }
    }
    
    if(moreLines){
      if(last!=0){
        inpstring[getIndexOfLastNonNullChar(inpstring, 200)+1]='\n';
	last++;
      }
      strncat(inpstring, bufferarray, 200-last);
      last=getIndexOfLastNonNullChar(inpstring, 200);
    }
    if(last>=200){
      inpstring[200]='\0';
      cout<<endl;
      return;
    }
  }
  inpstring[200]='\0';
  cout<<endl;
  return;
}

void getStringFromInput(char* inpstring){
  char bufferarray [201];
  //make sure it works
  bool acin=false;
  for(int i=0;i<201;i++){
    bufferarray[i]='\0';
  }
  while(acin==false){
    cout<<"200 characters or less, please."<<endl;
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
  strncpy(inpstring, bufferarray, 200);
  inpstring[200]='\0';
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

void ASCIIToBin(bool* bindump, bool big=false){
  char* inpstring = new char[201];
  for(int i=0; i<201; i++){
    inpstring[i]='\0';
  }
  cout<<"Please Insert ASCII Text."<<endl;
  //get text
  if(big){
    getBigStringFromInput(inpstring);
  }else{
    getStringFromInput(inpstring);
  }
  cout<<"(IAMWHOIAM)";
  for(int i=0; i<200; i++){
    cout<<inpstring[i];
  }
  cout<<endl;
  cout<<"(IAMWHOIAM)|";
  for(int i=0; i<200; i++){
    cout<<int(inpstring[i])<<'|';
  }
  cout<<endl;
  //prepare bindump
  for(int i=0; i<1600; i++){
    bindump[i]=0;
  }
  int lastindex = getIndexOfLastNonNullChar(inpstring, 201);
  //perform ASCII-To-Bin
  for(int i=0; i<lastindex+1; i++){
    int intvalue = inpstring[i];
    if(intvalue>=128){
      bindump [(8*i)+0] = 1;
      intvalue-=128;
    }
    if(intvalue>=64){
      bindump [(8*i)+1] = 1;
      intvalue-=64;
    }
    if(intvalue>=32){
      bindump [(8*i)+2] = 1;
      intvalue-=32;
    }
    if(intvalue>=16){
      bindump [(8*i)+3] = 1;
      intvalue-=16;
    }
    if(intvalue>=8){
      bindump [(8*i)+4] = 1;
      intvalue-=8;
    }
    if(intvalue>=4){
      bindump [(8*i)+5] = 1;
      intvalue-=4;
    }
    if(intvalue>=2){
      bindump [(8*i)+6] = 1;
      intvalue-=2;
    }
    bindump [(8*i)+7] = intvalue;
  }
  delete inpstring;
  return;
}


void BinToHex(bool* bindump, char* hex){
  //perform Bin-To-Hex
  for(int i=0; i<401; i++){
    hex[i]='\0';
  }
  char hexchars[17] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f','\0'};
  cout<<"(IAMWHOIAM)|";
  for(int i=0; i<400; i++){
    int bindex=0;
    if(bindump[4*i+3]){
      bindex=bindex+1;
    }
    if(bindump[4*i+2]){
      bindex=bindex+2;
    }
    if(bindump[4*i+1]){
      bindex=bindex+4;
    }
    if(bindump[4*i+0]){
      bindex=bindex+8;
    }
    //cout<<"index: "<<bindex<<" Char: "<<hexchars[bindex]<<endl;
    hex[i]=hexchars[bindex];
    cout<<bindex<<'|';
  }
  cout<<endl;
}

void makeKey(bool* key,int length){
  cout<<"Key. ";
  ASCIIToBin(key);
  int last = lastOneInBools(key, length);
  last = (floor(last/8)+1)*8;
  for(int i=0; i<1600; i++){
    key[i] = key[i%last];
  }
  return;
}

int lastOneInBools(bool* numb, int length){
  int box = -1;
  for(int i=0; i<length; i++){
    if(numb[i]){
      box=i;
    }
  }
  return box;
}
