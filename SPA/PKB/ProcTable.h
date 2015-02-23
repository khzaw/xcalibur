#pragma once
#include <string>
#include <vector>
#include <map>
using namespace std;

//public functions
class ProcTable{

private:
vector<string> pTable; 
map<string,int> pMap; 
public:
//Constructor
ProcTable();

//Accessor
int getSize(); 	// returns size of table
bool ProcTable::containsProc(string p); // returns true if proc table contains procedure p
string getProcName(int);	// get variable name using its index
int getProcIndex(string);	// get variable index using its string

//Mutator
int insertProc(string); // insert procedure into the proc Map if it does not exist

};