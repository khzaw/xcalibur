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
	isEmp = false;
}

ResultTuple::ResultTuple(vector<vector<int>> tups, vector<string> syns) {
	synonyms = syns;
	results = tups;
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
	vector<string> temp2 = other->getSynonyms();
	vector<string> tempSyn = vector<string>();
	tempSyn.insert(tempSyn.end(), synonyms.begin(), synonyms.end());
	tempSyn.insert(tempSyn.end(), temp2.begin(), temp2.end());
	final->setSynonym(tempSyn);
	for (size_t i = 0; i < tempSyn.size(); i++) {
		final->addSynonymToMap(tempSyn[i], i);
	}

	//cross product
	int s1 = results.size();
	for (int i = 0; i < s1; i++) {
		int s2 = other->getAllResults().size();
		for (int j = 0; j < s2; j++) {	
			vector<int> temp = vector<int>();
			vector<int> tempResult = results[i];
			vector<int> otherTempResult = other->getAllResults()[j];
			temp.insert(temp.end(), tempResult.begin(), tempResult.end());
			temp.insert(temp.end(), otherTempResult.begin(), otherTempResult.end());
			final->addResultRow(temp);
		}
	}

	return final;
}

ResultTuple* ResultTuple::join(ResultTuple* other) {
	vector<pair<int, int>> equalIndex;	
	vector<int> uniqueIndexInSecond;
	vector<string> solutionSynonyms = getSynonyms();
	
	// get the pairs of indexes for the same attributes
	// get the list of all synonyms in the solution
	for(size_t i = 0; i < other->getSynonyms().size(); i++ ) {
		bool in = false;
		for(size_t j = 0; j < synonyms.size(); j++) {
			//cout<<endl  << second.first.at(i) << " " << first.first.at(j) <<endl;
			if(other->getSynonyms().at(i).compare(synonyms.at(j)) == 0) {
				equalIndex.push_back(make_pair(j, i));
				in = true;
				break;
			} 
		}
		if(in == false) {
			uniqueIndexInSecond.push_back(i);
			solutionSynonyms.push_back(other->getSynonyms().at(i));
		}
	}
	vector<vector<int>> solutionValues(solutionSynonyms.size());
	for(size_t i = 0; i < results[0].size(); i ++) {
		for(size_t j = 0; j < other->getAllResults().at(0).size(); j++) {
			bool equal = true;
			// check if similar attributes have equal values
			for(size_t k = 0; k < equalIndex.size(); k++) {
				if (!(results[equalIndex.at(k).first].at(i) == other->getResultAt(equalIndex.at(k).second, j))) {
					equal = false;
					break;
				}
			}

			if(equal) {					//all similar attributes have equal values
				for(size_t a = 0; a < solutionSynonyms.size(); a++) {
					if(a < synonyms.size()) {
						// push each attribute of first set
						solutionValues[a].push_back(getResultAt(a, i));
					} else {
						// push each attribute of second set with index in uniqueIndexInSecond
						solutionValues[a].push_back(other->getResultAt(uniqueIndexInSecond[a - getAllResults().size()], j));
					}
				}
			}
		}
	}

	return new ResultTuple(solutionValues, solutionSynonyms);	
}

string ResultTuple::toString(){
	string result = "";
	int colSize = 8;
	for (size_t i = 0; i < synonyms.size(); i++){
		size_t left = (colSize - synonyms[i].length())/2;
		size_t right = colSize - synonyms[i].length() - left;
		result.append(left, ' ');
		result.append(synonyms[i]);
		result.append(right, ' ');
		result.append("|");
		if (i == synonyms.size() - 1){
			result.append("\n");
		}
	}
	for (size_t i = 0; i < results.size(); i++){
		for (size_t j = 0; j < results[i].size(); j++){
			size_t left = (colSize - to_string((long long)results[i][j]).length())/2;
			size_t right = colSize - to_string((long long)results[i][j]).length() - left;
			result.append(left, ' ');
			result.append(to_string((long long)results[i][j]));
			result.append(right, ' ');
			result.append("|");
			if (j == results[i].size() - 1){
				result.append("\n");
			}
		}
	}
	return result;
}