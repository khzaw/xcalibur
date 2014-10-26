#pragma once

#include<stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "Lexer.h"
/*
Token next_token;
vector<string> design_entity;
vector<string> relation_references;

void Match(Token token) {
	if(next_token = token) {
		//get next token
	} else {
		//throw exception
	}
}

void MatchDeclarationVariables() {
	Match(var_name);
	// add variable to a table
	if (next_token.compare(";")) {
		//get next_token
		return;
	} else {
		Match(",");
		MatchVariableDeclaration();
	}
}

void MatchDeclaration() {
	for (int i = 0; i < design_entity.size(); i++) {
		if(next_token.compare("Select") != 0) {
			try {
				Match(design_entity[i]);
				MatchDeclarationVariables();
				i = 0;
			} catch (string e) {
				continue;
			}
		} else {
			return;
		}
	}

	//if reaches here, no "Select" statement or invalid design-entity
}

void MatchAttributeCondition() {
	
}

void MatchPatternCondition() {

}

void MatchRelationRef(){
	Match("(");
	//
	Match(")");
}

void MatchRelationCondition() {
	Match("that");
	MatchRelationRef();
	if(next_token.compare("and") == 0) {
		//get next token
		MatchRelationCondition();
	}
}

void MatchConditions() {
	if(next_token.compare("such") == 0) {
		MatchRelationCondition();
	} else if (next_token.compare("pattern") == 0) {
		MatchPatternCondition();
	} else if (next_token.compare("with) == 0) {
		MatchAttributeCondition();
	}
}

void MatchTupleElements() {
	Match(elem);
	if (next_token.compare(",")) {
		//get next token
		MatchTupleElements();
	}
}

void MatchTuple() {
	if (next_token.compare("<") == 0) {
		Match("<");
		MatchTupleElements();
		Match(">");
	} else {
		//Match elem
	}
}

void MatchSelect() {
	Match("Select");
	if (next_token.compare("BOOLEAN") == 0) {
		Match("BOOLEAN");
	} else {
		MatchTuple();
		MatchConditions();		
	}
}
*/


int Parse () {
	/*
	try {
		MatchDeclaration();
		MatchSelect();
	} catch (string e) {
		cout << e;
	}

	*/
	return 0;
}