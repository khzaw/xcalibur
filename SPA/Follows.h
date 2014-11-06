#pragma once

#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Follows {

	private :
	vector<pair<int,int>> records;
	vector<int>recursiveFollowerStar(vector<int>&,int);
	vector<int>recursiveFolloweesStar(vector<int>&,int);
	
	public :
	Follows();
	void insertFollows(int,int);
	vector<int> getFollowers(int);
	vector<int> getFollowees(int);
	int getSize();
	bool isFollowsTrue(int,int);
	bool isFollowstarTrue(int,int);
	vector<int> getFollowersStar(int);
	vector<int> getFolloweesStar(int);
	vector<int> getAllFollowerStmt();
	vector<int> getAllFolloweeStmt();
	void printAll();
	
};