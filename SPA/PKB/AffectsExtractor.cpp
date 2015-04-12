
#include "AffectsExtractor.h"

using namespace std;

AffectsExtractor::AffectsExtractor(){
}

AffectsExtractor::AffectsExtractor(Modifies* modifies,Uses* uses,NextExtractor* nextExtractor ,VarTable* varTable, StatementTable* stmtTable ,Calls* callTable ){
	this->modifies = modifies;
	this->nextExtractor = nextExtractor;
	this->uses = uses ;
	this->varTable = varTable;
	this->stmtTable = stmtTable;
	this->calls = callTable;
}

AffectsExtractor::~AffectsExtractor() {

}

bool AffectsExtractor::isAffects(int progLine1 , int progLine2) 
{

	std::map<int,bool> checker;
	std::queue<shared_ptr<GNode>> queue;

	map<int,std::shared_ptr<GNode>> nodeMap = nextExtractor->getNodeMap();
	std::map<int, shared_ptr<GNode>>::iterator it;
	it = nodeMap.find(progLine1);

	int modifiedVar = getVarModifiedByStmt(progLine1);
	if(it == nodeMap.end()) {	
		return false;
	} else { 

		queue = addToQueue(it->second, checker, queue);
		
	}
	return isAffectProcess(progLine2 , modifiedVar , checker , queue);

}


set<int> AffectsExtractor::getAffects(int progLine1)
{
	checkerAffects.clear();
	std::queue<shared_ptr<GNode>> queue ;
	getAffectResultSet.clear();

	map<int,std::shared_ptr<GNode>> nodeMap = nextExtractor->getNodeMap();
	std::map<int, shared_ptr<GNode>>::iterator it = nodeMap.find(progLine1);
	int modifiedVar = getVarModifiedByStmt(progLine1);
	
	if(it == nodeMap.end()) {
		return getAffectResultSet;
	} else { 

		queue =addToQueue(it->second, checkerAffects, queue);

	}
	return getAffectProcess( modifiedVar , NULL , queue);

}

set<int> AffectsExtractor::getAffectsBy(int progLine2) 
{
	
	std::queue<shared_ptr<GNode>> queue ;
	getAffectByResultSet.clear();
	map<int,std::shared_ptr<GNode>> nodeMap = nextExtractor->getNodeMap();
	std::map<int, shared_ptr<GNode>>::iterator it;
	it = nodeMap.find(progLine2);
	set<int> usesVarSet = getVarUsesByStmt(progLine2);

	
	for (std::set<int>::iterator usesVarIndex=usesVarSet.begin(); usesVarIndex!=usesVarSet.end(); ++usesVarIndex){

		if(it == nodeMap.end()) {	
			return getAffectByResultSet;
		} else { 

			queue = addToByQueue(it->second , checkerAffectsBy, queue);

		}
		getAffectByProcess( *usesVarIndex , NULL , queue, getAffectByResultSet.size()); 

		checkerAffectsBy.clear();
		std::queue<shared_ptr<GNode>> newQueue;
		queue = newQueue;
	}
	return getAffectByResultSet;

}



