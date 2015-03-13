#pragma once
#include <fstream>
#include <iostream>
#include <stack>
#include <algorithm>

#include "../PKB/AST.h"
#include "../PKB/PKBController.h"
#include "Lexeme.h"
#include "Lexer.h"
#include "NewParser.h"
#include "Operator.h"

using namespace std;

Parser::Parser() {
}

Parser::Parser(string filepath) {
	this->filepath = filepath;
	this->controller = PKBController();
	this->lexer = Lexer("");
	this->line = 0;
	this->currentProc = 1; // there is at least one procedure
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
	lexer = Lexer(programString);

	program();
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
	procedure();
}

TNode* Parser::createASTNode(string nodeName, string data, TNode* parent, int line, int parentProc) {

}

void Parser::procedure() {
	// "procedure" proc_name "{" stmtLst "}"
	match("procedure");
	string procName = procedureName();
	TNode* procNode = new TNode("PROC_NODE", procName, line, currentProc);
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
	if(nextToken.token == CLOSE_BLOCK)
		return;
	stmtLst(parent);

}

void Parser::stmt(TNode* parent) {
	// stmt: call | while | if | assign
	if(nextToken.name == "call") {
		// call: "procedure" proc_name ";"
		TNode* callNode = createASTNode("CALL_NODE", nextToken.name, parent, ++line, currentProc);
		controller.statementTable.insertStatement(callNode);
		match("call");

		string newProcedure = procedureName();
		controller.callsTable.insertCalls(currentProc, getProcedureIndex(newProcedure));
		match(";");

	} else if(nextToken.name == "while") {
		// while: "while" var_name "{" stmtLst "}"
		TNode* whileNode = createASTNode("WHILE_NODE", nextToken.name, parent, ++line, currentProc);
		controller.statementTable.insertStatement(whileNode);
		match("while");

		TNode* whileVarNode = createASTNode("VAR_NODE", nextToken.name, whileNode, line, currentProc);
		variableName();

		match("{");
		TNode* whileStmtLstNode = createASTNode("STMTLST_NODE", "", whileNode, line, currentProc);
		stmtLst(whileStmtLstNode);

		match("}");
	} else if(nextToken.name == "if") {
		// if: "if" var_name "then" "{" stmtLst "}" "else" "{" stmtLst "}"
		TNode* ifNode = createASTNode("IF_NODE", nextToken.name, parent, ++line, currentProc);
		controller.statementTable.insertStatement(ifNode);
		match("if");
		TNode* ifVarNode = createASTNode("VAR_NODE", nextToken.name, ifNode, line, currentProc);
		variableName();

		TNode* thenNode = createASTNode("THEN_NODE", nextToken.name, ifNode, line, currentProc);
		match("then");
		match("{");
		TNode* thenStmtLstNode = createASTNode("STMTLST_NODE", "", thenNode, line, currentProc);
		stmtLst(thenStmtLstNode);
		match("}");

		TNode* elseNode = createASTNode("ELSE_NODE", nextToken.name, ifNode, line, currentProc);
		match("else");
		match("{");
		TNode* elseStmtLstNode = createASTNode("STMTLST_NODE", "", elseNode, line, currentProc);
		stmtLst(elseStmtLstNode);
		match("}");

	} else {
		// assign: var_name "=" expr ";";
	}
}

void Parser::variableName() {
	controller.varTable.insertVar(nextToken.name);
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

Lexeme Parser::getToken() {
	return lexer.lex();
}

