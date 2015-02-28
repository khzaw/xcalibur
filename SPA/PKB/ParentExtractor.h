#pragma once
#include <iostream>
#include "Parent.h"


using namespace std;

class ParentExtractor{

private:

	Parent* parent;

public:

		ParentExtractor(Parent* parent);
		ParentExtractor();
		void construct();

	//build follower/followee table
	void buildChildTable();  // done
	void buildParentTable(); // done

	//build follower/followee star table
	void buildChildStarTable();  // done
	void buildParentStarTable();  // done

	//build follower/followee index table
	void buildChildIndex(); // done
	void buildParentIndex(); // done


};
