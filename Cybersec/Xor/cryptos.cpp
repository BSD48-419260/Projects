#include<iostream>
#include<cstring>
using namespace std;

void getStringFromInput(char* inpstring);
int getIndexOfLastNonNullChar(char* inpstring, int length);
void HexToBin(bool* bindump);
void BinToHex(bool* bindump, char* hex);
float FreqCheck(char* sequence);

int main(){
  char* bob =nullptr;
  FreqCheck(bob);

  /*
  //prepare bindump
  bool* bindumpA = new bool[403];
  bool* bindumpB = new bool[403];
  HexToBin(bindumpA);
  HexToBin(bindumpB);
  
  for(int i=0; i<403; i++){
    cout<<bindumpA[i];
  }
  cout<<endl;

  for(int i=0; i<403; i++){
    cout<<bindumpB[i];
  }
  cout<<endl;
  bool* xordump = new bool[403];

  for(int i=0; i<403; i++){
    if(bindumpA[i]==bindumpB[i]){
      xordump[i]=0;
    }else{
      xordump[i]=1;
    }
  }
  
  for(int i=0; i<403; i++){
    cout<<xordump[i];
  }
  cout<<endl;
  char* hex = new char[101];

  BinToHex(xordump,hex);

  for(int i=101; i>=0; i--){
    if((hex[i]=='0')||(hex[i]=='\0')){
      hex[i]='\0';
    }else{
      i=-1;
    }
  }
  
  for(int i=100; i>=0; i--){
    cout<<hex[i];
  }


  */
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

void HexToBin(bool* bindump){
  char* inpstring = new char[101];
  for(int i=0; i<101; i++){
    inpstring[i]='\0';
  }
  cout<<"Please Insert Hex Code"<<endl;
  //get Hex
  getStringFromInput(inpstring);

  //prepare bindump
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
  delete inpstring;
}

void BinToHex(bool* bindump, char* hex){
  //perform Bin-To-Hex
  for(int i=0; i<101; i++){
    hex[i]='\0';
  }
  char hexchars[17] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f','\0'};
  for(int i=0; i<101; i++){
    int bindex=0;
    if(bindump[4*i]){
      bindex=bindex+1;
    }
    if(bindump[4*i+1]){
      bindex=bindex+2;
    }
    if(bindump[4*i+2]){
      bindex=bindex+4;
    }
    if(bindump[4*i+3]){
      bindex=bindex+8;
    }
    cout<<"index: "<<bindex<<" Char: "<<hexchars[bindex]<<endl;
    hex[i]=hexchars[bindex];
  }
}


float FreqCheck(char* sequence){
  float count=0;
  float freqs[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};
  for(int i=0; i<26; i++){
    count=count+freqs[i];
  }
  cout<<count<<endl;
  return 0;
}
