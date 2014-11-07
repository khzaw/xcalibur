// File name: QueryEvaluator.h
//header guard at start of header file
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H
#include <string>
#include <map>
#include "QueryTree.h"
#include "QTNode.h"
#include "PKB.h"
#include "PKBController.h"

//For Testing
#include "StatementTable.h"
#include "Follows.h"
#include "Parent.h"
#include "Modifies.h"
#include "Uses.h"
#include "ProcTable.h"
#include "VarTable.h"

using namespace std;

typedef string STRING;

class QueryEvaluator{
	public:
		//Constructor
		QueryEvaluator();
		QueryEvaluator(PKBController*);

		//Method
		list<string> evaluate(map<STRING, STRING>*, QueryTree*);

		//For Testing
		bool checkSynonymInSuchThat(string, QueryTree*);
		vector<int> solveForSuchThatFollows(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Follows*, ProcTable*, VarTable*);
		vector<int> solveForSuchThatParent(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Parent*, ProcTable*, VarTable*);
		vector<int> solveForSuchThatFollowsStar(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Follows*, ProcTable*, VarTable*);
		vector<int> solveForSuchThatParentStar(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Parent*, ProcTable*, VarTable*);
		vector<int> solveForSuchThatModifies(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Modifies*, ProcTable*, VarTable*);
		vector<int> solveForSuchThatUses(string, map<STRING, STRING>*, QueryTree*, StatementTable*, Uses*, ProcTable*, VarTable*);
	
	private:
		PKBController* pkb;
};
#endif