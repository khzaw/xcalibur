#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"
#include "QueryTree.h"
#include "..\PKB\PKBController.h"

using namespace std;

// constructor
Subquery::Subquery(){
}

void Subquery::init(map<string, string>* m, QueryTree* q, PKBController* p){
	synonymTable = m;
	subquery = q;
	pkb = p;
}

void Subquery::setPriority(int p){
	priority = p;
}

int Subquery::getPriority(){
	return priority;
}

map<string, vector<int> >* Subquery::solve(){
	map<string, vector<int> > temp;
	return &temp;
}

map<string, vector<int> >* solve(map<string, vector<int> >*){
	map<string, vector<int> > temp;
	return &temp;
}