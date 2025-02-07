#include <iostream>
#include <cmath>
#include <fstream>

int parentIndex(int index);
int leftIndex(int index);
int rightIndex(int index);
int earliestOpenIndex(int* heapofints, int sizeofarray);
void addNode(int* heapofints, int sizeofarray, int toadd);
void deleteNode(int* heapofints, int sizeofarray, int index);
void bubbleTo(int* heapofints,int sizeofarray,int index);
void swap(int& one, int& two);

int main(){
  //oh boy
  int* heapofints[127];
  int sizeofarray=127;
  for(int i=0; i<sizeofarray; i++){
    heapofints[i]=nullptr;
  }
  
  return 0;
}

int parentIndex(int index){
  return floor((x-1)/2);
}

int leftIndex(int index){
  return (index*2)+1;
}

int rightIndex(int index){
  return (index+1)*2;
}

int earliestOpenIndex(int* heapofints, int sizeofarray){
  for(int i=0; i<sizeofarray; i++){
    if(heapofints[i]=nullptr){
      return i;
    }
  }
  return -1;
}

void addNode(int*& heapofints, int sizeofarray, int toadd){
  
  return;
}

void deleteNode(int*& heapofints, int sizeofarray, int index){
  
  return;
}

void bubbleTo(int* heapofints,int sizeofarray,int index){
  
  return;
}

void swap(int& one, int& two){
  int buff=one;
  one=two;
  two=buff;
  return;
}
