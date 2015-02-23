#pragma once
#include <iostream>
#include "Follows.h"

using namespace std;

class FollowsExtractor{

private:

	Follows* follows;

public:

		FollowsExtractor(Follows* follows);
		FollowsExtractor();
		~FollowsExtractor(void);
		void construct();

	//build follower/followee table
	void buildFollowerTable();  // done
	void buildFolloweeTable(); // done

	//build follower/followee star table
	void buildFollowerStarTable();  // done
	void buildFolloweeStarTable();  // done

	//build follower/followee index table
	void buildFollowerIndex(); // done
	void buildFolloweeIndex(); // done


};

