#pragma once

#include <string>
#include <vector>
#include "..\Frontend\TNode.h"
using namespace std;

//public functions
class StatementTable{

private:
vector<pair<TNode*, string >> statement; 

public:

//Constructor
StatementTable();	

//Accessor
int getSize(); 	// returns the number of statements in program
TNode* getTNode(int);	// get node pointer using its index
string getTNodeType(int); // get statement type [ While/If/Call/Assign ]
vector<TNode*> getNodesMatchingNodeType(string); // returns a vector of node pointers of nodes matching specified node type
vector<int> getStmtNumUsingNodeType(string);	// return a vector of indexes of nodes matching specified node type
vector<int> getAllStmtNum();
vector<int> getAssignmentNodesNum(string, string); // returns a vector of assignment node pointers matching specified left hand side
bool containsStatement(string); // checks if program contains statement of a particular type
bool containsNodeOfStmtAndNodeType(string , int ); // checks if node at specified stmt num is of node type

//Mutator
void insertStatement(TNode*); // insert node pointer and node type into the table if it does not exist



};