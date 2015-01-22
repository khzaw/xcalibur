#pragma once

#include <iostream>

#include "..\PKB\AST.h"
#include "..\PKB\VarTable.h"
#include "..\PKB\ProcTable.h"
#include "..\PKB\ConstantTable.h"
#include "..\PKB\Parent.h"
#include "..\PKB\Follows.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Uses.h"
#include "..\PKB\StatementTable.h"
#include "..\PKB\Modifies.h"

using namespace std;

class PKBController {
public:
	VarTable varTable;
	ProcTable procTable;
	AST ast;
	ConstantTable constantTable;
	Parent parentTable;
	Follows followsTable;
	Modifies modifiesTable;
	Uses usesTable;
	StatementTable statementTable;
	PKBController();
	virtual ~PKBController();

};