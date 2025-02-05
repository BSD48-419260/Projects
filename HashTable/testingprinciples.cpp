#include<cmath>
#include<iostream>
#include<cstring>
#include<cmath>
using namespace std;


class Student{
  //this student only has a name for testing purposes.
 public:
  char* Firstname = new char[11];
  char* Lastname = new char[11];
  int ID;
  float GPA;
  Student(){

  }
  Student(char* newFirstname, char* newLastname, int newID, float newGPA){
    strncpy(Firstname,newFirstname,10);
    Firstname[10]='\0';
    strncpy(Lastname,newLastname,10);
    Lastname[10]='\0';
    ID = newID;
    GPA = newGPA;
  }
  ~Student(){
    delete[] Firstname;
    delete[] Lastname;
  }
};

class Node {
 private: //The node has two things, the link (what it goes to next), and the data
  Student* data;
  Node* link;
 public:
  Node(Student* argdata){
    data=argdata;
    link=nullptr;
  }
  ~Node(){
    delete data;
    data=nullptr;
    link=nullptr;
  }
  Node* getNext(){
    return link;
  }
  Student* getStudent(){
    return data;
  }
  void setNext(Node* arglink){
    link=arglink;
  }
};

void getStringFromInput(char* inpstring);
int blend(Student* blendy, int cap);
bool NeedRehash(Node* list);
void rehash(Node**& studarray, int& sizeofarray, bool& needreset);
void addStudent(Node**& studarray, int sizeofarray, int& newID, bool& needreset);
void blendAddChild(Node**& putchildin, int sizeofarray, Student* kid, bool& needreset);
void linearAdd(Node*& head, Node* current, Node* addme);
void AddDownTheList(Node**& studarray,int sizeofarray, Node* current, bool& needsreset);
Student* Randomkid(int& ID);
void addRandomKids(int howmany, int& ID, Node**&studarray, int sizeofarray, bool& needsreset);
void addRandomPreamble(int& ID, Node**&studarray, int sizeofarray, bool& needsreset);
void clearDown(Node* head);
void prepArray(Node **& studarray, int sizeofarray);
void listStudents(Node* head);
void readOutArray(Node** studarray, int sizeofarray);
void getStringFromInput(char* inpstring);
void killStudentPreamble(Node**& studarray, int sizeofarray);
void killStudent(Node* current, int ID);

int main(){
  srand(time(0));
  int sizeofarray=100;//the size of the array
  int resizes=0;//resizes. not strictly needed, and could probablt derive it. still, I want to know.
  int IDiteration=1;
  bool needsreset=false;
  Node** studarray = new Node*[sizeofarray];
  prepArray(studarray,sizeofarray);
  cout<<"==========================="<<endl;
  cout<<"Welcome to:"<<endl;
  cout<<"  _____         _____           _____ _____       __  __      ________ "<<endl;
  cout<<" / ___ \\        \\   /           \\   / \\   /      /  \\/  \\     \\  ____/ "<<endl;
  cout<<" | | /__\\        | |             | |   | |      / /\\__/\\ \\     | |     "<<endl;
  cout<<" | |___          | |             | |___| |      | |    | |     | |_/|  "<<endl;
  cout<<" \\____ \\         | |             | _____ |      | |    | |     |  _ |  "<<endl;
  cout<<"____ | |         | |             | |   | |      | |    | |     | | \\|  "<<endl;
  cout<<"\\  /_| |         | |___          | |   | |      | |    | |     | |___  "<<endl;
  cout<<" \\_____/ tudent /______\\ ister, /___\\ /___\\ ash/___\\  /___\\ap /______\\ dition."<<endl;
   bool notQuit=true;
  cout<<"(Please note this program is incapable of saving data, so don't actually use it for managing students)"<<endl;
  char inpstring[10];
  while(notQuit){
    //trying to be robust. Also, Command handler.
    cout<<"Please input a command. (Valid commands: ADD, ADDRANDOM, DELETE, PRINT, QUIT)"<<endl;
    for(int i=0; i<10; i++){
      inpstring[i]='\0';
    }
    cin >> inpstring;
    if(cin.fail()){
      cout<<"Something went wrong. Please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else if (strcmp(inpstring,"ADD")==0){
      addStudent(studarray, sizeofarray, IDiteration, needsreset);
    }else if (strcmp(inpstring,"ADDRANDOM")==0){
      addRandomPreamble(IDiteration,studarray,sizeofarray,needsreset);
    }else if (strcmp(inpstring,"DELETE")==0){
      killStudentPreamble(studarray,sizeofarray);
    }else if (strcmp(inpstring,"PRINT")==0){
      readOutArray(studarray,sizeofarray);
    }else if (strcmp(inpstring,"QUIT")==0){
      notQuit=false;
      //no command needed, just quit the loop.
    }else{
      cout<<"Invalid Command."<<endl;
    }
    while(needsreset){
      rehash(studarray,sizeofarray,needsreset);
      resizes++;
    }
  }
  cout<<"Have a nice day."<<endl;
  return 0;
}

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
    //being robust.
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

