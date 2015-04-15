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
	this->controller = new PKBController();
	this->lexer = Lexer("");
	this->line = 0;
	this->currentProc = -1;
	this->previousStmt = 0;			// for poulation of follows
	this->prev = NULL;
	this->lastVarIndex = -1;		// for modifies population
	this->totalParents = 0;
	this->totalSiblings = 0;
	parse();
	constructRelations();
	debug();
}

void Parser::constructRelations() {
	this->controller->constructCalls();
	this->controller->constructFollows();
	this->controller->constructModifies();
	this->controller->constructParent();
	this->controller->constructNext();
	this->controller->constructUses();
	this->controller->constructContains();
	this->controller->constructSiblings();
	// cout << "yay" << endl;
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
	// cout << programString << endl;
	lexer = Lexer(programString);
	program();
	debug();

}

void Parser::debug() {
	cout << "VarTable: " << controller->varTable->getSize() << endl;
	cout << "ConstTable: " << controller->constantTable->getSize() << endl;
	cout << "Statements: " << controller->statementTable->getSize() << endl;
	cout << "Parent : " << controller->parentTable->getSize() << endl;
	cout << "Follows : " << controller->followsTable->getSize() << endl;
	cout << "Calls: " << controller->callsTable->getSize() << endl;
	cout << "ModifiesStmt: " << controller->modifiesTable->getSizeStmtModifies() << endl;
	cout << "ModifiesProc: " << controller->modifiesTable->getSizeProcModifies() << endl;
	cout << "UsesStmt: " << controller->usesTable->getSizeStmtUses() << endl;
	cout << "UsesProc: " << controller->usesTable->getSizeProcUses() << endl;
	cout << "Total Parents: " << totalParents << endl;
	cout << "Total Siblings: " << totalSiblings << endl;
	cout << "Debug: Done" << endl;
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
	parent->addChild(node);
	node->addParent(parent);

	//controller->ast->assignChild(parent, node);
	//controller->ast->assignParent(node, parent);
	totalParents++;
	return node;
}

void Parser::procedure() {
	// "procedure" proc_name "{" stmtLst "}"
	this->previousStmt = 0;
	this->currentProc++;

	match("procedure");
	string procName = procedureName();
	this->currentProc = getProcedureIndex(procName);
	// cout << procName << endl;
	TNode* procNode = new TNode("PROC_NODE", procName, line, currentProc);

	match("{");
	TNode* procStmtLstNode = createASTNode("STMTLST_NODE", "", procNode, line, currentProc);
	stmtLst(procStmtLstNode);
	match("}");

	populateRoot(procNode, currentProc);
}

