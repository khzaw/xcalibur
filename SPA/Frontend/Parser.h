#pragma once
#include <iostream>
#include <set>
#include <stack>
#include "Lexer.h"
#include "Lexeme.h"
#include "../PKB/PKBController.h"
#include "TNode.h"
#include "Operator.h"

using namespace std;


static string KEYWORDS[] = {
	"procedure",
	"while",
	"call",
	"if",
	"then",
	"else",
	"call"
};


enum NAME {
	PROC_NAME,
	VAR_NAME
};

class Parser {
	string filename;
	string expressionPostfix;
	Lexeme nextToken;
	int loc;
	int temp;
	int lastVarIndex;
	int procCount;
	string procName;
	Lexer lexer;
	stack<Operator> operatorStack;
	stack<TNode*> operandStack;
	stack<int> containerStack;

public:
	PKBController controller;
	Parser();
	Parser(string filename);
	void parse();
	~Parser();
	void printOut();
	PKBController getController();
	int getTotalStatementNumber();
private:
	Lexeme getToken();
	void match(string s);
	void program();
	void procedure();
	void stmtLst(TNode* parent);
	void stmt(TNode* parent);
	void expr(TNode* assignNode);
	void exprPrime();
	void variableName();
	void procedureName();
	void constantValue();
	void factor(bool rightSide=false);
	void error();
	bool checkFileExists();
	// node creation
	TNode* createASTNode(int nodeType, string name, TNode *parentNode, int lineNo=0, int parentProc=0);

	// for operator precedence
	void popOperator(Operator op);
	void pushOperator(string op);

	void printOperatorStack();
	void printOperandStack();

	void populateModifies(int loc);
	void populateUses(int loc);
};