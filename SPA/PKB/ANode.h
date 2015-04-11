#pragma once
#include <iostream>
#include <set>

#include "..\PKB\Modifies.h"

using namespace std;

class ANode {
	public:
		ANode();
		
		// accessors
		set<int> getStatements;
		set<int> getIndexOfVarModifiedByThisNode();
		//set<pair<int, int>> getModifiesRelationships();

		// mutators
		void addStatement(int);
		void setPrevNode(ANode*);
		void setNextNode(ANode*);

	private:
		set<int> statements;
		//set<pair<int,int>> modifiesRelationships;
		
		ANode* prevNode;
		ANode* nextNode;
		
};