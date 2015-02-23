#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

//public functions
class VarTable{

private:
vector<string> varVec; 
map<string,int> varMap; 
public:

//Constructor
VarTable();	

string getVarName(int);	// get variable name using its index
int getVarIndex(string);	// get variable index using its string
vector<string> getAllVar(); // get all variables
vector<int> getAllVarNum();
bool containsVar(string); // checks if variable is in the var set
//void printTable(); 

int insertVar(string); // insert variable into varMap


int getSize(); 	// returns size of table

};