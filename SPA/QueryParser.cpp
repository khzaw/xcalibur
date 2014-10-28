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
	this->qt = *temp;
	parse();
}

void QueryParser::parse() {
	matchDeclaration();
	matchSelect();
}

void QueryParser::match(string s) {
	if (nextToken.name.compare(s) == 0) {
		nextToken = getToken();
	} else {
		throw("exception");
	}
}

void QueryParser::match(int type) {
	if (nextToken.token = type) {
		nextToken = getToken();
	} else {
	
	}
}

Lexeme QueryParser::getToken() {
	return lexer.lex();
}

void QueryParser::matchDeclaration() {
	for (size_t i = 0; i < DESIGN_ENTITIES.size(); i++) {
		if(nextToken.name.compare("Select") != 0) {
			try {
				match(DESIGN_ENTITIES[i]);
				matchDeclarationVariables(DESIGN_ENTITIES[i]);
				i = 0;
			} catch (string e) {
				continue;
			}
		} else {
			return;
		}
	}
}

void QueryParser::matchDeclarationVariables(string entity) {
	string var = nextToken.name;
	match(IDENT);
	synonyms.insert(pair<string, string>(var, entity));

	if(nextToken.name.compare(";") == 0) {
		return;
	} else {
		match(",");
		matchDeclarationVariables(entity);
	}
}

void QueryParser::matchSelect() {
	match("Select");
	if (nextToken.name.compare("BOOLEAN") == 0) {
		match("BOOLEAN");
		// add bool to solution subtree
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
	// add to solution subtree

	if (times != 0 && nextToken.name.compare(",") == 0) {
		matchTupleElements(1);
	}
}

void QueryParser::matchConditions() {
	if(nextToken.name.compare("such") == 0) {
		match("such");
		match("that");
		matchSuchThat();
	} 
	
	if (nextToken.name.compare("pattern") == 0) {
		matchPattern();
	} 
	
	if (nextToken.name.compare("with") == 0) {
		matchWith();
	}

	if(nextToken.token != EOL) {
		matchConditions();
	}
}

void QueryParser::matchSuchThat() {
	matchSuchThatConditions();
	if(nextToken.name.compare("and") == 0) {
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

}

void QueryParser::matchUses() {
	
}

// if transitive is != 0, Calls*, otherwise, Calls
void QueryParser::matchCalls(int transitive) {
	if (transitive) {
		//create Calls* Node
	} else {
		//create Calls Node
	}

	match("(");
	//matchEntRef
	//set as first child
	match(",");
	//matchEntRef
	//set as second child 
	match(")");

	//Insert into QT
}

// if transitive is != 0, Parent*, otherwise, Parent 
void QueryParser::matchParent(int transitive) {
	if (transitive) {
		//Create Parent* Node
	} else {
		//Create Parent Node
	}

	match("(");
	//matchStmtRef
	//set as first child
	match(",");
	//matchStmtRef
	//set as second child 
	match(")");

	//Insert into QT
}

// if transitive is != 0, Follows*, otherwise, Follows
void QueryParser::matchFollows(int transitive) {
	if (transitive) {
		//Create Follows* Node
	} else {
		//Create Follows Node
	}

	match("(");
	//matchStmtRef
	//set as first child
	match(",");
	//matchStmtRef
	//set as second child 
	match(")");

	//Insert into QT
}

/*
QTNode QueryParser::matchVarRef() {
	QTNode qtpi;
	if(nextToken.name.compare("_") == 0) {
		
	} else if (nextToken.token == IDENT) {
	
	} else if (nexToken.token == "\"") {
		match(IDENT);
		match ("\"");
	}

	return qtpi;	
}

QTNode QueryParser::matchEntRef() {
	QTNode qtpi;
	if(nextToken.name.compare("_") == 0) {
		
	} else if (nextToken.token == INT_LIT) {
	
	} else if (nextToken.token == IDENT) {
	
	} else if (nexToken.token == "\"") {
		match(IDENT);
		match ("\"");
	}

	return qtpi;
}

QTNode QueryParser::matchStmtRef() {
	QTNode qtpi;
	if(nextToken.name.compare("_") == 0) {
		
	} else if (nextToken.token == INT_LIT) {
	
	} else if (nextToken.token == IDENT) {
	
	} 

	return qtpi;
}
*/

void QueryParser::matchPattern() {
	
}

void QueryParser::matchWith() {
}