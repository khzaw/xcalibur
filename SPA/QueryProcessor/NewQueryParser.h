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
#include "WithSubquery.cpp"

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
	"prog_line",
	"plus",
	"minus",
	"times"
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
public:
	Lexeme nextToken;
	QueryLexer lexer;
	string query;
	map<string, string> synonyms;
	string postfix;
	QE* evaluator;
	vector<string> selectVariables;
	PKBController* controller;


	string result;		// postfix expression


	NewQueryParser();
	NewQueryParser(string, PKBController*);
	~NewQueryParser();
	void parse();
	void print();
	map<string, string> getSynonyms();


	bool withVar;
	bool withProc;
	bool withVal;
	bool withStmtNum;
	string withFirst;
	string withSecond;

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
	void matchAttrCompare();
	string matchRef(bool, WithSubquery*);

	void matchPatternCl();
	void matchPatternCond();
	void matchPattern();
	void matchPatternAssign(string);
	void matchPatternWhile(string);
	void matchPatternIf(string);
	QTNode* matchExpression();
	int comparePrecedence(string, string);

	void matchRelCond();
	void matchAttrCond();
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
	void matchContains();
	void matchContainsStar();
	void matchSiblings();


	string matchVarRef();
	string matchEntRef(bool, Subquery*&, bool = false, bool = false);
	string matchStmtRef();
	string matchLineRef();
	string matchNodeRef();

	// debug
	void printMap();

	void setSynonymsHelper(string, string, Subquery*);
};