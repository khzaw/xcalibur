#include "Follows.h"
#include <list>
#include <algorithm>

using namespace std;

Follows::Follows(){
}

void Follows::insertFollows(int stmt1, int stmt2){
	if(!(isFollowsTrue(stmt1,stmt2))){
	pair<int,int> record(stmt1,stmt2);
	records.push_back(record);
	}
}

vector<int> Follows::getFollowers(int stmt){
	vector<int> listFollowers;
	for(int i=0; i<records.size();i++){
			if(records[i].first==stmt){
				listFollowers.push_back(records[i].second);
			}
		}
		return listFollowers;
	}
	
vector<int> Follows::getFollowees(int stmt){
	vector<int> listFollowees;
	for(int i=0; i<records.size();i++){
			if(records[i].second==stmt){
				listFollowees.push_back(records[i].first);
			}
		}
		return listFollowees;
	}
	
vector<int> Follows::getFollowersStar(int stmt){
	vector<int> followers;
	followers = Follows::recursiveFollowerStar(followers,stmt);
	return followers;
}

vector<int> Follows::recursiveFollowerStar(vector<int> &followers,int stmt){
	vector<int> followersSublist ;
	followersSublist = Follows::getFollowers(stmt);
	if(followersSublist.size()==0)
		return followers;
	followers.insert(followers.end(), followersSublist.begin(), followersSublist.end());
	for(std::vector<int>::iterator it=followersSublist.begin(); it != followersSublist.end(); ++it){
		recursiveFollowerStar(followers,*it);
	}
	return followers;
}

vector<int> Follows::getFolloweesStar(int stmt){
	vector<int> followees;
	followees = Follows::recursiveFolloweesStar(followees,stmt);
	return followees;
}

vector<int> Follows::recursiveFolloweesStar(vector<int> &followees,int stmt){
	vector<int> followeesSublist ;
	followeesSublist = Follows::getFollowees(stmt);
	if(followeesSublist.size()==0)
		return followees;
	followees.insert(followees.end(), followeesSublist.begin(), followeesSublist.end());
	for(std::vector<int>::iterator it=followeesSublist.begin(); it != followeesSublist.end(); ++it){
		recursiveFolloweesStar(followees,*it);
	}
	return followees;
}
	
bool Follows::isFollowsTrue(int stmt1, int stmt2){
	vector<int> followers ;
	followers = Follows::getFollowers(stmt1);
	for (std::vector<int>::iterator it=followers.begin(); it != followers.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

int Follows::getSize(){
	return records.size();
}

vector<int> Follows::getAllFollowerStmt(){
	vector<int> followers ;
	for (int i=0; i<records.size();i++){
		if(std::find(followers.begin(), followers.end(), records[i].second)!=followers.end()){
		}else {
	    followers.push_back(records[i].second);
        }
	}
	//followers.unique();
	return followers;
}

vector<int> Follows::getAllFolloweeStmt(){
	vector<int> followees ;
	for (int i=0; i<records.size();i++){
		if(std::find(followees.begin(), followees.end(), records[i].first)!=followees.end()){
		}else {
	    followees.push_back(records[i].first);
        }
	}
	//followees.unique();
	return followees;
}

void Follows::printAll() {
	for(size_t i = 0; i < records.size(); i++) {
		cout << records[i].first << ", " << records[i].second << endl;
	}
}

