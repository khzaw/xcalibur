#pragma once

#include <iostream>

#include "VarTable.h"
#include "ProcTable.h"
#include "AST.h"
#include "ConstantTable.h"
#include "Parent.h"
#include "Follows.h"
#include "Modifies.h"
#include "Uses.h"
#include "StatementTable.h"

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