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

	//query = "call c; Select c.procName";
	//parser = new NewQueryParser(query, controller);

	//query = "variable v; Select v.varName such that Modifies(12, v)";
	//parser = new NewQueryParser(query, controller);

	//query = "assign a; Select a pattern a (\"x\", \"x*y+z\")";
	//parser = new NewQueryParser(query, controller);

	query = "assign a; Select a pattern a(_, \"(x*(y+z) + z)*z\")";
	parser = new NewQueryParser(query, controller);

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

	//query = "stmt s; constant c; Select s with s.stmt# = c.value";
	//parser = new NewQueryParser(query, controller);

	//query = "variable v; procedure p; Select p with p.procName = v.varName";
	//parser = new NewQueryParser(query, controller);

	//query = "stmt s; Select s with s.stmt# = 1";
	//parser = new NewQueryParser(query, controller);

	//query = "stmt s1; assign a1; Select s1 with s1.stmt# = a1.stmt#";
	//parser = new NewQueryParser(query, controller);

	//query = "while w1; Select w1 with 3 = w1.stmt#";
	//parser = new NewQueryParser(query, controller);

	//query = "Select BOOLEAN with 3 = 2";
	//parser = new NewQueryParser(query, controller);

	//query = "procedure p1; Select p1 with p1.procName = \"First\"";
	//parser = new NewQueryParser(query, controller);

	//query = "assign a; while w; Select a such that Parent* (w, a) and Next*(60, n) pattern a(\"x\", _) such that a.stmt# = n";
	//parser = new NewQueryParser(query, controller);



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