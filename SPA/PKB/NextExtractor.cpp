
#include <algorithm>
#include <queue>

#include "ProcTable.h"
#include "AST.h"
#include "NextExtractor.h"

using namespace std;

NextExtractor::NextExtractor()
{
}

NextExtractor::NextExtractor(ProcTable* procedureTable )
{
	this->procTable = procedureTable;
	//this->calls = Calls;
	//this->statementTable = StmtTable;
}

vector<std::shared_ptr<CFG>> NextExtractor::constructCFG()
{
	int numOfProc = procTable->getSize();
	for(int i =0; i < numOfProc; i++)
	{
		//initialization for traverseAST Parameters
		TNode* curTNode = this->procTable->getASTRootNode(i); //obtain curTNode from astProcTable
		shared_ptr<GNode> curGNodeParent = std::make_shared<GNode>(0, "PROCEDURE"); //create a CFG ROOT node

		nodeMap.insert(pair<int, shared_ptr<GNode>>(curGNodeParent->getStmtNum(), curGNodeParent)); //store all stmtNum--->GNode , start with Procedure node

		shared_ptr<CFG> cfg = std::make_shared<CFG>(curGNodeParent); //create a CFG with procedure node as parameters
		shared_ptr<stack<shared_ptr<GNode>>> level = std::make_shared<stack<shared_ptr<GNode>>>(); //a stack to keep track of nodes for IF-else statement

		shared_ptr<GNode> lastNode = converseAST(cfg,curTNode->getChild(0),curGNodeParent,level); //conversing start with node below procedure
		
		CFGTable.push_back(cfg);
	}
	return CFGTable;
}


std::shared_ptr<GNode> NextExtractor::converseAST(shared_ptr<CFG> cfg,TNode* curTNode, shared_ptr<GNode> curGNodeParent, shared_ptr<stack<shared_ptr<GNode>>> level)
{
	if (curTNode == NULL){
		return curGNodeParent;
	}
	string nodeType = curTNode->getNodeType();
	
		//ignore procedure and stmtlst TNode
	if (nodeType == "STMTLST_NODE") {
		return converseAST(cfg,  curTNode->getChild(0),curGNodeParent,level);
							   }						   
	else if(nodeType=="PROC_NODE") {
		return converseAST(cfg, curTNode->getChild(0),curGNodeParent,level);
								 }
	else if(nodeType=="THEN_NODE"){
		return converseAST(cfg ,curTNode->getChild(0), curGNodeParent, level);
						   }
	else if(nodeType=="ELSE_NODE"){
		return converseAST(cfg ,curTNode->getChild(0), curGNodeParent, level);
						   }
	else if(nodeType=="ASSIGN_NODE"){
		shared_ptr<GNode> gNode = setlink(cfg, curTNode, curGNodeParent, level);
		return converseAST(cfg ,  curTNode->getRightSibling(), gNode, level);

							 }
	else if(nodeType=="CALL_NODE"){
		shared_ptr<GNode> gNode = setlink(cfg, curTNode, curGNodeParent, level);
		return converseAST(cfg , curTNode->getRightSibling(), gNode, level);
						   }

	else if(nodeType=="IF_NODE"){
		shared_ptr<GNode> gNode = setlink(cfg, curTNode, curGNodeParent, level);
		level->push(gNode);
		converseAST(cfg ,  curTNode->getChild(0), gNode, level); // converse then node
		gNode = converseAST(cfg, curTNode->getChild(0)->getRightSibling(), gNode, level); // converse else node
		nodeMap.insert(pair<int, shared_ptr<GNode>>(gNode->getStmtNum(), gNode));

		if(lastIfWhileStmtStack.size() > 0 && lastIfWhileStmtStack.top().second == curTNode){

			TNode* curTNodeParent =  curTNode->getParent();
			string curTNodeType = curTNode->getNodeType();

			//this is for while-if code
			if(curTNodeParent->getNodeType() == "STMTLST_NODE" && curTNodeParent->getParent()->getData().compare("while") == 0)
			{
				cfg->setNext(gNode, level->top());
				level->pop();
			}

			//this is for if-if-LEFT code
			else if(curTNodeParent->getNodeType() == "STMTLST_NODE" && curTNodeParent->getParent()->getData().compare("then") == 0)
			{
				cout << "test" << endl;
				shared_ptr<GNode> nextG = make_shared<GNode>(INT_MIN, "EMPTY");
				lastIfNode.insert(pair<int,shared_ptr<GNode>>(level->top()->getStmtNum(), nextG));
				firstIfNode.insert(pair<shared_ptr<GNode> ,int>(nextG , level->top()->getStmtNum()));
				cfg->setNext(gNode,nextG);
				level->pop();
				level->push(nextG);
			}

			//this is for if-if-RIGHT code
			else if(curTNodeParent->getNodeType() =="STMTLST_NODE" && curTNodeParent->getParent()->getData().compare("else") == 0)
			{
				shared_ptr<GNode> nextG = level->top();
				cfg->setNext(gNode,level->top());
				level->pop();
				lastIfWhileStmtStack.pop();
				return nextG;
			}

			
			lastIfWhileStmtStack.pop();
			return gNode;
		}
		else
		{
			return converseAST(cfg,curTNode->getRightSibling(),gNode,level);//recursive !! curG is the empty node
		}
						 }

	else if(nodeType=="WHILE_NODE")
		{
			shared_ptr<GNode> gNode = setlink(cfg, curTNode, curGNodeParent, level);
			level->push(gNode);
			converseAST(cfg, curTNode->getChild(0), gNode, level); //converse while node

			if(lastIfWhileStmtStack.size() > 0 && lastIfWhileStmtStack.top().second == curTNode){

				TNode* curTNodeParent = curTNode->getParent();
				string curTNodeType = curTNode->getNodeType();

				//this is for while-while
				if(curTNodeParent->getNodeType() == "STMTLST_NODE" && curTNodeParent->getParent()->getData().compare("while") == 0) 
				{
					cfg->setNext(gNode, level->top());
					level->pop();
				}

				//this is for if-while-LEFT code
				else if(curTNodeParent->getNodeType() == "STMTLST_NODE" && curTNodeParent->getParent()->getData().compare("then") == 0)
				{
					shared_ptr<GNode> nextG = make_shared<GNode>(INT_MIN, "EMPTY");
					lastIfNode.insert(pair<int,shared_ptr<GNode>>(level->top()->getStmtNum(), nextG));
					firstIfNode.insert(pair<shared_ptr<GNode>,int>(nextG , level->top()->getStmtNum()));
					cfg->setNext(gNode,nextG);
					level->pop();
					level->push(nextG);
				}

				//this is for if-while-RIGHT code
				else if(curTNodeParent->getNodeType() == "STMTLST_NODE" && curTNodeParent->getParent()->getData().compare("else") == 0)
				{
					shared_ptr<GNode> nextG = level->top();
					cfg->setNext(gNode,level->top());
					level->pop();
					lastIfWhileStmtStack.pop();
					return nextG;
				}

				lastIfWhileStmtStack.pop();
				return gNode;
			}
			else
			{
				return converseAST(cfg,curTNode->getRightSibling(),gNode,level);//recurTNodesive
			}
		}else{
	return NULL;
	}
}


