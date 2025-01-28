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
    strncpy(Lastname,newLastname,10);
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
void rehash(Node**& studarray, int& sizeofarray);
void addStudent(Node**& studarray, int sizeofarray, int newID);
void blendAddChild(Node**& putchildin, int sizeofarray, Student* kid);
void linearAdd(Node*& head, Node* current, Node* addme);
Student* Randomkid(int& ID);
void clearDown(Node* head);
void prepArray(Node **& studarray, int sizeofarray);
void listStudents(Node* head);
void readOutArray(Node** studarray, int sizeofarray);
void getStringFromInput(char* inpstring);

int main(){
  srand(time(0));
  int sizeofarray=100;//the size of the array
  int resizes=0;//resizes. not strictly needed, and could probablt derive it. still, I want to know.
  int IDiteration=1;
  Node** studarray = new Node*[sizeofarray];
  prepArray(studarray,sizeofarray);
  readOutArray(studarray, sizeofarray);
  studarray[20] = new Node(new Student("Test","Kid", -1, 0.0f));

  readOutArray(studarray, sizeofarray);
  
  prepArray(studarray,sizeofarray);
  for(int i=0; i<100; i++){
    studarray[i] = new Node(Randomkid(IDiteration));
  }
  readOutArray(studarray, sizeofarray);
  cout<<"1"<<endl;
  rehash(studarray, sizeofarray);
  cout<<"-1"<<endl;
  readOutArray(studarray,sizeofarray);
	       
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
  cout<<"Lion"<<endl;
  char* fullname = new char[22];
  cout<<"Fulcrum"<<endl;
  for(int i=0; i<22; i++){
    fullname[i]='\0';
  }
  cout<<"Peter"<<endl;
  strncpy(fullname,blendy->Firstname,strlen(blendy->Firstname));
  cout<<"Door"<<endl;
  strcat(fullname,blendy->Lastname);
  cout<<"Lemons"<<endl;
  double sum=0;
  cout<<"Curse"<<endl;
  for(int i=0; i<strlen(fullname); i++){
    sum+=cos(floor(fullname[i]*i))*fullname[i];
  }
  cout<<"Sanctum"<<endl;
  delete fullname;
  cout<<"Ferris"<<endl;
  return ((int)(floor(sum))%cap);
}
void rehash(Node**& studarray, int& sizeofarray){
  cout<<"A"<<endl;
  Node** nuarray = new Node*[sizeofarray*2];
  cout<<"B"<<endl;
  prepArray(nuarray,sizeofarray*2);
  cout<<"C"<<endl;
  for(int i=0; i<sizeofarray;i++){
    if(studarray[i]!=nullptr){
      cout<<"Alpha"<<endl;
      if(studarray[i]->getStudent()!=nullptr){
	cout<<"Bravo"<<endl;
	blendAddChild(nuarray, sizeofarray*2, studarray[i]->getStudent());
	cout<<"Charlie"<<endl;
	if(studarray[i]->getNext()!=nullptr){
	  cout<<"Delta"<<endl;
	  blendAddChild(nuarray, sizeofarray*2, studarray[i]->getNext()->getStudent());
	  cout<<"Echo"<<endl;
	  if(studarray[i]->getNext()->getNext()!=nullptr){
	    cout<<"Foxtrot"<<endl;
	    blendAddChild(nuarray, sizeofarray*2, studarray[i]->getNext()->getNext()->getStudent());
	    cout<<"Golf"<<endl;
	  }
	}
      }
      cout<<"Hotel"<<endl;
      clearDown(studarray[i]);
      cout<<"India"<<endl;
    }
  }
  cout<<"D"<<endl;
  delete[] studarray;
  cout<<"E"<<endl;
  studarray = nuarray;
  cout<<"F"<<endl;
  sizeofarray=sizeofarray*2;
  cout<<"G"<<endl;
}

void addStudent(Node**& studarray, int sizeofarray, int newID){
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
  blendAddChild(studarray, sizeofarray, newkid);
  delete newkid;
  return;
}

void blendAddChild(Node**& putchildin, int sizeofarray, Student* kid){
  cout<<"Fear"<<endl;
  Student* copykid = new Student(kid->Firstname,kid->Lastname,kid->ID,kid->GPA);
  cout<<"Anger"<<endl;
  Node* copybox = new Node(copykid);
  cout<<"Hate"<<endl;
  linearAdd(putchildin[blend(kid,sizeofarray)],putchildin[blend(kid,sizeofarray)], copybox);
  cout<<"Suffering"<<endl;
}
 
void linearAdd(Node*& head, Node* current, Node* addme){
  cout<<"You're trying to kidnap what I've rightfully stolen!"<<endl;
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
  cout<<"The short man must not get the last word"<<endl;
}


Student* Randomkid(int& ID){
  int amt=(rand()%7+3);
  char* fname = new char[11];
  for(int i=0; i<11;i++){
    fname[i]='\0';
  }
  char* nuchar = new char((rand()%26)+65);
  strncpy(fname, nuchar,1);
  for(int i=0; i<amt;i++){
    delete nuchar;
    nuchar = new char((rand()%26)+97);
    strncat(fname, nuchar,1);
  }
  
  amt=(rand()%5+5);
  char* lname = new char[11];
  for(int i=0; i<11;i++){
    lname[i]='\0';
  }
  delete nuchar;
  nuchar = new char((rand()%26)+65);
  strncpy(lname, nuchar,1);
  for(int i=0; i<amt;i++){
    delete nuchar;
    nuchar = new char((rand()%26)+97);
    strncat(lname, nuchar,1);
  }
  Student* randokid = new Student(fname,lname,ID++,(((float)(rand()%400))/100));
  delete[] fname;
  delete[] lname;
  return randokid;
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
    clearDown(studarray[i]);
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