bool AffectsExtractor::isAffectProcess(int progLine2, int modifiedVar,std::map<int,bool> checker,std::queue<shared_ptr<GNode>> queue){

	while (!queue.empty()) {

		shared_ptr<GNode> progLineNode = queue.front();
		queue.pop();

		string nodeType = progLineNode->getASTNodeType();

		if(nodeType == "ASSIGN_NODE"){

			checker.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));	

			if (progLineNode->getStmtNum() == progLine2){ 

				if (uses->evaluateIsUsesStmt(progLineNode->getStmtNum() , modifiedVar)) {
					return true;
				} else {
					return false;
				}

			} else { 
				if (modifies->evaluateIsModifiesStmt(progLineNode ->getStmtNum() , modifiedVar)) { 
					return false;

				} else { 
					queue =addToQueue(progLineNode, checker, queue);
				} 
			}

			return isAffectProcess(progLine2 , modifiedVar , checker, queue);
								  } 

		else if (nodeType == "WHILE_NODE") {

			vector<shared_ptr<GNode>> tempVec= progLineNode->getNextArr();

			if (tempVec[0] != NULL && tempVec[1] != NULL) { 

				bool isNotWithinLoop = isNotWithinWhileLoop(progLineNode , progLine2);

				if (isNotWithinLoop) { 
					if (!checker.count(tempVec[1]->getStmtNum())) { 
						queue.push(tempVec[1]);
						checker.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));	
					}
				} else { 
					if (!checker.count(tempVec[0]->getStmtNum())){
						queue.push(tempVec[0]);
					}
				}
			} else { 
				if (!checker.count(tempVec[0]->getStmtNum())){
					queue.push(tempVec[0]);
				}


			}
			return isAffectProcess(progLine2 , modifiedVar , checker, queue);
								 } 

			else if (nodeType == "IF_NODE") {

			checker.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));

			map<int, shared_ptr<GNode>> lastIfNode = nextExtractor->getLastIfNode();
			std::map<int, shared_ptr<GNode>>::iterator it;
			it = lastIfNode.find(progLineNode->getStmtNum());

			if(it == lastIfNode.end()) {	
				return false;
			} else {

				vector<shared_ptr<GNode>> resultVec= it->second->getPrevArr(); 
				set<int> resultLessSet;
				resultLessSet = getPrevResultSet(resultVec , resultLessSet);

				vector<shared_ptr<GNode>> tempVec= progLineNode->getNextArr(); 

				bool isNotWithin = isNotWithinIf(resultLessSet , progLine2 , progLineNode->getStmtNum());

				if (isNotWithin){ 

					std::queue<shared_ptr<GNode>> queueIf;  
					std::queue<shared_ptr<GNode>> queueElse;  

					queueIf.push(tempVec[0]);
					queueElse.push(tempVec[1]);

					bool isModifiedIf = isModified(progLine2, queueIf , it->second, modifiedVar , checker );
					bool isModifiedElse = isModified(progLine2, queueElse , it->second, modifiedVar , checker);

					if (isModifiedIf && isModifiedElse){ 
						return false;
					} else {
						queue = addToQueue(it->second, checker, queue); 
					}


				} else if (progLine2 < tempVec[1]->getStmtNum()){ 

					if (!checker.count(tempVec[0]->getStmtNum())){

						queue.push(tempVec[0]);
				
					}

					return isAffectProcess(progLine2 , modifiedVar , checker, queue);

				}

				else if (progLine2 >= tempVec[1]->getStmtNum()){ 

					if (!checker.count(tempVec[1]->getStmtNum())){

						queue.push(tempVec[1]);
					
					}

					return isAffectProcess(progLine2 , modifiedVar , checker, queue);
				} 

			}

			return isAffectProcess(progLine2 , modifiedVar , checker, queue);
							  } 

			else if (nodeType == "EMPTY") {

			queue =addToQueue(progLineNode, checker, queue);
			return isAffectProcess(progLine2 , modifiedVar , checker, queue);
								 }

		else if (nodeType == "CALL_NODE") {

			checker.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));

			if (modifies->evaluateIsModifiesStmt(progLineNode ->getStmtNum() , modifiedVar)){
				return false; 
			} else { 
				queue =addToQueue(progLineNode, checker , queue);
			}
			return isAffectProcess(progLine2 , modifiedVar , checker, queue);
							   }
		}
	return false;
}

