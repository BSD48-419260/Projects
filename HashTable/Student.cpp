#include "Student.h"

Student::Student(){
  
}
Student::Student(char* newFirstname, char* newLastname, int newID, float newGPA){
  strncpy(Firstname,newFirstname,10);
  Firstname[10]='\0';
  strncpy(Lastname,newLastname,10);
  Lastname[10]='\0';
  ID = newID;
  GPA = newGPA;
}
Student::~Student(){
  delete[] Firstname;
  delete[] Lastname;
}
