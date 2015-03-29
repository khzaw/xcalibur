#pragma once
#include <iostream>
#include <map>
#include <vector>

#include "CacheTable.h"

using namespace std;

CacheTable::CacheTable() {
	pairAffectsCache = map<pair<int, int>, bool>();
	affectsCache = map<int, vector<int>>();
	affectedCache = map<int, vector<int>>();
	pairAffectsStarCache = map<pair<int, int>, bool>();
	affectsStarCache = map<int, vector<int>>();
	affectedStarCache = map<int, vector<int>>();
}

/***ACCESSORS***/
map<pair<int, int>, bool> CacheTable::getPairNextStarCache(){
	return pairNextStarCache;	
}

map<int, vector<int>> CacheTable::getNextStarCache() {
	return nextStarCache;
}

map<int, vector<int>> CacheTable::getPreviousStarCache() {
	return previousStarCache;
}

map<pair<int, int>, bool> CacheTable::getPairAffectsCache(){
	return pairAffectsCache;	
}

map<int, vector<int>> CacheTable::getAffectsCache() {
	return affectsCache;
}

map<int, vector<int>> CacheTable::getAffectedCache() {
	return affectedCache;
}

map<pair<int, int>, bool> CacheTable::getPairAffectsStarCache(){
	return pairAffectsStarCache;	
}

map<int, vector<int>> CacheTable::getAffectsStarCache() {
	return affectsStarCache;
}

map<int, vector<int>> CacheTable::getAffectedStarCache() {
	return affectedStarCache;
}

/***MODIFIERS***/
void CacheTable::insertToPairNextStarCache(int a, int b, bool truth) {
	pairNextStarCache.insert(map<pair<int, int>, bool>::value_type(make_pair(a, b), truth));
}

void CacheTable::insertNextStarCache(int i, vector<int> v) {
	nextStarCache.insert(map<int, vector<int>>::value_type(i, v));
}

void CacheTable::insertPreviousStarCache(int i, vector<int> v) {
	previousStarCache.insert(map<int, vector<int>>::value_type(i, v));
}
/********/
void CacheTable::insertToPairAffectsCache(int a, int b, bool truth) {
	pairAffectsCache.insert(map<pair<int, int>, bool>::value_type(make_pair(a, b), truth));
}

void CacheTable::insertAffectsCache(int i, vector<int> v) {
	affectsCache.insert(map<int, vector<int>>::value_type(i, v));
}

void CacheTable::insertAffectedCache(int i, vector<int> v) {
	affectedCache.insert(map<int, vector<int>>::value_type(i, v));
}

void CacheTable::insertToPairAffectsStarCache(int a, int b, bool truth) {
	pairAffectsStarCache.insert(map<pair<int, int>, bool>::value_type(make_pair(a, b), truth));
}

void CacheTable::insertAffectsStarCache(int i, vector<int> v) {
	affectsStarCache.insert(map<int, vector<int>>::value_type(i, v));
}

void CacheTable::insertAffectedStarCache(int i, vector<int> v) {
	affectedStarCache.insert(map<int, vector<int>>::value_type(i, v));
}

/***BULK UPDATE***/
void CacheTable::updateNextStarCache(map<int, vector<int>> update) {
	//EnterCriticalSection(&cs_nStar);
	nextStarCache.insert(update.begin(), update.end());
	//LeaveCriticalSection(&cs_nStar);
}

void CacheTable::updatePreviousStarCache(map<int, vector<int>> update) {
	//EnterCriticalSection(&cs_pStar);
	previousStarCache.insert(update.begin(), update.end());
	//LeaveCriticalSection(&cs_pStar);
}

void CacheTable::updateAffectsCache(map<int, vector<int>> update) {
	//EnterCriticalSection(&cs_affects);
	affectsCache.insert(update.begin(), update.end());
	//LeaveCriticalSection(&cs_affects);
}

void CacheTable::updateAffectedCache(map<int, vector<int>> update) {
	//EnterCriticalSection(&cs_affected);
	affectedCache.insert(update.begin(), update.end());
	//LeaveCriticalSection(&cs_affected);
}
void CacheTable::updateAffectsStarCache(map<int, vector<int>> update) {
	//EnterCriticalSection(&cs_affectsStar);
	affectsStarCache.insert(update.begin(), update.end());
	//LeaveCriticalSection(&cs_affectsStar);
}
void CacheTable::updateAffectedStarCache(map<int, vector<int>> update) {
	//EnterCriticalSection(&cs_affectedStar);
	affectedStarCache.insert(update.begin(), update.end());
	//LeaveCriticalSection(&cs_affectedStar);
}
