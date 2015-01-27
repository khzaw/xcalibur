#pragma once
#include <string>
#include <vector>
#include <set>
#include <map>

using namespace std;

class Calls{
	
private:
	vector<pair<int,int>> callTable; // contains entries of callers and callees 
	vector<set<int>> callerTable; // calls |  contains set of callers that calls callees
	vector<set<int>> calleeTable; // calls |  contains set of callees that is called by callers
	vector<set<int>> callerStarTable; // calls*| contains set of callers that calls callees
    vector<set<int>> calleeStarTable; // calls*| contains set of callees that is called by callers
	map<int,int> callerIndexMap; 
	map<int,int> calleeIndexMap;

public:
	
	Calls();
	int insertCalls(int,int);
	set<int> getCallees(int); //O(1)
	set<int> getCallers(int); // O(1)
	set<int> getCallersStar(int); // done
	set<int> getCalleesStar(int); // done
	vector<pair<int,int>> getCallTable();
	bool isCalls(int,int);
	bool isCallsStar(int,int);
	int getSize();
	// Helper
	set<int> getAllCallers(); // done
	set<int> getAllCallees(); // done 

	//get set of callers/callees from calltable
	set<int> getCalleesS(int); // done O(n)
	set<int> getCallerS(int); //done  O(n)

	int getCallerIndex(int); // done
	int getCalleeIndex(int); // done

	//test // done
	set<int> getCalleeStar(int);
	set<int> recursiveCalleeStar(set<int>&,int);
	set<int> getCallerStar(int);
	set<int> recursiveCallerStar(set<int>&,int);

	//build caller/callee table
	vector<set<int>> buildCallerTable();  // done
	vector<set<int>> buildCalleeTable(); // done

	//build caller/callee star table
	vector<set<int>> buildCallerStarTable();  // done
	vector<set<int>> buildCalleeStarTable();  // done

	//build caller/callee index table
	void buildCallerIndex(); // done
	void buildCalleeIndex(); // done
};