bool AffectsExtractor::isModified(int progLine2  , std::queue<shared_ptr<GNode>> queue , std::shared_ptr<GNode> lastIfNode , int modifiedVar , std::map<int,bool> checker){ 

	while (!queue.empty()){

		shared_ptr<GNode> progLineNode = queue.front();
		queue.pop();

	string nodeType = progLineNode->getASTNodeType();

		if(nodeType == "ASSIGN_NODE") {

			checker.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));

			if (modifies->evaluateIsModifiesStmt(progLineNode ->getStmtNum() , modifiedVar)) { 

				return true;
			} 
			else {

				vector<shared_ptr<GNode>> resultVec= progLineNode->getNextArr();

				for (unsigned i =0 ; i < resultVec.size(); i++){

					if (resultVec[i] != NULL){

						queue.push(resultVec[i]); 

					}
				}
			}
			return isModified(progLine2 , queue , lastIfNode , modifiedVar , checker);
								  } 

		else if(nodeType == "WHILE_NODE") {

			vector<shared_ptr<GNode>> tempVec= progLineNode->getNextArr();

			if (tempVec.size() == 2) { 

				queue.push(tempVec[1]);

			} else {
				if (!checker.count(tempVec[0]->getStmtNum())){

					queue.push(tempVec[0]);
				}

			}	

			return isModified(progLine2 , queue , lastIfNode , modifiedVar , checker );
								 }

		else if(nodeType == "IF_NODE"){

			checker.insert ( std::pair<int,bool>(progLineNode->getStmtNum(),true) ); 
			map<int, shared_ptr<GNode>> lastIfNode = nextExtractor->getLastIfNode();

			std::map<int, shared_ptr<GNode>>::iterator it;
			it = lastIfNode.find(progLineNode->getStmtNum());

			vector<shared_ptr<GNode>> tempVec= progLineNode->getNextArr();

			std::queue<shared_ptr<GNode>> queueIf;  
			std::queue<shared_ptr<GNode>> queueElse;  

			queueIf.push(tempVec[0]);
			queueElse.push(tempVec[1]);

			bool isModifiedIf = isModified(progLine2, queueIf , it->second, modifiedVar , checker);
			bool isModifiedElse = isModified(progLine2, queueElse ,it->second, modifiedVar , checker);

			if (isModifiedIf && isModifiedElse){ 
				return true;
			}  else {
				return false;
			} 
							  }

			else if(nodeType == "CALL_NODE"){

			checker.insert ( std::pair<int,bool>(progLineNode->getStmtNum(),true) );

			int procIndex = stmtTable->getTNode((progLineNode->getStmtNum()))->getProcIndex(); // may be wrong need to get procindex of caller

			if (modifies->evaluateIsModifiesProc(procIndex , modifiedVar)){
				return true;
			} else {

				vector<shared_ptr<GNode>> resultVec= progLineNode->getNextArr();

				for (unsigned i =0 ; i < resultVec.size(); i++){

					if (resultVec[i] != NULL){
						if (!checker.count(resultVec[i]->getStmtNum())){
							queue.push(resultVec[i]); 
						}
					}
				}
			}
			return isModified(progLine2 , queue , lastIfNode , modifiedVar , checker );
							   } 

		else if(nodeType == "EMPTY"){

			if (lastIfNode == progLineNode){
				return false;
			}

			vector<shared_ptr<GNode>> resultVec= progLineNode->getNextArr();

			for (unsigned i =0 ; i < resultVec.size(); i++){

				if (resultVec[i] != NULL){
					if (!checker.count(resultVec[i]->getStmtNum())){
						queue.push(resultVec[i]); 
					}
				}
			}
			return isModified(progLine2 , queue , lastIfNode , modifiedVar , checker );
								}
		}
	return false;
}

