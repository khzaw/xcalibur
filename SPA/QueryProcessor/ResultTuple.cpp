#pragma once
#include <vector>
#include <string>
#include "ResultTuple.h"

using namespace std;

ResultTuple::ResultTuple() {
	synonyms = vector<string>();
	results = vector<vector<int>>();
	synonymMap = map<string, int>();
	isBoolean = false;
}

bool ResultTuple::isBool() {
	return isBoolean;
}

void ResultTuple::setBool(bool boo) {
	isBoolean = boo;
}

vector<string> ResultTuple::getSynonyms() {
	return synonyms;
}

string ResultTuple::getSynonym(int index){
	return synonyms[index];
}

void ResultTuple::addSynonym(string newSyn) {
	synonyms.push_back(newSyn);
}
		
vector<vector<int> > ResultTuple::getAllResults() {
	return results;
}

vector<int> ResultTuple::getResultRow(int rIndex) {
	return results[rIndex];
}

int ResultTuple::getResultAt(int rIndex, int cIndex) {
	return results[rIndex][cIndex];
}

void ResultTuple::addResultRow(vector<int> newRow) {
	results.push_back(newRow);
}

void ResultTuple::addResult(int rIndex, int newResult) {
	results[rIndex].push_back(newResult);
}


void ResultTuple::addSynonymToMap(string syn, int index) {
	synonymMap.insert(map<string, int>::value_type(syn, index));
}

void ResultTuple::setSynonym(vector<string> syn) {
	this->synonyms = syn;
}

void ResultTuple::setSynonymMap(map<string, int> syn) {
	this->synonymMap = syn;
}

// NOTE: Both ResultTuple must not have the same synonyms
ResultTuple* ResultTuple::cross(ResultTuple* other) {
	ResultTuple* final = new ResultTuple();

	//adding synonym
	vector<string> tempSyn = vector<string>();
	tempSyn.insert(tempSyn.end(), synonyms.begin(), synonyms.end());
	tempSyn.insert(tempSyn.end(), other->getSynonyms().begin(), other->getSynonyms().end());
	final->setSynonym(tempSyn);
	for (int i = 0; i < tempSyn.size(); i++) {
		final->addSynonymToMap(tempSyn[i], i);
	}

	//cross product
	int s1 = results.size();
	for (int i = 0; i < s1; i++) {
		int s2 = other->getAllResults().size();
		for (int j = 0; j < s2; j++) {	
			vector<int> temp = vector<int>();
			temp.insert(temp.end(), results.begin(), results.end());
			temp.insert(temp.end(), other->getAllResults().begin(), other->getAllResults().end());
			final->addResultRow(temp);
		}
	}

	return final;
}