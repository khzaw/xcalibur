#pragma once

#include <iostream>

#include "AST.h"
#include "VarTable.h"
#include "ProcTable.h"

using namespace std;

class PKBController {
public:
	VarTable varTable;
	ProcTable procTable;
	AST ast;
	PKBController();
	virtual ~PKBController();

};