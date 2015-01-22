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
vector<string> getAllVar(); // get all variables
vector<int> getAllVarNum();
bool containsVar(string); // checks if variable is in the var set
void printTable(); 

//Mutator
int insertVar(string); // insert variable into the table if it does not exist



};