set<int> AffectsExtractor::getAffectProcess(int modifiedVar, shared_ptr<GNode> lastNodeOfIF, std::queue<shared_ptr<GNode>> queue) {

	while (!queue.empty()) {

		shared_ptr<GNode> progLineNode = queue.front();
		queue.pop();

		string nodeType = progLineNode->getASTNodeType();

		if(nodeType == "ASSIGN_NODE") {

			checkerAffects.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));	
			if (uses->evaluateIsUsesStmt(progLineNode->getStmtNum() , modifiedVar)) {
				getAffectResultSet.insert(progLineNode->getStmtNum());
			} 		
			if (modifies->evaluateIsModifiesStmt(progLineNode->getStmtNum() , modifiedVar)) {
				if (getAffectResultSet.size() == 0){
					set<int> emptySet ;
					return emptySet;
				} else {
					return getAffectResultSet ;
				}
			} 
			
			queue =addToQueue(progLineNode, checkerAffects, queue);

			return getAffectProcess(modifiedVar , lastNodeOfIF , queue);
		} 

		else if(nodeType == "WHILE_NODE") {

			vector<shared_ptr<GNode>> tempVec= progLineNode->getNextArr();

			if (tempVec[0] != NULL && tempVec[1] !=NULL) {

				if (uses->evaluateIsUsesStmt(progLineNode->getStmtNum() , modifiedVar)){
					if (!checkerAffects.count(tempVec[0]->getStmtNum())){
						queue.push(tempVec[0]);
						getAffectProcess( modifiedVar,lastNodeOfIF , queue);
						queue.pop();
					}
				}
				queue.push(tempVec[1]);
				checkerAffects.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));	

			} else { 

				if (!checkerAffects.count(tempVec[0]->getStmtNum())){
					queue.push(tempVec[0]);
				}
			}

			return getAffectProcess(modifiedVar , lastNodeOfIF , queue);

		} 

		else if(nodeType == "IF_NODE") {

			checkerAffects.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));	

			map<int, shared_ptr<GNode>> lastIfNode = nextExtractor->getLastIfNode();
			std::map<int, shared_ptr<GNode>>::iterator it;
			it = lastIfNode.find(progLineNode->getStmtNum());

			if(it == lastIfNode.end()) {	
				return getAffectResultSet ;
			} else {

				vector<shared_ptr<GNode>> tempVec= progLineNode->getNextArr(); 
				
				if (uses->evaluateIsUsesStmt(progLineNode->getStmtNum(), modifiedVar)){ 
						
					set<int> leftSet ; 
					set<int> rightSet ; 

					if (!checkerAffects.count(tempVec[0]->getStmtNum())){
						queue.push(tempVec[0]);
						
						leftSet = getAffectProcess( modifiedVar , it->second , queue);
						queue.pop();
					}

					
					if (!checkerAffects.count(tempVec[1]->getStmtNum())){
						queue.push(tempVec[1]); 
						
						rightSet = getAffectProcess( modifiedVar , it->second ,  queue);
						queue.pop();
					}			

					if (leftSet.size() > 0 && rightSet.size() > 0){ 

						return getAffectResultSet ;
					} else {
						queue =	addToQueue(it->second, checkerAffects, queue);
					}

				} else { 
					std::queue<shared_ptr<GNode>> queueIf;  
					std::queue<shared_ptr<GNode>> queueElse;  

					queueIf.push(tempVec[0]);
					queueElse.push(tempVec[1]);

					bool isModifiedIf = isModified(-1 , queueIf , it->second , modifiedVar , checkerAffects);
					bool isModifiedElse = isModified(-1 , queueElse , it->second , modifiedVar , checkerAffects);

					if (isModifiedIf && isModifiedElse){ 
						 return getAffectResultSet ;
					}  else {
						queue =	addToQueue(it->second, checkerAffects, queue);
					} 

				}
			}

			return getAffectProcess(modifiedVar, lastNodeOfIF, queue);
		}
		else if(nodeType == "EMPTY") {

			if (lastNodeOfIF == progLineNode){

				set<int> emptySet;
				return emptySet;
			}

			vector<shared_ptr<GNode>> resultVec= progLineNode->getNextArr();

			for (unsigned i =0 ; i < resultVec.size(); i++){

				if (resultVec[i] != NULL){
					if (!checkerAffects.count(resultVec[i]->getStmtNum())){
						queue.push(resultVec[i]); 
					}
				}
			}

			return getAffectProcess(modifiedVar , lastNodeOfIF ,  queue);
		}

			else if(nodeType == "CALL_NODE") {

			checkerAffects.insert(std::pair<int, bool>(progLineNode->getStmtNum(), true));
			
			if (modifies->evaluateIsModifiesStmt(progLineNode ->getStmtNum() , modifiedVar)){
					if (getAffectResultSet.size() == 0){
						set<int> itemSet ;
						return itemSet;
					} else {
						return getAffectResultSet;
					}

				} else { 
					queue =addToQueue(progLineNode, checkerAffects, queue);

				}
			}
			return getAffectProcess(modifiedVar , lastNodeOfIF  , queue);
								} 
	return getAffectResultSet;
}


