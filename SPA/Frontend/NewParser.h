#pragma once
#include "Operator.h"

using namespace std;

class Parser {
	string filepath;
	string postfix;
	Lexeme nextToken;
	int line;
	int currentProc;
	string procName;
	Lexer lexer;
	stack<Operator> operatorStack;
	stack<int> operandStack;
	stack<int> containerStack;
	vector<string> procedureNames;

public:
	PKBController controller;
	Parser();
	Parser(string);
	void parse();
	~Parser();
	void printOut();
	PKBController getController();
	int getTotalStatementNumber();

private:
	bool checkFileExists();
	Lexeme getToken();
	void match(string);
	void program();
	void procedure();
	string procedureName();
	void stmtLst(TNode*);
	void stmt(TNode*);
	void expr();
	void exprPrime();
	void variableName();
	TNode* createASTNode(string, string, TNode*, int, int);
	int getProcedureIndex(string);
};