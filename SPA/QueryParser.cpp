#pragma once

#include<stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <ctype.h>

#include "QueryParser.h"
#include "QueryLexer.h"
#include "QTNode.h"
#include "QueryTree.h"
#include "QueryException.h"

using namespace std;

QueryParser::QueryParser(){

}

QueryParser::QueryParser(string s) {
	this->nextToken = Lexeme();
	this->lexer = QueryLexer(s);
	QueryTree* temp = new QueryTree();
	this->qt = temp;
	parse();
	//qt->printTree();
	printMap();
}

QueryParser::~QueryParser() {

}

void QueryParser::printMap() {
	cout<< "Synonyms: ";
	for(map<string, string>::iterator it = synonyms.begin(); it!= synonyms.end(); ++it) {
		cout << "(" << it-> first << "," << it->second << ") ";
	}
	cout << endl;
}

void QueryParser::parse() {
	try {
		matchDeclaration();
		matchSelect();
	} catch (QueryException& e) {
		cout << e.what() << endl;
	}
}

map<string, string> QueryParser::getSynonyms() {
	return synonyms;
}

QueryTree* QueryParser::getQueryTree() {
	return qt;
}

void QueryParser::match(string s) {
	if (_stricmp(s.c_str(), nextToken.name.c_str()) == 0) {
		nextToken = getToken();
	} else {
		throw(QueryException("QUERY SYNTAX ERROR: Unexpected token " + nextToken.name + ", Expected token: " + s ));
	}
}

void QueryParser::match(int type) {
	if (nextToken.token == type){
		nextToken = getToken();
	} else if (type == IDENT && nextToken.token == SIMPLE_IDENT) {
		nextToken = getToken();
	} else {
		throw(QueryException("QUERY GRAMMAR ERROR:["+ nextToken.name +"] Unexpected " + TOKEN_TYPE_STRINGS[nextToken.token] + ", Expected " + TOKEN_TYPE_STRINGS[type]));
	}
}

Lexeme QueryParser::getToken() {
	return lexer.lex();
}

void QueryParser::matchDeclaration() {
	nextToken = getToken();

	for(size_t i = 0; i < DESIGN_ENTITIES.size(); i++) {
		if (_stricmp(nextToken.name.c_str(), DESIGN_ENTITIES[i].c_str()) == 0) {
			match(DESIGN_ENTITIES[i]);
			matchDeclarationVariables(DESIGN_ENTITIES[i]);
			i = 0;
		}
	}
}

void QueryParser::matchDeclarationVariables(string entity) {
	string var = nextToken.name;
	match(IDENT);
	synonyms.insert(pair<string, string>(var, entity));

	if (nextToken.name.compare(";") != 0) {
		match(",");
		matchDeclarationVariables(entity);
	} else {
		match(";");
	}
}

void QueryParser::matchSelect() {
	match("Select");
	if (_stricmp(nextToken.name.c_str(), "BOOLEAN") == 0) {
		match("BOOLEAN");
		QTNode* newNode = new QTNode("BOOLEAN");
		qt->getRootNode()->getChild(0)->addChild(newNode);
	} else {
		matchTuple();	
	}

	matchConditions();
}

void QueryParser::matchTuple() {
	if (nextToken.name.compare("<") == 0) {
		match("<");
		matchTupleElements(1);
		match(">");
	} else {
		matchTupleElements(0);
	}
}

// if times is zero, does not make a recursive call
void QueryParser::matchTupleElements(int times) {
	string elem = nextToken.name;
	match(IDENT);
	
	QTNode* answerNode = new QTNode(elem);
	answerNode->setParent(qt->getRootNode()->getChild(0));
	//cout << answerNode->getKey() << endl;
	qt->getRootNode()->getChild(0)->addChild(answerNode);
	//cout << qt->getRootNode()->getChild(0)->getNumChild() << endl;
	
	if ((times != 0) && (nextToken.name.compare(",") == 0)) {
		match(",");
		matchTupleElements(1);
	}
}

void QueryParser::matchConditions() {
	if (_stricmp(nextToken.name.c_str(), "such") == 0) {
		match("such");
		match("that");
		matchSuchThat();
	} else if (_stricmp(nextToken.name.c_str(), "pattern") == 0) {
		match("pattern");
		matchPattern();
	} else if (_stricmp(nextToken.name.c_str(), "with") == 0) {
		match("with");
		matchWith();
	} else if (nextToken.token == EOL) {
		cout << "End of query" << endl;
		return;
	} else {
		cout << "SYNTAX ERROR" << endl;
		return;
	}

	if (nextToken.token != EOL) {
		matchConditions();
	}
}

