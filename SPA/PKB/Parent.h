#pragma once
#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include "..\PKB\StatementTable.h"

using namespace std;

class Parent {

	private :
	vector<pair<int,int>> parentTable;
	set<int>recursiveChildrenStar(set<int>&,int);
	set<int>recursiveParentStar(set<int>&,int);
	StatementTable* statementTable;
	
	public :
	Parent();
	Parent(StatementTable* statementTable);

	  /**** for query evaluation ****/
	 bool evaluateIsParent(int,int);
	 bool evaluateIsParentStar(int,int);
	 set<int>  evaluateGetChildrenT(int,string);
	 set<int>  evaluateGetParentT(int,string);
	 set<int>  evaluateGetChildrenStarT(int,string);
	 set<int>  evaluateGetParentStarT(int,string);
	 /*****************************************/
	

	void insertParent(int,int);
	set<int> getChildren(int);
	set<int> getParents(int);
	int getSize();
	bool isParentTrue(int,int);
	bool isParentStarTrue(int, int);
	set<int> getChildrenStar(int);
	set<int> getParentStar(int);
	set<int> getAllChildrenStmt();
	set<int> getAllParentStmt();
	
		//optimization
	//vector<vector<bool>> followTable;
    //vector<vector<bool>> followStarTable; 
	vector<set<int>> cTable; // followee -> followers
	vector<set<int>> pTable; // followers -> followees
	vector<set<int>> childrenStarTable; // followee -> followers*
	vector<set<int>> parentStarTable; // followers -> followee*
	unordered_map<int,int> childrenMap; // done 
	unordered_map<int,int> parentMap; // done

	//getIndex
	int getParentIndex(int); // done
	int getChildrenIndex(int); // done
	
	 void insertToChildrenTable(set<int>);
	void insertToParentTable(set<int>);
	void insertToChildrenStarTable(set<int>);
	void insertToParentStarTable(set<int>);
	void insertToChildrenIndexMap(pair<int,int>);
	void insertToParentIndexMap(pair<int,int>);
	int getChildrenIndexMapSize();
	int getParentIndexMapSize();

	//methods for query evaluation
	 set<int> evaluateGetChildren(int);
	 set<int> evaluateGetParent(int);
	 set<int> evaluateGetChildrenStar(int);
	 set<int> evaluateGetParentStar(int);
};