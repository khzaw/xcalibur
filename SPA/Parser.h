#pragma once
#include <iostream>
#include "Token.h"
#include "Lexer.h"



using namespace std;

class Parser {
private:
	string filename;
	int nextToken;
	int loc;
	string procedureName;
	Lexer lexer;

public:
	Parser();
	void parse(string filename);
	~Parser();
private:
	int getToken();
	void match(int token);
	void program();
	void procedure();
	void stmtLst();
	void stmt();
	void error();
	bool checkFileExists();
};