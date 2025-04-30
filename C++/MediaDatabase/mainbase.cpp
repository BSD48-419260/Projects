/*
MediaDatabase
11/6/2024
By Elliott VanOrman for Jason Galbraith's C++ class.
made to theoretically store three kinds media in a single vector
please note this is useless without it's other tHree files!
*/
#include <iostream>
#include <cstring>
#include <vector>
#include "Media.cpp"
#include "Game.cpp"
#include "Music.cpp"
#include "Movie.cpp"
using namespace std;

//signatures
void getStringFromInput(char* &);
void addMedia(vector<Media*> & MainBase);
void killMedia(vector<Media*> & MainBase);
void listMedia(vector<Media*> MainBase);
void searchMedia(vector<Media*> MainBase);

//main function
int main(){
  //this is the vector I contain all the Media in.
  vector<Media*> MainBase;
  cout<<"==============================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<" ___  ___      __"<<endl;
  cout<<" | \\  / |      |_\\"<<endl;
  cout<<" ||\\\\//||      ||\\\\"<<endl;
  cout<<" || \\/ ||      || \\\\ "<<endl;
  cout<<" ||    ||      || ||"<<endl;
  cout<<" ||    ||      ||//"<<endl;
  cout<<" ||    ||      | /"<<endl;
  cout<<"/__\\  /__\\edia |/atabase"<<endl;
  cout<<"(Please note this program is\nincapable of saving data, so\ndon't actually use it for\nlogging media)"<<endl;
  bool notQuit=true;
  char*input = new char[16];
  while(notQuit){
    //command handler.
    cout<<"Please Input Command (ADD, DELETE, PRINT, SEARCH, QUIT)"<<endl;
    getStringFromInput(input);
    cout<<"Function got: "<<endl;
    for(int i=0; i<16; i++){
      cout<<input[i];
    }
    cout<<endl;
    if(strcmp(input,"ADD")==0){
      addMedia(MainBase);
    }else if(strcmp(input,"DELETE")==0){
      killMedia(MainBase);
    }else if(strcmp(input,"PRINT")==0){
      listMedia(MainBase);
    }else if(strcmp(input,"SEARCH")==0){
      searchMedia(MainBase);
    }else if(strcmp(input,"QUIT")==0){
      notQuit=false;
    }else{
      cout<<"Invalid Command."<<endl;
    }
  }
  //cleaning up just before I end
  delete[] input;
  return 0;
}

