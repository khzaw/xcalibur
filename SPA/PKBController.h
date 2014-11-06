#pragma once

#include <iostream>

#include "AST.h"
#include "VarTable.h"
#include "ProcTable.h"
#include "ConstantTable.h"
#include "Parent.h"
#include "Follows.h"
#include "Modifies.h"
#include "Uses.h"
#include "StatementTable.h"
#include "Modifies.h"

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