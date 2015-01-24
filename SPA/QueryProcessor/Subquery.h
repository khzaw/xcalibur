#pragma once
#include <string>
#include <vector>
#include <map>
#include "QueryTree.h"
#include "..\PKB\PKBController.h"

using namespace std;

class Subquery{

private: 
	int priority;

public:
	PKBController* pkb;
	map<string, string>* synonymTable;
	QueryTree* subquery;

	// constructor
	Subquery();
	void init(map<string, string>*, QueryTree*, PKBController*);

	// Mutators
	void setPriority(int);

	// Accessors	
	int getPriority();
	virtual map<string, vector<int> >* solve();
	virtual map<string, vector<int> >* solve(map<string, vector<int> >*);
};