string Parser::procedureName() {
	string procName = nextToken.name;
	if(find(procedureNames.begin(), procedureNames.end(), procName) == procedureNames.end()) { // not found
		procedureNames.push_back(procName);
	}
	controller->procTable->insertProc(procName);
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
		controller->statementTable->insertStatement(callNode);
		match("call");


		string newProcedure = procedureName();
		int procIndex = getProcedureIndex(newProcedure);

		controller->callsTable->insertCalls(currentProc, procIndex);
		callStatements.insert(pair<int, string>(line, newProcedure));
		match(";");

		populateProcAndContainers(procIndex, line);
		populateFollows(line, false, prev, callNode);
		populateParent(parent, line);

	} else if(nextToken.name == "while") {
		// while: "while" var_name "{" stmtLst "}"
		line++;
		TNode* whileNode = createASTNode("WHILE_NODE", nextToken.name, parent, line, currentProc);
		controller->statementTable->insertStatement(whileNode);
		match("while");

		populateFollows(line, true, prev, whileNode);
		populateParent(parent, line);
		containerStack.push(line);
		containerNodeStack.push(whileNode);
		populateProcAndContainers(currentProc, line);


		//TNode* whileVarNode = createASTNode("VAR_NODE", nextToken.name, whileNode, line, currentProc);
		whileNode->setData(nextToken.name);
		variableName();

		populateUses(line, currentProc);

		match("{");
		TNode* whileStmtLstNode = createASTNode("STMTLST_NODE", "", whileNode, line, currentProc);
		stmtLst(whileStmtLstNode);
		match("}");
		 
		previousStmt = containerStack.top(); containerStack.pop();
		prev = containerNodeStack.top(); containerNodeStack.pop();
		
	} else if(nextToken.name == "if") {
		// if: "if" var_name "then" "{" stmtLst "}" "else" "{" stmtLst "}"
		++line;
		TNode* ifNode = createASTNode("IF_NODE", nextToken.name, parent, line, currentProc);
		controller->statementTable->insertStatement(ifNode);
		match("if");

		populateFollows(line, true, prev, ifNode);
		populateParent(parent, line);
		containerStack.push(line);
		containerNodeStack.push(ifNode);
		populateProcAndContainers(currentProc, line);

		//TNode* ifVarNode = createASTNode("VAR_NODE", nextToken.name, ifNode, line, currentProc);
		ifNode->setData(nextToken.name);
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

		controller->ast->assignRightSibling(thenNode, elseNode);

		previousStmt = containerStack.top(); containerStack.pop();
		prev = containerNodeStack.top(); containerNodeStack.pop();

	} else {
		// assign: var_name "=" expr ";"
		line++;
		TNode* assignNode = createASTNode("ASSIGN_NODE", "", parent, line, currentProc);
		controller->statementTable->insertStatement(assignNode);

		postfix = "";
		operatorStack.push(Operator(0, "NULL")); // sentinel

		populateFollows(line, false, prev, assignNode);
		populateParent(parent, line);

		TNode* varNode = createASTNode("VAR_NODE", nextToken.name, assignNode, line, currentProc);
		variableName();

		populateModifies(line, currentProc);

		match("=");
		expr(assignNode);
		match(";");

		while(!operatorStack.top().isNull()) {
			popOperator(operatorStack.top());
		}

		//TNode top = operandStack.top();

		controller->ast->assignChild(assignNode, (operandStack.top()));
		controller->ast->assignParent(operandStack.top(), assignNode);

		cout << "postfix : " << postfix << endl;
		assignNode->setData(postfix);

		operatorStack.pop();		// remove the sentinel
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

		Operator plusOp(1, "+");
		while(!operatorStack.top().isNull() && operatorStack.top().op != 3) {
			if(operatorStack.top().op == OPERATOR_OPENPAREN) {
				operatorStack.push(plusOp);
			} else {
				if(plusOp.op <= operatorStack.top().op) {
					popOperator(operatorStack.top());
				} else {
					break;
				}
			}
		}

		operatorStack.push(plusOp);

		term(assignNode);
		exprPrime(assignNode);
	} else if(nextToken.name == "-") {
		match("-");

		Operator minusOp(1, "-");
		while(!operatorStack.top().isNull() && operatorStack.top().op != 3) {
			if(operatorStack.top().op == OPERATOR_OPENPAREN) {
				operatorStack.push(minusOp);
			} else {
				if(minusOp.op <= operatorStack.top().op) {
					popOperator(operatorStack.top());
				} else {
					break;
				}
			}
		}
		operatorStack.push(minusOp);

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

		Operator multiplyOp(2, "*");
		while(!operatorStack.top().isNull() && operatorStack.top().op != 3) {
			if(operatorStack.top().op == OPERATOR_OPENPAREN) {
				operatorStack.push(multiplyOp);
			} else {
				if(multiplyOp.op <= operatorStack.top().op) {
					popOperator(operatorStack.top());
				} else {
					break;
				}
			}
		}
		operatorStack.push(multiplyOp);

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
		Operator openParen(3, "(");
		operatorStack.push(openParen);
		expr(assignNode);
		match(")");
		while(operatorStack.top().op != 3)
			popOperator(operatorStack.top());
		operatorStack.pop(); // "("
	}
	else if(nextToken.token == IDENT) {
		operandStack.push(new TNode("VAR_NODE", nextToken.name, line, currentProc));
		if(postfix.length() > 0) postfix += " ";
		postfix += nextToken.name;

		variableName();


		populateUses(line, currentProc, true);
	} else {
		operandStack.push(new TNode("CONST_NODE", nextToken.name, line, currentProc));
		if(postfix.length() > 0) postfix += " ";
		postfix += nextToken.name;

		constantValue();

	}
}

void Parser::constantValue() {
	controller->constantTable->insertConst(atoi(nextToken.name.c_str()));
	nextToken = getToken();
}

void Parser::variableName() {
	lastVarIndex = controller->varTable->insertVar(nextToken.name);
	nextToken = getToken();
}

