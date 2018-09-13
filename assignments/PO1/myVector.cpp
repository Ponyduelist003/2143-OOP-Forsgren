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
  initSize = vSize;
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
  initSize = vSize;
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
   if (vSize % 2 == 0){
    int *extendVector = new myVector(vSize * 3 / 2);
   }
   else{
    int *extendVector = new myVector(vSize * 3 / 2 + 1);
   }
   for (i = 0; i < vSize; i++){
    extendVector[i] = theVector[i];
   }
   theVector -> extendVector;
   theVector[slotsFull] = val;
   slotsFull++;
   percentFull = [double] slotsFull/vSize;
  }
}

 /**
  *  Pushes a value onto the end of the vector
  *
  *  @param n/a
  *  @return {int} the value received
  */
int myVector::pop_back(){
 int result = 0;
 if(slotsFull == 0){
  cout << "Error! Attempted to pop from an empty vector!";
  return 0;
 }
 else{
  result = myVector[slotsFull];
  myVector[slotsFull] = 0;
  slotsFull--;
  percentFull = [double] slotsFull/vSize;
  return result;
 }
}

 /**
  *  Trims empty slots off the vector
  *
  *  @param n/a
  *  @return {myVector} trimmed vector
  */
void myVector::trim_vector(){
 if (percentFull <= .4 && slotsFull >= initSize){
  int *conciseVector = new myVector(vSize / 2);
  for (i = 0; i < slotsFull; i++){
   conciseVector[i] = theVector[i];
  }
  theVector -> conciseVector;
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
