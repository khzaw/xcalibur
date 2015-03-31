#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>
#include "..\Frontend\TNode.h"

using namespace std;

//public functions
class ProcTable{

private:
vector<string> pTable; 
map<string,int> pMap;
std::vector<TNode*> procRootTable;
public:
//Constructor
ProcTable();
//std::vector<TNode*> procRootTable;
//CFG
void insertASTRootNode(int ProcIndex, TNode* procNode);
TNode * getASTRootNode(int ProcIndex);

//Accessor
int getSize(); 	// returns size of table
bool ProcTable::containsProc(string p); // returns true if proc table contains procedure p
string getProcName(int);	// get variable name using its index
int getProcIndex(string);	// get variable index using its string
set<int> getAllProc();		// get all procedures indices

//Mutator
int insertProc(string); // insert procedure into the proc Map if it does not exist

};