/*
 StudentLister LinkedList Program
 Inteded to work as a prototype database for students using a linkedlist.
 the node called 'head' holds the start of the LinkedList
 Made by Elliott VanOrman for Jason Galbraith's C++ C++/Data Structures Class
 12/19/2024
 */
#include <cmath>
#include <iostream>
#include <vector>
#include <cstring>
#include "Student.cpp"
#include "Node.h"
using namespace std;


//signature list
void getStringFromInput(char* inpstring);
void addStudent(Node* head);
void linearAdd(Node* current, Node* addme);
void killStudent(Node* head);
void deleteStudent(Node* head, int ID);
void listStudents(Node* head);
void modStudent(Node* head);
void modifyStudent(Node* current, int ID);
void modifyThisStudent(Student* student);
void averageGPAS(Node* head);
void printAverage(Node* head, float GPA, int count);
Student* getStudentByID(int ID,Node* head);
int getID();
 

int main(){
  Node * head = new Node(nullptr);
  //opening scrawl
  cout<<"==========================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<"  _____         _____           _____         _____        ________ "<<endl;
  cout<<" / ___ \\        \\   /           \\   /         \\   /        \\  ____/ "<<endl;
  cout<<" | | /__\\        | |             | |           | |          | |     "<<endl;
  cout<<" | |___          | |             | |           | |          | |_/|  "<<endl;
  cout<<" \\____ \\         | |             | |           | |          |  _ |  "<<endl;
  cout<<"____ | |         | |             | |           | |          | | \\|  "<<endl;
  cout<<"\\  /_| |         | |___          | |___        | |___       | |___  "<<endl;
  cout<<" \\_____/ tudent /______\\ ister, /______\\ inked /______\\ ist /______\\ dition."<<endl;
  bool notQuit=true;
  cout<<"(Please note this program is incapable of saving data, so don't actually use it for managing students)"<<endl;
  char inpstring[8];
  while(notQuit){
    //trying to be robust. Also, Command handler.
    cout<<"Please input a command. (Valid commands: ADD, DELETE, PRINT, MODIFY, AVERAGE, QUIT)"<<endl;
    for(int i=0; i<8; i++){
      inpstring[i]='\0';
    }
    cin >> inpstring;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else if (strcmp(inpstring,"ADD")==0){
      addStudent(head);
    }else if (strcmp(inpstring,"DELETE")==0){
      killStudent(head);
    }else if (strcmp(inpstring,"PRINT")==0){
      listStudents(head);
    }else if (strcmp(inpstring,"MODIFY")==0){
      modStudent(head);
    }else if (strcmp(inpstring,"AVERAGE")==0){
      averageGPAS(head);
    }else if (strcmp(inpstring,"QUIT")==0){
      notQuit=false;
      //no command needed, just quit the loop.
    }else{
      cout<<"Invalid Command."<<endl;
    }
  }
  cout<<"Have a good day."<<endl;
  return 0;
}

