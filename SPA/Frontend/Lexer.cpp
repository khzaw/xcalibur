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
const_value: INTEGER
*/

#include "SPA/Frontend/Lexer.h"
#include <iostream>

using namespace std;

Lexer::Lexer() {
}

Lexer::Lexer(string in) {
	this->input = in;
	this->charClass = ERROR;
	this->nextChar = ' ';
	this->lexeme = "";
	getChar();
}

Lexer::~Lexer() {
}

void Lexer::setNewInput(string in) {
	input = in;
	getChar();
}

void Lexer::getChar() {
	if(input.size() > 0) {
		nextChar = input[0];
		input.erase(0, 1);
	} else nextChar = '$';

	charClass = ERROR;

	if((nextChar > 64 && nextChar < 91) || (nextChar > 96 && nextChar <123))
		charClass = LETTER;

	if(nextChar > 47 && nextChar < 58)
		charClass = DIGIT;

	if(nextChar == ' ') charClass = WHITESPACE;
	if(nextChar == '$') charClass = EOL;
	if(nextChar == '+') charClass = PLUS;
	if(nextChar == '*') charClass = TIMES;
	if(nextChar == '=') charClass = EQ;
	if(nextChar == ';') charClass = SEMICOLON;
	if(nextChar == '{') charClass = OPEN_BLOCK;
	if(nextChar == '}') charClass = CLOSE_BLOCK;
	if(nextChar == '\t') charClass = TAB_CHAR;
}

void Lexer::addChar() {
	lexeme += nextChar;
}

Lexeme Lexer::lex() {
	lexeme = "";

	while(charClass == WHITESPACE || charClass == TAB_CHAR) getChar();

	if(charClass == ERROR) { addChar(); getChar(); return Lexeme(ERROR, lexeme); }
	if(charClass == EOL) { return Lexeme(EOL, lexeme); }

	switch(charClass) {
	case LETTER:
		addChar(); getChar();
		while(charClass == LETTER || charClass == DIGIT) {
			addChar(); getChar();
		}
		return Lexeme(IDENT, lexeme);

	case DIGIT:
		addChar(); getChar();
		while(charClass == DIGIT) {
			addChar(); getChar();
		}
		return Lexeme(INT_LIT, lexeme);

	case PLUS:
		addChar(); getChar();
		return Lexeme(PLUS, lexeme);

	case TIMES:
		addChar(); getChar();
		return Lexeme(TIMES, lexeme);;

	case EQ:
		addChar(); getChar();
		return Lexeme(EQ, lexeme);

	case SEMICOLON:
		addChar(); getChar();
		return Lexeme(SEMICOLON, lexeme);

	case OPEN_BLOCK:
		addChar(); getChar();
		return Lexeme(OPEN_BLOCK, lexeme);

	case CLOSE_BLOCK:
		addChar(); getChar();
		return Lexeme(CLOSE_BLOCK, lexeme);
	}
}