#pragma once

#include <stdio.h>
#include <algorithm>
#include <string>
#include <map>
#include <stack>

#include "NewQueryParser.h"
#include "QueryLexer.h"
#include "QTNode.h"
#include "QueryException.h"

using namespace std;

NewQueryParser::NewQueryParser() {
}

NewQueryParser::NewQueryParser(string s) {
	this->nextToken = Lexeme();
	this->lexer = QueryLexer(s);
	parse();
}

NewQueryParser::~NewQueryParser() {
}

Lexeme NewQueryParser::getToken() {
	return lexer.lex();
}

void NewQueryParser::parse() {
	try {
		matchDeclaration();
		matchSelect();
	} catch (QueryException& e) {
		cout << e.what() << endl;
	}
}

void NewQueryParser::matchDeclaration() {
	nextToken = getToken();
	if(nextToken.name.compare("Select") != 0) { // start of synonyms
		for(size_t i = 0; i < DESIGN_ENTITIES.size(); ++i) {
			if(nextToken.name == DESIGN_ENTITIES[i]) {
				match(DESIGN_ENTITIES[i]);
				matchDeclarationVariables(DESIGN_ENTITIES[i]); 
				i = 0;
			}
		}
	}
}

void NewQueryParser::match(string s) {
	if(nextToken.name == s) {
		nextToken = getToken();
	} else {
		throw(QueryException("QUERY SYNTAX ERROR: Unexpected token " + nextToken.name + ", Expected token: " + s));
	}
}

void NewQueryParser::match(int type) {
	if(nextToken.token = type) {
		nextToken = getToken();
	} else if(type == IDENT && nextToken.token == SIMPLE_IDENT) {
		nextToken = getToken();
	} else {
		throw(QueryException("QUERY GRAMMAR ERROR:[" + nextToken.name + "] Unexpected " + TOKEN_TYPE_STRINGS[type]));
	}
}

void NewQueryParser::matchDeclarationVariables(string entity) {
	string var = nextToken.name;
	match(IDENT);
	synonyms[var] = entity;
	if(nextToken.name.compare(";") != 0) {
		match(",");
		matchDeclarationVariables(entity);
	} else {
		match(";");
	}
}

void NewQueryParser::matchSelect() {
	match("Select");
	matchResultCL();
	matchConditions();
}

void NewQueryParser::matchResultCL() {
	if(nextToken.name == "BOOLEAN") {
		match("BOOLEAN");
	} else {
		matchTuple();
	}
}

void NewQueryParser::matchTuple() {
	if(nextToken.name == "<") {
		match("<");
		matchTupleElements(true);
		match(">");
	} else {
		matchTupleElements(false);
	}
}

void NewQueryParser::matchTupleElements(bool recursive) {
	string elem = nextToken.name;
	match(IDENT);


	// construct elements in subquery

	if(recursive && nextToken.name == ",") {
		match(","); 
		matchTupleElements(true);
	}
}

void NewQueryParser::matchConditions() {
	if(nextToken.name == "such") {
		matchSuchThat();
	} else if(nextToken.name == "pattern") {
		matchPattern();
	} else if(nextToken.name == "with") {
		matchWith();
	} else {
		cout << "SYNTAX ERROR" << nextToken.name << endl;
		return;
	}
}

void NewQueryParser::matchSuchThat() {
	match("such");
	match("that");
	matchRelCond();
}

void NewQueryParser::matchPattern() {
	match("pattern");
	matchPatternCond();
}

void NewQueryParser::matchWith() {
	match("with");
	matchAttrCond();
}

void NewQueryParser::matchRelCond() {
	matchRelRef();
	if(nextToken.name == "and") {
		match("and");
		matchRelRef();
	}
}

void NewQueryParser::matchRelRef() {
	// relRef: ModifiesP | ModifiesS | UsesP | UsesS | Calls | CallsT |
	//         Parent | ParentT | Follows | FollowsT | Next | NextT | 
	//         Affects | AffectsT
	string relation = nextToken.name;
	nextToken = getToken();
	if(nextToken.token == TIMES) {
		relation += "*";
		nextToken = getToken();
	}

	if(relation == "Modifies") {
		matchModifies();
	} else if(relation == "Uses") {
		matchUses();
	} else if(relation == "Calls") {
		matchCalls();
	} else if(relation == "Calls*") {
		matchCallsStar();
	} else if(relation == "Parent") {
		matchParent();
	} else if(relation == "Parent*") {
		matchParentStar();
	} else if(relation == "Follows") {
		matchFollows();
	} else if(relation == "Follows*") {
		matchFollowsStar();
	} else if(relation == "Next") {
		matchNext();
	} else if(relation == "Next*") {
		matchNextStar();
	} else if(relation == "Affects") {
		matchAffects();
	} else if(relation == "Affects*") {
		matchAffectsStar();
	} else {
		cout << "SYNTAX ERROR" << nextToken.name << endl;
		return;
	}
}

void NewQueryParser::matchModifies() {
	// ModifiesP: "Modifies" "(" entRef "," varRef ")"
	// ModifiesP: "Modifies" "(" stmtRef "," varRef ")"
	match("(");
	match(",");
	matchVarRef();
	match(")");
}
void NewQueryParser::matchVarRef() {
	// varRef: synonym | "_" | """ IDENT """
	if(nextToken.name = "_") {
		match(UNDERSCORE);
	} else if(nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		match(IDENT); // synonym
	} else if(nextToken.name == "\"") {
		match("\"");
		match(IDENT);
		match("\"");
	}
}
void NewQueryParser::matchUses() {
}
void NewQueryParser::matchPatternCond() {
}

void NewQueryParser::matchAttrCond() {
}