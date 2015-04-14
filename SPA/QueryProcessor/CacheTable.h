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
	map<pair<int, int>, bool> isAffectsCache;
	map<int, vector<int>> affectsCache;
	map<int, vector<int>> affectedCache;
	map<pair<int, int>, bool> isAffectsStarCache;
	map<int, vector<int>> affectsStarCache;
	map<int, vector<int>> affectedStarCache;

private:
	CacheTable();
	static CacheTable* ct_instance;
};

