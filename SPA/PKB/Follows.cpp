#include "Follows.h"
#include <list>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;

Follows::Follows(){

}

Follows::Follows(StatementTable* s){
	statementTable = s;
}

void Follows::insertFollows(int stmt1, int stmt2){
	if(!(isFollowsTrue(stmt1,stmt2))){
    //cout << "stmt1 : " << stmt1 << ", " << "stmt2: " << stmt2 << endl;
	pair<int,int> record(stmt1,stmt2);
	followTable.push_back(record);
	}
}

set<int> Follows::getFollowers(int stmt){
	set<int> listFollowers;
	for(size_t i=0; i<followTable.size();i++){
			if(followTable[i].first==stmt){
				listFollowers.insert(followTable[i].second);
			}
		}
		return listFollowers;
	}
	
set<int> Follows::getFollowees(int stmt){
	set<int> listFollowees;
	for(size_t i=0; i<followTable.size();i++){
			if(followTable[i].second==stmt){
				listFollowees.insert(followTable[i].first);
			}
		}
		return listFollowees;
	}
	
set<int> Follows::getFollowersStar(int stmt){
	set<int> followers;
	followers = Follows::recursiveFollowerStar(followers,stmt);
	return followers;
}

set<int> Follows::recursiveFollowerStar(set<int> &followers,int stmt){
	set<int> followerSublist ;
	followerSublist = Follows::getFollowers(stmt);
	if(followerSublist.size()==0)
		return followers;
	followers.insert(followerSublist.begin(), followerSublist.end());
	for(std::set<int>::iterator it=followerSublist.begin(); it != followerSublist.end(); ++it){
		recursiveFollowerStar(followers,*it);
	}
	return followers;
}

set<int> Follows::getFolloweesStar(int stmt){
	set<int> followees;
	followees = Follows::recursiveFolloweesStar(followees,stmt);
	return followees;
}

set<int> Follows::recursiveFolloweesStar(set<int> &followees,int stmt){
	set<int> followeeSublist ;
	followeeSublist = Follows::getFollowees(stmt);
	if(followeeSublist.size()==0)
		return followees;
	followees.insert(followeeSublist.begin(), followeeSublist.end());
	for(std::set<int>::iterator it=followeeSublist.begin(); it != followeeSublist.end(); ++it){
		recursiveFolloweesStar(followees,*it);
	}
	return followees;
}
	