int Parser::getProcedureIndex(string procName) {
	for(size_t i = 0; i < procedureNames.size(); i++) {
		if(procedureNames.at(i) == procName) {
			return i;
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
		controller->parentTable->insertParent(parent->getStmtNum(), line);

	if(parent->getParent()->getNodeType() == "THEN_NODE" || parent->getParent()->getNodeType() == "ELSE_NODE") {
		//controller->parentTable->insertParent(parent->getStmtNum(), line); // stmtLst node has the same line number
		controller->parentTable->insertParent(containerStack.top(), line);
	}
}

void Parser::populateFollows(int line, bool isContainer, TNode* previousNode, TNode* currentNode) {
	//cout << " line : " << line << "\tpreviousStmt" << previousStmt << endl;
	//cout << "prev : ";
	//if(prev == NULL) cout << "NULL";
	//else cout << prev->getNodeType();

	//cout << "\t current : ";
	//if(current == NULL) cout << "NULL";
	//else cout << current->getNodeType();

	// call statement
		// populateFollows(line, false, prev, callNode);


	if(previousStmt > 0 && prev != NULL) {
		// cout << previousNode->getNodeType() << "" << previousNode->getStmtNum() << "\t" << currentNode->getNodeType() << "" << currentNode->getStmtNum() << endl;
		controller->ast->assignRightSibling(previousNode, currentNode);
		controller->followsTable->insertFollows(previousStmt, line);
		totalSiblings++;
		//cout << " right ";
	}
	//cout << endl;

	previousStmt = line;
	prev = currentNode;

	if(isContainer) {
		previousStmt = 0;
		prev = NULL;
	}
}

void Parser::populateModifies(int line, int procedure) {

	set<int> callers = controller->callsTable->getCallerS(procedure);
	string currentProcedureName = procedureNames.at(procedure);
	// for assignment statement
	controller->modifiesTable->insertModifiesStmt(line, lastVarIndex);
	controller->modifiesTable->insertModifiesProc(procedure, lastVarIndex);

	set<int>::iterator it;



	if(callStatements.size() > 0) {
		for(std::map<int, string>::iterator it=callStatements.begin(); it!=callStatements.end(); ++it) {
			if(it->second == currentProcedureName) {
				controller->modifiesTable->insertModifiesStmt(it->first, lastVarIndex);
			}
		}

	}

	for_each(callers.begin(), callers.end(), [&](int num){
		controller->modifiesTable->insertModifiesProc(num, lastVarIndex);
	});
	

	// container statements
	stack<int> tempStack = stack<int>();
	while(containerStack.size() > 0) {
		int top = containerStack.top();
		tempStack.push(top);

		controller->modifiesTable->insertModifiesStmt(top, lastVarIndex);
		controller->modifiesTable->insertModifiesProc(procedure, lastVarIndex); 
		containerStack.pop();
	}

	while(tempStack.size() > 0) {
		containerStack.push(tempStack.top());
		tempStack.pop();
	}
}

void Parser::populateProcAndContainers(int procedure, int containerLine) {
	map<int, stack<int>>::iterator it = procAndContainers.find(procedure);
	if(it != procAndContainers.end() && procedure == currentProc) {
		it->second.push(containerLine);
	} else {
		stack<int> newStack;
		newStack.push(containerLine);
		procAndContainers.insert(pair<int, stack<int>>(procedure, newStack));
	}

}

void Parser::populateUses(int line, int procedure, bool assignStatement) {
	set<int> callers = controller->callsTable->getCallerS(procedure);
	string currentProcedureName = procedureNames.at(procedure);
	if(assignStatement) {

		controller->usesTable->insertUsesStmt(line, lastVarIndex);
		controller->usesTable->insertUsesProc(procedure, lastVarIndex); 

		if(callStatements.size() > 0) {
			for(std::map<int, string>::iterator it=callStatements.begin(); it!=callStatements.end(); ++it) {
				if(it->second == currentProcedureName) {
					controller->usesTable->insertUsesStmt(it->first, lastVarIndex);
				}
			}
		}
	}

	for_each(callers.begin(), callers.end(), [&](int num){
		controller->usesTable->insertUsesProc(num, lastVarIndex);
	});

	stack<int> tempStack = stack<int>();
	while(containerStack.size() > 0) {
		int top = containerStack.top();
		tempStack.push(top);

		controller->usesTable->insertUsesStmt(top, lastVarIndex);
		if(callStatements.size() > 0) {
			for(std::map<int, string>::iterator it=callStatements.begin(); it!=callStatements.end(); ++it) {
				if(it->second == currentProcedureName) {
					controller->usesTable->insertUsesStmt(it->first, lastVarIndex);
				}
			}
		}
		controller->usesTable->insertUsesProc(procedure, lastVarIndex);
		containerStack.pop();
	}

	while(tempStack.size() > 0) {
		containerStack.push(tempStack.top());
		tempStack.pop();
	}
}

void Parser::populateRoot(TNode* procedureNode, int procedureIndex) {
	controller->ast->insertRoot(procedureNode);
	controller->procTable->insertASTRootNode(procedureIndex, procedureNode);
}

void Parser::popOperator(Operator op) {
	string nodeName = "";

	if(op.value == "+") {
		nodeName = "PLUS_NODE";
	} else if(op.value == "-") {
		nodeName = "MINUS_NODE";
	} else if(op.value == "*") {
		nodeName = "TIMES_NODE";
	}


	TNode* operatorNode = new TNode(nodeName, op.value, line, currentProc);
	
	TNode* rightOperand = operandStack.top();	operandStack.pop();
	TNode* leftOperand = operandStack.top();	operandStack.pop();

	operatorNode->addChild(leftOperand);
	operatorNode->addChild(rightOperand);

	operatorStack.pop();
	operandStack.push(operatorNode);

	postfix += " " + op.value; 
}

Lexeme Parser::getToken() {
	return lexer.lex();
}

