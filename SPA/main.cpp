#pragma once
#if !defined(_TEST_)
#define _TEST_

#include <iostream>
#include "Parser.h"
#include "Lexer.h"
#include "QueryParser.h"

using namespace std;

string convertToken(Lexeme t);

int main() {
	cout << "testing lexer" << endl;

//	Lexeme token;
//	Lexer Lex("procedure hehehe { y = xa3bc + 223 + ChArlie; x = a + b + c; z = 1 + 3 * 4; }");

//	while(!token.equals(Lexeme(EOL, ""))) {
//		token = Lex.lex();
//		cout << "lexeme : \"" << token << endl;
//	}
	cout << endl << " ====================" << endl;

	//Parser Pa("not_so_simple_sample.txt");
	Parser Pa("simple_sample.txt");
	
	//string t;
	//cin >> t;

	cout << "testing query lexer" << endl;

	Lexeme token2;
	string query = "while w; assign a; Select <a,b,c> such that Parent*(w, a) and Modifies(yolo, x) Calls(hohoho, hahaha)";
	Lexer Lex2(query);

	while(!token2.equals(Lexeme(EOL, ""))) {
		token2 = Lex2.lex();
		cout << "lexeme : \"" << token2 << endl;
	}
	cout << endl << " ====================" << endl;

	QueryParser QPa(query);

	string t;
	cin >> t;
}

string convertToken(Lexeme t) {
	switch(t.token) {
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
	case OPEN_BLOCK: return "OPEN_BLOCK";
	case CLOSE_BLOCK: return "CLOSE_BLOCK";
	default: return "UNKNOWN";
	}
}
#endif