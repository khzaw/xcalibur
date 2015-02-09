#pragma once
#include <string>
#include <vector>
#include <map>
#include "SPA/PKB/PKBController.h"
#include "SPA/QueryProcessor/Subquery.h"
#include "SPA/QueryProcessor/QueryTree.h"
#include "SPA/QueryProcessor/ResultTuple.h"

using namespace std;

// constructor
Subquery::Subquery(map<string, string>* m, PKBController* p){
	synonymTable = m;
	pkb = p;
	synToNodeType = map<string, TNODE_TYPE>();
	synToNodeType.insert(make_pair("assign", ASSIGN_NODE));
	synToNodeType.insert(make_pair("while", WHILE_NODE));
	synToNodeType.insert(make_pair("if", IF_NODE));
}

void Subquery::setPriority(int p){
	priority = p;
}

void Subquery::setSynonyms(string str1, string str2){
	leftSynonym = str1;
	rightSynonym = str2;
	if (str1 == "_" && str2 == "_") {
		isSyn = 6;
	} else if (str1 == "_") {
		isSyn = 4;
	} else if (str2 == "_") {
		isSyn = 5;
	} else {
		isSyn = 3;
	}
}
void Subquery::setSynonyms(string str1, int index2){
	leftSynonym = str1;
	rightIndex = index2;
	if (str1 == "_") {
		isSyn = 7;
	} else {
		isSyn = 2;
	}
}
void Subquery::setSynonyms(int index1, string str2){
	leftIndex = index1;
	rightSynonym = str2;
	if (str2 == "_") {
		isSyn = 8;
	} else {
		isSyn = 1;
	}
}
void Subquery::setSynonyms(int index1, int index2){
	leftIndex = index1;
	rightIndex = index2;
	isSyn = 0;
}

int Subquery::getPriority(){
	return priority;
}

ResultTuple* Subquery::solve(){
	return &ResultTuple();
}

ResultTuple* Subquery::solve(ResultTuple*){
	return &ResultTuple();
}