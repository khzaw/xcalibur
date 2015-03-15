#pragma once
#include <fstream>
#include <iostream>
#include <stack>
#include <algorithm>

#include "../PKB/AST.h"
#include "../PKB/PKBController.h"
#include "Lexeme.h"
#include "Lexer.h"
#include "Parser.h"
#include "Operator.h"

using namespace std;

Parser::Parser() {
}

Parser::Parser(string filepath) {
	this->filepath = filepath;
	this->controller = PKBController();
	this->lexer = Lexer("");
	this->line = 0;
	this->currentProc = 0;
	this->previousStmt = 0;			// for poulation of follows
	this->prev = NULL;

	this->lastVarIndex = -1;		// for modifies population
	parse();
}

Parser::~Parser() {
}

void Parser::parse() {
	if(!checkFileExists()) {
		cout << this->filepath << " does not exist!";
		return;
	}

	string currentLine, programString;
	ifstream inputFile;
	inputFile.open(filepath);
	while(!inputFile.eof()) {
		getline(inputFile, currentLine);
		size_t comment = currentLine.find("//");
		if(comment != string::npos) currentLine = currentLine.erase(comment);
		programString += " " + currentLine;
	}
	inputFile.close();
	cout << programString << endl;
	lexer = Lexer(programString);
	program();
	debug();

}

void Parser::debug() {
	cout << "Statements: " << controller.statementTable.getSize() << endl;
	cout << "Parent : " << controller.parentTable.getSize() << endl;
	cout << "Follows : " << controller.followsTable.getSize() << endl;
	cout << "Calls: " << controller.callsTable.getSize() << endl;
	cout << "ModifiesStmt: " << controller.modifiesTable.getSizeStmtModifies() << endl;
	cout << "ModifiesProc: " << controller.modifiesTable.getSizeProcModifies() << endl;
	cout << "UsesStmt: " << controller.usesTable.getSizeStmtUses() << endl;
	cout << "UsesProc: " << controller.usesTable.getSizeProcUses() << endl;
}

bool Parser::checkFileExists() {
	ifstream inputFile(filepath);
	if(inputFile.fail())
		return false;
	inputFile.close();
	return true;
}

void Parser::program() {
	// program: procedure+
	nextToken = getToken();
	procedure();
	while(nextToken.name == "procedure") {
		procedure();
	}
}

TNode* Parser::createASTNode(string nodeName, string data, TNode* parent, int line, int parentProc) {
	TNode* node = new TNode(nodeName, data, line, parentProc);
	controller.ast.assignChild(parent, node);
	return node;
}

void Parser::procedure() {
	// "procedure" proc_name "{" stmtLst "}"
	this->previousStmt = 0;
	this->currentProc++;

	match("procedure");
	string procName = procedureName();
	cout << procName << endl;
	TNode* procNode = new TNode("PROC_NODE", procName, line, currentProc);
	controller.ast.insertRoot(procNode);
	match("{");
	TNode* procStmtLstNode = createASTNode("STMTLST_NODE", "", procNode, line, currentProc);
	stmtLst(procStmtLstNode);
	match("}");
}

string Parser::procedureName() {
	string procName = nextToken.name;
	if(find(procedureNames.begin(), procedureNames.end(), procName) == procedureNames.end()) { // not found
		procedureNames.push_back(procName);
	}
	controller.procTable.insertProc(procName);
	nextToken = getToken();
	return procName;
}

void Parser::stmtLst(TNode* parent) {
	// stmtLst: stmt+
	stmt(parent);
	if(nextToken.token == CLOSE_BLOCK) {
		return;
	} else {
		//cout << nextToken.name << endl;
		stmtLst(parent);
	}
}

void Parser::stmt(TNode* parent) {
	// stmt: call | while | if | assign
	if(nextToken.name == "call") {
		// call: "procedure" proc_name ";"
		line++;
		TNode* callNode = createASTNode("CALL_NODE", nextToken.name, parent, line, currentProc);
		controller.statementTable.insertStatement(callNode);
		match("call");

		populateParent(parent, line);

		string newProcedure = procedureName();
		controller.callsTable.insertCalls(currentProc, getProcedureIndex(newProcedure));
		match(";");

		populateFollows(line, false, parent, callNode);

	} else if(nextToken.name == "while") {
		// while: "while" var_name "{" stmtLst "}"
		line++;
		TNode* whileNode = createASTNode("WHILE_NODE", nextToken.name, parent, line, currentProc);
		controller.statementTable.insertStatement(whileNode);
		match("while");

		populateParent(parent, line);
		populateFollows(line, true, parent, whileNode);
		containerStack.push(line);


		TNode* whileVarNode = createASTNode("VAR_NODE", nextToken.name, whileNode, line, currentProc);
		variableName();

		populateUses(line, currentProc);

		match("{");
		TNode* whileStmtLstNode = createASTNode("STMTLST_NODE", "", whileNode, line, currentProc);
		stmtLst(whileStmtLstNode);
		match("}");
		 
		previousStmt = containerStack.top(); containerStack.pop();
		
	} else if(nextToken.name == "if") {
		// if: "if" var_name "then" "{" stmtLst "}" "else" "{" stmtLst "}"
		++line;
		TNode* ifNode = createASTNode("IF_NODE", nextToken.name, parent, line, currentProc);
		controller.statementTable.insertStatement(ifNode);
		match("if");

		populateParent(parent, line);
		populateFollows(line, true, parent, ifNode);
		containerStack.push(line);

		TNode* ifVarNode = createASTNode("VAR_NODE", nextToken.name, ifNode, line, currentProc);
		variableName();

		populateUses(line, currentProc);

		TNode* thenNode = createASTNode("THEN_NODE", nextToken.name, ifNode, line, currentProc);
		match("then");
		match("{");
		TNode* thenStmtLstNode = createASTNode("STMTLST_NODE", "", thenNode, line, currentProc);
		stmtLst(thenStmtLstNode);
		match("}");
		previousStmt = 0;

		TNode* elseNode = createASTNode("ELSE_NODE", nextToken.name, ifNode, line, currentProc);
		match("else");
		match("{");
		TNode* elseStmtLstNode = createASTNode("STMTLST_NODE", "", elseNode, line, currentProc);
		stmtLst(elseStmtLstNode);
		match("}");

		previousStmt = containerStack.top(); containerStack.pop();

	} else {
		// assign: var_name "=" expr ";"
		line++;
		TNode* assignNode = createASTNode("ASSIGN_NODE", "", parent, line, currentProc);
		controller.statementTable.insertStatement(assignNode);

		populateParent(parent, line);
		populateFollows(line, false, parent, assignNode);

		TNode* varNode = createASTNode("VAR_NODE", nextToken.name, assignNode, line, currentProc);
		variableName();

		populateModifies(line, currentProc);

		match("=");
		expr(assignNode);
		match(";");
		
	}
}

