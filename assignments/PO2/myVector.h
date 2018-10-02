/*
* Course: CMPS 2143 - OOP
*
* Purpose: Overload and utilize [], <<, +, -, *, /, ==, =, and pushBack.
*
* @author Ponyduelist003
* @version 1.1 01/03/17
* @github repo: http://github.com/2143-OOP-Forsgren
*/ 
#pragma once
#include <iostream>

using namespace std;

class myVector {
private:
	int *vPtr;      // int pointer to array
	int maxSize;    // max size of array
	int minSize;    // min size of array
	int index;      // current location to insert or remove
	int* _resize(int);

public:
	myVector(int size);
	void pushBack(int item);
	void pushBack(int *ptr, int size);
	int popBack();
	int getValue(int index);
  void setValue(int index, int value);
	double percentFull();
	int* resize(double);
	int* resize(int);

	void print();
	int size();
	void size(int);
	int vSize();

	/*
  * Purpose: Overloads [] so that vectors can be treated as arrays
  *
  * @param {int} index to reference a point in the "array"
  * @return {int&} value at the point in the "array" 
  */
	int& operator[](int i)
	{
    //if i is over maxSize, return out of bound error
		if (i >= maxSize)
		{
			cout << "Array index out of bound, exiting\n";
			exit(0);
		}
    //else if i over the index, warn value is undefined
		else if (i >= index) {
			cout << "Warning: vector[" << i << "] is undefined ...\n";
		}
		return vPtr[i];
	}
  
  /*
  * Purpose: overloads << to pass in vectors
  *
  * @param {ostream&} {myVector} outstream and vector to pass
  * @return {ostream&} os passing vector
  */
	friend ostream& operator<<(ostream& os, myVector V) {
    //for every defined value in vector, pass value
		for (int i = 0; i < V.index; i++) {
			os << V.vPtr[i] << " ";
		}
		return os;
	}

	/*
  * Purpose: Overloads + to add 2 vectors together
  *
  * @param {myVector&} right hand vector to add
  * @return {myVector} sum of the vectors
  */
	myVector operator+(myVector& rhs) {

		//rhs = vector on the right of the + sign
		//lhs = THIS vector (the one were in)
    //min and max are min and max between indexes
		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0;
    int min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize) {
			max = rhsSize;
      min = lhsSize;
		}
		else {
			max = lhsSize;
      min = rhsSize;
		}

		// create a new vector with the bigger size
		myVector newVector(max);

    //for values from 0 to smaller index, sum the values and place in newVector
    for (int i = 0; i < min; i++) {
      newVector.index++;
			newVector.vPtr[i] += rhs.getValue(i);
      newVector.vPtr[i] += getValue(i);
		}

    //if rhs is larger, drop rhs values into newVector
    //else, drop lhs values into newVector
    if(max == rhsSize){
      for(int i = min; i < max; i++){
        newVector.index++;
        newVector.vPtr[i] += rhs.getValue(i);
      }
    }
    else{
      for(int i = min; i < max; i++){
        newVector.index++;
        newVector.vPtr[i] += getValue(i);
      }
    }
		return newVector;
	}
  /*
  * Purpose: Overloads - to subtract one vector from another
  *
  * @param {myVector&} right hand vector to subtract
  * @return {myVector} difference of the vectors
  */
		myVector operator-(myVector& rhs) {

		//rhs = vector on the right of the + sign
		//lhs = THIS vector (the one were in)
    //min and max are min and max between indexes
		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0;
    int min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize) {
			max = rhsSize;
      min = lhsSize;
		}
		else {
			max = lhsSize;
      min = rhsSize;
		}

		// create a new vector with the bigger size
		myVector newVector(max);

    //for values from 0 to smaller index, find the difference of the values and place in newVector
    for (int i = 0; i < min; i++) {
      newVector.index++;
			newVector.vPtr[i] += rhs.getValue(i);
      newVector.vPtr[i] -= getValue(i);
		}

    //if rhs is larger, drop rhs values into newVector
    //else, drop lhs values into newVector
    if(max == rhsSize){
      for(int i = min; i < max; i++){
        newVector.index++;
        newVector.vPtr[i] += rhs.getValue(i);
      }
    }
    else{
      for(int i = min; i < max; i++){
        newVector.index++;
        newVector.vPtr[i] += getValue(i);
      }
    }

		return newVector;
	}

  /*
  * Purpose: Overloads * to multiply 2 vectors
  *
  * @param {myVector&} right hand vector to multiply
  * @return {myVector} product of the vectors
  */
	myVector operator*(myVector& rhs) {

		//rhs = vector on the right of the + sign
		//lhs = THIS vector (the one were in)
    //min and max are min and max between indexes
		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0;
    int min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize) {
			max = rhsSize;
      min = lhsSize;
		}
		else {
			max = lhsSize;
      min = rhsSize;
		}

		// create a new vector with the bigger size
		myVector newVector(max);

    //for values from 0 to smaller index, find the product of the values and place in newVector
    for (int i = 0; i < min; i++) {
      newVector.index++;
			newVector.vPtr[i] += rhs.getValue(i);
      newVector.vPtr[i] *= getValue(i);
		}
  
		return newVector;
	}
  /*
  * Purpose: Overloads * to multiply a vector and an int
  *
  * @param {int} right hand int to multiply
  * @return {myVector} product of the vector and int
  */
  myVector operator*(int rhs) {

    //make a newVector as large as source vector
		myVector newVector(index);

    //for every point in newVector, add source vector and multiply by int
    for (int i = 0; i < index; i++){
      newVector.index++;
      newVector.vPtr[i] += getValue(i);
      newVector.vPtr[i] *= rhs;
    }
		return newVector;
	}

  /*
  * Purpose: Overloads / to divide 2 vectors
  *
  * @param {myVector&} right hand vector to divide
  * @return {myVector} dividend of the vectors
  */
	myVector operator/(myVector& rhs) {

		//rhs = vector on the right of the + sign
		//lhs = THIS vector (the one were in)
    //min and max are min and max between indexes
		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0;
    int min = 0;

		// which vector is bigger?
		if (rhsSize > lhsSize) {
			max = rhsSize;
      min = lhsSize;
		}
		else {
			max = lhsSize;
      min = rhsSize;
		}

		// create a new vector with the bigger size
		myVector newVector(max);

    //for values from 0 to smaller index, find the dividend of the values and place in newVector
    for (int i = 0; i < min; i++) {
      newVector.index++;
			newVector.vPtr[i] += rhs.getValue(i);
      newVector.vPtr[i] /= getValue(i);
		}
		return newVector;
	}

  /*
  * Purpose: Determines is two vectors are equal
  *
  * @param {myVector&} right hand vector to check
  * @return {bool} whether or not vectors are equal
  */
  bool operator==(myVector& rhs){
    //rhs = right hand side
    //lhs = left hand size
    int rhsSize = rhs.index;
    int lhsSize = index;

    //if sizes are difference, vectors are not equal
    if (rhsSize != lhsSize){
      return false;
    }
    //else, check individual values
    else{
      //for all values in the vectors, if one pair are unequal vectors are not equal.
      for(int i = 0; i < rhsSize; i++){
        if (rhs.getValue(i) != getValue(i)){
          return false;
        }
      }
    }
    return true;
  }

  /*
  * Purpose: Sets one vector equal to another
  *
  * @param {myVector&} right hand side to pass into left hand side
  * @return {myVector} vector set to right hand side values
  */
	myVector operator=(myVector& rhs) {
    //rhs = right hand side
    //lhs = left hand side
    //max = maximum size between vectors
		int rhsSize = rhs.index;
		int lhsSize = index;
		int max = 0;

    // Which vector is bigger?
		if (rhsSize > lhsSize)
			max = rhsSize;
		else
			max = lhsSize;

    //set newVector equal to a vector of max size
		myVector newVector(max);

    //for every point in newVector, set value equal to value in rhs
		for (int i = 0; i < max; i++) {
			setValue(i, rhs.getValue(i));
		}

		return newVector;
	}
};