// setlink is to connect the curTNodeParent and the gNode node as well as check whether it is the last statement so as to link back to the head node(while or if)
// level to store while and if info
shared_ptr<GNode> NextExtractor::setlink(shared_ptr<CFG> cfg, TNode* curTNode, shared_ptr<GNode> curGNodeParent, shared_ptr<stack<shared_ptr<GNode>>> level)
{
	shared_ptr<GNode> gNode = std::make_shared<GNode> (curTNode->getStmtNum(), curTNode->getNodeType()); 
	nodeMap.insert(pair<int, shared_ptr<GNode>>(gNode->getStmtNum(), gNode));
	bool success = cfg->setNext(curGNodeParent,gNode);

	if(!success) // while loop with only one statement if or nest if
	{
		shared_ptr<GNode> temp = curGNodeParent->getNextArr()[0];
		cfg->removeNext(curGNodeParent,temp);
		cfg->setNext(level->top(),temp);
		cfg->setNext(curGNodeParent,gNode);
	}

	// Below is to link back to the While-GNode or If-GNode after setlink the curTNodeParent and gNode GNode
	if(level->size() > 0 && isLastStmt(curTNode))
	{
		//if it is the only while without any nested if-else or while statement
		if(level->top()->getASTNodeType() == "WHILE_NODE")//while
		{
			cfg->setNext(gNode, level->top());
			level->pop();
		}
		else if(level->top()->getASTNodeType() == "IF_NODE")//if
		{
			shared_ptr<GNode> nextG = make_shared<GNode>(INT_MIN, "EMPTY");//temp set as empty
			lastIfNode.insert(pair<int,shared_ptr<GNode>>(level->top()->getStmtNum(), nextG)); //statemnt of If ---> end of its node
			firstIfNode.insert(pair<shared_ptr<GNode> ,int>(nextG , level->top()->getStmtNum()));//statemnt of end of its node ---> if
			level->pop();
			level->push(nextG);
			cfg->setNext(gNode,level->top()); // curTNode -> empty

		}
		else if(level->top()->getASTNodeType() == "EMPTY")//else or recurTNodesive if
		{
			shared_ptr<GNode> nextG = level->top();
			//nextG->stmtNum = 0 - nextG->stmtNum;
			cfg->setNext(gNode, nextG);// curTNode -> empty
			if(nextG->getPrevArr()[0] != NULL && nextG->getPrevArr()[1] != NULL)			
				level->pop();

			return nextG;
		}
	}
	return gNode;
}

