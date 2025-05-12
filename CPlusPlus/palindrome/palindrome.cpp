/*
Palindrome Detector, made to detect palindromes made from
just alphanumerical characters
By Elliott VanOrman
9/11/2024
May those who died on this day 23 years ago rest in peace
*/
#include<iostream>
using namespace std;
int main(){
  char message[80];
  int forLeng=80;
  for(int c=0; c<forLeng; c++){
    message[c]='\0';
  }
  cout<<"======================================================"<<endl;
  cout<<" ____"<<endl;
  cout<<"/ ___\\"<<endl;
  cout<<"| |_| |"<<endl;
  cout<<"| ___/"<<endl;
  cout<<"||"<<endl;
  cout<<"||   alindrome"<<endl;
  //input acceptor, always checking for ACceptable INput.(ACIN)
  bool acin=false;
  while(acin==false){
    cout<<"Please input an 80-character statement for palindrome determinaton"<<endl;
    cin.getline(message,sizeof(message));
    acin=true;
  }
  //leng represents how many characters are left to process
  //letang represents confirmed alphabetical characters.
  int leng=80;
  int letlang=0;
  //'String' (character "Buffer" I think it's called) processor.
  for(int let=0;let<leng;let++){
    //If I reach a null char than the rest of the array is blank. so I exit the loop.
    if(message[let]!='\0'){
      if(isalnum(message[let])){
	message[let]=(char) tolower(message[let]);
	letlang++;
      }else{
	for(int fix=let; fix<leng; fix++){
	  if (fix<leng-1){
	    message[fix]=message[fix+1];
	  }else{
	    //If by some chance the array is super long I need to clean up.
	    message[leng-1]='\0';
	  }
	}
	let--;
	leng=leng-1;
      }
    }else{
      leng=let;
    }
  }
  //reverse checker
  for(int c=0; c<letlang; c++){
    if(message[c]!=message[letlang-(c+1)]){
      cout<<"Not a palindrome."<<endl;
      //return 0;
    }
  }
  cout<<"Palindrome."<<endl;
  return 0;
}
