#include <iostream>
#include<string>

using namespace std;

class FollowsRecord{

	private :
	
	int stmt1;
	int stmt2;
	
	public :
	
	FollowsRecord(int,int);
	int getFollower();
	int getFollowee();
};
	