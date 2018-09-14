#pragma once
#include <iostream>
#include <fstream>

using namespace std;

class myVector {
private:
	int *theVector;
	int *diffVector;
	int vSize;
	int initSize;
	int slotsFull = 0;
	double percentFull = 0;
public:
	myVector(int size);
	myVector();
	void push_back(int val, ofstream& outfile);
	int pop_back(ofstream& outfile);
	int size();
	void print(ofstream& outfile);
};
