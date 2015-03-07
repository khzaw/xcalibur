#pragma once
#include <vector>
#include <string>
#include <map>

using namespace std;

class ResultTuple {
private:
	vector<vector<int>> results;
	map<string, int> synonymMap;
	vector<string> synonyms;
	bool isBoolean;
	bool isEmp;

public:
	ResultTuple();
	ResultTuple(vector<vector<int>>, vector<string>);
		
	//modifiers
	int addSynonym(string);
	void addSynonymToMap(string, int);
	void addResultRow(vector<int>);
	void addResult(int, int);
	void setSynonym(vector<string>);
	void setSynonymMap(map<string, int>);
	ResultTuple* cross(ResultTuple*);
	ResultTuple* join(ResultTuple*);

	//accessors
	bool isBool();
	bool isEmpty();
	void setEmpty(bool);
	void setBool(bool);
	int getResultAt(int, int);
	string getSynonym(int);		//might not need
	vector<string> getSynonyms();
	map<string, int> getSynonymMap();
	int getSynonymIndex(string);
	vector<int> getResultRow(int);
	vector<vector<int> > getAllResults();

	string toString();
};