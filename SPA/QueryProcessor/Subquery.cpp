#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"
#include "QueryTree.h"
#include "..\PKB\PKBController.h"
#include "ResultTuple.h"

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
	isSyn = 3;
}
void Subquery::setSynonyms(string str1, int index2){
	leftSynonym = str1;
	rightIndex = index2;
	isSyn = 2;
}
void Subquery::setSynonyms(int index1, string str2){
	leftIndex = index1;
	rightSynonym = str2;
	isSyn = 1;
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

ResultTuple* solve(ResultTuple*){
	return &ResultTuple();
}