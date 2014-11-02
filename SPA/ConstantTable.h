#pragma once
#include <string>
#include <vector>
using namespace std;

//public functions
class ConstantTable{

private:
	vector<int> constVec; 

public:

	//Constructor
	ConstantTable();	

	//Accessor
	int getSize(); 	// returns size of table
	int getConstant(int);	// get constant name using its index
	int getConstIndex(int);	// get constant index using its value
	vector<int> getAllConstant(); // get all constants
	bool containsConst(int); // checks if constant is in the constant vec

	//Mutator
	void insertConst(int); // insert variable into the table if it does not exist
};