//return true if node is last statement of a node
bool NextExtractor::isLastStmt(TNode* curTNode){
    if(curTNode->getRightSibling() == NULL) 	
   {
		if(curTNode->getNodeType() == "IF_NODE")
		{
			//traverse IF node and get last statement
			TNode* lastTNodeStmt = getLastRightSibling(curTNode);
			lastIfWhileStmtStack.push(pair<TNode*, TNode*>(lastTNodeStmt, curTNode)); //store right sibiling of IF node stmt
			return false;
		}
		else if(curTNode->getNodeType() == "WHILE_NODE")
		{
			//traverse WHILE node and get last statement
			TNode* lastTNodeStmt = getLastRightSibling(curTNode);
			lastIfWhileStmtStack.push(pair<TNode*, TNode*>(lastTNodeStmt, curTNode)); //store last statement of WHILE node
			return false;
		}
		return true;
	}
	return false;
}


TNode* NextExtractor::getLastRightSibling(TNode* curTNode){

	if (curTNode->getRightSibling() != NULL){
		return getLastRightSibling( curTNode->getRightSibling());
	}

	else if ( curTNode->getNodeType() == "ASSIGN_NODE"||
		curTNode->getNodeType() == "CALL_NODE"){

			return curTNode;
	}

	else if (curTNode->getNodeType() == "WHILE_NODE"||
		curTNode->getNodeType() == "IF_NODE" ){

			return  curTNode->getChild(0);
	}

	else if (curTNode->getNodeType() == "STMTLST_NODE" || curTNode->getNodeType() == "THEN_NODE" ||
		curTNode->getNodeType() == "ELSE_NODE" ){

			return getLastRightSibling(curTNode->getChild(0));
	}

	else {
		return curTNode;	
	}
}


void NextExtractor::construct()
{
	CFGTable = constructCFG();
}


bool NextExtractor::isNext(int progLine1, int progLine2)
{
	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet ;
	it = nodeMap.find(progLine1);

	if(it == nodeMap.end()) {	// variable not found, return -1
		return false;
	} else {	// variable found, return its index

		vector<shared_ptr<GNode>> resultVec= it->second->getNextArr();

		resultSet = getNextResultSet(resultVec , resultSet);

		for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){

			if (*it == progLine2){
				return true;
			}
		}
		return false;

	}
}

bool NextExtractor::isPrev(int progLine1, int progLine2)
{
	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet ;
	it = nodeMap.find(progLine1);

	if(it == nodeMap.end()) {	// variable not found, return -1
		return false;
	} else {	// variable found, return its index

	vector<shared_ptr<GNode>> resultVec= it->second->getPrevArr();
		
		resultSet = getPrevResultSet(resultVec , resultSet);
		
		for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){	
			 if (*it == progLine2){
				return true;
			 }
		 }
		return false;
	}
}


set<int> NextExtractor::getNext(int progLine) {

	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet ;
	it = nodeMap.find(progLine);

	if(it == nodeMap.end()) {	// variable not found, return -1
		return resultSet;
	} else {	// variable found, return its index

		vector<shared_ptr<GNode>> resultVec= it->second->getNextArr();
		resultSet = getNextResultSet(resultVec , resultSet);
		return resultSet;
	}
}

set<int> NextExtractor::getPrev(int progLine) {

	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet ;
	it = nodeMap.find(progLine);

	if(it == nodeMap.end()) {	// variable not found, return -1
		return resultSet;
	} else {	// variable found, return its index

		vector<shared_ptr<GNode>> resultVec= it->second->getPrevArr();	 
		resultSet = getPrevResultSet(resultVec , resultSet);
		return resultSet;
	}
}

bool NextExtractor::isNextStar(int progLine1, int progLine2)
{
	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet ;

	it = nodeMap.find(progLine1);
	std::queue<int> queue;  
	std::map<int,bool> checker;

	if(it == nodeMap.end()) {	// variable not found, return -1
		return false;
	} else {	// variable found, return its index


		resultSet = getNext(progLine1);	
		 for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){
			
			queue.push(*it); //push it into the queue for conversing later
			checker.insert ( std::pair<int,bool>(*it,true)); //update next visited node				
		 }
		
		while (!queue.empty()){

			int plnum = queue.front();
			if (plnum == progLine2){
				return true;
			}
			else {
				queue.pop();

				resultSet = getNext(plnum);

				for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){

					if (!checker.count(*it)){

						queue.push(*it);
						checker.insert ( std::pair<int,bool>(*it,true) ); 

					}

				}

			}
		}
		return false;
	}
}


