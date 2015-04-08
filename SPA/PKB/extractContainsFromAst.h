#pragma once
#include <iostream>
#include "Frontend\TNode.h"
#include "Contains.h"
#include "PKB\VarTable.h"
#include "PKB\ConstantTable.h"
#include "PKB\ProcTable.h"

using namespace std;

class ExtractContainsFromAST {

private :
	Contains *contains;
	ProcTable *procTable;
	VarTable *varTable;
	ConstantTable *constTable;
	int plusCount;
	int minusCount;
	int timesCount;

public :

	ExtractContainsFromAST();
	ExtractContainsFromAST( Contains* , VarTable*, ConstantTable*, ProcTable*);
	void extractContains();
	void recursiveExtractContains(TNode*);

};