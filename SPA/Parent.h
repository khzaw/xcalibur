#pragma once
#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Parent {

	private :
	vector<pair<int,int>> records;
	vector<int>recursiveChildrenStar(vector<int>&,int);
	vector<int>recursiveParentStar(vector<int>&,int);
	
	public :
	Parent();
	void insertParent(int,int);
	vector<int> getChildren(int);
	vector<int> getParents(int);
	int getSize();
	bool isParentTrue(int,int);
	vector<int> getChildrenStar(int);
	vector<int> getParentStar(int);
	vector<int> getAllChildrenStmt();
	vector<int> getAllParentStmt();
	
};