//primary string getter, as I was tired of repeating robust input code.
void getStringFromInput(char* inpstring){
  char bufferarray [11];
  //make sure it works
  bool acin=false;
  for(int i=0;i<11;i++){
    bufferarray[i]='\0';
  }
  while(acin==false){
    cout<<"10 characters or less, please."<<endl;
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
  strncpy(inpstring, bufferarray, 10);
  inpstring[10]='\0';
  cout<<endl;
  return;
}

//student adding command. Despite name, actuall adding logic sits in linearAdd function. this one just gets all the information
void addStudent(Node* head){
  Student* newkid = new Student();
  bool acin=false;
  //name getting
  char* inpstring = new char[11];
  cin.clear();
  cin.ignore(100000,'\n');
  cout<<"Please input First Name"<<endl;
  getStringFromInput(inpstring);
  strncpy(newkid->Firstname,inpstring,11);
  cout<<"Please input Last Name"<<endl;
  getStringFromInput(inpstring);
  strncpy(newkid->Lastname,inpstring,11);
  //ID getting. can recycle getID method here.
  int posid;
  acin=false;
  while(acin==false){
    posid=getID();
    if(getStudentByID(posid,head)==nullptr){
      acin=true;
    }else{
      cout<<"A student with that ID already exists!"<<endl;
    }
  }
  newkid->ID=posid;
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
  newkid->GPA=newGPA;
  Node* addme = new Node(newkid);
  addme->setNext(nullptr);
  linearAdd(head,addme);
  return;
}

//this all this code does is find a student by their ID number.
Student* getStudentByID(int ID,Node* head){
  if (head->getStudent()==nullptr){
      return nullptr;
  }else if(head->getStudent()->ID==ID){
    return head->getStudent(); 
  }else{
    if (head->getNext()==nullptr){
      return nullptr;
    }else{
      return getStudentByID(ID,head->getNext());
    }
  }
}

//actual student adding logic. above code is just data gathering
void linearAdd(Node* current, Node* addme){
  if (current->getStudent()==nullptr){
    delete current;
    current=new Node(addme->getStudent());
    current->setNext(nullptr);
    addme =new Node(nullptr);
    delete addme;
  }else if (head->getStudent()->ID > addme->getStudent()->ID){
    head = addme;
    head->setNext(current);
  }else if (current->getNext()==nullptr){
    current->setNext(addme);
  }else if ((current->getStudent()->ID < addme->getStudent()->ID)&&(current->getNext()->getStudent()->ID > addme->getStudent()->ID)){
    addme->setNext(current->getNext());
    current->setNext(addme);
  }else{
    linearAdd(head, current->getNext(), addme);
  }

}

//actual lister function. when called, prints all students
void listStudents(Node* head){
  if(head->getStudent()==nullptr){
    cout<<"There are no students!"<<endl;
    return;
  }
  cout<<"Student Name: "<<head->getStudent()->Firstname<<" "<<head->getStudent()->Lastname<<" ID: "<<head->getStudent()->ID<<" GPA: "<<(round(head->getStudent()->GPA * 100))/100<<endl;
  if(head->getNext()!=nullptr){
    listStudents(head->getNext());
  }
}


//student deleter preamble. doesn't actually delete anything, just preps for the real deletion code. 
void killStudent(Node* head){
  listStudents(head);
  if(head->getStudent()==nullptr){
    return;
  }
  int index = getID();
  if(head->getStudent()->ID==index){
    if(head->getNext()!=nullptr){
      Student* buffer = head->getStudent();
      Node* afterhead = head->getNext();
      delete head;
      head = new Node(afterhead->getStudent());
      head->setNext(afterhead->getNext());
      afterhead = new Node(buffer);
      delete afterhead;
    }else{
      delete head->getStudent();
      head = new Node(nullptr);
    }
    return;
  }
  deleteStudent(head,index);
}

//Real deleter.clears memory and removes from the list.
void deleteStudent(Node* current, int ID){
  if(current->getNext()==nullptr){
    //if we're in the head
    delete current->getStudent();
    current = new Node(nullptr);
    return;
  }else if(current->getNext()->getStudent()->ID==ID){
    //take the node out of the loop, then delete it.
    Node* killbuffer = current->getNext();
    current->setNext(current->getNext()->getNext());
    delete killbuffer;
    return;
  }else{
    //if we can't move on, we should just leave.
    if (current->getNext()->getNext()==nullptr){
      cout<<"ERROR: No student with that ID exists!"<<endl;
    }else {
      deleteStudent(current->getNext(),ID);
    }
  }
}

//gpa Averager preamble. doesn't actually calculate, just kicks off the process.
void averageGPAS(Node* head){
  if(head->getStudent()==nullptr){
    return;
  }
  printAverage(head, 0,0);
}

//actual recursive GPA printer function
void printAverage(Node* head, float GPA, int count){
  GPA+=head->getStudent()->GPA;
  count+=1;
  if(head->getNext()==nullptr){
    cout<<"Number of students: "<<count<<". Average GPA: "<<(round((GPA/count) * 100))/100<<endl;
  }else{
    printAverage(head->getNext(),GPA,count);
  }
}

//for getting IDs. used both when declaring an when searching by
int getID(){
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

/*
====================================================
CONVERSION TO LINKEDLIST REQUIRED BEYOND THIS POINT!
====================================================
*/

//student modifier preamble. 
void modStudent(Node* head){
  listStudents(head);
  if(head->getStudent()==nullptr){
    return;
  }
  int index = getID();
  if(head->getStudent()->ID==index){
    modifyThisStudent(head->getStudent());
    return;
  }
  modifyStudent(head,index);
}

//Student Modifier. not strictly needed, but I have time 
void modifyStudent(Node* current, int ID){
  if(current->getNext()->getStudent()->ID==ID){
    //if we find the kid, modify the kid.
    modifyThisStudent(current->getNext()->getStudent());
  }else{
    //if we can't move on, we should just leave.
    if (current->getNext()->getNext()==nullptr){
      cout<<"ERROR: No student with that ID exists!"<<endl;
    }else {
      modifyStudent(current->getNext(),ID);
    }
  }
}

//actual individual modification. not recursive, but I feel it to be a complex enough process to warrant it's own function.
void modifyThisStudent(Student* modKid){
  bool acin=false;
  bool notQuit=true;
  char* inpstring = new char[11];
  //name getting
  while(notQuit){
    //trying to be robust. Also, Command handler.
    cout<<"Please input which field to modify. (Valid commands: FIRSTNAME, LASTNAME, GPA, CANCEL)\n(Please note, it's only possible to modify ID by deleting and recreating this student.)"<<endl;
    //that's technically not true. there is a way I could do it, but I think I need to worry more about getting the next, presumably more difficult project finished
    for(int i=0; i<11; i++){
      inpstring[i]='\0';
    }
    cin >> inpstring;
    notQuit=false;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else if (strcmp(inpstring,"FIRSTNAME")==0){
      cin.clear();
      cin.ignore(100000,'\n');
      cout<<"Please input First Name"<<endl;
      getStringFromInput(inpstring);
      strncpy(modKid->Firstname,inpstring,11);  
    }else if (strcmp(inpstring,"LASTNAME")==0){
      cin.clear();
      cin.ignore(100000,'\n');
      cout<<"Please input Last Name"<<endl;
      getStringFromInput(inpstring);
      strncpy(modKid->Lastname,inpstring,11);
    }else if (strcmp(inpstring,"GPA")==0){
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
      modKid->GPA=newGPA;
    }else if (strcmp(inpstring,"CANCEL")==0){
      //NotQuit already set to false
      //no command needed, just quit the loop.
    }else{
      notQuit=true;
      cout<<"Invalid Command."<<endl;
    }
  }
  delete[] inpstring;
  return;
}

/*

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
*/

