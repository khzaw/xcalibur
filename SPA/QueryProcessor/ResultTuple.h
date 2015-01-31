#pragma once
#include <vector>
#include <string>

using namespace std;

class ResultTuple {
	private:
		vector<string> synonyms;
		vector<vector<int> > results;
	public:
		ResultTuple();
		vector<string> getSynonyms();
		string getSynonym(int);
		void addSynonym(string);
		vector<vector<int> > getAllResults();
		vector<int> getResultRow(int);
		int getResultAt(int, int);
		void addResultRow(vector<int>);
		void addResult(int, int);
};