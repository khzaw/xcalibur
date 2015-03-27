#pragma once
#include <iostream>
#include <map>
#include <vector>

using namespace std;

class CacheTable{

private:
	map<pair<int, int>, bool> pairNextStarCache;
	map<int, vector<int>> nextStarCache;
	map<int, vector<int>> previousStarCache;

	map<pair<int, int>, bool> pairAffectsCache;
	map<int, vector<int>> affectsCache;
	map<int, vector<int>> affectedCache;
	map<pair<int, int>, bool> pairAffectsStarCache;
	map<int, vector<int>> affectsStarCache;
	map<int, vector<int>> affectedStarCache;

public:
	CacheTable();

	/****ACCESSORS****/
	map<pair<int, int>, bool> getPairNextStarCache();
	map<int, vector<int>> getNextStarCache();
	map<int, vector<int>> getPreviousStarCache();

	map<pair<int, int>, bool> getPairAffectsCache();
	map<int, vector<int>> getAffectsCache();
	map<int, vector<int>> getAffectedCache();
	map<pair<int, int>, bool> getPairAffectsStarCache();
	map<int, vector<int>> getAffectsStarCache();
	map<int, vector<int>> getAffectedStarCache();

	/****MODIFIER****/
	void insertToPairNextStarCache(int, int, bool);
	void insertNextStarCache(int, vector<int>);
	void insertPreviousStarCache(int, vector<int>);

	void insertToPairAffectsCache(int, int, bool);
	void insertAffectsCache(int, vector<int>);
	void insertAffectedCache(int, vector<int>);
	void insertToPairAffectsStarCache(int, int, bool);
	void insertAffectsStarCache(int, vector<int>);
	void insertAffectedStarCache(int, vector<int>);

};

