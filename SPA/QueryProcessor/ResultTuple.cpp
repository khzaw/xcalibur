#pragma once
#include <vector>
#include <string>
#include "SPA/QueryProcessor/ResultTuple.h"

using namespace std;

ResultTuple::ResultTuple() {
	synonyms = vector<string>();
	results = vector<vector<int>>();
	synonymMap = map<string, int>();
	isBoolean = false;
	isEmp = false;
}

bool ResultTuple::isBool() {
	return isBoolean;
}

void ResultTuple::setBool(bool boo) {
	isBoolean = boo;
}

bool ResultTuple::isEmpty() {
	return isEmp;
}

void ResultTuple::setEmpty(bool boo) {
	isEmp = boo;
}

vector<string> ResultTuple::getSynonyms() {
	return synonyms;
}

string ResultTuple::getSynonym(int index){
	return synonyms[index];
}

int ResultTuple::getSynonymIndex(string syn) {
	try {
		return synonymMap.at(syn);
	} catch (exception e){
		return -1;
	}
}

map<string, int> ResultTuple::getSynonymMap() {
	return synonymMap;
}

int ResultTuple::addSynonym(string newSyn) {
	synonyms.push_back(newSyn);
	return synonyms.size() - 1;
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
			temp.insert(temp.end(), results[i].begin(), results[i].end());
			temp.insert(temp.end(), other->getAllResults()[j].begin(), other->getAllResults()[j].end());
			final->addResultRow(temp);
		}
	}

	return final;
}