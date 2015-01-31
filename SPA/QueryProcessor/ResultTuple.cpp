#pragma once
#include <vector>
#include <string>
#include "..\QueryProcessor\ResultTuple.h"

using namespace std;

ResultTuple::ResultTuple(){
	synonyms = vector<string>();
	results = vector<vector<int> >();
}

vector<string> ResultTuple::getSynonyms(){
	return synonyms;
}

string ResultTuple::getSynonym(int index){
	return synonyms[index];
}

void ResultTuple::addSynonym(string newSyn){
	synonyms.push_back(newSyn);
}
		
vector<vector<int> > ResultTuple::getAllResults(){
	return results;
}

vector<int> ResultTuple::getResultRow(int rIndex){
	return results[rIndex];
}

int ResultTuple::getResultAt(int rIndex, int cIndex){
	return results[rIndex][cIndex];
}

void ResultTuple::addResultRow(vector<int> newRow){
	results.push_back(newRow);
}

void ResultTuple::addResult(int rIndex, int newResult){
	results[rIndex].push_back(newResult);
}