#include <iostream>
#include "myVector.h"

using namespace std;

 /**
  *  Initializes a vector when size is not provided.
  *
  *  @param n/a
  *  @return {myVector} theVector initialized
  */
myVector::myVector(){
  vSize = 10;
  theVector = new int[vSize];
  for(int i = 0; i < vSize; i++){
    theVector[i] = 0;
  }
}

 /**
  *  Initializes a vector when size is provided.
  *
  *  @param {int} size of theVector
  *  @return {myVector} theVector initialized
  */
myVector::myVector(int size){
  vSize = size;
  theVector = new int[vSize];
  //just so we have stuff to print!!!!!
  for(int i=0;i<vSize;i++){
    theVector[i] = 0;
  }
}
 /**
  *  Pushes a value onto the end of the vector
  *
  *  @param {int} value pushed onto vector
  *  @return {myVector} theVector updated
  */
void myVector::push_back(int val){
  if (percentFull < 1){
    theVector[slotsFull] = val;
    slotsFull++;
    percentFull = [double] slotsFull/vSize;
  }
  else{
    //increase size of vector
    theVector[slotsFull] = val;
    slotsFull++;
    percentFull = [double] slotsFull/vSize;
  }
}

 /**
  *  Prints out every value in the vector
  *
  *  @param n/a
  *  @return n/a
  */
void myVector::print(){
  for(int i=0;i<vSize;i++){
    cout<<theVector[i]<<" ";
  }
}
