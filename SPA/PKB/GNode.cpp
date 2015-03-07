#include "GNode.h"


GNode::GNode(int i, string type) {


	stmtNum = i;
	nodeType =type;

	this->nextArr.push_back(NULL);
	this->nextArr.push_back(NULL);

	this->prevArr.push_back(NULL);
	this->prevArr.push_back(NULL);
		
}



vector<shared_ptr<GNode>> GNode::getAssociateNode(bool isNext)
{
	if(isNext)
		return nextArr;
	else
		return prevArr;
}

int GNode::getStmtNum(){
	return this->stmtNum;
}

string GNode::getASTNodeType(){
	return this->nodeType;
}

vector<shared_ptr<GNode>> GNode::getNextArr(){
	return nextArr;
}

vector<shared_ptr<GNode>> GNode::getPrevArr(){
	return prevArr;
}

void GNode::setPrevArr(int i ,shared_ptr<GNode> GNode){
	prevArr[i] = GNode;
}

void GNode::setNextArr(int i , shared_ptr<GNode> GNode){
	nextArr[i] = GNode;
}



shared_ptr<GNode> GNode::createNode(int stmtNum, string type)
{	
	shared_ptr<GNode> node = std::make_shared<GNode>(stmtNum, type);
	return node;
}