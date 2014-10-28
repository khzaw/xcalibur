#include <iostream>
#include <vector>
#include "ParentRecord.h"
#include <list>

using namespace std;

class Parent {

	private :
	vector<ParentRecord> records;
	list<int>recursiveChildrenStar(list<int>&,int);
	list<int>recursiveParentStar(list<int>&,int);
	
	public :
	Parent();
	void insertParent(int,int);
	list<int> getChildren(int);
	list<int> getParents(int);
	bool isParentTrue(int,int);
	list<int> getChildrenStar(int);
	list<int> getParentStar(int);
	list<int> getAllChildrenStmt();
	list<int> getAllParentStmt();
	
};