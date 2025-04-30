/*
TicTacToe.cpp
By Elliott VanOrman
Made for Jason Galbraith's C++ class.
Meant to play the game of TicTacToe with replayability and score tracking.
9/19/2024
*/

#include<iostream>
using namespace std;
//variable declarations
int board[3][3];
const int BLANK=0;
const int X=1;
const int O=2;
int xwins=0,owins=0;
bool xturn=true;

//function signatures
void clearBoard();
void printBoard();
void runGame();
void win(int mark);
char getMark(int val);
bool checkWin();
bool checkTie();

//mainloop
int main(){
  //setup and openeing scrawk
  char rep[2];
  clearBoard();
  xturn=true;
  cout<<"=================================================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<" __________ __________ __________"<<endl;
  cout<<" | __  __ | | __  __ | | __  __ |"<<endl;
  cout<<" |/ |  | \\| |/ |  | \\| |/ |  | \\|"<<endl;
  cout<<"    |  |       |  |       |  |"<<endl;
  cout<<"    |  |       |  |       |  |"<<endl;
  cout<<"    |  |       |  |       |  |"<<endl;
  cout<<"    /__\\ ic    /__\\ac     /__\\oe"<<endl;
  bool replay=true, acin=false;
  //game and replay handler (acin means ACceptable INput)
  while (replay==true){
    runGame();
    cout<<"X score: "<<xwins<<", O score: "<<owins<<endl;
    acin=false;
    while (acin==false){
      //trying to be robust.
      cout<<"Play again? (Y/N): ";
      cin.getline(rep,sizeof(rep));
      if(cin.fail()){
	cout<<"I think you did something wrong. please try again."<<endl;
	cin.clear();
	cin.ignore(100000,'\n');
      }else if ((rep[0]!='Y')&&(rep[0]!='N')){
	cout<<"Not Understood. please input N or Y"<<endl;
      }else{
	acin=true;
      }
    }
    if(rep[0]=='Y'){
      cout<<"Once more!"<<endl;
    }else{
      replay=false;
    }
  }
  return 0;
}

//clear function
void clearBoard(){
  for(int c=0;c<3;c++){
    for(int d=0;d<3;d++){
      board[c][d]=BLANK;
    }
  }
  return;
}

//print function
void printBoard(){
  cout<<"  1 2 3"<<endl;
  cout<<" ======="<<endl;
  for(int c=0;c<3;c++){
    cout<<((char)(65+c));
    for(int d=0;d<3;d++){
      cout<<"|"<<getMark(board[c][d]);
    }
    cout<<"|"<<endl;
    cout<<" ======="<<endl;
  }
  return;
}

//used in print function to convert Ints to Chars
char getMark(int val){
  if(val==1){
    return 'X';
  }else if (val==2){
    return 'O';
  }else{
    return ' ';
  }
}

//Main Game as function
void runGame(){
  //Setup, Starting with X, clearing the board, etc.
  xturn=true;
  clearBoard();
  bool gameloop=true;
  char inpcords[3];
  bool lacin=false;
  //turn loop
  while(gameloop){
    printBoard();
    if (checkWin()){
      gameloop=false;
      return;
    }else if(checkTie()){
      cout<<"Tie!"<<endl;
      return;
    }
    //clearing input.
    for(int i=0;i<3;i++){
      inpcords[i]=' ';
    }
    bool lacin=false;
    lacin=false;
    while (lacin==false){
      if(xturn==true){
	cout<<"X";
      }else{
	cout<<"O";
      }
      cout<<", please input Coordinates. (ex, A1): ";
      //input handling, becuase (relatively, this is very basic) robust code is the (relatively) best kind of code.
      cin.getline(inpcords,sizeof(inpcords));
      if(cin.fail()){
	cout<<"Something went wrong. Please try again."<<endl;
	cin.clear();
	cin.ignore(100000,'\n');
      }else if ((((inpcords[0]!='A')&&(inpcords[0]!='B'))&&(inpcords[0]!='C'))||(((inpcords[1]!='1')&&(inpcords[1]!='2'))&&(inpcords[1]!='3'))){
	cout<<"Input invalid. Please try again."<<endl;
      }else{
	//checking if spot is blank
	int* spot= &board[(inpcords[0]-65)][(inpcords[1]-49)];
	if(*spot==BLANK){
	  lacin=true;
	  if(xturn){
	    *spot=X;
	  }else{
	    *spot=O;
	  }
	}else{
	  cout<<"That spot is full. Please try again."<<endl;
	}
      }
    }
    //turn swapper
    if(xturn){
      xturn=false;
    }else{
      xturn=true;
    }
    
  }
  
  return;
}

//win checker
bool checkWin(){
  bool Win=false;
  //rows
  if((board[0][0]==board[0][1])&&(board[0][0]==board[0][2])){
    if (board[0][0]!=BLANK){
      win(board[0][0]);
      Win=true;
    }
  }else if((board[1][0]==board[1][1])&&(board[1][0]==board[1][2])){
    if (board[1][0]!=BLANK){
      win(board[1][0]);
      Win=true;
    }
  }else if((board[2][0]==board[2][1])&&(board[2][0]==board[2][2])){
    if (board[2][0]!=BLANK){
      win(board[2][0]);
      Win=true;
    }
  }else if((board[0][0]==board[1][0])&&(board[0][0]==board[2][0])){ //column
    if (board[0][0]!=BLANK){
      win(board[0][0]);
      Win=true;
    }
  }else if((board[0][1]==board[1][1])&&(board[0][1]==board[2][1])){
    if (board[0][1]!=BLANK){
      win(board[0][1]);
      Win=true;
    }
  }else if((board[0][2]==board[1][2])&&(board[0][2]==board[2][2])){ //diagonals
    if (board[0][2]!=BLANK){
      win(board[0][2]);
      Win=true;
    }
  }else if((board[0][0]==board[1][1])&&(board[0][0]==board[2][2])){
    if (board[0][0]!=BLANK){
      win(board[0][0]);
      Win=true;
    }
  }else if((board[0][2]==board[1][1])&&(board[0][2]==board[2][0])){
    if (board[0][2]!=BLANK){
      win(board[0][2]);
      Win=true;
    }
  }
  return Win;
}

//winning & Scoring
void win(int mark){
  if (mark==X){
    cout<<"X Wins!"<<endl;
    xwins++;
  }else{
    cout<<"O Wins!"<<endl;
    owins++;
  }
  return;
}

//tie checker.
bool checkTie(){
  for(int c=0;c<3;c++){
    for(int d=0;d<3;d++){
      if(board[c][d]==BLANK){
	return false;
      }
    }
  }
  return true;
}
