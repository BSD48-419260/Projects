#include<iostream>
#include<cstring>
#include<cctype>
#include<cmath>
#include<cfloat>
using namespace std;

void getStringFromInput(char* inpstring);
int getIndexOfLastNonNullChar(char* inpstring, int length);
void HexToBin(bool* bindump);
void BinToHex(bool* bindump, char* hex);
double FreqCheck(char* sequence);
void boolIncrement(bool* numb, int len);

int main(){
  //prepare bindump
  bool* bindumpA = new bool[403];  
  bool* xordump = new bool[403];
  bool* key = new bool[8];
  for(int i=0; i<8; i++){
    key[i]=0;
  }

  bool notdone=true;
  int g=0;
  //buffer that holds sequence
  char* sequence = new char[51];
  //box to hold best values
  char** sequences = new char*[10];
  for(int i=0; i<10; i++){
    sequences[i] = new char[51];
  }
  double* values = new double[10];
  double* indexofseq = new double[10];
  double* keyofseq = new double[10];

  for (int i=0; i<10; i++){
    values[i]=DBL_MAX;
    indexofseq[i]=-1;
    keyofseq[i]=-1;
    for(int j=0; j<51; j++){
      sequences[i][j]='\0';
    }
  }

  bool h=true;
  int count=0;
  while(h){
    g=0;
    count++;
    notdone=true;
    HexToBin(bindumpA);
    
    if(bindumpA[402]){
      h=false;
    }else{
      
      for(int i=0; i<8; i++){
	key[i]=0;
      }
      //actual translation setup
      while(notdone){
	cout<<"Count: "<<count<<" Key: "<<g<<endl;
	for(int i=0; i<403; i++){
	  if(bindumpA[i]==key[i%8]){
	    xordump[i]=0;
	  }else{
	    xordump[i]=1;
	  }
	}
	for(int i=0; i<51; i++){
	  sequence[i]='\0';
	}
	bool isvalid=true;
	for(int i=0; i<50; i++){
	  int bindex=0;
	  if(xordump[8*i]){
	    bindex=bindex+1;
	  }
	  if(xordump[8*i+1]){
	    bindex=bindex+2;
	  }
	  if(xordump[8*i+2]){
	    bindex=bindex+4;
	  }
	  if(xordump[8*i+3]){
	    bindex=bindex+8;
	  }
	  if(xordump[8*i+4]){
	    bindex=bindex+16;
	  }
	  if(xordump[8*i+5]){
	    bindex=bindex+32;
	  }
	  if(xordump[8*i+6]){
	    bindex=bindex+64;
	  }
	  if(xordump[8*i+7]){
	    bindex=bindex+128;
	  }
	  if(bindex<=128){
	    sequence[i]=static_cast<char>(bindex);
	  }else{
	    i=51;
	    isvalid=false;
	  }
	}
	if(isvalid){
	  double freqsec = FreqCheck(sequence);
	  if(freqsec!=0){
	    int maxindex;
	    double max=-1;
	    for(int i=0; i<10; i++){
	      if(values[i]>max){
		max = values[i];
		maxindex = i;
	      }
	    }
	    if(freqsec<values[maxindex]){
	      strncpy(sequences[maxindex],sequence,50);
	      values[maxindex] = freqsec;
	      indexofseq[maxindex] = count; 
	      keyofseq[maxindex] = g;
	    }
	  }
	}
	boolIncrement(key,8);
	g++;
	notdone=(g!=256);
      }
    }
  }
  
  cout<<"Best 10 sequences are as follows: (please note, these are unsorted.)"<<endl;
  for(int i=0; i<10; i++){
    cout<<"Number "<<i+1<<":"<<endl;
    cout<<"QSADETC: "<<values[i]<<endl;
    cout<<"Count: "<<indexofseq[i]<<" Key: "<<keyofseq[i]<<endl;
    cout<<"Backwards: "<<endl;
    for(int j=0; j<50; j++){
      cout<<sequences[i][49-j];
    }
    cout<<endl;
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
      i = lastindex+3;
      bindump[402]=1;
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

//takes the expected frequency. Subtracts the true, then takes the abs value. divides by charcount to keep small-char values from dominating.
double FreqCheck(char* sequence){
  //part of expected frequency.
  double freqs[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};
  double* counts = new double[26];
  for(int i=0; i<26; i++){
    counts[i]=0;
  }
  bool nulter = false;
  int i=0;
  double charcount=0;
  //getting observed frequency. will use charcount to calc expected frequency.
  while(nulter==false){
    if(sequence[i]!='\0'){
      if(((tolower(sequence[i])-97)>=0)&&((tolower(sequence[i])-97)<=25)){
        counts[tolower(sequence[i])-97]++;
        charcount+=1;
      }
      i++;
    }else{
      nulter=true;
    }
  }
  cout<<"I HATE YOU EBEZEER SCROOOGE YOU INCORRIGIBLE PIECE OF: "<<charcount<<endl;
  if(charcount==0){
    return DBL_MAX;
  }
  double value = 0;
  for(int g=0; g<26; g++){
    value+=(abs((freqs[g]*charcount)-counts[g])/charcount);
  }
  delete counts;
  return value;
}

void boolIncrement(bool* numb, int len){
  for(int i=0; i<len; i++){
    if(numb[i]){
      numb[i]=false;
    }else{
      numb[i]=true;
      i=len;
    }
  }
}
