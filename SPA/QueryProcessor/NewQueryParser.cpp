#pragma once

#include <stdio.h>
#include <algorithm>
#include <string>
#include <map>
#include <stack>
#include <iostream>
#include <sstream>

#include "NewQueryParser.h"
#include "QueryLexer.h"
#include "QTNode.h"
#include "QueryException.h"
#include "Subquery.h"
#include "ModifiesSubquery.cpp"
#include "UsesSubquery.cpp"
#include "ParentSubquery.cpp"
#include "WithSubquery.cpp"
#include "CallsSubquery.cpp"


using namespace std;

template <typename T>
T lexical_cast(const std::string& s) {
	std::stringstream ss(s);
	T result;
	if((ss >> result).falt() || !(ss >> std::ws).eof()) {
		throw std::bad_cast();
	}
	return result;
}

template <typename T>
bool lexical_cast(const std::string& s, T& t) {
	try {
		t = lexical_cast<T>(s);
	} catch(const std::bad_cast& e) {
		return false;
	}
}

NewQueryParser::NewQueryParser() {
}

NewQueryParser::NewQueryParser(string s, PKBController* controller) {
	this->nextToken = Lexeme();
	this->lexer = QueryLexer(s);
	this->selectVariables = vector<string>(); 
	this->synonyms = map<string, string>();
	parse();
	printMap();
}

void NewQueryParser::printMap() {
	cout << "Synonyms: ";
	for(map<string, string>::iterator it = synonyms.begin(); it != synonyms.end(); ++it) {
		cout << "(" << it->first << "," << it->second << ") ";
	}
	cout << "\nSelect string: ";
	for(vector<string>::iterator it = selectVariables.begin(); it != selectVariables.end(); ++it) {
		cout << *it << "\n";
	}
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
	synonyms[var] = entity;
	match(var);
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
		selectVariables.push_back("BOOLEAN");
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
	selectVariables.push_back(elem);
	match(elem);

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
		cout << "SYNTAX ERROR -> " << nextToken.name << "\t" << nextToken.token << endl;
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
	// ModifiesC: "Modifies" "(" stmtRef "," varRef ")"
	//ModifiesSubuqery modifiesSq = ModifiesSubquery(&synonyms, &controller);
	match("(");
	string fst = matchEntRef(true);
	match(",");
	string snd = matchVarRef();
	match(")");
	//modifiesSq.setSynonyms(fst, snd);
	cout << "fst : " << fst;
	cout << "snd : " << snd;
}

string NewQueryParser::matchEntRef(bool excludeUnderScore) {
	// entRef: synonym | "_" | """ IDENT """ | INTEGER
	string fst = "";
	if(nextToken.name.compare("_") == 0) {
		if(!excludeUnderScore) {
			fst = "_";
			match(UNDERSCORE);
		} else {
			throw(QueryException("VAGUE QUERY ERROR: The first argument of Uses and Modifies cannot be a \"_\""));
		}
	} else if(nextToken.token == INT_LIT) {
		fst = nextToken.name;
		match(nextToken.name);
	} else if(nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		fst = nextToken.name;
		match(nextToken.name);
	} else if(nextToken.name.compare("\"") == 0) {
		match("\"");
		fst = nextToken.name;
		match(nextToken.name);
		match("\"");
	}
	return fst;
}

string NewQueryParser::matchVarRef() {
	// varRef: synonym | "_" | """ IDENT """
	string snd = "";
	if(nextToken.name == "_") {
		match(UNDERSCORE);
		snd = "_";
	} else if(nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		snd = nextToken.name;
		match(nextToken.name); // synonym
	} else if(nextToken.name == "\"") {
		match("\"");
		snd = nextToken.name;
		match(nextToken.name);
		match("\"");
	}
	return snd;
}

void NewQueryParser::matchUses() {
	// UsesP: "Uses" "(" entRef "," varRef ")"
	// UsesC: "Uses" "(" entRef "," varRef ")"
	match("(");
	string fst = matchEntRef(true);
	match(",");
	string snd = matchVarRef();
	match(")");
	cout << "Uses fst : " << fst << "\tUses snd : " << snd;
}

