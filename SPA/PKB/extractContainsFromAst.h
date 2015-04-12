#pragma once
#include <iostream>
#include "..\Frontend\TNode.h"
#include "Contains.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ProcTable.h"

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