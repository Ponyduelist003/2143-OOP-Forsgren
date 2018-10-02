/*
* Course: CMPS 2143 - OOP
*
* Purpose: Overload and utilize [], <<, +, -, *, /, ==, =, and pushBack.
*
* @author Ponyduelist003
* @version 1.1 01/03/17
* @github repo: http://github.com/2143-OOP-Forsgren
*/ 
#include <iostream>
#include <cstdlib>
#include "myVector.h"

using namespace std;


int main() {
  //Establish Vectors V1 and V2
	myVector V1(10);
	myVector V2(20);

  //Establish array pointer ptr
  int *ptr = new int[5];

  //set ptr = [1, 2, 3, 4, 5]
  for (int i = 0; i < 5; i++){
    ptr[i] = i + 1;
  }

  //set V1 equal to 7 random values
	for (int i = 0; i < 7; i++) {
		V1.pushBack(rand() % 100);
	}

  //set V2 equal to 5 randoom values
	for (int i = 0; i < 5; i++) {
		V2.pushBack(rand() % 100);
	}

  //cout V1 and V2
	cout << V1 << endl;
	cout << V2 << endl;

  //Set new vector v3 equal to V1 + V2
  //cout v3
	myVector v3 = V1 + V2;
	cout << v3 << endl;

  //set new vector V4 equal to V1 - V2
  //cout V4
  myVector V4 = V1 - V2;
  cout << V4 << endl;

  //set new vector V5 equal to V1 * V2;
  //cout V5
  myVector V5 = V1 * V2;
  cout << V5 << endl;

  //set new vector V6 equal to V1/V2
  //cout V6
  myVector V6 = V1 / V2;
  cout << V6 << endl;

  //set new vector V7 equal to V1 * 5
  //cout V7
  myVector V7 = V1 * 5;
  cout << V7 << endl;

  //push ptr onto V1, cout V1
  V1.pushBack(ptr, 5);
  cout << V1 << endl;

  //test equality, V1 and V2 should not be equal.
  if (V1 == V2){
    cout << "Equality is broken!" << endl;
  }
  else{
    cout << "Equality works!" << endl;
  }

  //test equality again, V1 should equal V1
  if (V1 == V1){
    cout << "Equality definitely works!" << endl;
  }
  else{
    cout << "Equality is broken!" << endl;
  }
}
