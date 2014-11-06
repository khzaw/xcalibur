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
#include <stack>

#include "AST.h"
#include "Parser.h"
#include "Lexer.h"
#include "Lexeme.h"
#include "PKBController.h"
#include "Operator.h"

using namespace std;

Parser::Parser() {
}

Parser::Parser(string file) {
	this->procName = "";
	this->nextToken = Lexeme();
	this->filename = file;
	this->loc = 0;
	this->temp = 0;
	this->lastVarIndex = -1;
	this->lexer = Lexer("");
	this->controller = PKBController(); 
	this->procCount = 0;
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
	match(KEYWORDS[0]); nextToken = getToken();

	procedureName();
	TNode procNode = TNode(TNODE_NAMES[PROC_NODE], procName, loc, procCount);

	match("{"); nextToken = getToken();

	TNode procStmtLstNode = createASTNode(STMTLST_NODE, "", &procNode);
	stmtLst(procStmtLstNode);

	match("}"); nextToken = getToken();
}

void Parser::stmtLst(TNode parent) {
	stmt(parent);
	if(nextToken.token == CLOSE_BLOCK) return;
	else stmtLst(parent);
}


void Parser::stmt(TNode parent) {
	if(nextToken.token == IDENT && nextToken.name == "while") {			// while statement
		loc++; 
		TNode whileNode = createASTNode(WHILE_NODE, nextToken.name, &parent, loc);

		// for a container stmt, set back to zero
		if(temp > 0) {
			controller.followsTable.insertFollows(temp, loc);
		}
		temp = 0;
		containerStack.push(loc);

		controller.statementTable.insertStatement(&whileNode);


		match(KEYWORDS[1]); nextToken = getToken();

		TNode whileVarNode = createASTNode(VAR_NODE, nextToken.name, &whileNode, loc);	// whileVar
		variableName(); 
		nextToken = getToken();

		match("{"); nextToken = getToken();

		TNode whileStmtLstNode = createASTNode(STMTLST_NODE, "", &whileNode, loc);
		stmtLst(whileStmtLstNode);

		match("}"); 
		temp = containerStack.top();	containerStack.pop();
		nextToken = getToken();
	} else if(nextToken.token == IDENT) {

		loc++;
		TNode assignNode = createASTNode(ASSIGN_NODE, "", &parent, loc); 
		TNode varNode = createASTNode(VAR_NODE, nextToken.name, &assignNode, loc);
		controller.statementTable.insertStatement(&assignNode);
		//cout << nextToken.name << "\t" << loc << endl;
		variableName(); 
		populateModifies(loc);
		if(parent.getNodeType() == TNODE_NAMES[WHILE_NODE] || parent.getNodeType() == TNODE_NAMES[IF_NODE])
			controller.parentTable.insertParent(parent.getStmtNum(), loc);

		if(temp > 0) {
			controller.followsTable.insertFollows(temp, loc);
		}
		temp = loc;

		// assignment modifies
		//controller.modifiesTable.insertModifiesStmt(loc, );

		nextToken = getToken();

		match("="); nextToken = getToken();
		expr(assignNode);
		match(";"); nextToken = getToken(); 
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

	
	operatorStack.push(Operator(OPERATOR_NULL, "NULL"));		// sentinel

	factor();  nextToken = getToken();
	exprPrime();

	while(!operatorStack.top().isNull()) {
		popOperator(operatorStack.top());
	}

	controller.ast.assignChild(&assignNode, &(operandStack.top()));
	// cout << "PARENT : " <<  assignNode.getNodeType() << "\t" << "CHILD: " << operandStack.top().getNodeType() << "," << operandStack.top().getData() << endl;
	operatorStack.pop();		// remove the sentinel
}


void Parser::printOperatorStack() {
	cout << "Operator Stack" << endl;
	 for (std::stack<Operator> dump = operatorStack; !dump.empty(); dump.pop())
		std::cout << dump.top().value << '\n';
}

void Parser::printOperandStack() {
	cout << "Operand Stack" << endl;
	 for (std::stack<TNode> dump = operandStack; !dump.empty(); dump.pop())
		std::cout << dump.top().getData() << '\n';
}

void Parser::factor() {
	// factor: var_name | const_value
	if(nextToken.token == IDENT) {			// TODO: check valid IDENT (not keywords)
		//node = createASTNode(VAR_NODE, nextToken.name, &assignNode);
		variableName();
		operandStack.push(TNode(TNODE_NAMES[VAR_NODE], nextToken.name, loc, 0));
	} else {
		// INT_LIT;
		//node = createASTNode(CONSTANT_NODE, nextToken.name, &assignNode);
		constantValue();
		operandStack.push(TNode(TNODE_NAMES[CONSTANT_NODE], nextToken.name, loc, 0));
	}
}

void Parser::exprPrime() {
	// parse an operator
	if(nextToken.token == PLUS) {

		match("+"); 
		Operator plusOp(OPERATOR_ADDITION, "+");

		while(operatorStack.top().op > plusOp.op) {


			if(operatorStack.top().isNull()) { // sentinel value reached;
				operatorStack.pop();
			}

			popOperator(plusOp);
		}
		operatorStack.push(plusOp);
		nextToken = getToken();

		factor(); nextToken = getToken();
		exprPrime();
	} else {
		return;
	}
}

void Parser::popOperator(Operator op) {
	TNode operatorNode = TNode(TNODE_NAMES[PLUS_NODE], "+", loc, 0);

	TNode rightOperand = operandStack.top(); operandStack.pop();
	TNode leftOperand = operandStack.top(); operandStack.pop();

	operatorNode.addChild(&leftOperand);
	operatorNode.addChild(&rightOperand);

	operatorStack.pop();
	operandStack.push(operatorNode);
}


TNode Parser::createASTNode(int nodeType, string name, TNode *parentNode, int lineNo, int parentProc) {
	TNode node = TNode(TNODE_NAMES[nodeType], name, lineNo, parentProc);
	if(nodeType == PROC_NODE) {
		controller.procTable.insertProc(name);
		controller.ast.insertRoot(&node);
	}
	controller.ast.assignChild(parentNode, &node);
	 //cout << "PARENT : " <<  parentNode->getNodeType() << "\t" << "CHILD: " << TNODE_NAMES[nodeType] << "," << node.getData() << endl;
	return node;
}

void Parser::variableName() {
	// TODO check valid variable name
	// cout << "variableName: " << nextToken.name << endl;
	lastVarIndex = controller.varTable.insertVar(nextToken.name);
	//nextToken = getToken();
}


void Parser::constantValue() {
	//cout << "constantValue: " << nextToken.name << endl;
	//nextToken = getToken();
	controller.constantTable.insertConst(atoi(nextToken.name.c_str()));

}

void Parser::procedureName() {
	// TODO check valid variable name
	procName = nextToken.name;
	//cout << "procName: " << nextToken.name << endl;


	nextToken = getToken();
}


void Parser::match(string s) {
	if(nextToken.name == s) {
		// match operator
	} else {
		//cout << "Syntax error: Expecting " << nextToken.name << " on line number " << loc << endl;
	}

}

PKBController Parser::getController() {
	return controller;
}

Lexeme Parser::getToken() {
	return lexer.lex();
}

int Parser::getTotalStatementNumber() {
	return loc;
}

void Parser::populateModifies(int loc) {

	// assignment statement
	controller.modifiesTable.insertModifiesStmt(loc, lastVarIndex);
	controller.modifiesTable.insertModifiesProc(loc, procCount);

	// container statement
	stack<int> temp = stack<int>();
	while(containerStack.size() > 0) {
		int top = containerStack.top();
		temp.push(top);
		controller.modifiesTable.insertModifiesStmt(top, lastVarIndex);
		controller.modifiesTable.insertModifiesStmt(top, procCount);
		containerStack.pop();
	}


	while(temp.size() > 0) {
		containerStack.push(temp.top());
		temp.pop();
	}
}

void Parser::populateUses(int loc) {
}