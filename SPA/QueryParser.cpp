#pragma once

#include<stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

#include "QueryParser.h"
#include "Lexer.h"
#include "QTNode.h"
#include "QueryTree.h"

using namespace std;

QueryParser::QueryParser(){

}

QueryParser::QueryParser(string s) {
	this->nextToken = Lexeme();
	this->lexer = Lexer(s);
	QueryTree* temp = new QueryTree();
	this->qt = temp;
	parse();
	qt->printTree();
}

QueryParser::~QueryParser() {

}

void QueryParser::parse() {
	try {
		matchDeclaration();
		matchSelect();
	} catch (string e) {
		cout << "Caught Exception";
	}
}

void QueryParser::match(string s) {
	if (nextToken.name.compare(s) == 0) {
		nextToken = getToken();
	} else {
		throw("Exception");
	}
}

void QueryParser::match(int type) {
	if (nextToken.token == type) {
		nextToken = getToken();
	} else {
	
	}
}

Lexeme QueryParser::getToken() {
	return lexer.lex();
}

void QueryParser::matchDeclaration() {
	nextToken = getToken();
	while(nextToken.name.compare("Select") != 0) {
		for(size_t i = 0; i < DESIGN_ENTITIES.size(); i++) {
			//cout << "Matching " + nextToken.name + " with " + DESIGN_ENTITIES[i] << endl;
			if (nextToken.name.compare(DESIGN_ENTITIES[i]) == 0) {
				match(DESIGN_ENTITIES[i]);
				//cout << "Matched with " + DESIGN_ENTITIES[i] << endl;
				matchDeclarationVariables(DESIGN_ENTITIES[i]);
				break;
			}
		}

		if (nextToken.token == EOL) {
			break;
		}
	}
}

void QueryParser::matchDeclarationVariables(string entity) {
	string var = nextToken.name;
	match(IDENT);
	synonyms.insert(pair<string, string>(var, entity));

	if(nextToken.name.compare(";") != 0) {
		match(",");
		matchDeclarationVariables(entity);
	} else {
		match(";");
	}
}

void QueryParser::matchSelect() {
	match("Select");
	if (nextToken.name.compare("BOOLEAN") == 0) {
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
	cout << answerNode->getKey() << endl;
	qt->getRootNode()->getChild(0)->addChild(answerNode);
	cout << qt->getRootNode()->getChild(0)->getNumChild() << endl;
	if ((times != 0) && (nextToken.name.compare(",") == 0)) {
		match(",");
		matchTupleElements(1);
	}
}

void QueryParser::matchConditions() {
	//cout << "Matching Conditions" << endl;
	if(nextToken.name.compare("such") == 0) {
		match("such");
		match("that");
		matchSuchThat();
	} else if (nextToken.name.compare("pattern") == 0) {
		matchPattern();
	} else if (nextToken.name.compare("with") == 0) {
		matchWith();
	} else {
		cout << "SYNTAX ERROR" << endl;
		return;
	}

	if(nextToken.token != EOL) {
		cout << nextToken.name << endl;
		matchConditions();
	}
}

void QueryParser::matchSuchThat() {
	matchSuchThatConditions();
	if(nextToken.name.compare("and") == 0) {
		match("and");
		matchSuchThatConditions();
	}
}

void QueryParser::matchSuchThatConditions(){
	string relation = nextToken.name;
	nextToken = getToken();
	if(nextToken.token == TIMES) {
		relation += "*";
		nextToken = getToken();
	}

	if (relation.compare("Modifies") == 0) {
		matchModifies();
	} else if (relation.compare("Uses") == 0) {
		matchUses();
	} else if (relation.compare("Calls") == 0) {
		matchCalls(0);
	} else if (relation.compare("Calls*") == 0) {
		matchCalls(1);
	} else if (relation.compare("Parent") == 0) {
		matchParent(0);
	} else if (relation.compare("Parent*") == 0) {
		matchParent(1);
	} else if (relation.compare("Follows") == 0) {
		matchFollows(0);
	} else if (relation.compare("Follows*") == 0) {
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
	if(nextToken.name.compare("_") == 0) {
		qtpi = new QTNode("_");
		match("_");
	} else if (nextToken.token == IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} else if (nextToken.name.compare("\"") == 0) {
		qtpi = new QTNode("\"" + nextToken.name + "\"") ;
		match(IDENT);
		match ("\"");
	}

	return qtpi;	
}

QTNode* QueryParser::matchEntRef() {
	QTNode* qtpi;
	if(nextToken.name.compare("_") == 0) {
		qtpi = new QTNode("_");
		match("_");
	} else if (nextToken.token == INT_LIT) {
		qtpi = new QTNode(stoi(nextToken.name));
		match(INT_LIT);
	} else if (nextToken.token == IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} else if (nextToken.name.compare("\"") == 0) {
		qtpi = new QTNode("\"" + nextToken.name + "\"") ;
		match(IDENT);
		match ("\"");
	}

	return qtpi;
}

QTNode* QueryParser::matchStmtRef() {
	QTNode* qtpi;
	if(nextToken.name.compare("_") == 0) {
		qtpi = new QTNode("_");
		match("_");
	} else if (nextToken.token == INT_LIT) {
		qtpi = new QTNode(stoi(nextToken.name));
		match(INT_LIT);
	} else if (nextToken.token == IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} 

	return qtpi;
}

void QueryParser::matchPattern() {
	matchPatternConditions();
	if(nextToken.name.compare("and") == 0) {
		matchPatternConditions();
	}
}

void QueryParser::matchPatternConditions(){
	/*
	string patternSynonym = nextToken.name;
	match(IDENT);
	*/
}

void QueryParser::matchWith() {
}