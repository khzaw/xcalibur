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
#include "Lexeme.h"

using namespace std;

Parser::Parser() {
}

Parser::Parser(string file) {
	this->procedureName = "";
	this->nextToken = Lexeme();
	this->filename = file;
	this->loc = 0;
	this->lexer = Lexer("");
	parse();
}

Parser::~Parser() {
}

void Parser::parse() {
	if(!(checkFileExists())) {
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
	lexer = Lexer(programString);
	//program();
}

void Parser::printOut() {
	Lexeme token;
	while(!token.equals(Lexeme(EOL, ""))) {
		token = lexer.lex();
		cout << "lexeme: \"" << token << endl;
	}
	cout << endl << "=========" << endl;
}

bool Parser::checkFileExists() {
	ifstream inputFile(filename);
	if(inputFile.fail()) return false;
	inputFile.close();
	return true;
}

void Parser::program() {
	nextToken = getToken();
	procedure();
}

void Parser::procedure() {
//	match(KEYWORDS[0]);
//	match("proc_name");
//	match("{");

//	match("}");
}


void Parser::match(string s) {

}

Lexeme Parser::getToken() {
	return lexer.lex();
}