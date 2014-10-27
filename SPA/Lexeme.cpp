#pragma once

#include <iostream>
#include "Lexer.h"
#include "Lexeme.h"

using namespace std;

Lexeme::Lexeme() {
	token = ERROR;
	name = "ERROR";

}

Lexeme::Lexeme(int t, string n) {
	token = t;
	name = n;
}

Lexeme::~Lexeme() {
}

bool Lexeme::equals(Lexeme l) {
	return (token == l.token) && (name == l.name);
}

ostream& operator <<(ostream &strm, const Lexeme &lexeme) {
	return strm << "Lexeme(" << TOKEN_TYPE_STRINGS[lexeme.token] << "," << lexeme.name << ")"; 
}