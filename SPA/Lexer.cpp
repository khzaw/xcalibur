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

#include "Lexer.h"
#include <iostream>

using namespace std;

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
}

void Lexer::addChar() {
	lexeme += nextChar;
}

int Lexer::lex() {
	lexeme = "";

	while(charClass == WHITESPACE) getChar();

	if(charClass == ERROR) { addChar(); getChar(); return ERROR; }
	if(charClass == EOL) { return EOL; }

	switch(charClass) {
	case LETTER:
		addChar();
		getChar();
		while(charClass == LETTER || charClass == DIGIT) {
			addChar();
			getChar();
		}
		return IDENT;
		break;
	
	case DIGIT:
		addChar();
		getChar();
		while(charClass == DIGIT) {
			addChar();
			getChar();
		}
		return INT_LIT;
		break;

	case PLUS:
		addChar();
		getChar();
		return PLUS;
		break;

	case EQ:
		addChar();
		getChar();
		return EQ;
		break;

	case SEMICOLON:
		addChar();
		getChar();
		return SEMICOLON;
		break;
	}
}