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

QueryEvaluator::QueryEvaluator(PKB* newPKB){
	pkb = newPKB;
};

/******* Methods *******/
STRING QueryEvaluator::evaluate(map<STRING, STRING> symbolTable, QueryTree tree){
	// Algorithm
	// -Select "Select" subtree from QueryTree
	// --Get child of selectSubtree to find select synonym (e.g. a1-assign, w-while, etc.)
	// -Select "Such that" subtree from QueryTree
	// --For each children of suchthatSubtree, check whether the content contains selectSynonym 
	// ---If true call methods from PKB
	// ---If false, evaluate the suchthat statement as Boolean and find result accordingly
	// --Merge results
	// -Select "pattern" subtree and continue...
	// -Merge all results and return
	return "Hello World!";
};