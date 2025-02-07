#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<cstring>
using namespace std;

class Student{
  //this student only has a name for testing purposes.
 public:
  char* Firstname = new char[11];
  char* Lastname = new char[11];
  int ID;
  float GPA;
  Student();
  Student(char*, char*, int, float);
  ~Student();
};
#endif
