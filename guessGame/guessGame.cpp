/*
  This is code for a game that makes you guess numbers from 0 to 100. you may know this game as higher-or-lower.
  Made by Elliott Hunter VanOrman for Jason Galbraith's C++/Data Structures class.
  Made from 8/29/2024 to 9/??/2024
  the FIVE (I don't know why you said three, there are five.) rules of C++ are as follows:
  1: No global variables. Global constants are okay but no variables.
  2: No strings. cstrings and character arrays are okay. cstring and cctpye libraries are okay. but no strings.
  3: #include<iostream>. DO NOT #include<stdio>. use new & delete, not malloc & free
  4: Never use your mouse. Use the shortcuts. this was somewhat unneccesary seeing as emacs in cygwin does not accept input from the mouse, but whatever works?
  5: Break/Continue are if you have to commands. neer use them otherwise.
 */
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
using namespace std;

int main(){

  //Intro Scrawl.
  cout<<"==========================================================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<"     __ __        ___   ___"<<endl;
  cout<<"     ||_||       / _ \\  | |"<<endl;
  cout<<"     | _ |       ||_||  | |__"<<endl;
  cout<<"     || || igher \\___/r |___| ower"<<endl;
  cout<<"The game is quite simple:"<<endl;
  cout<<"You guess a number. I say if it is higher, lower, or \n exactly the numer I have."<<endl;
  cout<<"you win after guessing right. if you want, we play again."<<endl;
  cout<<"the game begins now."<<endl;
  //start the game loop
  //in addition, subloop command determines whether you are guessing or playing again. I reused the variable to save space
  bool gameloop=true, subloop = false;
  int goalNumb, guess, numberOfGuesses;
  char repeat;
  while(gameloop==true){
    //random number seeding and generation
    srand(time(NULL));
    goalNumb=((rand()%101));
    //resetting guese.
    numberOfGuesses=0;
    //main guessing loop
    while(subloop==false){
      numberOfGuesses++;
      cout<<"Your guess is: ";
      guess=-1;
      cin>>guess;
      if (cin.fail()){
        cin.clear();
        cin.ignore(100000,'\n');
      }
      cout<<endl;
      //judging
      if(guess==0){
	//this triggers if cin fails. I'd just use a continue insdie the cin.fail if statement but we're not supposed to so instead it goes in the judging if.
	cout<<"I think you put in something that wasn't a number."<<endl;
	cout<<"Please try again."<<endl;
      }else if((guess<goalNumb)){
	cout<<"You are too low."<<endl;
      }else if(guess>goalNumb){
	cout<<"You are too high."<<endl;
      }else if(guess==goalNumb){
	cout<<"Correct! the number was "<<goalNumb<<" and it took you "<<numberOfGuesses<<" Guesses."<<endl;
	subloop=true;
      }else{	
	cout<<"I think you put in something that wasn't a number."<<endl;
	cout<<"Please try again."<<endl;
      }
    }
    //play again? script. 
    cout<<"Good job. Would you like to play again? \n respond with one character (y/n) "<<endl;
    while(subloop==true){
      cin>>repeat;
      if (cin.fail()){
        cin.clear();
        cin.ignore(1000000,'\n');
	//for some reason this triggers if you type more than one character. as far as I know the only way to fix this would be to use a continue.
      }
      if (repeat=='y'){
	subloop=false;
	cout<<"We go again!"<<endl;
      } else if (repeat=='n'){
	gameloop=false;
	subloop=false;
	cout<<"Thank you for playing. Have a nice day!"<<endl;
      }else{
	cout<<"The only inputs we accept are y and n. lowercase. no space."<<endl;
	cout<<"Please try again."<<endl;
      }

    }
    
  }
  //visual decoration
  cout<<"==========================================================="<<endl;
  return 0;

}
