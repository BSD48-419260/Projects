#include "Student.h"

Student::Student(char* newFirstname, char* newLastname, int newID, float newGPA){
  strncpy(Firstname,newFirstname,10);
  strncpy(Lastname,newLastname,10);
}
Student::~Student(){
  delete[] Firstname;
  delete[] Lastname;
}