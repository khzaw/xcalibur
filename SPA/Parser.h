#pragma once
#include <iostream>
#include "Lexer.h"
#include "Lexeme.h"


using namespace std;

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
	void program();
	void procedure();
	void stmtLst();
	void stmt();
	void error();
	bool checkFileExists();
};