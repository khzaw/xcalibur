#pragma once

#include "CallsExtractor.cpp"
#include "ParentExtractor.cpp"
#include "FollowsExtractor.cpp"
#include "ModifiesExtractor.cpp"
#include "UsesExtractor.cpp"
#include "SiblingsExtractor.cpp"
#include "extractContainsFromAst.h"

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
	this->containsTable = new Contains();
	this->siblingTable = new Sibling();
	this->callsExtractor = new CallsExtractor(callsTable);
	this->followsExtractor = new FollowsExtractor(followsTable);
	this->parentExtractor = new ParentExtractor(parentTable);
	this->modifiesExtractor = new ModifiesExtractor(modifiesTable, procTable, callsTable);
	this->usesExtractor = new UsesExtractor(usesTable);
	this->nextExtractor = new NextExtractor(procTable, statementTable);
  this->optimizedCFG = new OptimizedCFG(procTable, statementTable, parentTable, followsTable, modifiesTable, usesTable);
	this->affectsExtractor = new AffectsExtractor(modifiesTable,usesTable,nextExtractor ,varTable, statementTable,callsTable);
	this->containsExtractor = new ExtractContainsFromAST(containsTable, varTable, constantTable, procTable);
	this->siblingsExtractor = new SiblingsExtractor(siblingTable, varTable, constantTable, procTable);
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

void PKBController::constructOptimizedCFG(){
	optimizedCFG->construct();
}

void PKBController::constructContains(){
	containsExtractor->extractContains();
}

void PKBController::constructSiblings(){
	siblingsExtractor->extractSibling();
}