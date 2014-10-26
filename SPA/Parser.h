#pragma once
#include <iostream>
#include "Lexer.h"


using namespace std;

class Parser {
	string filename;
	int nextToken;
	int loc;
	string procedureName;
	Lexer lexer;

public:
	Parser();
	Parser(string filename);
	void parse();
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