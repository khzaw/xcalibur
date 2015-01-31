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
	this->modifiesTable = Modifies();
	this->usesTable = Uses();
	this->statementTable = StatementTable();
	this->modifiesTable = Modifies();
	this->callsTable = Calls();
	this->callsExtractor= CallsExtractor( &callsTable);
	this->followsExtractor=FollowsExtractor(&followsTable);
	this->parentExtractor = ParentExtractor(&parentTable);
}

PKBController::~PKBController() {
}

void PKBController::constructFollows() {
	followsExtractor.construct();
}

void PKBController::constructParent() {
	parentExtractor.construct();
}

void PKBController::constructCalls() {
	callsExtractor.construct();
}