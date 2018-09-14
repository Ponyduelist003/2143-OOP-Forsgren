#include <iostream>
#include <typeinfo>
#include <fstream>
#include "myVector.h"

using namespace std;

/**
*  Initializes a vector when size is not provided.
*
*  @param n/a
*  @return {myVector} theVector initialized
*/
myVector::myVector() {
	vSize = 10;
	initSize = vSize;
	theVector = new int[vSize];
	//for i from 0 up to vSize -1, set theVector[i] to 0
	for (int i = 0; i < vSize; i++) {
		theVector[i] = 0;
	}
}

/**
*  Initializes a vector when size is provided.
*
*  @param {int} size of theVector
*  @return {myVector} theVector initialized
*/
myVector::myVector(int size) {
	vSize = size;
	initSize = vSize;
	theVector = new int[vSize];
	//for i from 0 up to vSize -1, set theVector[i] to 0
	for (int i = 0; i<vSize; i++) {
		theVector[i] = 0;
	}
}

/**
*  Pushes a value onto the end of the vector
*
*  @param {int} value pushed onto vector and {ofstream} outfile to print to
*  @return {myVector} theVector updated and {ofstream} outfile printed to
*/
void myVector::push_back(int val, ofstream& outfile) {
	//if type id matches to an int
	if (typeid(val) == typeid(int)) {
		//if vector is less than 100 percent full
		if (percentFull < 1) {
			theVector[vSize - slotsFull - 1] = val;
			slotsFull++;
			percentFull = (double)slotsFull / vSize;
		}
		//if vector is 100 percent full
		else {
			int usedSize = vSize;
			int sizeDiff;
			vSize = vSize * 1.5;
			diffVector = new int[vSize];
			sizeDiff = vSize - usedSize;
			//for i from 0 up to the old size - 1, put actual values of
			//theVector into diffVector
			for (int i = 0; i < usedSize; i++) {
				diffVector[i + sizeDiff] = theVector[i];
			}
			//from i equals usedSize to new size - 1, set remaining values to 0;
			for (int i = usedSize; i <= vSize; i++) {
				diffVector[vSize - i] = 0;
			}
			/*
			theVector = new int[vSize];
			for (int i = 0; i < vSize; i++) {
				theVector[i] = extendVector[i];
			}
			*/
			theVector = diffVector;
			theVector[vSize - slotsFull - 1] = val;
			slotsFull++;
			percentFull = (double)slotsFull / vSize;
		}
	}
	else {
		outfile << "Error! User Attempeted to input a non-integer!\n";
	}
}

/**
*  Pushes a value onto the end of the vector
*
*  @param {ofstream} outfile to print to
*  @return {int} the value received and {ofstream} outfile printed to
*/
int myVector::pop_back(ofstream& outfile) {
	int result = 0;
	//if no values are in vector, print error
	if (slotsFull == 0) {
		outfile << "Error! Attempted to pop from an empty vector!\n";
		return 0;
	}
	//if values are in vector, pop values
	else {
		result = theVector[vSize];
		theVector[vSize] = 0;
		slotsFull--;
		vSize--;
		percentFull = (double)slotsFull / vSize;
		//if vector is less than 40% full and more than twice it's original size,
		//reduce the vector by 1/2
		if (percentFull <= .4 && vSize >= 2 * initSize) {
			vSize = vSize * .5;
			diffVector = new int[vSize];
			//for i equal 0 up to vSize - 1, input values from the Vector
			//into diffVector
			for(int i = 0; i < vSize; i++){
			diffVector[i] = theVector[i + vSize + 1];
			}
			theVector = diffVector;
		}
		return result;
	}
}

/**
*  Returns the size of the vector
*
*
*  @Param n/a
*  @return {int} size of the vector
*/
int myVector::size() {
	return vSize;
}

/**
*  Prints out every value in the vector
*
*  @param {ofstream} outfile to print to
*  @return {ofstream} outfile printed to
*/
void myVector::print(ofstream& outfile) {
	//from i equal 0 up to vSize - 1, outfile vector value and space
	for (int i = 0; i<vSize; i++) {
		outfile << theVector[i] << " ";
	}
	outfile << endl;
}