void QueryParser::matchSuchThat() {
	matchSuchThatConditions();
	if (_stricmp(nextToken.name.c_str(), "and") == 0) {
		match("and");
		matchSuchThatConditions();
	}
}

void QueryParser::matchSuchThatConditions(){
	string relation = nextToken.name;
	nextToken = getToken();
	if (nextToken.token == TIMES) {
		relation += "*";
		nextToken = getToken();
	}

	if (_stricmp(relation.c_str(), "Modifies") == 0) {
		matchModifies();
	} else if (_stricmp(relation.c_str(), "Uses") == 0) {
		matchUses();
	} else if (_stricmp(relation.c_str(), "Calls") == 0) {
		matchCalls(0);
	} else if (_stricmp(relation.c_str(), "Calls*") == 0) {
		matchCalls(1);
	} else if (_stricmp(relation.c_str(), "Parent") == 0) {
		matchParent(0);
	} else if (_stricmp(relation.c_str(), "Parent*") == 0) {
		matchParent(1);
	} else if (_stricmp(relation.c_str(), "Follows") == 0) {
		matchFollows(0);
	} else if (_stricmp(relation.c_str(), "Follows*") == 0) {
		matchFollows(1);
	} 
}

void QueryParser::matchModifies() {
	QTNode* modifiesNode = new QTNode("Modifies");

	match("(");
	modifiesNode->addChild(matchEntRef());
	match(",");
	modifiesNode->addChild(matchVarRef());
	match(")");
	
	qt->getRootNode()->getChild(1)->addChild(modifiesNode);
}

void QueryParser::matchUses() {
	QTNode* usesNode = new QTNode("Uses");

	match("(");
	usesNode->addChild(matchEntRef());
	match(",");
	usesNode->addChild(matchVarRef());
	match(")");
	
	qt->getRootNode()->getChild(1)->addChild(usesNode);
}

// if transitive is != 0, Calls*, otherwise, Calls
void QueryParser::matchCalls(int transitive) {
	QTNode* callNode;
	if (transitive) {
		callNode = new QTNode("Calls*");
	} else {
		callNode = new QTNode("Calls");
	}

	match("(");
	callNode->addChild(matchEntRef());
	match(",");
	callNode->addChild(matchEntRef());
	match(")");

	qt->getRootNode()->getChild(1)->addChild(callNode);
}

// if transitive is != 0, Parent*, otherwise, Parent 
void QueryParser::matchParent(int transitive) {
	QTNode* parentNode;
	if (transitive) {
		parentNode = new QTNode("Parent*");
	} else {
		parentNode = new QTNode("Parent");
	}

	match("(");
	parentNode->addChild(matchStmtRef());
	match(",");
	parentNode->addChild(matchStmtRef());
	match(")");

	qt->getRootNode()->getChild(1)->addChild(parentNode);
}

// if transitive is != 0, Follows*, otherwise, Follows
void QueryParser::matchFollows(int transitive) {
	QTNode* followsNode;
	if (transitive) {
		followsNode = new QTNode("Follows*");
	} else {
		followsNode = new QTNode("Follows");
	}

	match("(");
	followsNode->addChild(matchStmtRef());
	match(",");
	followsNode->addChild(matchStmtRef());
	match(")");

	qt->getRootNode()->getChild(1)->addChild(followsNode);
}

QTNode* QueryParser::matchVarRef() {
	QTNode* qtpi;
	if (nextToken.name.compare("_") == 0) {
		qtpi = new QTNode("_");
		match("_");
	} else if (nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} else if (nextToken.name.compare("\"") == 0) {
		qtpi = new QTNode("\"" + nextToken.name + "\"") ;
		match("\"");
		match(IDENT);
		match ("\"");
	}

	return qtpi;	
}

QTNode* QueryParser::matchEntRef() {
	QTNode* qtpi;
	if (nextToken.name.compare("_") == 0) {
		qtpi = new QTNode("_");
		match("_");
	} else if (nextToken.token == INT_LIT) {
		qtpi = new QTNode(stoi(nextToken.name));
		match(INT_LIT);
	} else if (nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} else if (nextToken.name.compare("\"") == 0) {
		qtpi = new QTNode("\"" + nextToken.name + "\"") ;
		match("\"");
		match(IDENT);
		match ("\"");
	}

	return qtpi;
}

