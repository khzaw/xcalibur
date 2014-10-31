#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Follows {

	private :
	vector<pair<int,int>> records;
	list<int>recursiveFollowerStar(list<int>&,int);
	list<int>recursiveFolloweesStar(list<int>&,int);
	
	public :
	Follows();
	void insertFollows(int,int);
	list<int> getFollowers(int);
	list<int> getFollowees(int);
	bool isFollowsTrue(int,int);
	list<int> getFollowersStar(int);
	list<int> getFolloweesStar(int);
	list<int> getAllFollowerStmt();
	list<int> getAllFolloweeStmt();
	
};