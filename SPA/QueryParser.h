#pragma once
#include <iostream>
#include <set>
#include "Lexer.h"
#include "Lexeme.h"

using namespace std;

static vector<string> DESIGN_ENTITIES = {
	"procedure",
	"stmtLst",
	"stmt",
	"assign",
	"call",
	"while",
	"if",
	"variable",
	"constant",
	"prog_line"
	//plus, minus, times
};

enum RELATION {
	MODIFIES,
	USES,
	CALLS,
	CALLS_STAR,
	PARENT,
	PARENT_STAR,
	FOLLOWS,
	FOLLOWS_STAR,
	NEXT,
	NEXT_STAR,
	AFFECTS,
	AFFECTS_STAR
};

class QueryParser {
	Lexeme nextToken;
	Lexer lexer;
	string query;
	vector<string> synonyms;

public:
	QueryParser();
	QueryParser(string s);
	~QueryParser();
	void parse();

private:
	Lexeme getToken();
	void match(string s);
	void match(int relation);
	void matchDeclaration();
	void matchDeclarationVariables();
	void matchSelect();
	void matchTuple();
	void matchTupleElements(int times);
	void matchConditions();
	void matchSuchThat();
	void matchSuchThatConditions();
	void matchModifies();
	void matchUses();
	void matchCalls(int transitive);
	void matchParent(int transitive);
	void matchFollows(int transitive);
	void matchPattern();
	void matchPatternConditions();
	void matchWith();
	void matchWithConditions();
}