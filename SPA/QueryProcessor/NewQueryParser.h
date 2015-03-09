#pragma once
#include <iostream>
#include <set>
#include <vector>
#include <string>

#include "QueryLexer.h"
#include "..\Frontend\Lexeme.h"
#include "QTNode.h" 
#include "QE.h"
#include "..\PKB\PKBController.h"
#include "Subquery.h"

using namespace std;

static const string design_entity[] = {
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
};

static vector<string> DESIGN_ENTITIES(design_entity, design_entity + sizeof(design_entity) / sizeof(design_entity[0]));

enum RELATION {
	modifies,
	uses,
	calls,
	calls_star,
	parent,
	parent_star,
	follows,
	follows_star,
	next,
	next_star,
	affects,
	affects_star
};

class NewQueryParser {
	Lexeme nextToken;
	QueryLexer lexer;
	string query;
	map<string, string> synonyms;
	string postfix;
	QE* evaluator;
	vector<string> selectVariables;
	PKBController* controller;


public:
	NewQueryParser();
	NewQueryParser(string, PKBController*);
	~NewQueryParser();
	void parse();
	void print();
	map<string, string> getSynonyms();

private:
	Lexeme getToken();
	void match(string);
	void match(int);
	void matchDeclaration();
	void matchDeclarationVariables(string);
	void matchSelect();
	void matchResultCL();
	void matchConditions();
	void matchTuple();
	void matchTupleElements(bool);
	void matchSuchThat();
	void matchWith();
	void matchPattern();
	void matchRelCond();
	void matchAttrCond();
	void matchPatternCond();
	void matchRelRef();
	
	void matchModifies();
	void matchUses();
	void matchCalls();
	void matchCallsStar();
	void matchParent();
	void matchParentStar();
	void matchFollows();
	void matchFollowsStar();
	void matchNext();
	void matchNextStar();
	void matchAffects();
	void matchAffectsStar();

	string matchVarRef();
	string matchEntRef(bool);
	string matchStmtRef();
	string matchLineRef();

	// debug
	void printMap();
};