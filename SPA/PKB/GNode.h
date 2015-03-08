#pragma warning (disable: 4290)
#pragma once
#include <iostream>
#include "..\Frontend\TNode.h"


using namespace std;

class GNode {
	public:

		GNode(int, string);
		static shared_ptr<GNode> createNode(int, string);
				
		vector<shared_ptr<GNode>> getAssociateNode(bool isNext);
		
		//getter method
		int getStmtNum();
		string getASTNodeType();

		void setNextArr(int ,shared_ptr<GNode>);
		void setPrevArr(int ,shared_ptr<GNode>);

		vector<shared_ptr<GNode>> getNextArr();
		vector<shared_ptr<GNode>> getPrevArr();


	private:
		vector<shared_ptr<GNode>> nextArr;
		vector<shared_ptr<GNode>> prevArr;

		int stmtNum;
		string nodeType;
		
};

