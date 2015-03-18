#pragma once

#include "CallsExtractor.cpp"
#include "ParentExtractor.cpp"
#include "FollowsExtractor.cpp"
#include "ModifiesExtractor.cpp"
#include "UsesExtractor.cpp"

#include "PKBController.h"

using namespace std;

PKBController::PKBController(){
	this->ast = new AST();
	this->procTable = new ProcTable();
	this->varTable = new VarTable();
	this->constantTable = new ConstantTable();
	this->statementTable = new StatementTable();
	this->parentTable = new Parent(statementTable);
	this->followsTable = new Follows(statementTable);
	this->modifiesTable = new Modifies();
	this->usesTable = new Uses();	
	this->modifiesTable = new Modifies();
	this->callsTable = new Calls();
	this->callsExtractor = new CallsExtractor(callsTable);
	this->followsExtractor = new FollowsExtractor(followsTable);
	this->parentExtractor = new ParentExtractor(parentTable);
	this->modifiesExtractor = new ModifiesExtractor(modifiesTable);
	this->usesExtractor = new UsesExtractor(usesTable);
	this->nextExtractor = new NextExtractor(procTable, statementTable);
}

PKBController::~PKBController() {
}

void PKBController::constructFollows() {
	followsExtractor->construct();
}

void PKBController::constructParent() {
	parentExtractor->construct();
}

void PKBController::constructCalls() {
	this->callsTable;
	callsExtractor->construct();
}

void PKBController::constructModifies() {
	modifiesExtractor->construct();
}

void PKBController::constructUses() {
	usesExtractor->construct();
}

void PKBController::constructNext(){
	nextExtractor->construct();
}