#include<iostream>
#include<cstring>
#include<cctype>
#include<cmath>
#include<cfloat>
using namespace std;


int getPosNonZeroInt();
void getBigStringFromInput(char* inpstring);
void getStringFromInput(char* inpstring);
int getIndexOfLastNonNullChar(char* inpstring, int length);
void ASCIIToBin(bool* bindump, bool big = false);
void ASCIIBinTranslate(bool* bindump, char* string);
void BinToHex(bool* bindump, char* hex);
double FreqCheck(char* sequence);
void boolIncrement(bool* numb, int len);
int lastOneInBools(bool* numb, int length);
int HammingDist(bool* one, bool* two, int max);
bool* singXor(bool* box, int len);

int main(){
  cout<<"Please insert guessed key length (probably between 2 and 40)."<<endl;
  int keysize = getPosNonZeroInt();
  
  //prepare bindump
  bool* bindump = new bool[1600];
  ASCIIToBin(bindump);
  int last = lastOneInBools(bindump, 1600);
  last = (floor(last/8)+1)*8;
  cout<<"Last: "<<last<<endl;
  for(int i=0; i<last; i++){
    cout<<bindump[i];
  }
  cout<<endl;

  int* minDists = new int[4];
  double* minEditVals = new double[4];
  for(int i=0; i<4; i++){
    minDists[i]=0;
    minEditVals[i]=DBL_MAX;
  }
  
  bool* smallA =nullptr;
  bool* smallB =nullptr;
  bool* smallC =nullptr;
  bool* smallD =nullptr;
  for(int i=1; i<=min(keysize,last/32); i++){
    delete smallA;
    delete smallB;
    delete smallC;
    delete smallD;
    int guessbit = i*8;
    smallA = new bool[guessbit];
    smallB = new bool[guessbit];
    smallC = new bool[guessbit];
    smallD = new bool[guessbit];
    for(int j=0; j<guessbit; j++){
      smallA[j]=bindump[j];
      smallB[j]=bindump[guessbit+j];
      smallC[j]=bindump[guessbit*2+j];
      smallD[j]=bindump[guessbit*3+j];
    }
    int dist = 0;

    dist = dist + HammingDist(smallA,smallB,guessbit);
    dist = dist + HammingDist(smallA,smallC,guessbit);
    dist = dist + HammingDist(smallA,smallD,guessbit);
    dist = dist + HammingDist(smallB,smallC,guessbit);
    dist = dist + HammingDist(smallB,smallD,guessbit);
    dist = dist + HammingDist(smallC,smallD,guessbit);
    
    double normdist = (double(dist)/6)/i;
    int editmax=0;
    for(int j=0; j<4; j++){
      if(minEditVals[editmax]<minEditVals[j]){
	editmax=j;
      }
    }
    if(minEditVals[editmax]>normdist){
      minEditVals[editmax]=normdist;
      minDists[editmax]=i;
    }
    
    cout<<"Keysize: "<<i<<", Dist: "<<dist<<", Normdist: "<<normdist<<endl;
  }

  int trumin = 0;
  for(int i=0; i<4; i++){
    cout<<"minDist: "<<minEditVals[i]<<", Val: "<<minDists[i]<<endl;
    if(minEditVals[trumin]<minEditVals[i]){
      trumin=i;
    }
  }
  int numblocks=minDists[trumin]; //numblocks is estimated key length.
  int numchars = floor((last/8)/numblocks)+1; // last/8 is the number of chars.
  //numbchars is the max number of characters in every block. 
  bool** transposeBuffer = new bool*[numblocks];
  for(int i=0; i<numblocks; i++){
    transposeBuffer[i] = new bool[(numchars-(!(i<=((last/8)-((floor(double(last/8)/double(numblocks)))*numblocks)))))*8];
  }
  for(int i=0; i<numblocks; i++){
    for(int j=0; j<(numchars-(!(i<=((last/8)-((floor(double(last/8)/double(numblocks)))*numblocks))))); j++){
      for(int l=0; l<8; l++){
	transposeBuffer[i][j*8+l]=bindump[8*(i+j*6)+l];
      }
    }
  }
  bool** keys = new bool*[numblocks];
  for(int i=0; i<numblocks; i++){
    keys[i] = singXor(transposeBuffer[i], (numchars-(!(i<=((last/8)-((floor(double(last/8)/double(numblocks)))*numblocks))))));
  }
  cout<<"Keys found."<<endl;
  bool* xordump = new bool[1600];
  
  for(int i=0; i<last; i++){
    xordump[i]=(numb[i]!=key[i%8]);
  }
  
  
  return 0;  
}

int getPosNonZeroInt(){
  bool acin=false;
  int Integ;
  while (acin==false){
    cout<<"A positive, non-zero whole number, please: "<<endl;
    cin>>Integ;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      if(Integ>0){
	acin=true;
      }else{
	cout<<"The number needs to be postive and non-zero."<<endl;
      }
    }
  }
  cin.ignore(100000,'\n');
  return Integ;
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

void ASCIIToBin(bool* bindump, bool big){
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
  ASCIIBinTranslate(bindump, inpstring);
  delete inpstring;
  return;
}

void ASCIIBinTranslate(bool* bindump, char* string){
  for(int i=0; i<1600; i++){
    bindump[i]=0;
  }
  int lastindex = getIndexOfLastNonNullChar(string, 201);
  //perform ASCII-To-Bin
  for(int i=0; i<lastindex+1; i++){
    int intvalue = string[i];
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

int lastOneInBools(bool* numb, int length){
  int box = -1;
  for(int i=0; i<length; i++){
    if(numb[i]){
      box=i;
    }
  }
  return box;
}

int HammingDist(bool* one, bool* two, int max){
  int last = min(lastOneInBools(one, max),lastOneInBools(two, max));
  last = (floor(last/8)+1)*8;
  int difs=0;
  for(int i=0; i<last; i++){
    difs+=(one[i]!=two[i]);
  }
  return difs;
}

bool* singXor(bool* box, int len){
  bool* xordump = new bool[len];
  char* sequence = new char[(len/8)+1];
  double value = DBL_MAX;
  int keyAsInt;
  bool* key = new bool[8];
  bool* bestkey = new bool[8];
  for(int i=0; i<8; i++){
    key[i]=0;
    bestkey[i]=0;
  }
  int g=0;
  bool notdone=true;
  //actual translation setup
  while(notdone){
    cout<<"Key: "<<g<<" ";
    for(int i=0; i<8; i++){
      cout<<key[i];
    }
    cout<<endl;
    for(int i=0; i<len; i++){
      xordump[i]=(numb[i]!=key[i%8]);
    }
    for(int i=0; i<(len/8)+1; i++){
      sequence[i]='\0';
    }
    bool isvalid=true;
    for(int i=0; i<(len/8); i++){
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
	i=(len/8)+1;
	isvalid=false;
      }
    }
    if(isvalid){
      double freqsec = FreqCheck(sequence);
      if(freqsec!=0){
	if(freqsec<value){
	  value = freqsec;
	  keyAsInt = g;
	  for(int i=0; i<8; i++){
	    bestkey[i]=key[i];
	  }
	}
      }
    }
    boolIncrement(key,8);
    g++;
    notdone=(g!=256);
  }
  delete key;
  delete sequence;
  delete xordump;
  
  return keyAsInt;
}
