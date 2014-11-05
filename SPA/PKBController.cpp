#pragma once
#include "PKBController.h"

using namespace std;

PKBController::PKBController() {
	this->ast = AST();
	this->procTable = ProcTable();
	this->varTable = VarTable();
	this->constantTable = ConstantTable();
	this->parentTable = Parent();
	this->followsTable = Follows();
	this->statementTable = StatementTable();
}

PKBController::~PKBController() {
}