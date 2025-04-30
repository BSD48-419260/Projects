#ifndef STUDENT_H
#define STUDENT_H
#include<iostream>
#include<cstring>
using namespace std;

class Student{
  //this student only has a name for testing purposes.
 public:
  char* name = new char[10];
  Student(char* newname){
    strncpy(name,newname,10);
  }
  ~Student(){
    delete name;
  }
};
#endif
