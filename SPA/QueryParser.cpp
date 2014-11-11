#pragma once

#include<stdio.h>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <ctype.h>
#include <stack>

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
	//printMap();
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

	if(nextToken.name.compare("Select") != 0) {
	//cout << "SYNSIZE:" << DESIGN_ENTITIES.size() << endl;
	for(size_t i = 0; i < DESIGN_ENTITIES.size(); i++) {
		if (_stricmp(nextToken.name.c_str(), DESIGN_ENTITIES[i].c_str()) == 0) {
			match(DESIGN_ENTITIES[i]);
			matchDeclarationVariables(DESIGN_ENTITIES[i]);
			i = 0;
		}
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
	//cout << nextToken.name <<endl;
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
		//cout << "End of query" << endl;
		return;
	} else {
		cout << "SYNTAX ERROR" << nextToken.name << endl;
		return;
	}

	if (nextToken.token != EOL) {
		matchConditions();
	}
}

void QueryParser::matchSuchThat() {
	matchSuchThatConditions();
	while (_stricmp(nextToken.name.c_str(), "and") == 0) {
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
	modifiesNode->addChild(matchEntRef(true));
	match(",");
	modifiesNode->addChild(matchVarRef());
	match(")");
	
	qt->getRootNode()->getChild(1)->addChild(modifiesNode);
}

void QueryParser::matchUses() {
	QTNode* usesNode = new QTNode("Uses");

	match("(");
	//cout << "Matched ( successfully, mathching entRef _ ..." << endl;
	usesNode->addChild(matchEntRef(true));
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
	callNode->addChild(matchEntRef(false));
	match(",");
	callNode->addChild(matchEntRef(false));
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
		match(UNDERSCORE);
	} else if (nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} else if (nextToken.name.compare("\"") == 0) {
		match("\"");
		qtpi = new QTNode("\"" + nextToken.name + "\"") ;
		match(IDENT);
		match ("\"");
	}

	return qtpi;	
}

QTNode* QueryParser::matchEntRef(bool excludeUnderScore) {
	QTNode* qtpi;
	//cout << "EntRef: " << nextToken.name << "," << nextToken.name.length() << endl;
	if (nextToken.name.compare("_") == 0) {
		if(!excludeUnderScore) {
			qtpi = new QTNode("_");
			match(UNDERSCORE);
		} else {
			throw (QueryException("VAGUE QUERY ERROR: The first argument of Uses and Modifies cannot be a \"_\""));
		}
	} else if (nextToken.token == INT_LIT) {
		qtpi = new QTNode(stoi(nextToken.name));
		match(INT_LIT);
	} else if (nextToken.token == IDENT || nextToken.token == SIMPLE_IDENT) {
		qtpi = new QTNode(nextToken.name);
		match(IDENT);
	} else if (nextToken.name.compare("\"") == 0) {
		match("\"");
		qtpi = new QTNode("\"" + nextToken.name + "\"") ;
		match(IDENT);
		match ("\"");
	}

	return qtpi;
}