void Parser::expr(TNode* assignNode) {
	// expr: expr "+" term | expr "-" term | term
	// transform left recursive grammar into
	// expr: E' | term
	// E' : "+" term E' | "-" term E' | epilson
	// 
	// term: term "*" factor | factor
	// factor: var_name | const_value | "(" expr ")"
	term(assignNode);
	exprPrime(assignNode);
}

void Parser::exprPrime(TNode* assignNode) {
	if(nextToken.name == "+") {
		match("+");
		term(assignNode);
		exprPrime(assignNode);
	} else if(nextToken.name == "-") {
		match("-");
		term(assignNode);
		exprPrime(assignNode);
	} else {
		return;
	}
}

void Parser::term(TNode* assignNode) {
	// term: T'
	// T': "*" factor T' | epilson
	factor(assignNode);
	termPrime(assignNode);
}

void Parser::termPrime(TNode* assignNode) {
	// T': "*" factor T' | epilson
	if(nextToken.name == "*") {
		match("*");
		factor(assignNode);
		termPrime(assignNode);
	} else {
		return;
	}
}

void Parser::factor(TNode* assignNode) {
	// factor: var_name | const_value | "(" expr ")"
	if(nextToken.name == "(") {
		match("(");
		expr(assignNode);
		match(")");
	}
	else if(nextToken.token == IDENT) {
		variableName();
		populateUses(line, currentProc, true);
	} else {
		constantValue();
	}
}

void Parser::constantValue() {
	controller.constantTable.insertConst(atoi(nextToken.name.c_str()));
	nextToken = getToken();
}

void Parser::variableName() {
	lastVarIndex = controller.varTable.insertVar(nextToken.name);
	nextToken = getToken();
}

int Parser::getProcedureIndex(string procName) {
	for(size_t i = 0; i < procedureNames.size(); i++) {
		if(procedureNames.at(i) == procName) {
			return i+1;
		}
	}
	return -1;
}

void Parser::match(string tokenName) {
	if(nextToken.name == tokenName) {
		nextToken = getToken();
	} else {
		cout << "Syntax error: Expecting " << nextToken.name << " and lexeme " << nextToken.token << endl;
	}
}

void Parser::populateParent(TNode* parent, int line) {
	if(parent->getParent()->getNodeType() == "WHILE_NODE") 
		controller.parentTable.insertParent(parent->getStmtNum(), line);

	if(parent->getParent()->getNodeType() == "THEN_NODE" || parent->getParent()->getNodeType() == "ELSE_NODE")
		controller.parentTable.insertParent(parent->getStmtNum(), line); // stmtLst node has the same line number
}

void Parser::populateFollows(int line, bool isContainer, TNode* prev, TNode* current) {
	//cout << " line : " << line << "\tpreviousStmt" << previousStmt << endl;
	if(previousStmt > 0 && prev != NULL) {
		controller.followsTable.insertFollows(previousStmt, line);
		controller.ast.assignRightSibling(prev, current);
	}

	previousStmt = line;
	prev = current;

	if(isContainer) {
		previousStmt = 0;
		prev = NULL;
	}
}

void Parser::populateModifies(int line, int procedure) {
	// for assignment statement
	controller.modifiesTable.insertModifiesStmt(line, lastVarIndex);
	controller.modifiesTable.insertModifiesProc(line, procedure);

	// container statements
	stack<int> tempStack = stack<int>();
	while(containerStack.size() > 0) {
		int top = containerStack.top();
		tempStack.push(top);

		controller.modifiesTable.insertModifiesStmt(top, lastVarIndex);
		controller.modifiesTable.insertModifiesProc(top, procedure);
		containerStack.pop();
	}

	while(tempStack.size() > 0) {
		containerStack.push(tempStack.top());
		tempStack.pop();
	}
}

void Parser::populateUses(int line, int procedure, bool assignStatement) {
	if(assignStatement) {
		controller.usesTable.insertUsesStmt(line, lastVarIndex);
		controller.usesTable.insertUsesProc(line, procedure);
	}

	stack<int> tempStack = stack<int>();
	while(containerStack.size() > 0) {
		int top = containerStack.top();
		tempStack.push(top);

		controller.usesTable.insertUsesStmt(top, lastVarIndex);
		controller.usesTable.insertUsesProc(top, procedure);
		containerStack.pop();
	}

	while(tempStack.size() > 0) {
		containerStack.push(tempStack.top());
		tempStack.pop();
	}
}

Lexeme Parser::getToken() {
	return lexer.lex();
}