int blend(Student* blendy, int cap){
  char* fullname = new char[22];
  for(int i=0; i<22; i++){
    fullname[i]='\0';
  }
  strncpy(fullname,blendy->Firstname,strlen(blendy->Firstname));
  strcat(fullname,blendy->Lastname);
  fullname[21]='\0';
  unsigned long sum=0;
  for(int i=0; i<strlen(fullname); i++){
    sum=(i*sum*7489)+fullname[i];
  }
  delete[] fullname;
  return ((sum)%cap);
}

bool NeedRehash(Node* list){
 if(list!=nullptr){
   if(list->getNext()!=nullptr){
     if(list->getNext()->getNext()!=nullptr){
       if(list->getNext()->getNext()->getNext()!=nullptr){
	 cout<<"HELLO! WHAT THE HECK IS THIS!?"<<endl;
	 return true;
       }
     }
   }
 }
 return false;
}

void rehash(Node**& studarray, int& sizeofarray, bool& needsreset){
  Node** nuarray = new Node*[sizeofarray*2];
  needsreset=false;
  prepArray(nuarray,sizeofarray*2);
  for(int i=0; i<sizeofarray;i++){
    if(studarray[i]!=nullptr){
      if(studarray[i]->getStudent()!=nullptr){
	AddDownTheList(nuarray,sizeofarray*2,studarray[i],needsreset);
      }
      clearDown(studarray[i]);
    }
  }
  delete[] studarray;
  studarray = nuarray;
  sizeofarray=sizeofarray*2;
}

void addStudent(Node**& studarray, int sizeofarray, int& newID, bool& needsreset){
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
  //ID incrementing.
  newkid->ID=newID++;
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
  blendAddChild(studarray, sizeofarray, newkid, needsreset);
  delete newkid;
  return;
}

void blendAddChild(Node**& putchildin, int sizeofarray, Student* kid, bool& needsreset){
  cout<<"Hi"<<endl;
  Student* copykid = new Student(kid->Firstname,kid->Lastname,kid->ID,kid->GPA);
  copykid->Firstname[10]='\0';
  cout<<"there"<<endl;
  Node* copybox = new Node(copykid);
  copykid->Lastname[10]='\0';
  cout<<"buddy"<<endl;
  cout<<sizeofarray<<endl;
  cout<<kid<<endl;
  cout<<blend(kid,sizeofarray)<<endl;
  cout<<putchildin[blend(kid,sizeofarray)]<<endl;
  linearAdd(putchildin[blend(kid,sizeofarray)],putchildin[blend(kid,sizeofarray)], copybox);
  cout<<"chum"<<endl;
  if(needsreset==false){
    needsreset = NeedRehash(putchildin[blend(kid,sizeofarray)]);
  }
  cout<<"pal"<<endl;
}

void linearAdd(Node*& head, Node* current, Node* addme){
  cout<<"My favorite food is"<<endl;
  if (current->getStudent()==nullptr){
    cout<<"Salt"<<endl;
    delete current;
    current=new Node(addme->getStudent());
    current->setNext(nullptr);
      //current->setStudent(addme->getStudent());
    addme =new Node(nullptr);
    delete addme;
  }else if (head->getStudent()->ID > addme->getStudent()->ID){
    cout<<"Sodium"<<endl;
    head = addme;
    head->setNext(current);
  }else if (current->getNext()==nullptr){
    cout<<"Stibnite"<<endl;
    current->setNext(addme);
  }else if ((current->getStudent()->ID < addme->getStudent()->ID)&&(current->getNext()->getStudent()->ID > addme->getStudent()->ID)){
    cout<<"Sauteed Beef"<<endl;
    addme->setNext(current->getNext());
    current->setNext(addme);
  }else{
    cout<<"The concept of Steel"<<endl;
    linearAdd(head, current->getNext(), addme);
  }
}

void AddDownTheList(Node**& studarray,int sizeofarray, Node* current, bool& needsreset){
  if(current!=nullptr){
    if (current->getStudent()!=nullptr){
      blendAddChild(studarray,sizeofarray,current->getStudent(),needsreset);
      //delete current->getStudent();
    }
  }
  if(current->getNext()!=nullptr){
    AddDownTheList(studarray,sizeofarray,current->getNext(),needsreset);
  }
}