set<int> AffectsExtractor::getAffectByProcess(int usesVar, int ifStmt, std::queue<shared_ptr<GNode>> queue, int resultSize) {

	while (!queue.empty()) {

		shared_ptr<GNode> progLineNode = queue.front();
		queue.pop();
	
		string nodeType = progLineNode->getASTNodeType();

		if(nodeType == "ASSIGN_NODE") {

			checkerAffectsBy.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));	

			if (modifies->evaluateIsModifiesStmt(progLineNode->getStmtNum() , usesVar)) {
				getAffectByResultSet.insert(progLineNode->getStmtNum());
				return getAffectByResultSet ;

			} 

			queue =addToByQueue(progLineNode, checkerAffectsBy, queue);

			return getAffectByProcess(usesVar , ifStmt  ,queue, resultSize);
		} 

		else if(nodeType== "WHILE_NODE") {

			vector<shared_ptr<GNode>> tempVec= progLineNode->getPrevArr();

			if (modifies->evaluateIsModifiesStmt(progLineNode->getStmtNum() , usesVar)){
				if (!checkerAffectsBy.count(tempVec[1]->getStmtNum())){
					queue.push(tempVec[1]);
					getAffectByProcess(usesVar , ifStmt , queue, resultSize); 		
					queue.pop();
					}
				
			}				

			queue.push(tempVec[0]);
			checkerAffectsBy.insert(std::pair<int,bool>(progLineNode->getStmtNum(),true));	

			return getAffectByProcess(usesVar , ifStmt , queue, resultSize);

								 }

		else if(nodeType== "IF_NODE") {

			if (ifStmt == progLineNode->getStmtNum()){

				unsigned int resultSize = getAffectByResultSet.size() ;
				if ( resultSize > resultSize){
					return getAffectByResultSet;
				} else {
					set<int> emptySet;
					return emptySet;
				}
			}

			vector<shared_ptr<GNode>> resultVec= progLineNode->getPrevArr();

			for (unsigned i =0 ; i < resultVec.size(); i++){

				if (resultVec[i] != NULL){
					if (!checkerAffectsBy.count(resultVec[i]->getStmtNum())){
						queue.push(resultVec[i]); 
					}
				}
			}

			return getAffectByProcess(usesVar , ifStmt ,  queue, resultSize);
			
		}


		else if(nodeType== "EMPTY") {	

			map<shared_ptr<GNode>,int> firstIfNode = nextExtractor->getFirstIfNode();
			std::map<shared_ptr<GNode>,int>::iterator it;
			it = firstIfNode.find(progLineNode);

			if(it == firstIfNode.end()) {	
				return getAffectByResultSet ;
			} else {

				vector<shared_ptr<GNode>> tempVec= progLineNode->getPrevArr(); 
				
				if (modifies->evaluateIsModifiesStmt(it->second, usesVar)){ 
		
					bool isVisited = true;
					set<int> prevSet;
					prevSet= getPrevResultSet(progLineNode->getPrevArr() , prevSet);
					for (std::set<int>::iterator it2=prevSet.begin(); it2!=prevSet.end(); ++it2){
						if (!checkerAffectsBy.count(*it2)){
							isVisited = false;
						}
					}
					
					if (isVisited){
						return getAffectByResultSet;
					}

					set<int> leftSet ;
					set<int> rightSet ;

					if (!checkerAffectsBy.count(tempVec[0]->getStmtNum())){
						queue.push(tempVec[0]);
						leftSet = getAffectByProcess( usesVar , it->second , queue , getAffectByResultSet.size());
						queue.pop();
					}
					

					if (!checkerAffectsBy.count(tempVec[1]->getStmtNum())){
						queue.push(tempVec[1]);
						rightSet = getAffectByProcess( usesVar , it->second , queue,getAffectByResultSet.size());
						queue.pop();
					}			

					if (leftSet.size() > 0 && rightSet.size() > 0){ 

						return getAffectByResultSet ;
					} else {
						queue =addToByQueue(nextExtractor->getNodeFromMap(it->second), checkerAffectsBy, queue);
						if (!queue.empty()){
							std::map<shared_ptr<GNode>,int>::iterator it3;
							vector<shared_ptr<GNode>> temp2= progLineNode->getNextArr();
							it3 = firstIfNode.find(temp2[0]);

							if(it3 != firstIfNode.end()) {
							if (it3->second == queue.front()->getStmtNum()) { 
								set<int> emptySet;
								return emptySet;
							}
							}				
                    }
					}		
				} else { 

				queue =	addToByQueue(nextExtractor->getNodeFromMap(it->second), checkerAffectsBy, queue);			
				}
			}

			return getAffectByProcess(usesVar , ifStmt ,  queue, resultSize);
		}

		else if(nodeType== "CALL_NODE") {
			checkerAffectsBy.insert(std::pair<int, bool>(progLineNode->getStmtNum(), true));	

			if (modifies->evaluateIsModifiesStmt(progLineNode ->getStmtNum() , usesVar)){
					
					if (getAffectByResultSet.size() == 0){
						set<int> itemSet;
						itemSet.insert(0);
						return itemSet;
					} else {
						return getAffectByResultSet ;
					}

				} else { 

					queue =addToByQueue(progLineNode, checkerAffectsBy, queue);

				} 

			return getAffectByProcess(usesVar , ifStmt ,  queue, resultSize);
								}
		else if (nodeType == "PROC_NODE"){
			if(!callStack.empty()){			
				callStack.pop();
			}
			return getAffectByProcess(usesVar , ifStmt , queue, resultSize);
		}
		}
	return getAffectByResultSet;
}

