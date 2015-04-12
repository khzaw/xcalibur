#pragma once
#include <iostream>
#include <map>
#include <vector>
//#include <windows.h>

using namespace std;

class CacheTable {
private:
	/*
	static CRITICAL_SECTION cs_nStar;
	static CRITICAL_SECTION cs_pStar;
	static CRITICAL_SECTION cs_affects;
	static CRITICAL_SECTION cs_affected;
	static CRITICAL_SECTION cs_affectsStar;
	static CRITICAL_SECTION cs_affectedStar;
	*/

	static map<pair<int, int>, bool> *pairNextStarCache;
	static map<int, vector<int>> *nextStarCache;
	static map<int, vector<int>> *previousStarCache;

	static map<pair<int, int>, bool> pairAffectsCache;
	static map<int, vector<int>> affectsCache;
	static map<int, vector<int>> affectedCache;
	static map<pair<int, int>, bool> pairAffectsStarCache;
	static map<int, vector<int>> affectsStarCache;
	static map<int, vector<int>> affectedStarCache;

public:
	CacheTable();

	/****NEXT STAR MODIFIERS AND ACCESSORS****/
	static map<pair<int, int>, bool>* getPairNextStarCache();
	static map<int, vector<int>>* getNextStarCache();
	static map<int, vector<int>>* getPreviousStarCache();;

	static void updateNextStarCache(map<int, vector<int>>*);
	static void updatePreviousStarCache(map<int, vector<int>>*);
	
	/**** AFFECTS MODIFIERS AND ACCESSORS ****/
	map<pair<int, int>, bool> getPairAffectsCache();
	map<int, vector<int>> getAffectsCache();
	map<int, vector<int>> getAffectedCache();
	map<pair<int, int>, bool> getPairAffectsStarCache();
	map<int, vector<int>> getAffectsStarCache();
	map<int, vector<int>> getAffectedStarCache();


	void insertToPairNextStarCache(int, int, bool);
	void insertNextStarCache(int, vector<int>);
	void insertPreviousStarCache(int, vector<int>);

	void insertToPairAffectsCache(int, int, bool);
	void insertAffectsCache(int, vector<int>);
	void insertAffectedCache(int, vector<int>);
	void insertToPairAffectsStarCache(int, int, bool);
	void insertAffectsStarCache(int, vector<int>);
	void insertAffectedStarCache(int, vector<int>);


	void updateAffectsCache(map<int, vector<int>>);
	void updateAffectedCache(map<int, vector<int>>);
	void updateAffectsStarCache(map<int, vector<int>>);
	void updateAffectedStarCache(map<int, vector<int>>);
};

