#pragma once

#include <iostream>
#include "SPA/Frontend/Lexer.h"

using namespace std;

class Lexeme {
public:
	int token;
	string name;
	Lexeme();
	Lexeme(int t, string n);
	~Lexeme();
	bool equals(Lexeme l);
	friend ostream& operator<<(ostream&os, const Lexeme& lexeme);
};