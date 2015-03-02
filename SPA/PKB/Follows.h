#pragma once

#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <set>
#include "..\PKB\StatementTable.h"

using namespace std;

class Follows {

	private :
	vector<pair<int,int>> followTable;
	set<int>recursiveFollowerStar(set<int>&,int);
	set<int>recursiveFolloweesStar(set<int>&,int);
	StatementTable* statementTable;
	
	public :
    Follows();
	Follows(StatementTable* statementTable);
     /**** for query evaluation ****/
	 bool evaluateIsFollows(int,int);
	 bool evaluateIsFollowsStar(int,int);
	 set<int> evaluateGetFollowersT(int,string);
	 set<int> evaluateGetFolloweesT(int,string);
	 set<int> evaluateGetFollowerStarT(int,string);
	 set<int> evaluateGetFolloweeStarT(int,string);
	 /*****************************************/
	void insertFollows(int,int);
	set<int> getFollowers(int);
	set<int> getFollowees(int);
	int getSize();
	bool isFollowsTrue(int,int);
	bool isFollowsStarTrue(int,int);
	set<int> getFollowersStar(int);
	set<int> getFolloweesStar(int);
	set<int> getAllFollowerStmt();
	set<int> getAllFolloweeStmt();
	void printAll();



	//optimization
	//vector<vector<bool>> followTable;
   // vector<vector<bool>> followStarTable; 
	vector<set<int>> followerTable; // followee -> followers
	vector<set<int>> followeeTable; // followers -> followees
	vector<set<int>> followerStarTable; // followee -> followers*
	vector<set<int>> followeeStarTable; // followers -> followee*
	unordered_map<int,int> followerMap; // done 
	unordered_map<int,int> followeeMap; // done

	//getIndex
	int getFollowerIndex(int); // done
	int getFolloweeIndex(int); // done
	

	void insertToFolloweeTable(set<int>);
	void insertToFollowerTable(set<int>);
	void insertToFolloweeStarTable(set<int>);
	void insertToFollowerStarTable(set<int>);
	void insertToFolloweeIndexMap(pair<int,int>);
	void insertToFollowerIndexMap(pair<int,int>);
	int getFolloweeIndexMapSize();
	int getFollowerIndexMapSize();

	
	
	 set<int> evaluateGetFollowers(int);
	 set<int> evaluateGetFollowees(int);
	 set<int> evaluateGetFollowerStar(int);
	 set<int> evaluateGetFolloweeStar(int);



};