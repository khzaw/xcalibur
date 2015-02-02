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
#include "Calls.h"
#include "StatementTable.h"
#include "Modifies.h"
#include "Uses.h"

//Design Extractor
#include "CallsExtractor.h"
#include "ParentExtractor.h"
#include "FollowsExtractor.h"
#include "ModifiesExtractor.h"
#include "UsesExtractor.h"



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
	Calls callsTable;
	PKBController();
	virtual ~PKBController();

	//Design Extractor
	CallsExtractor callsExtractor;
	FollowsExtractor followsExtractor;
	ParentExtractor parentExtractor;
	ModifiesExtractor modifiesExtractor;
	UsesExtractor usesExtractor;

	//DE
	void constructParent();
	void constructFollows();
	void constructCalls();
	void constructModifies();
	void constructUses();
};