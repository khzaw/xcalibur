#pragma once
#include <iostream>
#include <set>
#include "Lexer.h"
#include "Lexeme.h"
#include "PKBController.h"

using namespace std;

static string KEYWORDS[] = {
	"procedure",
	"while"
};

enum NAME {
	PROC_NAME,
	VAR_NAME
};

class Parser {
	string filename;
	Lexeme nextToken;
	int loc;
	string procName;
	Lexer lexer;
	PKBController controller;

public:
	Parser();
	Parser(string filename);
	void parse();
	~Parser();
	void printOut();
	PKBController getController();
private:
	Lexeme getToken();
	void match(string s);
	void program();
	void procedure();
	void stmtLst(TNode parent);
	void stmt(TNode parent);
	void expr(TNode assignNode);
	void exprPrime(TNode assignNode);
	void variableName();
	void procedureName();
	void constantValue();
	void factor(TNode assignNode);
	void error();
	bool checkFileExists();
	// node creation
	TNode createASTNode(int nodeType, string name, TNode parentNode, int lineNo=0, int parentProc=0);
};