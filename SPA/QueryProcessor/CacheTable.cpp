#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "CacheTable.h"
using namespace std;

CacheTable* CacheTable::ct_instance = NULL;

CacheTable* CacheTable::instance() {
	if(!ct_instance) {
		ct_instance = new CacheTable();	
	}
	return ct_instance;
}

CacheTable::CacheTable() {
	CacheTable::isNextStarCache = map<pair<int, int>, bool>() ;
	CacheTable::nextStarCache = map<int, vector<int>>();
	previousStarCache = map<int, vector<int>>();
}

void CacheTable::initCache() {
	CacheTable::isNextStarCache = map<pair<int, int>, bool>() ;
	CacheTable::nextStarCache = map<int, vector<int>>();
	previousStarCache = map<int, vector<int>>();
}
