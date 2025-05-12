/*
 StudentLister Program
 Inteded to work as a prototype database for students
 students are structs kept in student* vector.
 Made by Elliott VanOrman for Jason Galbraith's C++ C++/Data Structures Class
 10/3/2024
 */
#include <cmath>
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

//student struct. no defaults.
struct Student{
  char Firstname[11];
  char Lastname[11];
  int ID;
  float GPA;
};


//signature list
void addStudent(vector <Student*> & StudentList);
void killStudent(vector <Student*> & StudentList);
void listStudents(vector <Student*> StudentList);
void modStudent(vector <Student*> & StudentList);
int getIndex(int ID,vector <Student*> & StudentList);
int getID(vector <Student*> & StudentList);


int main(){
  vector <Student*> StudentList;
  //opening scrawl
  cout<<"==========================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<"  ____         ___"<<endl;
  cout<<" / ___\\        | |"<<endl;
  cout<<" | | |_\\       | |"<<endl;
  cout<<" | |__         | |"<<endl;
  cout<<" \\___ \\        | |"<<endl;
  cout<<"__  | |        | |"<<endl;
  cout<<"\\ |_| |        | |___"<<endl;
  cout<<" \\____/ tudent |____| ister"<<endl;
  bool notQuit=true;
  cout<<"(Please note this program is incapable of saving data, so don't actually use it for managing students)"<<endl;
  while(notQuit){
    //trying to be robust. Also, Command handler.
    cout<<"Please input a command. (Valid commands: ADD, DELETE, PRINT, MODIFY, QUIT)"<<endl;
    char inpstring[7];
    cin >> inpstring;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else if (strcmp(inpstring,"ADD")==0){
      addStudent(StudentList);
    }else if (strcmp(inpstring,"DELETE")==0){
      killStudent(StudentList);
    }else if (strcmp(inpstring,"PRINT")==0){
      listStudents(StudentList);
    }else if (strcmp(inpstring,"MODIFY")==0){
      modStudent(StudentList);
    }else if (strcmp(inpstring,"QUIT")==0){
      notQuit=false;
      //no command needed, just quit the loop.
    }else{
      cout<<"Invalid Command."<<endl;
    }
  }
  cout<<"Have a wonderful day."<<endl;
  return 0;
}

