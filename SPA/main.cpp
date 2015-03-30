#pragma once
#if !defined(_TEST_)
#define _TEST_

#include <iostream>
#include "Frontend/Parser.h"
#include "Frontend/Lexer.h"
#include "QueryProcessor/NewQueryParser.h"
#include "PKB/PKBController.h"


using namespace std;

string convertToken(Lexeme t);

int main() {

	cout << "Testing Query Parser" << endl;

	
	
	//cout << "testing lexer" << endl;

	//Lexeme token;
	//Lexer Lex("procedure hehehe { y = xa3bc + 223 + ChArlie; x = a - b + c; z = 1 + 3 * 4; }");

	//while(!token.equals(Lexeme(EOL, ""))) {
	//	token = Lex.lex();
	//	cout << "lexeme : \"" << token << endl;
	//}
	//cout << endl << " ====================" << endl;



	Parser Pa("Source.txt");

	string query;
	NewQueryParser* parser;
	PKBController* controller = new PKBController();

	//query = "while w; Select w such that Parent*(w, 12)";
	//parser = new NewQueryParser(query, controller);

	//query = "stmt s; while w; Select w such that Follows* (s, w)";
	//parser = new NewQueryParser(query, controller);

	//query = "if ifstat; Select ifstat such that Follows* (ifstat, 17)";
	//parser = new NewQueryParser(query, controller);

	//query = "variable v; Select v such that Modifies (18, v)";
	//parser = new NewQueryParser(query, controller);

	//query = "assign a; Select a such that Modifies (a, \"y\") and Uses (a, \"y\")";
	//parser = new NewQueryParser(query, controller);

	//query = "procedure p; Select p such that Calls* (p, \"Trio\")";
	//parser = new NewQueryParser(query, controller);

	//query = "assign a; Select a pattern a (\"m\", \"z * x\")";
	//parser = new NewQueryParser(query, controller);

	//query = "prog_line n; Select n such that Next* (9, n) and Next* (n, 12)";
	//parser = new NewQueryParser(query, controller);

	//query = "assign a; Select a such that Modifies (a, \"y\") and Uses (a, \"y\")";
	//parser = new NewQueryParser(query, controller);

	query = "stmt s; constant c; Select s with s.stmt# = c.value";
	parser = new NewQueryParser(query, controller);

	query = "variable v; procedure p; Select p with p.procName = v.varName";
	parser = new NewQueryParser(query, controller);

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