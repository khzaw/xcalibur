// File name: QueryEvaluator.h
//header guard at start of header file
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H
#include <string>
#include <map>
#include "QueryTree.h"
#include "QTNode.h"
#include "PKB.h"

//For Testing
#include "StatementTable.h"
#include "Follows.h"
#include "Modifies.h"
#include "ProcTable.h"
#include "VarTable.h"

using namespace std;

typedef string STRING;

class QueryEvaluator{
	public:
		//Constructor
		QueryEvaluator();
		QueryEvaluator(PKB*);

		//Method
		STRING evaluate(map<STRING, STRING>*, QueryTree*);

		//For Testing
		bool checkSynonymInSuchThat(string, QueryTree*);
		vector<int> solveForSuchThatFollows(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Follows*, ProcTable*, VarTable*);
		vector<int> solveForSuchThatModifies(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Modifies*, ProcTable*, VarTable*);
	
	private:
		PKB* pkb;
};
#endif