//student adding command
void addStudent(vector <Student*> & StudentList){
  Student* newkid = new Student();
  bool acin=false;
  //name getting
  char inpstring[11];
  //First name getter
  for(int i=0; i<11; i++){
    inpstring[i]='\0';
  }
  cin.ignore(100000,'\n');
  while (acin==false){
    cout<<"Please Enter Firstname (10 characters or less): "<<endl;
    cin.getline(inpstring,sizeof(inpstring));
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  for(int i=0; i<10; i++){
    (*newkid).Firstname[i]=inpstring[i];
  }
  (*newkid).Firstname[10]='\0';
  //Last name getter
  acin=false;
  for(int i=0; i<11; i++){
    inpstring[i]='\0';
  }
  while (acin==false){
    cout<<"Please Enter Lastname (10 characters or less): "<<endl;
    cin.getline(inpstring,sizeof(inpstring));
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  for(int i=0; i<10; i++){
    (*newkid).Lastname[i]=inpstring[i];
  }
  (*newkid).Lastname[10]='\0';
  //ID getting. can recycle getID method here.
  int posid;
  acin=false;
  while(acin==false){
    posid=getID(StudentList);
    if(getIndex(posid,StudentList)==-1){
      acin=true;
    }else{
      cout<<"A student with that ID already exists!"<<endl;
    }
  }
  (*newkid).ID=posid;
  //GPA getting
  float newGPA;
  acin=false;
  while (acin==false){
    cout<<"Please Enter GPA: "<<endl;
    cin>>newGPA;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  acin=false;
  (*newkid).GPA=newGPA;
  StudentList.push_back(newkid);
  //making sure the kid exists before returning.
  return;
}

//student deleter. clears memory and removes from the list.
void killStudent(vector <Student*> & StudentList){
  listStudents(StudentList);
  int index = getIndex(getID(StudentList),StudentList);
  if (index == -1){
    cout<<"INVALID ID"<<endl;
    return;
  }
  //clear the data first. nobody likes a memory leak.
  delete *(StudentList.begin()+index);
  //then clear the part of the list.
  StudentList.erase(StudentList.begin()+index);
  return;
}

//actual lister function. when called, prints all students
void listStudents(vector <Student*> StudentList){
  for(auto i=StudentList.begin(); i!=StudentList.end(); ++i){
    cout<<"Firstname: "<<(*(*i)).Firstname<<", Lastname: "<<(*(*i)).Lastname<<", ID: "<<(*(*i)).ID<<", GPA: "<<(round((*(*i)).GPA * 100))/100<<endl;
  }
  return;
}

//student modifier. because why not?
void modStudent(vector <Student*> & StudentList){
  listStudents(StudentList);
  int index = getIndex(getID(StudentList),StudentList);
  if(index==-1){
    cout<<"INVALID ID"<<endl;
  }
  bool lacin=false;
  //almost all of these are copied directly from the AddStudent function.
  while (lacin==false){
    cout<<"Field to Modify. (Valid commands: FIRSTNAME, LASTNAME, ID, GPA, NEVERMIND)"<<endl;
    char linpstring[10];
    cin >> linpstring;
    lacin=true;
    bool acin=false;
    //Commands should be pretty clear on what is being modified.
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
      lacin=false;
    }else if (strcmp(linpstring,"FIRSTNAME")==0){
      char inpstring[11];
      for(int i=0; i<11; i++){
	inpstring[i]='\0';
      }
      cin.ignore(100000,'\n');
      while (acin==false){
	cout<<"Please Enter Firstname (10 characters or less): "<<endl;
	cin.getline(inpstring,sizeof(inpstring));
	if(cin.fail()){
	  cout<<"I think you did something wrong. please try again."<<endl;
	  cin.clear();
	  cin.ignore(100000,'\n');
	}else{
	  acin=true;
	}
      }
      for(int i=0; i<10; i++){
	(**(StudentList.begin()+index)).Firstname[i]=inpstring[i];
      }
      (**(StudentList.begin()+index)).Firstname[10]='\0';
    }else if (strcmp(linpstring,"LASTNAME")==0){
      char inpstring[11];
      for(int i=0; i<11; i++){
	inpstring[i]='\0';
      }
      cin.ignore(100000,'\n');
      while (acin==false){
	cout<<"Please Enter Lastname (10 characters or less): "<<endl;
	cin.getline(inpstring,sizeof(inpstring));
	if(cin.fail()){
	  cout<<"I think you did something wrong. please try again."<<endl;
	  cin.clear();
	  cin.ignore(100000,'\n');
	}else{
	  acin=true;
	}
      }
      for(int i=0; i<10; i++){
	(**(StudentList.begin()+index)).Lastname[i]=inpstring[i];
      }
      (**(StudentList.begin()+index)).Lastname[10]='\0';
    }else if (strcmp(linpstring,"ID")==0){
      int posid;
      acin=false;
      while(acin==false){
	posid=getID(StudentList);
	if(getIndex(posid,StudentList)==-1){
	  acin=true;
	}else{
	  cout<<"A student with that ID already exists!"<<endl;
	}
      }
      (**(StudentList.begin()+index)).ID=posid;
    }else if (strcmp(linpstring,"GPA")==0){
      float newGPA;
      acin=false;
      while (acin==false){
	cout<<"Please Enter GPA: "<<endl;
	cin>>newGPA;
	if(cin.fail()){
	  cout<<"I think you did something wrong. please try again."<<endl;
	  cin.clear();
	  cin.ignore(100000,'\n');
	}else{
	  acin=true;
	}
      }
      acin=false;
      (**(StudentList.begin()+index)).GPA=newGPA;
    }else if (strcmp(linpstring,"NEVERMIND")==0){
      return;
      //no command needed, just quit the function.
    }else{
      cout<<"Invalid Command."<<endl;
      lacin=false;
    }
  }
  return;
}

//for getting index of student in the list
int getIndex(int ID, vector <Student*> & StudentList){
  for(auto i = StudentList.begin(); i!=StudentList.end(); ++i){
    int thisID = (*(*i)).ID;
    if (thisID==ID){
      return (i-StudentList.begin());
    }
  }
  return -1;
}

//for getting IDs.
int getID(vector <Student*> & StudentList){
  bool acin=false;
  int ID;
  while (acin==false){
    cout<<"Please Enter Student ID (Serial Integer): "<<endl;
    cin>>ID;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  return ID;
}
