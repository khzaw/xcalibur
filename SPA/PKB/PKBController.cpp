#pragma once

#include "CallsExtractor.cpp"
#include "ParentExtractor.cpp"
#include "FollowsExtractor.cpp"
#include "ModifiesExtractor.cpp"
#include "UsesExtractor.cpp"

#include "PKBController.h"

using namespace std;

PKBController::PKBController(){
	this->ast = AST();
	this->procTable = ProcTable();
	this->varTable = VarTable();
	this->constantTable = ConstantTable();
	this->statementTable = StatementTable();
	this->parentTable = Parent(&statementTable);
	this->followsTable = Follows(&statementTable);
	this->modifiesTable = Modifies();
	this->usesTable = Uses();	
	this->modifiesTable = Modifies();
	this->callsTable = Calls();
	this->callsExtractor = CallsExtractor(&callsTable);
	this->followsExtractor = FollowsExtractor(&followsTable);
	this->parentExtractor = ParentExtractor(&parentTable);
	this->modifiesExtractor = ModifiesExtractor(&modifiesTable);
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