/**
* Function constructor
*   Sets up the vector
* @param {int} size : initial size of vector
* @return void
*/
myVector::myVector(int size) {
	maxSize = size;
	minSize = size;
	// create the array of vSize
	vPtr = new int[maxSize];
	index = 0;
}

/**
* Function print
*   Prints the current values in the vector
* @param void
* @return void
*/
void myVector::print() {
	for (int i = 0; i < index; i++) {
		cout << vPtr[i] << " ";
	}
	cout << endl;
}

/**
* Function pushBack
*   Adds value to vector
* @param {int} item : integer value
* @return void
*/
void myVector::pushBack(int item) {
	if (index >= maxSize) {
		vPtr = resize(1.5);
	}
	vPtr[index++] = item;
}

/*
* Purpose: push an array onto the vector
*
* @param{int*} {int} pointer to array and size of array 
* @return n/a
*/
void myVector::pushBack(int *ptr, int size) {
	for (int i = 0; i < size; i++) {
		pushBack(ptr[i]);
	}
}

/**
* Function popBack
*   Returns value from vector
* @param none
* @return {int} : last item on vector
*/
int myVector::popBack() {

	index--;

	if (index < 0) {
		return 0;
	}

	if (percentFull() <= .4) {
		vPtr = resize(.5);
	}

	return vPtr[index];
}

/*
* Purpose: get a value at any point in the vector
*
* @param {int} point in the vector
* @return {int} value at the point in the vector
*/
int myVector::getValue(int index) {
  //if index is less than 0, return error
	if (index < 0) {
		cout << "Error! No value at input index!" << endl;
		return 0;
	}
	return vPtr[index];
}

/*
* Purpose: set a value at any point in the vector
* 
* @param {int} {int} point in the vector and value to set
* @return n/a
*/
void myVector::setValue(int index, int value) {
  //if index is less than 0, return error
	if (index < 0) {
		cout << "Error! No memory at given address!" << endl;
	}
	vPtr[index] = value;
}

/**
* Function resize
*   Resizes our vector based on passed in ratio
* @param {double} ratio : new array size
* @return {int*} : pointer to new array
*/
int* myVector::resize(double ratio) {
	// figure out what our new size is, bigger or smaller
	int newSize = maxSize * ratio;

	return _resize(newSize);
}

int* myVector::resize(int size) {

	return _resize(size);

}

int* myVector::_resize(int newSize) {
	// Lets keep our vector above some minimum size
	if (newSize < minSize) {
		newSize = minSize;
	}

	// allocate new bigger vector
	int* vBigger = new int[newSize];

	//copy everything over
	for (int i = 0; i < index; i++) {
		vBigger[i] = vPtr[i];
	}

	// update new max size
	maxSize = newSize;

	// delete old memory
	delete[] vPtr;

	//return ptr to new memory
	return vBigger;
}

/**
* Function percentFull
*   helper function to calculate how full vector is
* @param none
* @return {double} : how full vector is
*/
double myVector::percentFull() {
	return double(index) / double(maxSize);
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
int myVector::size() {
	return index;
}

/**
* Function size
*    Returns number of current items in vector
* @param none
* @return {int} : num items
*/
void myVector::size(int newSize) {
	vPtr = _resize(newSize);
}

/**
* Function vSize
*    Returns actual size of allocated memory
* @param none
* @return {int} : mem size
*/
int myVector::vSize() {
	return maxSize;
}
