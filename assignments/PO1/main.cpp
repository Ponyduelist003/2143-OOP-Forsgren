 /**
 *  Course: CMPS 2143 - OOP
 *  Assignment: P01
 *  Purpose: Simulate the Vector class
 * 
 *  @author Ponyduelist003
 *  @version 1.1 01/03/17 
 */
#include <iostream>
#include "myVector.h"

using namespace std;

int main() {
  myVector V(10);
  V.pop_back();
  V.push_back(13);
  V.push_back(31);
  V.push_back(71);
  V.print();
  for(int i = 0; i < 1000; i++){
    V.push_back(i + 1);
  }
  for(int i = 0; i < 998; i++){
    V.pop_back();
  }
  cout << V.size() << endl;
  V.print();

  return 0;
}
