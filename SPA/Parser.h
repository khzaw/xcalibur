#pragma once
#include <iostream>
#include <set>
#include "Lexer.h"
#include "Lexeme.h"

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

public:
	Parser();
	Parser(string filename);
	void parse();
	~Parser();
	void printOut();
private:
	Lexeme getToken();
	void match(string s);
	void program();
	void procedure();
	void stmtLst();
	void stmt();
	void expr();
	void exprPrime();
	void variableName();
	void procedureName();
	void constantValue();
	void factor();
	void error();
	bool checkFileExists();
};