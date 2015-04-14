#pragma once
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class CacheTable {
public:
	static CacheTable* instance();
	void initCache();
	map<pair<int, int>, bool> isNextStarCache;
	map<int, vector<int>> nextStarCache;
	map<int, vector<int>> previousStarCache;

private:
	CacheTable();
	static CacheTable* ct_instance;
};

