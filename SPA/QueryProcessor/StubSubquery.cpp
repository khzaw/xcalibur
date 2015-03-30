#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"

using namespace std;

class StubSubquery : public Subquery {
public:
	StubSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
	}
	
	ResultTuple* solve(){
		ResultTuple* tuple = new ResultTuple();
		tuple->addSynonymToMap(leftSynonym, tuple->addSynonym(leftSynonym));
		vector<int> res = getStatements(synonymTable->at(leftSynonym));
		for (size_t i = 0; i < res.size(); i++) {
			vector<int> temp = vector<int>();
			temp.push_back(res[i]);
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	bool validate() {
		return true;
	}

	void setPriority() {
		priority = 0;
	}

	// should not be used at all
	ResultTuple* solve(ResultTuple* tuple) {
		return new ResultTuple();
	}

	vector<int> getStatements(string synonymType) {
		if (synonymType == "assign") {
			return pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
		} else if (synonymType == "while") {
			return pkb->statementTable->getStmtNumUsingNodeType("WHILE_NODE");
		} else if (synonymType == "if") {
			return pkb->statementTable->getStmtNumUsingNodeType("IF_NODE");
		} else if (synonymType == "call") {
			return pkb->statementTable->getStmtNumUsingNodeType("CALL_NODE");
		} else if (synonymType == "stmt" || synonymType == "prog_line") {
			return pkb->statementTable->getAllStmtNum();
		} else if (synonymType == "procedure") {
			vector<int> rows = vector<int>();
			for (size_t i = 0; i < pkb->procTable->getSize(); i++) {
				rows.push_back(i);
			}
			return rows;
		} else if (synonymType == "constant") {
			return pkb->constantTable->getAllConstNum();
		} else {
			return pkb->varTable->getAllVarNum();
		} 
	}
};