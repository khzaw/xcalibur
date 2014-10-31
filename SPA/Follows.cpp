#include "Follows.h"
#include <list>

using namespace std;

Follows::Follows(){
}

void Follows::insertFollows(int stmt1, int stmt2){
	pair<int,int> record(stmt1,stmt2);
	records.push_back(record);
}

list<int> Follows::getFollowers(int stmt){
	list<int> listFollowers;
	for(int i=0; i<records.size();i++){
			if(records[i].first==stmt){
				listFollowers.push_back(records[i].second);
			}
		}
		return listFollowers;
	}
	
list<int> Follows::getFollowees(int stmt){
	list<int> listFollowees;
	for(int i=0; i<records.size();i++){
			if(records[i].second==stmt){
				listFollowees.push_back(records[i].first);
			}
		}
		return listFollowees;
	}
	
list<int> Follows::getFollowersStar(int stmt){
	list<int> followers;
	followers = Follows::recursiveFollowerStar(followers,stmt);
	return followers;
}

list<int> Follows::recursiveFollowerStar(list<int> &followers,int stmt){
	list<int> followersSublist ;
	followersSublist = Follows::getFollowers(stmt);
	if(followersSublist.size()==0)
		return followers;
	followers.insert(followers.end(), followersSublist.begin(), followersSublist.end());
	for(std::list<int>::iterator it=followersSublist.begin(); it != followersSublist.end(); ++it){
		recursiveFollowerStar(followers,*it);
	}
	return followers;
}

list<int> Follows::getFolloweesStar(int stmt){
	list<int> followees;
	followees = Follows::recursiveFolloweesStar(followees,stmt);
	return followees;
}

list<int> Follows::recursiveFolloweesStar(list<int> &followees,int stmt){
	list<int> followeesSublist ;
	followeesSublist = Follows::getFollowees(stmt);
	if(followeesSublist.size()==0)
		return followees;
	followees.insert(followees.end(), followeesSublist.begin(), followeesSublist.end());
	for(std::list<int>::iterator it=followeesSublist.begin(); it != followeesSublist.end(); ++it){
		recursiveFolloweesStar(followees,*it);
	}
	return followees;
}
	
bool Follows::isFollowsTrue(int stmt1, int stmt2){
	list<int> followers ;
	followers = Follows::getFollowers(stmt1);
	for (std::list<int>::iterator it=followers.begin(); it != followers.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

list<int> Follows::getAllFollowerStmt(){
	list<int> followers ;
	for (int i=0; i<records.size();i++){
		followers.push_back(records[i].second);
	}
	followers.unique();
	return followers;
}

list<int> Follows::getAllFolloweeStmt(){
	list<int> followees ;
	for (int i=0; i<records.size();i++){
		followees.push_back(records[i].first);
	}
	followees.unique();
	return followees;
}

