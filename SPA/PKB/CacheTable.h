#pragma once
#include <iostream>
#include <map>
#include <vector>
//#include <windows.h>

/*
CRITICAL_SECTION cs_nStar;
CRITICAL_SECTION cs_pStar;
CRITICAL_SECTION cs_affects;
CRITICAL_SECTION cs_affected;
CRITICAL_SECTION cs_affectsStar;
CRITICAL_SECTION cs_affectedStar;
*/

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

	void updateNextStarCache(map<int, vector<int>>);
	void updatePreviousStarCache(map<int, vector<int>>);
	void updateAffectsCache(map<int, vector<int>>);
	void updateAffectedCache(map<int, vector<int>>);
	void updateAffectsStarCache(map<int, vector<int>>);
	void updateAffectedStarCache(map<int, vector<int>>);
};

