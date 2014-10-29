#pragma once
/*
NAME: LETTER(LETTER|DIGIT)
INTERGER: DIGIT+

procedure: 'procedure' proc_name '{' stmtLst '}'
stmtLst: stmt+
stmt: assign|while
while: 'while' var_name '{' stmtLst '}'
assign: var_name '=' expr ';'
expr: expr '+' factor | factor
factor: var_name | const_value
var_name: NAME
proc_name: NAME
const_value: INTEGER
*/
#include <fstream>
#include <iostream>

#include "AST.h"
#include "Parser.h"
#include "Lexer.h"
#include "Lexeme.h"
#include "PKBController.h"

using namespace std;

Parser::Parser() {
}

Parser::Parser(string file) {
	this->procName = "";
	this->nextToken = Lexeme();
	this->filename = file;
	this->loc = 0;
	this->lexer = Lexer("");
	this->controller = PKBController(); 
	parse();
}

Parser::~Parser() {
}

void Parser::parse() {
	if(!(checkFileExists())) {
		cout << filename << " does not exist!";
		return;
	}

	string currentLine, programString;
	ifstream inputFile;
	inputFile.open(filename);
	while(!inputFile.eof()) {
		getline(inputFile, currentLine);
		// can strip out comments from here .. not sure it's the best approach though
		programString += " " + currentLine;
	}
	inputFile.close();
	lexer = Lexer(programString);
	program();
}

void Parser::printOut() {
	Lexeme token;
	while(!token.equals(Lexeme(EOL, ""))) {
		token = lexer.lex();
		cout << "lexeme: \"" << token << endl;
	}
	cout << "=========" << endl;
}

bool Parser::checkFileExists() {
	ifstream inputFile(filename);
	if(inputFile.fail()) return false;
	inputFile.close();
	return true;
}

void Parser::program() {
	nextToken = getToken();
	procedure();
}

void Parser::procedure() {
	match(KEYWORDS[0]);

	procedureName();
	TNode procNode = TNode(TNODE_NAMES[PROC_NODE], procName, 0, 0);

	match("{");

	TNode procStmtLstNode = createASTNode(STMTLST_NODE, "", procNode);
	stmtLst(procStmtLstNode);

    match("}");
}

void Parser::stmtLst(TNode parent) {
	stmt(parent);
	if(nextToken.token == CLOSE_BLOCK) return;
	else stmtLst(parent);
}


void Parser::stmt(TNode parent) {
	if(nextToken.token == IDENT && nextToken.name == "while") {			// while statement
		TNode whileNode = createASTNode(WHILE_NODE, nextToken.name, parent);
		match(KEYWORDS[1]);

		TNode whileVarNode = createASTNode(VAR_NODE, nextToken.name, whileNode);	// whileVar
		variableName();

		match("{");

		TNode whileStmtLstNode = createASTNode(STMTLST_NODE, "", whileNode);
		stmtLst(whileStmtLstNode);

		match("}");
	} else if(nextToken.token == IDENT) {

		//cout << "parent of assignment: " <<  parent.getNodeType() << endl;
		TNode assignNode = createASTNode(ASSIGN_NODE, "", parent);

		TNode varNode = createASTNode(VAR_NODE, nextToken.name, assignNode);
		variableName();

		match("=");
		expr(assignNode);
		match(";");

	}

}

void Parser::expr(TNode assignNode) {
	// expr: expr '+' factor | factor
	/*
	 * this is a left-recursive grammar, top down parsing can't handle this
	 * transform it into
	 * expr: FE'
	 * E' : +TE' | epsilon
	 */

	factor(assignNode);
	exprPrime(assignNode);
		
}


void Parser::factor(TNode assignNode) {
	// factor: var_name | const_value
	if(nextToken.token == IDENT) {			// TODO: check valid IDENT (not keywords)
		TNode varNode = createASTNode(VAR_NODE, nextToken.name, assignNode);
		variableName();
	} else {
		// INT_LIT;
		TNode constantNode = createASTNode(CONSTANT_NODE, nextToken.name, assignNode);
		constantValue();
	}
}

void Parser::exprPrime(TNode assignNode) {
	if(nextToken.token == PLUS) {

		TNode plusNode = createASTNode(PLUS_NODE, nextToken.name, assignNode);
		match("+");

		factor(assignNode);
		exprPrime(assignNode);
	} else {
		return;
	}
}

TNode Parser::createASTNode(int nodeType, string name, TNode parentNode, int lineNo, int parentProc) {
	TNode node = TNode(TNODE_NAMES[nodeType], name, lineNo, parentProc);
	if(nodeType == PROC_NODE) {
		controller.procTable.insertProc(name);
		controller.ast.insertRoot(&node);
	}
	controller.ast.assignChild(&parentNode, &node);
	// cout << "PARENT : " <<  parentNode.getNodeType() << "\t" << "CHILD: " << TNODE_NAMES[nodeType] << "," << node.getData() << endl;
	return node;
}

void Parser::variableName() {
	// TODO check valid variable name
	cout << "variableName: " << nextToken.name << endl;
	controller.varTable.insertVar(nextToken.name);
	nextToken = getToken();
}


void Parser::constantValue() {
	 //cout << "constantValue: " << nextToken.name << endl;
	nextToken = getToken();
}

void Parser::procedureName() {
	// TODO check valid variable name
	procName = nextToken.name;
	 //cout << "procName: " << nextToken.name << endl;

	
	nextToken = getToken();
}


void Parser::match(string s) {
	if(nextToken.name == s) {
		//loc++;
		nextToken = getToken();
	} else {
		//cout << "Syntax error: Expecting " << s << " on line number " << loc << endl;
	}

}

PKBController Parser::getController() {
	return controller;
}

Lexeme Parser::getToken() {
	return lexer.lex();
}