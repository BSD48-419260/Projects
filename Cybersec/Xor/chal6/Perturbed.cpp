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

void scrubNewlines(char* outstring, char* instring, int max);

void ASCIIToBin(bool* bindump, bool big = false);
void ASCIIBinTranslate(bool* bindump, char* string);

int Baseified(char becomeBase);
void BaseToBin(bool* bindump, bool big = false);
void BaseBinTranslate(bool* bindump, char* string);

void BinToHex(bool* bindump, char* hex);
double FreqCheck(char* sequence);
void boolIncrement(bool* numb, int len);
int lastOneInBools(bool* numb, int length);
int HammingDist(bool* one, bool* two, int max);
bool* singXor(bool* box, int len);

int main(){
  int guesses = 1;
  cout<<"Please insert guessed key length (probably between 2 and 40)."<<endl;
  int keysize = getPosNonZeroInt();
  
  //prepare bindump
  bool* bindump = new bool[100000];
  BaseToBin(bindump, true);
  cout"What?"<<endl;
  cout<<"Begining processing..."<<endl;
  int last = lastOneInBools(bindump, 100000);
  last = (floor(last/8)+1)*8;
  cout<<"Last: "<<last<<endl;
  /*
  for(int i=0; i<last; i++){
    cout<<bindump[i];
  }
  cout<<endl;
  //*/
  cout<<"Beginning Estimation..."<<endl;
  int* minDists = new int[guesses];
  double* minEditVals = new double[guesses];
  for(int i=0; i<guesses; i++){
    minDists[i]=0;
    minEditVals[i]=DBL_MAX;
  }

  //*
  bool* smallA =nullptr;
  bool* smallB =nullptr;
  bool* smallC =nullptr;
  bool* smallD =nullptr;
  for(int i=1; i<=min(keysize,last/32); i++){
    delete[] smallA;
    delete[] smallB;
    delete[] smallC;
    delete[] smallD;
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
    for(int j=0; j<guesses; j++){
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
  delete[] smallA;
  delete[] smallB;
  delete[] smallC;
  delete[] smallD;
  cout<<"Estimation Complete"<<endl;
  //*/
  
  for(int i=0; i<guesses; i++){
    cout<<"minDist: "<<minEditVals[i]<<", Val: "<<minDists[i]<<endl;
  }
  cout<<"Begining Decryptions..."<<endl;
  for(int h=0; h<guesses; h++){
    int numblocks=minDists[h]; //numblocks is estimated key length.
    int numchars = floor((last/8)/numblocks)+1; // last/8 is the number of chars.
    //numbchars is the max number of characters in every block. 
    bool** transposeBuffer = new bool*[numblocks];
    cout<<"Estimaed number of characters in key: "<<numblocks<<" Esimated number of characters per block: "<<numchars<<endl;
    for(int i=0; i<numblocks; i++){
      transposeBuffer[i] = new bool[(numchars-(!(i<=((last/8)-((floor(double(last/8)/double(numblocks)))*numblocks)))))*8];
    }
    for(int i=0; i<numblocks; i++){
      for(int j=0; j<(numchars-(!(i<=((last/8)-((floor(double(last/8)/double(numblocks)))*numblocks))))); j++){
	for(int l=0; l<8; l++){
	  transposeBuffer[i][j*8+l]=bindump[8*(i+j*numblocks)+l];
	}
      }
    }
    bool** keys = new bool*[numblocks];
    for(int i=0; i<numblocks; i++){
      keys[i] = singXor(transposeBuffer[i], (numchars-(!(i<=((last/8)-((floor(double(last/8)/double(numblocks)))*numblocks))))));
    }
    cout<<"Keys found. Suspected key: "<<endl;
    bool* xordump = new bool[100000];
    //*
    for(int i=0; i<numblocks; i++){
      int bindex=0;
      if(keys[i][0]){
	bindex=bindex+1;
      }
      if(keys[i][1]){
	bindex=bindex+2;
      }
      if(keys[i][2]){
	bindex=bindex+4;
      }
      if(keys[i][3]){
	bindex=bindex+8;
      }
      if(keys[i][4]){
	bindex=bindex+16;
      }
      if(keys[i][5]){
	bindex=bindex+32;
      }
      if(keys[i][6]){
	bindex=bindex+64;
      }
      if(keys[i][7]){
	bindex=bindex+128;
      }
      cout<<static_cast<char>(bindex);
    }
    //*/
    cout<<endl<<'|';
    for(int i=0; i<numblocks;i++){
      for(int j=0; j<8; j++){
	cout<<keys[i][j];
      }
      cout<<'|';
    }
    cout<<endl;
    
    for(int i=0; i<last; i++){
      xordump[i]=(bindump[i]!=keys[int(floor(i/8))%numblocks][i%8]);
      //cout<<xordump[i];
    }
    //cout<<endl;
    cout<<"Suspected solution:"<<endl;
    for(int i=0; i<last/8; i++){
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
      cout<<static_cast<char>(bindex);
    }
    cout<<endl;
    for(int i=0; i<numblocks; i++){
      delete[] transposeBuffer[i];
      delete[] keys[i];
    }
    delete[] transposeBuffer;
    delete[] keys;
    delete[] xordump;
  }
  delete[] minDists;
  delete[] minEditVals;
  cout<<"Decryptions Complete."<<endl;
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
  char bufferarray [12501];
  //Ensure Valid Input.
  bool acin;
  for(int i=0;i<12501;i++){
    inpstring[i]='\0';
  }
  int last=0;
  bool moreLines = true;
  cout<<"12500 characters or less, please."<<endl;
  while(moreLines){
    for(int i=0;i<12501;i++){
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
        inpstring[getIndexOfLastNonNullChar(inpstring, 12500)+1]='\n';
	last++;
      }
      strncat(inpstring, bufferarray, 12500-last);
      last=getIndexOfLastNonNullChar(inpstring, 12500);
    }
    if(last>=12500){
      inpstring[12500]='\0';
      cout<<endl;
      return;
    }
  }
  inpstring[12500]='\0';
  cout<<endl;
  return;
}

void getStringFromInput(char* inpstring){
  char bufferarray [12501];
  //make sure it works
  bool acin=false;
  for(int i=0;i<12501;i++){
    bufferarray[i]='\0';
  }
  while(acin==false){
    cout<<"12500 characters or less, please."<<endl;
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
  strncpy(inpstring, bufferarray, 12500);
  inpstring[12500]='\0';
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

void scrubNewlines(char* outstring, char* instring, int max){
  cout<<"Starting newlinescrubbing..."<<endl;
  bool checkmax=(max!=0);
  bool negated=false;
  int offset = 0;
  int i=0;
  while (negated==false){
    if(instring[i+offset]=='\n'){
      offset++;
    }
    outstring[i]=instring[i+offset];
    if((instring[i+offset]=='\0')||(i+offset>=max)){
      negated=true;
    }
    i++;
  }
  cout<<"Scrubbing Complete."<<endl;
}

void ASCIIToBin(bool* bindump, bool big){
  char* inpstring = new char[12501];
  for(int i=0; i<12501; i++){
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
  for(int i=0; i<12500; i++){
    cout<<inpstring[i];
  }
  cout<<endl;
  cout<<"(IAMWHOIAM)|";
  for(int i=0; i<12500; i++){
    cout<<int(inpstring[i])<<'|';
  }
  cout<<endl;
  ASCIIBinTranslate(bindump, inpstring);
  delete inpstring;
  return;
}

void ASCIIBinTranslate(bool* bindump, char* stringy){
  cout<<"Assault";
  for(int i=0; i<100000; i++){
    bindump[i]=0;
  }
  int lastindex = getIndexOfLastNonNullChar(stringy, 12501);
  //perform ASCII-To-Bin
  for(int i=0; i<lastindex+1; i++){
    int intvalue = stringy[i];
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
  cout<<" Vehicle"<<endl;
}

int Baseified(char becomeBase){
  int sauce = becomeBase;
  if(sauce==43){
    return 62;
  }else if(sauce==47){
    return 63;
  }else{
    if((sauce<=57)&&(sauce>=48)){
      return sauce+4;
    }else if((sauce<=90)&&(sauce>=65)){
      return sauce-65;
    }else if((sauce<=122)&&(sauce>=97)){
      return sauce-71;
    }
  }
  return -1;
}

//*
void BaseToBin(bool* bindump, bool big){
  char* inpstring = new char[12501];
  for(int i=0; i<12501; i++){
    inpstring[i]='\0';
  }
  cout<<"Please Insert Base64 Text."<<endl;
  //get text
  if(big){
    getBigStringFromInput(inpstring);
  }else{
    getStringFromInput(inpstring);
  }
  cout<<"(IAMWHOIAM)";
  for(int i=0; i<12500; i++){
    cout<<inpstring[i];
  }
  cout<<endl;
  /*
  cout<<"(IAMWHOIAM)|";
  for(int i=0; i<12500; i++){
    cout<<int(inpstring[i])<<'|';
  }
  //*/
  cout<<endl;
  cout<<"Beginning translation..."<<endl;
  BaseBinTranslate(bindump, inpstring);
  cout<<"Translation complete."<<endl;
  delete inpstring;
  return;
}

void BaseBinTranslate(bool* bindump, char* stringy){
  char* scrubbed = new char[12500];
  scrubNewlines(scrubbed, stringy, 12500);
  for(int i=0; i<100000; i++){
    bindump[i]=0;
  }
  int lastindex = getIndexOfLastNonNullChar(scrubbed, 12501);
  //perform Base-To-Bin
  for(int i=0; i<lastindex+1; i++){
    int intvalue = Baseified(scrubbed[i]);
    if(intvalue>=32){
      bindump [(8*i)+0] = 1;
      intvalue-=32;
    }
    if(intvalue>=16){
      bindump [(8*i)+1] = 1;
      intvalue-=16;
    }
    if(intvalue>=8){
      bindump [(8*i)+2] = 1;
      intvalue-=8;
    }
    if(intvalue>=4){
      bindump [(8*i)+3] = 1;
      intvalue-=4;
    }
    if(intvalue>=2){
      bindump [(8*i)+4] = 1;
      intvalue-=2;
    }
    bindump [(8*i)+5] = intvalue;
  }
  delete scrubbed;
}
//*/

//lower is better. that's the only rule.
double FreqCheck(char* sequence){
  //part of expected frequency.
  //double freqs[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

  //I got this list of frequencies from chatgpt when it occured to me that spaces would be useful. 
  double englishFrequencies[27] = {
    0.07234, // a
    0.01321, // b
    0.02462, // c
    0.03763, // d
    0.11241, // e
    0.01971, // f
    0.01783, // g
    0.05394, // h
    0.06165, // i
    0.00135, // j
    0.00683, // k
    0.03562, // l
    0.02129, // m
    0.05973, // n
    0.06645, // o
    0.01707, // p
    0.00084, // q
    0.05299, // r
    0.05598, // s
    0.08006, // t
    0.02440, // u
    0.00866, // v
    0.02088, // w
    0.00133, // x
    0.01747, // y
    0.00065, // z
    0.11504  // space
  };
  double* counts = new double[27];
  for(int i=0; i<27; i++){
    counts[i]=0;
  }
  bool nulter = false;
  int i=0;
  double charcount=0;
  double avgwordlength=0;
  int numwords=0;
  int lastwordlength=0;
  //getting observed frequency. will use charcount to calc expected frequency.
  while(sequence[i]!='\0'){
    if(((tolower(sequence[i])-97)>=0)&&((tolower(sequence[i])-97)<=25)){
      counts[tolower(sequence[i])-97]++;
      charcount+=1;
      lastwordlength++;
    }else if(sequence[i]==' '){
      counts[26]++;
      charcount+=1;

      avgwordlength=((avgwordlength*numwords)+lastwordlength)/(double(numwords+1));
      numwords++;
      lastwordlength=0;
    }/*else{
      avgwordlength=((avgwordlength*numwords)+lastwordlength)/(double(numwords+1));
      numwords++;
      lastwordlength=0;
      }*/
    i++;
  }
  avgwordlength=((avgwordlength*numwords)+lastwordlength)/(double(numwords+1));
  //cout<<"I HATE YOU EBEZEER SCROOOGE YOU INCORRIGIBLE PIECE OF: "<<charcount<<endl;
  if((charcount==0)||((charcount/i)<0.5)){
    return DBL_MAX;
  }
  double value = 0;
  for(int g=0; g<27; g++){
    //cout<<"Letter: "<<+static_cast<char>(g+65)<<" Freq: "<<englishFrequencies[g]<<" count: "<<counts[g]<<" expected: "<<(englishFrequencies[g]*charcount)<<endl;
    value+=(pow((counts[g])-(englishFrequencies[g]*charcount),2)/(englishFrequencies[g]*charcount));
    //value+=(abs((counts[g])-(englishFrequencies[g]*charcount))/charcount);
    //value+=(pow((counts[g])-(englishFrequencies[g]*charcount),2)/(englishFrequencies[g]*charcount))/charcount;
  }
  value=((value/10000)+(abs(avgwordlength-4.7)))/2;
  delete[] counts;
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
    //*
    cout<<"Key: "<<g<<" "<<static_cast<char>(g)<<" ";
    for(int i=0; i<8; i++){
      cout<<key[i];
    }
    cout<<endl;
    //*/
    for(int i=0; i<len; i++){
      xordump[i]=(box[i]!=key[i%8]);
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
    if(true){
      //cout<<"Salt Shakers."<<endl;
      double freqsec = FreqCheck(sequence);
      if(freqsec!=0){
	cout<<"Freqsec: "<<freqsec<<" Curval: "<<value<<endl;
	if(freqsec<value){
	  value = freqsec;
	  keyAsInt = g;
	  for(int i=0; i<8; i++){
	    bestkey[i]=key[i];
	  }
	}
      }
    }
    if(isvalid){
      for(int i=0; i<40; i++){
	cout<<sequence[i];
      }
      cout<<endl;
    }
    boolIncrement(key,8);
    g++;
    notdone=(g!=256);
  }
  delete key;
  delete sequence;
  delete xordump;
  return bestkey;
}