//string handler. I needed it. it makes everything soooo much easier.
void getStringFromInput(char* & inpstring){
  char bufferarray [16];
  //make sure it works
  bool acin=false;
  for(int i=0;i<16;i++){
    bufferarray[i]='\0';
  }
  while(acin==false){
    cout<<16-1<<" characters or less, please."<<endl;
    cin.getline(bufferarray, sizeof(bufferarray),'\n');
    //need to try robust.
    if(cin.fail()){
      cout<<"I think you did something wrong. Please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  strncpy(inpstring, bufferarray, 15);
  inpstring[15]='\0';
  cout<<endl;
  return;
}

//Media adding function.
void addMedia(vector<Media*> & MainBase){
  char* inpstring = new char[16];
  cout<<"Please declare which type of media you want to make: (GAME, MUSIC, MOVIE, CANCEL)"<<endl;
  bool acin=false;
  //command handler
  while(acin==false){
    getStringFromInput(inpstring);
    cout<<"Function got: "<<endl;
    cout<<endl;
    //game handler
    if(strcmp(inpstring,"GAME")==0){
      acin=true;
      Game* newGame = new Game();
      cout<<"Title? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newGame->setTitle(inpstring);
      cout<<"Year?"<<endl;
      bool sacin=false;
      int nwyear;
      while(sacin==false){
      	cin>>nwyear;
      	if(cin.fail()){
      	  cout<<"I think you did something wrong. Please try again."<<endl;
      	  cin.clear();
      	  cin.ignore(100000,'\n');
      	}else{
      	  sacin=true;
      	}
      }
      cin.ignore(100000,'\n');
      newGame->setYear(nwyear);
      cout<<"Publisher? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newGame->setPublisher(inpstring);
      cout<<"Rating? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newGame->setRating(inpstring);
      MainBase.push_back(newGame); 
    }else if(strcmp(inpstring,"MUSIC")==0){
      acin=true;
      Music* newMusic = new Music();
      cout<<"Title? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newMusic->setTitle(inpstring);
      cout<<"Artist? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newMusic->setArtist(inpstring);
      cout<<"Year?"<<endl;
      bool sacin=false;
      int nwyear;
      while(sacin==false){
      	cin>>nwyear;
      	if(cin.fail()){
      	  cout<<"I think you did something wrong. Please try again."<<endl;
      	  cin.clear();
      	  cin.ignore(100000,'\n');
      	}else{
      	  sacin=true;
      	}
      }
      sacin=false;
      cin.ignore(100000,'\n');
      newMusic->setYear(nwyear);
      int nwduration;
      cout<<"Duration?"<<endl;
      while(sacin==false){
      	cin>>nwduration;
      	if(cin.fail()){
      	  cout<<"I think you did something wrong. Please try again."<<endl;
      	  cin.clear();
      	  cin.ignore(100000,'\n');
      	}else{
      	  sacin=true;
      	}
      }
      cin.ignore(100000,'\n');
      newMusic->setDuration(nwduration);
      cout<<"Publisher? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newMusic->setPublisher(inpstring);
      MainBase.push_back(newMusic);
    }else if(strcmp(inpstring,"MOVIE")==0){ //Using
      acin=true;
      Movie* newMovie = new Movie();
      cout<<"Title? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newMovie->setTitle(inpstring);
      cout<<"Director? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newMovie->setDirector(inpstring);
      cout<<"Year?"<<endl;
      bool sacin=false;
      int nwyear;
      while(sacin==false){
      	cin>>nwyear;
      	if(cin.fail()){
      	  cout<<"I think you did something wrong. Please try again."<<endl;
      	  cin.clear();
      	  cin.ignore(100000,'\n');
      	}else{
      	  sacin=true;
      	}
      } 
      sacin=false;
      newMovie->setYear(nwyear);
      int nwduration;
      cout<<"Duration?"<<endl;
      while(sacin==false){
      	cin>>nwduration;
      	if(cin.fail()){
      	  cout<<"I think you did something wrong. Please try again."<<endl;
      	  cin.clear();
      	  cin.ignore(100000,'\n');
      	}else{
      	  sacin=true;
      	}
      }
      newMovie->setDuration(nwduration);
      cin.ignore(100000,'\n');
      cout<<"Rating? (15 chars or less, please)"<<endl;
      getStringFromInput(inpstring);
      newMovie->setRating(inpstring);
      MainBase.push_back(newMovie);
    }else if(strcmp(inpstring,"CANCEL")==0){
      delete[] inpstring;
      return;
    }else{
      cout<<"Invalid Command."<<endl;
    }
  }
  //don't need to delete anything because we passed all the pointers of the 'new' media into the MainBase
  //do want to avoid memory leak however...
  delete[] inpstring;
}
void killMedia(vector<Media*> & MainBase){
  bool notQuit=true;
  char*input = new char[16];
  int searchIndex;
  while(notQuit){
    cout<<"What field do you wish to delete by? (TITLE, YEAR, CANCEL)"<<endl;
    getStringFromInput(input);
    cout<<"Function got: "<<endl;
    for(int i=0; i<16; i++){
      cout<<input[i];
    }
    cout<<endl;
    notQuit=false;
    if(strcmp(input,"TITLE")==0){
      searchIndex=1;
    }else if(strcmp(input,"YEAR")==0){
      searchIndex=2;
    }else if(strcmp(input,"CANCEL")==0){
      return;
    }else{
      cout<<"Invalid Command."<<endl;
      notQuit=true;
    }
  }
  
  int numberfound=0;
  vector<int> indexes;
  if(searchIndex==1){
    cout<<"Search by title name:"<<endl;
    getStringFromInput(input);
    //searching by title
    for(auto i=MainBase.begin(); i!=MainBase.end(); ++i){
      if (strcmp((input),(*i)->getTitle())==0){
        numberfound++;
        //it may not be strictly necesary but I judge all aspects of deleted media to be relevant.
        indexes.push_back(static_cast<int>(i-MainBase.begin()));
        if((*(*i)).getType()=='G'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: GAME, Title:"<<static_cast <Game*>(*i)->getTitle()<<", Year:"<<static_cast <Game*>(*i)->getYear()<<", Publisher:"<<static_cast <Game*>(*i)->getPublisher()<<", Rating:"<<static_cast <Game*>(*i)->getRating()<<endl;
        }else if((*(*i)).getType()=='U'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MUSIC, Title:"<<static_cast <Music*>(*i)->getTitle()<<", Artist:"<<static_cast <Music*>(*i)->getArtist()<<", Year:"<<static_cast <Music*>(*i)->getYear()<<", Duration:"<<static_cast <Music*>(*i)->getDuration()<<", Publisher:"<<static_cast <Music*>(*i)->getPublisher()<<endl;
        }else if((*(*i)).getType()=='O'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MOVIE, Title:"<<static_cast <Movie*>(*i)->getTitle()<<", Director:"<<static_cast <Movie*>(*i)->getDirector()<<", Year:"<<static_cast <Movie*>(*i)->getYear()<<", Duration:"<<static_cast <Movie*>(*i)->getDuration()<<", Rating:"<<static_cast <Movie*>(*i)->getRating()<<endl;
        }else{
          cout<<"ERROR! UNTYPED MEDIA"<<endl;
        }
      }
    }
  }else if(searchIndex==2){
    bool sacin=false;
    int nwyear;
    while(sacin==false){
      cin>>nwyear;
      if(cin.fail()){
        cout<<"I think you did something wrong. Please try again."<<endl;
        cin.clear();
        cin.ignore(100000,'\n');
      }else{
        sacin=true;
      }
    }
    cin.ignore(100000,'\n');
    //searching by year
    for(auto i=MainBase.begin(); i!=MainBase.end(); ++i){
      if (nwyear==((*i)->getYear())){
        numberfound++;
        indexes.push_back(static_cast<int>(i-MainBase.begin()));
        if((*(*i)).getType()=='G'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: GAME, Title:"<<static_cast <Game*>(*i)->getTitle()<<", Year:"<<static_cast <Game*>(*i)->getYear()<<", Publisher:"<<static_cast <Game*>(*i)->getPublisher()<<", Rating:"<<static_cast <Game*>(*i)->getRating()<<endl;
        }else if((*(*i)).getType()=='U'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MUSIC, Title:"<<static_cast <Music*>(*i)->getTitle()<<", Artist:"<<static_cast <Music*>(*i)->getArtist()<<", Year:"<<static_cast <Music*>(*i)->getYear()<<", Duration:"<<static_cast <Music*>(*i)->getDuration()<<", Publisher:"<<static_cast <Music*>(*i)->getPublisher()<<endl;
        }else if((*(*i)).getType()=='O'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MOVIE, Title:"<<static_cast <Movie*>(*i)->getTitle()<<", Director:"<<static_cast <Movie*>(*i)->getDirector()<<", Year:"<<static_cast <Movie*>(*i)->getYear()<<", Duration:"<<static_cast <Movie*>(*i)->getDuration()<<", Rating:"<<static_cast <Movie*>(*i)->getRating()<<endl;
        }else{
          cout<<"ERROR! UNTYPED MEDIA"<<endl;
        }
      }
    }
  }
  cout<<"Total media found: "<<numberfound<<endl;
  cout<<"Are you sure you want to delete listed item(s)? there is no way to undo this. if so, type DELETE"<<endl;
  getStringFromInput(input);
  if(strcmp(input,"DELETE")!=0){
    //only thing I need to delete...
    delete input;
    return;
  }
  
  //this is an important bit: I need to delete in reverse order or else the indexes will move, so deletions will delete the wrong things
  //note: copied below from GPT because I was low on time. as such, I must explain why it does what it does in depth to explain my understanding.
  //the purpose of the sort is to reverse the array for reasons previously mentioned.
  //the purpose of the for loop is to go throuhg each individual index on the deleter
  //the purpose of the if is to check if the index is inside the MainBase. not strictly necesary but useful in case of errors.
  //the .erase is to actually delete the object
  //the couts are for telemetry.
  sort(indexes.rbegin(), indexes.rend());
  // Traditional for loop to delete elements from MainBase at the specified indexes
  for (int j = 0; j < indexes.size(); ++j) {
    int i = indexes[j];
      
    // Ensure index is within bounds
    if (i >= 0 && i < MainBase.size()) {
      MainBase.erase(MainBase.begin() + i);
      cout << "Deleted media at index: " << i << endl;
    }
  }
  cout << "Media deleted." << endl;
  //end code copied from GPT
  
  //only thing I need to delete...
  delete input;
}
//listing media. not strictly necesary but nice to have. 
void listMedia(vector<Media*> MainBase){
  for(auto i=MainBase.begin(); i!=MainBase.end(); ++i){
    if((*(*i)).getType()=='G'){
      cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: GAME, Title:"<<static_cast <Game*>(*i)->getTitle()<<", Year:"<<static_cast <Game*>(*i)->getYear()<<", Publisher:"<<static_cast <Game*>(*i)->getPublisher()<<", Rating:"<<static_cast <Game*>(*i)->getRating()<<endl;
    }else if((*(*i)).getType()=='U'){
      cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MUSIC, Title:"<<static_cast <Music*>(*i)->getTitle()<<", Artist:"<<static_cast <Music*>(*i)->getArtist()<<", Year:"<<static_cast <Music*>(*i)->getYear()<<", Duration:"<<static_cast <Music*>(*i)->getDuration()<<", Publisher:"<<static_cast <Music*>(*i)->getPublisher()<<endl;
    }else if((*(*i)).getType()=='O'){
      cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MOVIE, Title:"<<static_cast <Movie*>(*i)->getTitle()<<", Director:"<<static_cast <Movie*>(*i)->getDirector()<<", Year:"<<static_cast <Movie*>(*i)->getYear()<<", Duration:"<<static_cast <Movie*>(*i)->getDuration()<<", Rating:"<<static_cast <Movie*>(*i)->getRating()<<endl;
    }else{
      //this should be literally impossible but you never know what might happen.
      cout<<"ERROR! UNTYPED MEDIA"<<endl;
    }
  }
  return;
}

//searchMedia. never called in the delete function but the main functionality is all there, just with a few edits. 
void searchMedia(vector<Media*> MainBase){
  bool notQuit=true;
  char*input = new char[16];
  int searchIndex;
  while(notQuit){
    cout<<"What field do you wish to search by? (TITLE, YEAR, CANCEL)"<<endl;
    getStringFromInput(input);
    cout<<"Function got: "<<endl;
    for(int i=0; i<16; i++){
      cout<<input[i];
    }
    cout<<endl;
    notQuit=false;
    //I understand the use of SearchIndex may not be strictly needed but for a while I thought I was going to need literally every field.
    if(strcmp(input,"TITLE")==0){
      searchIndex=1;
    }else if(strcmp(input,"YEAR")==0){
      searchIndex=2;
    }else if(strcmp(input,"CANCEL")==0){
      return;
    }else{
      cout<<"Invalid Command."<<endl;
      notQuit=true;
    }
  }
  
  int numberfound=0;
  if(searchIndex==1){
    //search by title.
    cout<<"Search by title name:"<<endl;
    getStringFromInput(input);
    for(auto i=MainBase.begin(); i!=MainBase.end(); ++i){
      if (strcmp((input),(*i)->getTitle())==0){
        numberfound++;
        if((*(*i)).getType()=='G'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: GAME, Title:"<<static_cast <Game*>(*i)->getTitle()<<", Year:"<<static_cast <Game*>(*i)->getYear()<<", Publisher:"<<static_cast <Game*>(*i)->getPublisher()<<", Rating:"<<static_cast <Game*>(*i)->getRating()<<endl;
        }else if((*(*i)).getType()=='U'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MUSIC, Title:"<<static_cast <Music*>(*i)->getTitle()<<", Artist:"<<static_cast <Music*>(*i)->getArtist()<<", Year:"<<static_cast <Music*>(*i)->getYear()<<", Duration:"<<static_cast <Music*>(*i)->getDuration()<<", Publisher:"<<static_cast <Music*>(*i)->getPublisher()<<endl;
        }else if((*(*i)).getType()=='O'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MOVIE, Title:"<<static_cast <Movie*>(*i)->getTitle()<<", Director:"<<static_cast <Movie*>(*i)->getDirector()<<", Year:"<<static_cast <Movie*>(*i)->getYear()<<", Duration:"<<static_cast <Movie*>(*i)->getDuration()<<", Rating:"<<static_cast <Movie*>(*i)->getRating()<<endl;
        }else{
          cout<<"ERROR! UNTYPED MEDIA"<<endl;
        }
      }
    }
  }else if(searchIndex==2){
    //search by year.
    bool sacin=false;
    int nwyear;
    cout<<"Search by Year:"<<endl;
    while(sacin==false){
      cin>>nwyear;
      if(cin.fail()){
        cout<<"I think you did something wrong. Please try again."<<endl;
        cin.clear();
        cin.ignore(100000,'\n');
      }else{
        sacin=true;
      }
    }
    cin.ignore(100000,'\n');
    
    for(auto i=MainBase.begin(); i!=MainBase.end(); ++i){
      if (nwyear==((*i)->getYear())){
        numberfound++;
        if((*(*i)).getType()=='G'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: GAME, Title:"<<static_cast <Game*>(*i)->getTitle()<<", Year:"<<static_cast <Game*>(*i)->getYear()<<", Publisher:"<<static_cast <Game*>(*i)->getPublisher()<<", Rating:"<<static_cast <Game*>(*i)->getRating()<<endl;
        }else if((*(*i)).getType()=='U'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MUSIC, Title:"<<static_cast <Music*>(*i)->getTitle()<<", Artist:"<<static_cast <Music*>(*i)->getArtist()<<", Year:"<<static_cast <Music*>(*i)->getYear()<<", Duration:"<<static_cast <Music*>(*i)->getDuration()<<", Publisher:"<<static_cast <Music*>(*i)->getPublisher()<<endl;
        }else if((*(*i)).getType()=='O'){
          cout<<"Internal Index: "<<static_cast<int>(i-MainBase.begin())<<", Type: MOVIE, Title:"<<static_cast <Movie*>(*i)->getTitle()<<", Director:"<<static_cast <Movie*>(*i)->getDirector()<<", Year:"<<static_cast <Movie*>(*i)->getYear()<<", Duration:"<<static_cast <Movie*>(*i)->getDuration()<<", Rating:"<<static_cast <Movie*>(*i)->getRating()<<endl;
        }else{
          cout<<"ERROR! UNTYPED MEDIA"<<endl;
        }
      }
    }
  }
  cout<<"Total media found: "<<numberfound<<endl;
  delete input;
}