/*  AFFECTS STAR */

bool AffectsExtractor::isAffectsStar(int progLine1 , int progLine2) 
{
	isAffectStarResultSet.clear();
	if (isAffects(progLine1,progLine2)) {
		return true;
	} else {
		std::map<int,bool> checker;
		std::queue<shared_ptr<GNode>> queue;

		map<int,std::shared_ptr<GNode>> nodeMap = nextExtractor->getNodeMap();
		std::map<int, shared_ptr<GNode>>::iterator it;
		it = nodeMap.find(progLine1);
		int modifiedVar = getVarModifiedByStmt(progLine1);

		if(it == nodeMap.end()) {	
			return false;
		} else { 
	
			set<int> resultSet = getAffects(progLine1);
			std::queue<int> queue;

			if (resultSet.count(0) > 0) {  
				return false; 
			}

			addToIsAffectStarSet(resultSet);	
			for (std::set<int>::iterator it=isAffectStarResultSet.begin(); it!=isAffectStarResultSet.end(); ++it){
				queue.push(*it);
			}

			while (!queue.empty()){

				int queueItem = queue.front();
				queue.pop();

				if (progLine2 == queueItem){
					return true;
				}

				set<int> newSet = getAffects(queueItem);

				for (std::set<int>::iterator it2=isAffectStarResultSet.begin(); it2!=isAffectStarResultSet.end(); ++it2){ //eliminate those that are in resultSet

					if (newSet.size() == 0){
						break;
					}

					if (newSet.count(*it2)){
						newSet.erase(*it2);
					}
				}

				for (std::set<int>::iterator it3=newSet.begin(); it3!=newSet.end(); ++it3){ 
					if (*it3 != 0) {  
						queue.push(*it3);
						isAffectStarResultSet.insert(*it3);
					}
				}

			}

			return false;
		}
		
	}
}

set<int> AffectsExtractor::getAffectsStar(int progLine1)
{
	std::map<int,bool> checker;
	std::queue<shared_ptr<GNode>> queue ;
	getAffectStarResultSet.clear();
	map<int,std::shared_ptr<GNode>> nodeMap = nextExtractor->getNodeMap();
	std::map<int, shared_ptr<GNode>>::iterator it;
	it = nodeMap.find(progLine1);

	int newVar = getVarModifiedByStmt(progLine1);

	if(it == nodeMap.end()) {	
		set<int> emptySet;
		return emptySet;
	} else { 
	
		set<int> resultSet = getAffects(progLine1);
		std::queue<int> queue;

		if (resultSet.count(0) > 0) {  
			return getAffectStarResultSet;  
		}

		addToAffectStarSet(resultSet);	

		for (std::set<int>::iterator it=getAffectStarResultSet.begin(); it!=getAffectStarResultSet.end(); ++it){
			queue.push(*it);
		}

		while (!queue.empty()){

			int queueItem = queue.front();
			queue.pop();

			set<int> newSet = getAffects(queueItem);

			for (std::set<int>::iterator it2=getAffectStarResultSet.begin(); it2!=getAffectStarResultSet.end(); ++it2){ //eliminate those that are in resultSet
				
				if (newSet.size() == 0){
					break;
				}

				if (newSet.count(*it2)){
					newSet.erase(*it2);
				}
			}

			for (std::set<int>::iterator it3=newSet.begin(); it3!=newSet.end(); ++it3){ 
				if (*it3 != 0) { 
					queue.push(*it3);
					getAffectStarResultSet.insert(*it3);
				}
			}

		}

	}
	
	return getAffectStarResultSet;

}

set<int> AffectsExtractor::getAffectsStarBy(int progLine2) 
{
	std::map<int,bool> checker;
	std::queue<shared_ptr<GNode>> queue ;
	getAffectStarByResultSet.clear();

	map<int,std::shared_ptr<GNode>> nodeMap = nextExtractor->getNodeMap();
	std::map<int, shared_ptr<GNode>>::iterator it;
	it = nodeMap.find(progLine2);
	
	if(it == nodeMap.end()) {	
		set<int> emptySet;
		return emptySet;
	} else { 
		
		set<int> resultSet = getAffectsBy(progLine2);
		addToAffectStarBySet(resultSet);	
		std::queue<int> queue ;
		for (std::set<int>::iterator it=getAffectStarByResultSet.begin(); it!=getAffectStarByResultSet.end(); ++it){
			queue.push(*it);
		}

		while (!queue.empty()){

			int queueItem = queue.front();
			queue.pop();

			set<int> newSet = getAffectsBy(queueItem);

			for (std::set<int>::iterator it2=getAffectStarByResultSet.begin(); it2!=getAffectStarByResultSet.end(); ++it2){ 
				
				if (newSet.size() == 0){
					break;
				}

				if (newSet.count(*it2)){
					newSet.erase(*it2);
				}
			}

			for (std::set<int>::iterator newIT=newSet.begin(); newIT!=newSet.end(); ++newIT){ //add to queue and resultSet
				
				queue.push(*newIT);
				getAffectStarByResultSet.insert(*newIT);
			}

		}
	}
	return getAffectStarByResultSet;

}


