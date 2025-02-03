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
void addStudent(Node**& studarray, int sizeofarray, int newID, bool& needreset);
void blendAddChild(Node**& putchildin, int sizeofarray, Student* kid, bool& needreset);
void linearAdd(Node*& head, Node* current, Node* addme);
void AddDownTheList(Node**& studarray,int sizeofarray, Node* current, bool& needsreset);
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
  bool needsreset=false;
  Node** studarray = new Node*[sizeofarray];
  prepArray(studarray,sizeofarray);
  readOutArray(studarray, sizeofarray);
  /*
  studarray[0] = new Node(new Student("Test","Kid", -1, 0.0f));
  studarray[0]->setNext(new Node(new Student("Test","Kid2", -2, 0.0f)));
  studarray[0]->getNext()->setNext(new Node(new Student("Test","Kid3", -3, 0.0f)));
  studarray[0]->getNext()->getNext()->setNext(new Node(new Student("Test","Kid4", -4, 0.0f)));
  */
  
  readOutArray(studarray, sizeofarray);
  
  for(int i=0; i<400; i++){
     Student* kiddo = Randomkid(IDiteration);
     blendAddChild(studarray, sizeofarray, kiddo, needsreset);
     if(needsreset){
       cout<<"I see it."<<endl;
     }
     delete kiddo;
  }
  
  readOutArray(studarray, sizeofarray);
  cout<<"1"<<endl;
  needsreset=true;
  while(needsreset){
    cout<<"What?"<<endl;
    rehash(studarray, sizeofarray, needsreset);
    resizes++;
    readOutArray(studarray,sizeofarray);
  }
  cout<<"-1"<<endl;
  cout<<resizes<<endl;
	       
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
  double sum=0;
  for(int i=0; i<strlen(fullname); i++){
    sum+=cos(floor(fullname[i]*i))*pow(fullname[i],(i%3)+1);
  }
  sum=sum*strlen(fullname);
  delete fullname;
  return ((int)abs((floor(sum)))%cap);
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
  cout<<"Am"<<endl;
  Node** nuarray = new Node*[sizeofarray*2];
  cout<<"I"<<endl;
  needsreset=false;
  cout<<"Having"<<endl;
  prepArray(nuarray,sizeofarray*2);
  cout<<"a"<<endl;
  for(int i=0; i<sizeofarray;i++){
    cout<<"midlife"<<endl;
    if(studarray[i]!=nullptr){
      if(studarray[i]->getStudent()!=nullptr){
	cout<<"Crisis?"<<endl;
	AddDownTheList(nuarray,sizeofarray*2,studarray[i],needsreset);
      }
      clearDown(studarray[i]);
    }
  }
  cout<<"...What?"<<endl;
  delete[] studarray;
  studarray = nuarray;
  sizeofarray=sizeofarray*2;
}

void addStudent(Node**& studarray, int sizeofarray, int newID, bool& needsreset){
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
  Student* copykid = new Student(kid->Firstname,kid->Lastname,kid->ID,kid->GPA);
  copykid->Firstname[10]='\0';
  Node* copybox = new Node(copykid);
  copykid->Lastname[10]='\0';
  linearAdd(putchildin[blend(kid,sizeofarray)],putchildin[blend(kid,sizeofarray)], copybox);
  if(needsreset==false){
    needsreset = NeedRehash(putchildin[blend(kid,sizeofarray)]);
  }
}

void linearAdd(Node*& head, Node* current, Node* addme){
  if (current->getStudent()==nullptr){
    delete current;
    current=new Node(addme->getStudent());
    current->setNext(nullptr);
      //current->setStudent(addme->getStudent());
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
