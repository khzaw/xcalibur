#pragma once
#include <string>
#include <vector>
using namespace std;

//public functions
class VarTable{

private:
vector<string> varVec; 

public:

//Constructor
VarTable();	

//Accessor
int getSize(); 	// returns size of table
string getVarName(int);	// get variable name using its index
int getVarIndex(string);	// get variable index using its string
bool containsVar(string); // checks if variable is in the var set
void printTable(); 

//Mutator
void insertVar(string); // insert variable into the table if it does not exist



};