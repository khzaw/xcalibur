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
	string procedureName;
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
	void match(int i);
	void program();
	void procedure();
	void stmtLst();
	void stmt();
	void error();
	bool checkFileExists();
};