QTNode* QueryParser::matchStmtRef() {
	QTNode* qtpi;
	if (nextToken.name.compare("_") == 0) {
		qtpi = new QTNode("_");
		match(UNDERSCORE);
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
	result = "";
	assignNode->addChild(new QTNode(s));
	match("(");
	assignNode->addChild(matchVarRef());
	match(",");
	/*
	string expression = "";
	if (nextToken.name.compare("_") == 0) {
		expression += nextToken.name;
		match(UNDERSCORE);
	}
	
	expression = matchExpression(expression);
	
	if (nextToken.name.compare("_") == 0) {
		if(expression.compare("_") == 0) {
			throw(QueryException("EXPRESSION ERROR: SIMPLE Expressions of the form __ is invalid"));
		} else {
			expression += nextToken.name;
			match(UNDERSCORE);
		}
	}

	match(")");

	assignNode->addChild(new QTNode(expression));
	qt->getRootNode()->getChild(2)->addChild(assignNode);
	*/

	if(nextToken.name.compare("_") == 0) {
		match(UNDERSCORE);
		assignNode->addChild(new QTNode("_"));
	}
	if(nextToken.name.compare("\"") == 0) {
		match("\"");
		assignNode->addChild(matchExpression());
		match("\"");
	}
	if(nextToken.name.compare("_") == 0) {
		match(UNDERSCORE);
		assignNode->addChild(new QTNode("_"));
	}

	match(")");
	assignNode->setData(result);
	qt->getRootNode()->getChild(2)->addChild(assignNode);
}

QTNode* QueryParser::matchExpression() {
	stack<string> operatorStack;
	stack<QTNode*> operandStack;
	QTNode* left;
	QTNode* right;
	QTNode* current;

	//shunting yard algorithm
	next:
	while(nextToken.name.compare("\"") != 0) {
		string popped;
		if (nextToken.token == OPEN_PARENTHESES) {
			match(OPEN_PARENTHESES);
			operatorStack.push("(");
		} else if (nextToken.token == CLOSE_PARENTHESES) {
			match(CLOSE_PARENTHESES);
			while(!operatorStack.empty()) {
				popped = operatorStack.top();
				operatorStack.pop();
				if (popped.compare("(") == 0) {
					goto next;
				} else {
					//add node(operandStack, popped);
					right = operandStack.top();
					operandStack.pop();
					left = operandStack.top();
					operandStack.pop();
					current = new QTNode(popped);
					current->addChild(left);
					current->addChild(right);
					operandStack.push(current);
				}
			}
			//throw unbalance parentheses exception
		} else {
			if(nextToken.token == PLUS || nextToken.token == MINUS || nextToken.token == TIMES) {
				string op1 = nextToken.name;
				match(op1);
				string op2;
				while (!operatorStack.empty() && !(op2 = operatorStack.top()).empty()) {
					if(comparePrecedence(op1, op2) <= 0) {
						operatorStack.pop();
						//addNode(operandStack, o2)
						right = operandStack.top();
						operandStack.pop();
						left = operandStack.top();
						operandStack.pop();
						current = new QTNode(op2);
						current->addChild(left);
						current->addChild(right);
						operandStack.push(current);
						if(result.length() > 0) result += " ";
						result += op2;
					} else {
						break;
					}
				}
				operatorStack.push(op1);
			} else {
				string factor = nextToken.name;
				if(nextToken.token == INT_LIT) {
					match(INT_LIT);
				} else {
					match(SIMPLE_IDENT);
				}
				if(result.length() > 0) result += " ";
				result += factor;
				operandStack.push(new QTNode(factor));
			}
		}	
	}
	while(!operatorStack.empty()) {
		string op = operatorStack.top();
		operatorStack.pop();
		right = operandStack.top();
		operandStack.pop();
		left = operandStack.top();
		operandStack.pop();
		current = new QTNode(op);
		current->addChild(left);
		current->addChild(right);
		operandStack.push(current);
		result += " " + op;
	}

	//cout << "postfix : " << result << endl;

	return operandStack.top();
}

//if a > b, return 1
//if a < b, return -1
//else return 0
int QueryParser::comparePrecedence(string a, string b) {
	if (a.compare(b) == 0) {
		return 0;
	}
	if (a.compare("-") == 0 && b.compare("+") == 0) {
		return 0;
	}
	if (a.compare("+") == 0 && b.compare("-") == 0) {
		return 0;
	}
	if (a.compare("*") == 0) {
		return 1;
	}
	return -1;
}

/*
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
*/
void QueryParser::matchPatternIf (string s) {
	QTNode* ifNode = new QTNode("if");
	ifNode->addChild(new QTNode(s));
	match("(");
	ifNode->addChild(matchVarRef());
	match(",");
	match(UNDERSCORE);
	match(",");
	match(UNDERSCORE);
	match(")");

	qt->getRootNode()->getChild(2)->addChild(ifNode);
}

void QueryParser::matchPatternWhile(string s) {
	QTNode* whileNode = new QTNode("while");
	whileNode->addChild(new QTNode(s));
	match("(");
	whileNode->addChild(matchVarRef());
	match(",");
	match(UNDERSCORE);
	match(")");

	qt->getRootNode()->getChild(2)->addChild(whileNode);
}

void QueryParser::matchWith() {
}

string QueryParser::getPostFixExpressionString() {
	return result;
}
