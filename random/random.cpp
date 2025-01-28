#include <iostream>
using namespace std;

int main()
{
  srand(time(0));
  int amt=(rand()%5)+10;
  cout<<"[";
  for(int i=0; i<amt-1;i++){
    cout<<(rand()%55)+65<<',';
  }
  cout<<(rand()%55)+65<<']'<<endl;
  return 0;
}