bool NextExtractor::isPrevStar(int progLine1, int progLine2)
{
	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet;

	it = nodeMap.find(progLine1);
	std::queue<int> queue;  
	std::map<int,bool> checker;

	if(it == nodeMap.end()) {	// variable not found, return -1
		return false;
	} else {	// variable found, return its index


		resultSet = getPrev(progLine1);
		
		 for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){
			
			queue.push(*it); //push it into the queue for conversing later
			checker.insert ( std::pair<int,bool>(*it,true)); //update next visited node
						
		 }
		while (!queue.empty()){
			int plnum = queue.front();

			if (plnum == progLine2){
				return true;
			}
			else {
				queue.pop();
				resultSet = getPrev(plnum);

				for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){

					if (!checker.count(*it)){

						queue.push(*it);
						checker.insert ( std::pair<int,bool>(*it,true) ); 
					}
				}
			}
		}
		return false;
	}
}


set<int> NextExtractor::getNextStar(int progLine1)
{
	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet;
	it = nodeMap.find(progLine1);
	std::queue<int> queue;  
	std::map<int,bool> checker;

	if(it == nodeMap.end()) {	// variable not found, return -1
		return resultSet;
	} else {	// variable found, return its index


		resultSet = getNext(progLine1);
		
		 for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){		
			 checker.insert(std::pair<int,bool>(*it,true));
			 queue.push(*it);
		 }
		while (!queue.empty()){

			int plnum = queue.front();

			queue.pop();
			resultSet = getNext(plnum);

			for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){

				if (!checker.count(*it)){
					queue.push(*it);
					checker.insert ( std::pair<int,bool>(*it,true) ); 
				}
			}
		}

		resultSet.clear();

		for (std::map<int,bool>::iterator it=checker.begin(); it!=checker.end(); ++it){
			resultSet.insert(it->first);
		}

		return resultSet;
	}
}

set<int> NextExtractor::getPrevStar(int progLine1)
{
	std::map<int, shared_ptr<GNode>>::iterator it;
	set<int> resultSet;

	it = nodeMap.find(progLine1);
	std::queue<int> queue;  
	std::map<int,bool> checker;

	if(it == nodeMap.end()) {	// variable not found, return -1
		return resultSet;
	} else {	// variable found, return its index

		
		resultSet = getPrev(progLine1);
		
		 for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){
			
			 checker.insert(std::pair<int,bool>(*it,true));
			 queue.push(*it);

		 }
		 
		while (!queue.empty()){

			int plnum = queue.front();

			queue.pop();
			resultSet = getPrev(plnum);

			for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){
				if (!checker.count(*it) && *it > 0){
					queue.push(*it);
					checker.insert ( std::pair<int,bool>(*it,true) ); 
				}
			}
		}

		resultSet.clear();

		for (std::map<int,bool>::iterator it=checker.begin(); it!=checker.end(); ++it){
			resultSet.insert(it->first);
		}

		return resultSet;
	}
}

set<int> NextExtractor::getNextResultSet(vector<shared_ptr<GNode>> nextArray , set<int> result){

	for (unsigned i =0 ; i < nextArray.size(); i++){

		if (nextArray[i] != NULL){

			if (nextArray[i]->getStmtNum() == INT_MIN){ //this only occurs for if else empty node at the end

				getNextResultSet(nextArray[i]->getNextArr() , result);
								
			}else {

				result.insert(nextArray[i]->getStmtNum());
			}
		}
	}

	return result;
}

set<int> NextExtractor::getPrevResultSet(vector<shared_ptr<GNode>> prevArray , set<int> result){

	for (unsigned i =0 ; i < prevArray.size(); i++){

		if (prevArray[i] != NULL){

			if (prevArray[i]->getStmtNum() == INT_MIN){ //this only occurs for if else empty node at the end

				getPrevResultSet(prevArray[i]->getPrevArr() , result);
								
			}else {

				result.insert(prevArray[i]->getStmtNum());
			}
		}
	}

	return result;
}

map<int,std::shared_ptr<GNode>> NextExtractor::getNodeMap(){
	return this->nodeMap ;
}

map<int,std::shared_ptr<GNode>> NextExtractor::getLastIfNode(){
	return this->lastIfNode ;
}

map<std::shared_ptr<GNode>,int> NextExtractor::getFirstIfNode(){
	return this->firstIfNode ;
}

std::shared_ptr<GNode> NextExtractor::getNodeFromMap(int progLineNum){

	std::map<int , shared_ptr<GNode>>::iterator it;
	it = nodeMap.find(progLineNum);

	return it->second;

}