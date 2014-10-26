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

#include "Parser.h"
#include "Lexer.h"


using namespace std;

Parser::Parser() {
	this->nextToken = ERROR;
	this->procedureName = "";
}

void Parser::parse(string filename) {
	if(!(Parser::checkFileExists)) {
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
//	this->lexer = Lexer(programString);
//	program();
}

void Parser::program() {
	nextToken = getToken();
	procedure();
}

void Parser::procedure() {
	
}


void Parser::match(int token) {

}
int Parser::getToken() {
	return lexer.lex();
}