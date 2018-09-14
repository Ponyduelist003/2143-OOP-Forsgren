#include <iostream>
#include <typeinfo>
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
	//just so we have stuff to print!!!!!
	for (int i = 0; i<vSize; i++) {
		theVector[i] = 0;
	}
}

/**
*  Pushes a value onto the end of the vector
*
*  @param {int} value pushed onto vector
*  @return {myVector} theVector updated
*/
void myVector::push_back(int val) {
	if (typeid(val) == typeid(int)) {
		if (percentFull < 1) {
			theVector[vSize - slotsFull - 1] = val;
			slotsFull++;
			percentFull = (double)slotsFull / vSize;
		}
		else {
			int *diffVector;
			int usedSize = vSize;
			int sizeDiff;
			vSize = vSize * 1.5;
			diffVector = new int[vSize];
			sizeDiff = vSize - usedSize;
			for (int i = 0; i < usedSize; i++) {
				diffVector[i + sizeDiff] = theVector[i];
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
		cout << "Error! User Attempeted to input a non-integer!\n";
	}
}

/**
*  Pushes a value onto the end of the vector
*
*  @param n/a
*  @return {int} the value received
*/
int myVector::pop_back() {
	int result = 0;
	int usedSize = vSize;
	if (slotsFull == 0) {
		cout << "Error! Attempted to pop from an empty vector!\n";
		return 0;
	}
	else {
		result = theVector[vSize];
		theVector[vSize] = 0;
		slotsFull--;
		vSize--;
		percentFull = (double)slotsFull / vSize;
		if (percentFull <= .4 && vSize >= 2 * initSize) {
			int *shortVector;
			//vSize = vSize * .5;
			shortVector = new int[vSize];
			/**
			for(int i = 0; i < vSize; i++){
			conciseVector[i] = theVector[i + vSize];
			}
			theVector = new int[vSize];
			for(int i = 0; i < vSize; i++){
			theVector[i] = conciseVector[i];
			}
			*/
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
*  @param n/a
*  @return n/a
*/
void myVector::print() {
	for (int i = 0; i<vSize; i++) {
		cout << theVector[i] << " ";
	}
	cout << endl;
}
