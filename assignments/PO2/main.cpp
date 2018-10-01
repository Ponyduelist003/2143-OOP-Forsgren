#include <iostream>
#include <cstdlib>
#include "myVector.h"

using namespace std;


int main() {
	myVector V1(10);
	myVector V2(20);

  int *ptr = new int[5];

  for (int i = 0; i < 5; i++){
    ptr[i] = i + 1;
  }

	for (int i = 0; i < 7; i++) {
		V1.pushBack(rand() % 100);
	}

	for (int i = 0; i < 5; i++) {
		V2.pushBack(rand() % 100);
	}

	cout << V1 << endl;
	cout << V2 << endl;
	myVector v3 = V1 + V2;
	cout << v3 << endl;

  myVector V4 = V1 - V2;
  cout << V4 << endl;

  myVector V5 = V1 * V2;
  cout << V5 << endl;

  myVector V6 = V1 / V2;
  cout << V6 << endl;

  myVector V7 = V1 * 5;
  cout << V7 << endl;

  V1.pushBack(ptr, 5);
  cout << V1 << endl;
  if (V1 == V2){
    cout << "Something probably went wrong!" << endl;
  }
  else{
    cout << "Equality probably works!" << endl;
  }
}
