// File name: QueryEvaluator.h
//header guard at start of header file
#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H
#include <string>
#include <map>
#include "QueryTree.h"
#include "QTNode.h"
#include "SPA/PKB/PKB.h"
#include "SPA/PKB/PKBController.h"

//For Testing
#include "SPA/PKB/StatementTable.h"
#include "SPA/PKB/Follows.h"
#include "SPA/PKB/Parent.h"
#include "SPA/PKB/Modifies.h"
#include "SPA/PKB/Uses.h"
#include "SPA/PKB/ProcTable.h"
#include "SPA/PKB/VarTable.h"
#include "SPA/PKB/ConstantTable.h"

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
		pair<vector<string>, vector<vector<int>>> mergeSolutions(pair<vector<string>,vector<vector<int>>>, pair<vector<string>, vector<vector<int>>>);
		bool checkSynonymInSuchThat(string, QueryTree*);
		vector<int> solveForSelect(string, map<STRING, STRING>*, StatementTable*, ProcTable*, VarTable*, ConstantTable*);
		vector<vector<int>> solveForSuchThatFollows(map<STRING, STRING>*, QueryTree*);
		vector<vector<int>> solveForSuchThatParent(map<STRING, STRING>*, QueryTree*);
		vector<vector<int>> solveForSuchThatFollowsStar(map<STRING, STRING>*, QueryTree*);
		vector<vector<int>> solveForSuchThatParentStar(map<STRING, STRING>*, QueryTree*);
		vector<vector<int>> solveForSuchThatModifies(map<STRING, STRING>*, QueryTree*);
		vector<vector<int>> solveForSuchThatUses(map<STRING, STRING>*, QueryTree*);
		
		vector<int> solve(string, map<STRING, STRING>*, QueryTree*);
		vector<vector<int>> solveForSuchThat(map<STRING, STRING>*, QueryTree*);
		vector<int>	solveForPattern(string, map<STRING, STRING>*, QueryTree*);
	private:
		PKBController* pkb;
};
#endif