Student* Randomkid(int& ID){
  int amt=(rand()%7+3);
  char* fname = new char[11];
  for(int i=0; i<11;i++){
    fname[i]='\0';
  }
  char nuchar = (rand()%26)+65;
  strncpy(fname, &nuchar,1);
  for(int i=0; i<amt;i++){
    nuchar = (rand()%26)+97;
    strncat(fname, &nuchar,1);
  }
  amt=(rand()%5+5);
  char* lname = new char[11];
  for(int i=0; i<11;i++){
    lname[i]='\0';
  }
  nuchar = (rand()%26)+65;
  strncpy(lname, &nuchar,1);
  for(int i=0; i<amt;i++){
    nuchar = (rand()%26)+97;
    strncat(lname, &nuchar,1);
  }
  Student* randokid = new Student(fname,lname,ID++,(((float)(rand()%400))/100));
  delete[] fname;
  delete[] lname;
  return randokid;
}

void addRandomKids(int howmany, int& ID, Node**&studarray, int sizeofarray, bool& needsreset){
  for(int i=0; i<howmany; i++){
     Student* kiddo = Randomkid(ID);
     blendAddChild(studarray, sizeofarray, kiddo, needsreset);
     delete kiddo;
  }
}

void addRandomPreamble(int& ID, Node**&studarray, int sizeofarray, bool& needsreset){
  bool acin=false;
  int numbtoadd;
  while (acin==false){
    cout<<"Please give a number of students to add"<<endl;
    cin>>numbtoadd;
    if(cin.fail()){
      cout<<"ERROR! please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  cout<<"Adding students..."<<endl;
  addRandomKids(numbtoadd,ID,studarray,sizeofarray,needsreset);
  cout<<"Complete! Added "<<numbtoadd<<" Students."<<endl;
}

void clearDown(Node* head){
  if(head==nullptr){
    return;
  }
  if(head->getNext()!=nullptr){
    clearDown(head->getNext());
  }
  delete head;
  head=nullptr;
}

void prepArray(Node **& studarray, int sizeofarray){
  for(int i=0; i<sizeofarray;i++){
    studarray[i] = new Node(nullptr);
  }
}

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

void readOutArray(Node**studarray,int sizeofarray){
  cout<<"Size of Array: "<<sizeofarray<<endl;
  for(int i=0; i<sizeofarray; i++){
    cout<<endl<<"Box Number: "<<i<<endl;
    cout<<"Contents: "<<endl;
    listStudents(studarray[i]);
  }
}

//Student Deleter Preamble.
void killStudentPreamble(Node**& studarray, int sizeofarray){
  readOutArray(studarray, sizeofarray);
  char* inpstring = new char[11];
  Student* emptychild = new Student();
  cin.clear();
  cin.ignore(100000,'\n');
  cout<<"Please provide student's first name.(Case and character Sensitive)"<<endl;
  getStringFromInput(inpstring);
  strncpy(emptychild->Firstname,inpstring,11);
  cout<<"Please provide student's last name.(Case and character Sensitive)"<<endl;
  getStringFromInput(inpstring);
  strncpy(emptychild->Lastname,inpstring,11);
  int box = blend(emptychild,sizeofarray);
  cout<<"Student is in box number "<<box<<endl;
  listStudents(studarray[box]);
  delete[] inpstring;
  delete emptychild;
  if (studarray[box]->getStudent()==nullptr){
    cout<<"Box empty. Canceling DELETE..."<<endl;
    return;
  }
  cout<<"Due to certain factors, multiple students with the same name can exist."<<endl;
  cout<<"Please provide ID of student you wish to delete. if some mistake has been made, enter a negative number to cancel"<<endl;
  bool acin=false;
  int index;
  while (acin==false){
    cout<<"Please Enter Student ID (Serial Integer): "<<endl;
    cin>>index;
    if(cin.fail()){
      cout<<"I think you did something wrong. please try again."<<endl;
      cin.clear();
      cin.ignore(100000,'\n');
    }else{
      acin=true;
    }
  }
  if(index<0){
    return;
  }
  if(studarray[box]->getStudent()->ID==index){
    if(studarray[box]->getNext()!=nullptr){
      Student* buffer = studarray[box]->getStudent();
      Node* afterhead = studarray[box]->getNext();
      delete studarray[box];
      studarray[box] = new Node(afterhead->getStudent());
      studarray[box]->setNext(afterhead->getNext());
      afterhead = new Node(buffer);
      delete afterhead;
    }else{
      delete studarray[box]->getStudent();
      studarray[box] = new Node(nullptr);
    }
    return;
  }
  killStudent(studarray[box],index);
  
}

//Main student deletion code. Recycled from old project.
void killStudent(Node* current, int ID){
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
      killStudent(current->getNext(),ID);
    }
  }
}
