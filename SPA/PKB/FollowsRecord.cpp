#include "FollowsRecord.h" 

using namespace std;

FollowsRecord::FollowsRecord(int stmt1, int stmt2){
	this->stmt1 = stmt1;
	this->stmt2 = stmt2;
}

int FollowsRecord::getFollower(){
	return stmt2;
}
	
int FollowsRecord::getFollowee(){
	return stmt1;
}