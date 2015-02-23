#pragma once
#include "PKBController.h"

using namespace std;

#include "PKB.h"
#include "..\Frontend\TNode.h"

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
	this->modifiesExtractor= ModifiesExtractor(&modifiesTable);
	this->usesExtractor = UsesExtractor(&usesTable);
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

void PKBController::constructModifies() {
	modifiesExtractor.construct();
}

void PKBController::constructUses() {
	usesExtractor.construct();
}