bool Follows::isFollowsTrue(int stmt1, int stmt2){
	set<int> followers ;
	followers = Follows::getFollowers(stmt1);
	for (std::set<int>::iterator it=followers.begin(); it != followers.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

bool Follows::isFollowsStarTrue(int stmt1, int stmt2){
	set<int> followersStar;
	followersStar = Follows::getFollowersStar(stmt1);
	for (std::set<int>::iterator it=followersStar.begin(); it != followersStar.end(); ++it){
		if(*it==stmt2)
			return true;
	}
	return false;
}

int Follows::getSize() {
	return followTable.size();
}

set<int> Follows::getAllFollowerStmt(){
	set<int> followers;
		//std::set<int>::iterator it = followeeSet.begin();
		for (size_t i = 0; i < followTable.size(); i++){		
				followers.insert(followTable[i].second);
		}
		return followers;
}

set<int> Follows::getAllFolloweeStmt(){
	set<int> followees;
		//std::set<int>::iterator it = followeeSet.begin();
		for (size_t i = 0; i < followTable.size(); i++){		
				followees.insert(followTable[i].first);
		}
		return followees;
}

int Follows::getFollowerIndex(int follower){
		std::unordered_map<int, int>::iterator it = followerMap.find(follower);
		if(it == followerMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
}

int Follows::getFolloweeIndex(int followee){
		std::unordered_map<int, int>::iterator it = followeeMap.find(followee);
		if(it == followeeMap.end()) {	
		return -1;
	} else {
		return it->second;
	}
}


void Follows::printAll() {
	for(size_t i = 0; i < followTable.size(); i++) {
		cout << followTable[i].first << ", " << followTable[i].second << endl;
	}
}

set<int> Follows::evaluateGetFollowers(int stmt){
	set<int> results;
	int index = Follows::getFolloweeIndex(stmt);
	if (index == -1 || (size_t)index >= followerTable.size()){
		return results;
	}else{
		results = followerTable[index];
		return results;
	}
}
	 set<int> Follows::evaluateGetFollowees(int stmt){
	set<int> results;
	int index = Follows::getFollowerIndex(stmt);
	
	if(index == -1 || (size_t)index >= followeeTable.size()){
	
		return results;
	}else{
		results = followeeTable[index];

		return results;
	}
	

}

	 set<int> Follows::evaluateGetFollowerStar(int stmt){
	set<int> results;
	int index = Follows::getFolloweeIndex(stmt);
	if(index == -1 || (size_t)index >= followerStarTable.size()){
		return results;
	}else{
		results = followerStarTable[index];
		return results;
	}
	
}

	 set<int> Follows::evaluateGetFolloweeStar(int stmt){
	 set<int> results;
	int index = Follows::getFollowerIndex(stmt);
	if(index == -1 || (size_t)index >= followeeStarTable.size()){
		return results;
	}else{
		results = followeeStarTable[index];
		return results;
	}
	 }

	 bool Follows::evaluateIsFollows(int followee,int follower){
		 int index = getFolloweeIndex(followee);
		 if(index == -1){
			 return false;
		 }else{
			 set<int> followerSet = followerTable[index]; 
		      std::set<int>::iterator it = followerSet.find(follower);
	   if( it == followerSet.end()){
		   return false;
	   }else{
		   return true;
	   }
		 }
	 }

	 bool Follows::evaluateIsFollowsStar(int followee,int follower){
		 int index = getFolloweeIndex(followee);
		 if(index == -1){
			 return false;
		 }else{
			 set<int> followerStarSet = followerStarTable[index]; 
		      std::set<int>::iterator it = followerStarSet.find(follower);
	   if( it == followerStarSet.end()){
		   return false;
	   }else{
		   return true;
	   }
		 }
	 }

/* Query Evaluator should only touch these methods */
	  set<int> Follows::evaluateGetFollowersT(int n,string nodeType){
		  if(nodeType == "all"){
			  return evaluateGetFollowers(n);
		  }
		  set<int> results = evaluateGetFollowers(n);
		  set<int> finalresults;
		  for (std::set<int>::iterator it=results.begin(); it != results.end(); ++it){
		if(statementTable->getTNodeType(*it)== nodeType){
			finalresults.insert(*it);
		  }
		  }
		  return finalresults;
	  }

	 set<int> Follows::evaluateGetFolloweesT(int n,string nodeType){
		  if(nodeType == "all"){
			  return evaluateGetFollowees(n);
		  }
		 set<int> results = evaluateGetFollowees(n);
		 set<int> finalresults;
		  for (std::set<int>::iterator it=results.begin(); it != results.end(); ++it){
			  	if(statementTable->getTNodeType(*it)== nodeType){
			finalresults.insert(*it);
		  }
		  }
		  return finalresults;
	 }

	 set<int> Follows::evaluateGetFollowerStarT(int n,string nodeType){
		  if(nodeType == "all"){
			  return evaluateGetFollowerStar(n);
		  }
		 set<int> results = evaluateGetFollowerStar(n);
		 set<int> finalresults;
		  for (std::set<int>::iterator it=results.begin(); it != results.end(); ++it){
			  if(statementTable->getTNodeType(*it)== nodeType){
			finalresults.insert(*it);
		  }
		  }
		    return finalresults;
	 }

	 set<int> Follows::evaluateGetFolloweeStarT(int n ,string nodeType){
		   if(nodeType == "all"){
			  return evaluateGetFolloweeStar(n);
		  }
		 set<int> results = evaluateGetFolloweeStar(n);
		 set<int> finalresults;
		  for (std::set<int>::iterator it=results.begin(); it != results.end(); ++it){
			  if(statementTable->getTNodeType(*it)== nodeType){
			finalresults.insert(*it);
		  }
		  }
		  return finalresults;
	 }
	 
	void Follows::insertToFollowerTable(set<int> follower){
		followerTable.push_back(follower);
	}

	void Follows::insertToFolloweeTable(set<int> followee){
		followeeTable.push_back(followee);
	}

	void Follows::insertToFollowerStarTable(set<int> followerStar){
		followerStarTable.push_back(followerStar);
	}

	void Follows::insertToFolloweeStarTable(set<int> followeeStar){
		followeeStarTable.push_back(followeeStar);
	}

	void Follows::insertToFollowerIndexMap(pair<int,int> follower){
		followerMap.insert(follower);
	}

	void Follows::insertToFolloweeIndexMap(pair<int,int> followee){
		followeeMap.insert(followee);
	}

	int Follows::getFolloweeIndexMapSize(){

		return followeeMap.size();
	}

	int Follows::getFollowerIndexMapSize(){
		
		return followerMap.size();
	}