bool AffectsExtractor::isNotWithinIf(set<int> resultSet, int progLine2 , int ifStmtNum){

	for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){

		if (progLine2 > ifStmtNum && progLine2 <= *it){

			return false;
		}			
	}
	return true;

}

bool AffectsExtractor::isNotWithinWhileLoop(shared_ptr<GNode> whileNode , int progLine2){

	vector<shared_ptr<GNode>> prevArray= whileNode->getPrevArr();

	if (prevArray[1]->getASTNodeType() == "WHILE_NODE"){

		if (progLine2 < prevArray[1]->getStmtNum()){
			return false;
		} else {
			return isNotWithinWhileLoop(prevArray[1], progLine2);
		}
	}

	set<int> resultSet ;
	resultSet = getPrevResultSet(prevArray , resultSet); 

	int endOfWhileStmt = -1;
	for (std::set<int>::iterator it=resultSet.begin(); it!=resultSet.end(); ++it){ 
		if (*it >= progLine2){
			endOfWhileStmt = *it ;
		}
	}
	if (progLine2 > whileNode->getStmtNum() && progLine2 <= endOfWhileStmt){
		return false;
	}
	return true;

}


set<int> AffectsExtractor::getPrevResultSet(vector<shared_ptr<GNode>> prevArray , set<int> result){

	for (unsigned i =0 ; i < prevArray.size(); i++){

		if (prevArray[i] != NULL){
			if (prevArray[i]->getStmtNum() == INT_MIN){
				getPrevResultSet(prevArray[i]->getPrevArr() , result);
			}else {
				result.insert(prevArray[i]->getStmtNum());
			}
		}
	}
	return result;
}

std::queue<shared_ptr<GNode>> AffectsExtractor::addToQueue(shared_ptr<GNode> progLineNode , std::map<int,bool> checker , std::queue<shared_ptr<GNode>> queue){

	vector<shared_ptr<GNode>> result= progLineNode->getNextArr();

	for (unsigned i =0 ; i < result.size(); i++){

		if (result[i] != NULL){
			if (!checker.count(result[i]->getStmtNum())){
				queue.push(result[i]); 
			}
		}
	}
	return queue;
}

std::queue<shared_ptr<GNode>> AffectsExtractor::addToByQueue(shared_ptr<GNode> progLineNode , std::map<int,bool> checker,std::queue<shared_ptr<GNode>> queue ){
	
	vector<shared_ptr<GNode>> result= progLineNode->getPrevArr();

	for (unsigned i =0 ; i < result.size(); i++){

		if (result[i] != NULL){
			if (!checker.count(result[i]->getStmtNum())){
				queue.push(result[i]);
			}
		}
	}
	return queue;
}

int AffectsExtractor::getVarModifiedByStmt(int stmt){ 
	set<int> modifiedVarSet = modifies->evaluateGetModifiedVarStmt(stmt);
	std::set<int>::iterator it=modifiedVarSet.begin();
	return *it;
}

set<int> AffectsExtractor::getVarUsesByStmt(int stmt){ 
	set<int> usesVarSet = uses->evaluateGetUsedVarStmt(stmt);
	return usesVarSet;
}

void AffectsExtractor::addToAffectStarSet(set<int> resultSet){ 
	getAffectStarResultSet.insert(resultSet.begin(),resultSet.end());
}

void AffectsExtractor::addToIsAffectStarSet(set<int> resultSet){ 
	isAffectStarResultSet.insert(resultSet.begin(),resultSet.end());
}

void AffectsExtractor::addToAffectStarBySet(set<int> resultSet){ 
	getAffectStarByResultSet.insert(resultSet.begin(),resultSet.end());
}