void NewQueryParser::matchCalls() {
	// Calls : "Calls" "(" entRef "," varRef ")"
	match("(");
	string fst = entRef(false);
	match(",");
	string snd = varRef();
	match(")");

	cout << "Calls: fst -> " << fst << "\tsnd -> " << snd;
}

void NewQueryParser::matchCallsStar() {
	// CallsT : "Calls*" "(" entRef "," varRef ")"
	match("(");
	string fst = entRef(false);
	match(",");
	string snd = varRef();
	match(")");

	cout << "Calls*: fst -> " << fst << "\tsnd -> " << snd;
}

void NewQueryParser::matchParent() {
	match("(");
	string fst = matchStmtRef();
	match(",");
	string snd = matchStmtRef();
	match(")");

	cout << "Parent: fst -> " << fst << "\tsnd -> " << snd;
}

void NewQueryParser::matchParentStar() {
	match("(");
	string fst = matchStmtRef();
	match(",");
	string snd = matchStmtRef();
	match(")");

	cout << "Parent*: fst -> " << fst << "\tsnd -> " << snd;
}

string NewQueryParser::matchStmtRef() {
	// stmtRef: synonym | "_" | INTEGER
	string param;
	if(nextToken.name == "_") {
		param = "_";
		match(UNDERSCORE);
	} else if(nextToken.token == INT_LIT) {
		param = nextToken.name;
		match(INT_LIT);
	} else if(nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		param = nextToken.name;
		match(IDENT);
	} else {
		cout << "SYNTAX ERROR -> " << nextToken.name << "\t" << nextToken.token << endl;
	}
	return param;
}

void NewQueryParser::matchFollows() {
	// Follows: "Follows" "(" stmtRef "," stmtRef ")";
	match("(");
	string fst = matchStmtRef();
	match(",");
	string snd = matchStmtRef();
	match(")");
	cout << "Follows: fst -> " << fst << "\tsnd -> " << snd;
}

void NewQueryParser::matchFollowsStar() {
	match("(");
	string fst = matchStmtRef();
	match(",");
	string snd = matchStmtRef();
	match(")");
	cout << "Follows*: fst -> " << fst << "\tsnd -> " << snd;
}

void NewQueryParser::matchNext() {
    match("(");
    string fst = matchLineRef();
    match(",");
    string snd = matchLineRef();
    match(")");

	cout << "Next: fst -> " << fst << "\tsnd -> " << snd;
}

void NewQueryParser::matchNextStar() {
    match("(");
    string fst = matchLineRef();
    match(",");
    string snd = matchLineRef();
    match(")");

	cout << "Next*: fst -> " << fst << "\tsnd -> " << snd;
}

string NewQueryParser::matchLineRef() {
    // lineRef:  synonym | "_" | INTEGER
	string param;
	if(nextToken.name == "_") {
		param = "_";
		match(UNDERSCORE);
	} else if(nextToken.token == INT_LIT) {
		param = nextToken.name;
		match(INT_LIT);
	} else if(nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		param = nextToken.name;
		match(IDENT);
	} else {
		cout << "SYNTAX ERROR -> " << nextToken.name << "\t" << nextToken.token << endl;
	}
	return param;
}

void NewQueryParser::matchAffects() {
    match("(");
    string fst = matchStmtRef();
    match(",");
    string snd = matchStmtRef();
    match(")");
	cout << "Affects: fst -> " << fst << "\tsnd -> " << snd;
}

void NewQueryParser::matchAffectsStar() {
    match("(");
    string fst = matchStmtRef();
    match(",");
    string snd = matchStmtRef();
    match(")");
	cout << "Affects: fst -> " << fst << "\tsnd -> " << snd;
}
void NewQueryParser::matchPatternCond() {
}

void NewQueryParser::matchAttrCond() {
}