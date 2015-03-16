#include "QueryLexer.h"
#include <iostream>

using namespace std;

QueryLexer::QueryLexer() {
}

QueryLexer::QueryLexer(string in) {
	this->input = in;
	this->charClass = ERROR;
	this->nextChar = ' ';
	this->lexeme = "";
	getChar();
}

QueryLexer::~QueryLexer() {
}

void QueryLexer::getChar() {
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
	if(nextChar == '$' || nextChar == '\0') charClass = EOL;
	if(nextChar == '+') charClass = PLUS;
	if(nextChar == '*') charClass = TIMES;
	if(nextChar == '-') charClass = MINUS;
	if(nextChar == '=') charClass = EQ;
	if(nextChar == ';') charClass = SEMICOLON;
	if(nextChar == '\t') charClass = TAB_CHAR;
	if(nextChar == '#') charClass = HEX;
	if(nextChar == '(') charClass = OPEN_PARENTHESES;
	if(nextChar == ')') charClass = CLOSE_PARENTHESES;
	if(nextChar == ',') charClass = COMMA;
	if(nextChar == '\"') charClass = APOSTROPHE;
	if(nextChar == '_') charClass = UNDERSCORE;
}

void QueryLexer::addChar() {
	lexeme += nextChar;
}

Lexeme QueryLexer::lex() {
	lexeme = "";

	while(charClass == WHITESPACE || charClass == TAB_CHAR) getChar();

	if(charClass == ERROR) { addChar(); getChar(); return Lexeme(ERROR, lexeme); }
	if(charClass == EOL) { return Lexeme(EOL, lexeme); }

	bool isSimple = true;
	bool isUnderscore = false;
	switch(charClass) {
		case LETTER:
			addChar(); getChar();
			while(charClass == LETTER || charClass == DIGIT || charClass == HEX || charClass == UNDERSCORE) {
				if (charClass == HEX) {
					isSimple = false;
				}
				if (charClass == UNDERSCORE) {
					isUnderscore = true;	
				}
				addChar(); getChar();
			}
		
			if(isUnderscore) {
				if(lexeme.compare("prog_line") != 0) {
					return Lexeme(ERROR, lexeme);
				} else {
					return Lexeme(PROG_LINE, lexeme);
				}
			}

			if(isSimple) {
				return Lexeme(SIMPLE_IDENT, lexeme);
			} else {
				return Lexeme(IDENT, lexeme);
			}
			break;
	
		case DIGIT:
			addChar(); getChar();
			while(charClass == DIGIT) {
				addChar(); getChar();
			}
			return Lexeme(INT_LIT, lexeme);
			break;

		case PLUS:
			addChar(); getChar();
			return Lexeme(PLUS, lexeme);
			break;

		case MINUS:
			addChar(); getChar();
			return Lexeme(MINUS, lexeme);
			break;

		case TIMES:
			addChar(); getChar();
			return Lexeme(TIMES, lexeme);;
			break;

		case HEX:
			addChar(); getChar();
			return Lexeme(HEX, lexeme);
			break;
			
		case SEMICOLON:
			addChar(); getChar();
			return Lexeme(SEMICOLON, lexeme);
			break;

		case OPEN_PARENTHESES:
			addChar(); getChar();
			return Lexeme(OPEN_PARENTHESES, lexeme);
			break;
	
		case CLOSE_PARENTHESES:
			addChar(); getChar();
			return Lexeme(CLOSE_PARENTHESES, lexeme);
			break;

		case COMMA:
			addChar(); getChar();
			return Lexeme(COMMA, lexeme);
			break;
	
		case APOSTROPHE:
			addChar(); getChar();
			return Lexeme(APOSTROPHE, lexeme);
			break;

		case UNDERSCORE:
			addChar(); getChar();
			return Lexeme(UNDERSCORE, lexeme);
			break;

		default:
			return Lexeme(ERROR, lexeme);
	}
}