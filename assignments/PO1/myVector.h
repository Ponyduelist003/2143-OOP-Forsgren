#include <iostream>

using namespace std;

class myVector{
private:
  int *theVector;
  int vSize;
  int initSize;
  int slotsFull = 0;
  double percentFull = 0;
public:
  myVector(int size);
  myVector();
  void push_back(int val);
  int pop_back();
  int size();
  void print();
};
