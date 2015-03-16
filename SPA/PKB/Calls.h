 #pragma once
#include <string>
#include <vector>
#include <set>
#include <unordered_map>

using namespace std;

class Calls{
	
private:
	vector<pair<int,int>>* callTable; // contains entries of callers and callees 
	vector<set<int>>* callerTable; // calls |  contains set of callers that calls callees
	vector<set<int>>* calleeTable; // calls |  contains set of callees that is called by callers
	vector<set<int>>* callerStarTable; // calls*| contains set of callers that calls callees
    vector<set<int>>* calleeStarTable; // calls*| contains set of callees that is called by callers
	unordered_map<int,int>* callerIndexMap; 
	unordered_map<int,int>* calleeIndexMap;

public:
	
	Calls();
	int insertCalls(int,int);

	vector<pair<int,int>>* getCallTable();
	int getSize();
	// Helper
	set<int> getAllCallers(); // done
	set<int> getAllCallees(); // done 

	//get set of callers/callees from calltable
	set<int> getCalleesS(int); // done O(n) don't use this for evaluation
	set<int> getCallerS(int); //done  O(n) don't use this for evaluation

	int getCallerIndex(int); // done
	int getCalleeIndex(int); // done

	//test // done
	set<int> getCalleeStar(int);
	set<int> recursiveCalleeStar(set<int>&,int);
	set<int> getCallerStar(int);
	set<int> recursiveCallerStar(set<int>&,int);

	//
	void insertToCallerTable(set<int>);
	void insertToCalleeTable(set<int>);
	void insertToCallerStarTable(set<int>);
	void insertToCalleeStarTable(set<int>);
	void insertToCallerIndexMap(pair<int,int>);
	void insertToCalleeIndexMap(pair<int,int>);
	int getCalleeIndexMapSize();
	int getCallerIndexMapSize();

	//for query evaluation
	bool isCalls(int,int);
	bool isCallsStar(int,int);
	set<int> evaluateGetCallees(int); //O(1) for eval 
	set<int> evaluateGetCallers(int); // O(1) for eval 
	set<int> evaluateGetCallersStar(int); // done for eval
	set<int> evaluateGetCalleesStar(int); // done for eval
	
};