QTNode* QueryParser::matchStmtRef() {
	QTNode* qtpi;
	if (nextToken.name.compare("_") == 0) {
		qtpi = new QTNode("_");
		match("_");
	} else if (nextToken.token == INT_LIT) {
		qtpi = new QTNode(stoi(nextToken.name));
		match(INT_LIT);
	} else if (nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} 

	return qtpi;
}

void QueryParser::matchPattern() {
	matchPatternConditions();
	if (_stricmp(nextToken.name.c_str(), "and") == 0) {
		match("and");
		matchPatternConditions();
	}
}

void QueryParser::matchPatternConditions(){

	string syn = nextToken.name;
	match(IDENT);
	map<string, string>::iterator it = synonyms.find(syn);
	string synType = (it != synonyms.end()) ? it->second : "";
	
	if (_stricmp(synType.c_str(), "assign") == 0) {
		matchPatternAssign(syn);
	} else if (_stricmp(synType.c_str(), "while") == 0) {
		matchPatternWhile(syn);
	} else if (_stricmp(synType.c_str(), "if") == 0) {
		matchPatternIf (syn);
	} else {
		throw(QueryException("INVALID SYNONYM: " + syn + " is not a synonym of the type \"if\", \"while\" or \"assign\"")); 
	}
}

void QueryParser::matchPatternAssign(string s) {
	QTNode* assignNode = new QTNode("assign");
	assignNode->addChild(new QTNode(s));
	match("(");
	assignNode->addChild(matchVarRef());
	match(",");
	
	string expression = "";
	if (nextToken.name.compare("_") == 0) {
		expression += nextToken.name;
		match("_");
	}
	
	expression = matchExpression(expression);
	
	if (nextToken.name.compare("_") == 0) {
		if(expression.compare("_") == 0) {
			throw(QueryException("EXPRESSION ERROR: SIMPLE Expressions of the form __ is invalid"));
		} else {
			expression += nextToken.name;
			match("_");
		}
	}

	match(")");

	assignNode->addChild(new QTNode(expression));
	qt->getRootNode()->getChild(2)->addChild(assignNode);
}

string QueryParser::matchExpression(string exp) {
	if (nextToken.token != CLOSE_PARENTHESES) {
		exp = matchFactor(exp);
	}
	while (nextToken.token !=  CLOSE_PARENTHESES && nextToken.name.compare("_") != 0) {
		if (nextToken.token == PLUS ) {
			exp += nextToken.name;
			match(PLUS);
			exp = matchFactor(exp);
		} else if (nextToken.token == MINUS) {
			exp += nextToken.name;
			match(MINUS);
			exp = matchFactor(exp);
		} else if (nextToken.token == TIMES) {
			exp += nextToken.name;
			match(TIMES);
			exp = matchFactor(exp);
		} else {
			throw(QueryException("EXPRESSION ERROR: Expected a \"+\", \"-\" or \" *\""));
		}
	}

	return exp;
}

string QueryParser::matchFactor(string exp) {
	//cout << "Before Match: " << exp << endl;
	if (nextToken.token == SIMPLE_IDENT) {
		exp += nextToken.name;
		match(SIMPLE_IDENT);
	} else if (nextToken.token == INT_LIT) {
		exp += nextToken.name;
		match(INT_LIT);
	}else if (nextToken.token == OPEN_PARENTHESES) {
		match("(");
		exp += "(";
		exp = matchExpression(exp);
		match(")");
		exp += (")");
	} else {
		throw(QueryException("EXPRESSION ERROR:["+ nextToken.name +"] Unexpected token" + TOKEN_TYPE_STRINGS[nextToken.token]));
	}

	//cout << "After Match: " << exp << endl;
	return exp;
}

void QueryParser::matchPatternIf (string s) {
	QTNode* ifNode = new QTNode("if");
	ifNode->addChild(new QTNode(s));
	match("(");
	ifNode->addChild(matchVarRef());
	match(",");
	match("_");
	match(",");
	match("_");
	match(")");

	qt->getRootNode()->getChild(2)->addChild(ifNode);
}

void QueryParser::matchPatternWhile(string s) {
	QTNode* whileNode = new QTNode("while");
	whileNode->addChild(new QTNode(s));
	match("(");
	whileNode->addChild(matchVarRef());
	match(",");
	match("_");
	match(")");

	qt->getRootNode()->getChild(2)->addChild(whileNode);
}

void QueryParser::matchWith() {
}
