#pragma once
#include <string>
#include <vector>
#include <map>
#include "QueryTree.h"
#include "..\PKB\PKBController.h"
#include "ResultTuple.h"

using namespace std;

class Subquery{

public:
	int priority;
	PKBController* pkb;
	map<string, string>* synonymTable;
	int leftIndex, rightIndex;
	string leftSynonym, rightSynonym, specialValue;
	map<string, TNODE_TYPE> synToNodeType;
	bool isUnderscore;
	int isSyn;	// variable to indicate how many synonyms are there,
				// 0: both are int, 1: left int, right string
				// 2: left string, right int, 3: both are string
				// 4: ("_", syn)
				// 5: (syn, "_")
				// 6: ("_", "_")
				// 7: ("_", dig)
				// 8: (dig, "_")

	// constructor
	Subquery(map<string, string>*, PKBController*, bool);
	Subquery(map<string, string>*, PKBController*);

	// Mutators
	void setSynonyms(string, string);
	void setSynonyms(string, int);
	void setSynonyms(int, string);
	void setSynonyms(int, int);
	void setValue(string, bool);

	// Accessors	
	int getPriority();
	virtual ResultTuple* solve();
	virtual ResultTuple* solve(ResultTuple*);
	virtual bool validate();
	virtual void setPriority();
};