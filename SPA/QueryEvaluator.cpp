// File name: QueryEvaluator.cpp
#include <string>
#include <map>
#include "QueryTree.h"
#include "QTNode.h"
#include "PKB.h"

#include "QueryEvaluator.h"

using namespace std;

typedef string STRING;

/******* Constructors *******/
QueryEvaluator::QueryEvaluator(){

};

QueryEvaluator::QueryEvaluator(PKB newPKB){
	pkb = newPKB;
};

/******* Methods *******/
STRING QueryEvaluator::evaluate(map<STRING, STRING> symbolTable, QueryTree tree){
	return "Hello World!";
};