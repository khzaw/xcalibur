#pragma once
#include <iostream>
#include "..\Frontend\TNode.h"
#include "Siblings.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ProcTable.h"
using namespace std;

class SiblingsExtractor {

private :
	Sibling *sibling;
	ProcTable *procTable;
	VarTable *varTable;
	ConstantTable *constTable;
	int plusCount;
	int minusCount;
	int timesCount;

public :

	SiblingsExtractor();
	SiblingsExtractor( Sibling* , VarTable*, ConstantTable*, ProcTable*);
	void extractSibling();
	void recursiveExtractSibling(TNode*);

};