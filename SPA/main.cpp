#if !defined(_TEST_)
#define _TEST_

#include <iostream>
#include "Lexer.h"

using namespace std;

string convertToken(int t);

int main() {
	
	cout << "testing lexer" << endl;
	int token = WHITESPACE;
	string test;

	Lexer Lex("y = xa3bc + 223 + y;");

	while(token != EOL) {
		token = Lex.lex();
		cout << "lexeme : \"" << Lex.lexeme << "\" token: " << convertToken(token) << endl;
	}

	string t;
	cout << endl << " ====================" << endl;
	cin >> t;


}

string convertToken(int t) {
	switch(t) {
	case WHITESPACE: return "WHITESPACE";
	case LETTER: return "LETTER";
	case DIGIT: return "DIGIT";
	case IDENT: return "IDENT";
	case INT_LIT: return "INT_LIT";
	case ERROR: return "ERROR";
	case EOL: return "EOL";
	case PLUS: return "PLUS";
	case TIMES: return "TIMES";
	case SEMICOLON: return "SEMICOLON";
	case EQ: return "EQ";
	default: return "UNKNOWN";
	}
}
#endif