/**
*  Course: CMPS 2143 - OOP
*  Assignment: P01
*  Purpose: Simulate the Vector class by pushing and popping values,
*  then printing size and vector.
*
*  @author Ponyduelist003
*  @version 1.1 01/03/17
*/
#include <iostream>
#include <fstream>
#include "myVector.h"

using namespace std;

int main() {
	//establish and open outfile
	ofstream outfile;
	outfile.open("output.txt");

	//instantiate vector
	myVector V(10);

	//attempt to pop from empty vector
	V.pop_back(outfile);

	//push values onto vector, then print
	V.push_back(13, outfile);
	V.push_back(31, outfile);
	V.push_back(71, outfile);
	V.print(outfile);

	//for i from 0 to 999, push i + 1 onto vector
	for (int i = 0; i < 1000; i++) {
		V.push_back(i + 1, outfile);
	}

	//for i from 0 to 997, pop a value off the vector
	for (int i = 0; i < 998; i++) {
		V.pop_back(outfile);
	}

	//print size and final vector
	outfile << V.size() << endl;
	V.print(outfile);
	return 0;
}
