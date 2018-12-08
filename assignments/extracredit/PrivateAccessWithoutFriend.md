https://www.geeksforgeeks.org/can-access-private-data-members-class-without-using-member-friend-function/

The question asked on this page is whether or not we can access Private data from a class without calling Friend, which is the normal
method by which we would do so. While at first the answer would seem to be no, as an answer of yes would make us question why we even have
Friend, it is actually possible to forgoe the use of Friend when trying to access private data. 

#include<iostream> 
using namespace std; 

//A class called Test with Private Data, a default constructor, and a getter. 
class Test 
{ 
private: 
    int data; 
public: 
    Test() { 
      data = 0;
    } 
    int getData() {
      return data; 
    } 
}; 
  
int main() 
{ 
    // instantiate a Test of t, make an int pointer ptr that points to the int values of t, set ptr to 10, and get data
    Test t; 
    int* ptr = (int*)&t; 
    *ptr = 10; 
    cout << t.getData(); 
    return 0; 
}

This code would then run and output a 10, as the change in ptr affects the int values of Test, namely data, and so the private data can be
modified without use of Friend. However, given how pointers tend to complicate programs and are best used only when necessary, using
Friend is usually the better method and why we have Friend in the first place.
