#pragma once
#include "PKBController.h"
#include "Parent.h"
#include "ConstantTable.h"
#include "VarTable.h"
#include "ProcTable.h"
#include "AST.h"
#include "Follows.h"
#include "Modifies.h"
#include "Uses.h"
#include "StatementTable.h"

using namespace std;

PKBController::PKBController() {
	this->ast = AST();
	this->procTable = ProcTable();
	this->varTable = VarTable();
	this->constantTable = ConstantTable();
	this->parentTable = Parent();
	this->followsTable = Follows();
	this->modifiesTable = Modifies();
	this->usesTable = Uses();
	this->statementTable = StatementTable();
	this->modifiesTable = Modifies();
}

PKBController::~PKBController() {
}