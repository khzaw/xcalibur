#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <map>

#include "QueryLexer.h"
#include "Lexeme.h"
#include "QTNode.h"
#include "QueryTree.h"

using namespace std;

static const string arr[] = {
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
	//plus, minus, times};
};
static vector<string> DESIGN_ENTITIES(arr, arr + sizeof(arr) / sizeof(arr[0]) );

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
	QueryLexer lexer;
	string query;
	map<string, string> synonyms;
	QueryTree* qt;
	string result;		// postfix expression

public:
	QueryParser();
	QueryParser(string s);
	~QueryParser();
	void parse();
	void printMap();
	map<string, string> getSynonyms();
	QueryTree * getQueryTree();

private:
	Lexeme getToken();
	void match(string);
	void match(int);
	void matchDeclaration();
	void matchDeclarationVariables(string);
	void matchSelect();
	void matchTuple();
	void matchTupleElements(int);
	void matchConditions();
	void matchSuchThat();
	void matchSuchThatConditions();
	void matchModifies();
	void matchUses();
	void matchCalls(int);
	void matchParent(int);
	void matchFollows(int);
	void matchPattern();
	void matchPatternConditions();
	void matchPatternAssign(string);
	QTNode* matchExpression();
	int comparePrecedence(string, string);
	string matchFactor(string);
	void matchPatternWhile(string);
	void matchPatternIf(string);
	void matchWith();
	void matchWithConditions();
	QTNode* matchVarRef();
	QTNode* matchEntRef(bool);
	QTNode* matchStmtRef();
	string getPostFixExpressionString();
};