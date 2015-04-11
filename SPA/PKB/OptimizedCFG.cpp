#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <stdexcept>


#include "OptimizedCFG.h"
#include "..\Frontend\TNode.h"

// Constructor
OptimizedCFG::OptimizedCFG() {
}

// build OptimizedCFG from AST root
OptimizedCFG::OptimizedCFG(TNode* root, PKBController* pk) {

	std::stack<TNode*> pq;

	vector<TNode*> firstStmtList = root->getChild(0)->getChildren();
	// link all children of stmtList and push them onto stack
	linkStmtList(firstStmtList);
	pushStmtListOntoStack(&pq, firstStmtList);

  // simple NextList, ds: AdjList<int>
	// DFS

  while (!pq.empty()) {
		TNode* curr = pq.top(); pq.pop();
		string type = curr->getNodeType();

		// if-else loop
		// then link stmtList of if and stmtList of else separately
		// link last child of if & else to next neighbour after if-else loop
		if (type=="IF_NODE") {
		
			// std::cout << "in if-node\n";

			// get if-else stmtLists
			vector<TNode*> thenStmtList = curr->getChild(0)->getChild(0)->getChildren();
			vector<TNode*> elseStmtList = curr->getChild(1)->getChild(0)->getChildren();

			// link IF_NODE to first child of each stmtList
			addLink(curr->getStmtNum(), thenStmtList.at(0)->getStmtNum());
			addLink(curr->getStmtNum(), elseStmtList.at(0)->getStmtNum());

			// link last stmt of each stmtList to END_IF sentinel
			addLink(thenStmtList.at(thenStmtList.size()-1)->getStmtNum(), 0-curr->getStmtNum());
			addLink(elseStmtList.at(elseStmtList.size()-1)->getStmtNum(), 0-curr->getStmtNum());

			// link then and else stmtList
			linkStmtList(thenStmtList);
			linkStmtList(elseStmtList);

			// push children onto stack
			pushStmtListOntoStack(&pq, thenStmtList);
			pushStmtListOntoStack(&pq, elseStmtList);

			// std::cout << "done with this if-node\n";
		}

		// while loop
		// link everything in stmtList 
		// last child link back to while node
		else if (type=="WHILE_NODE") {
			
			// std::cout << "ín while-node\n";

      TNode* stmtListNode = curr->getChild(0);
			vector<TNode*> stmtList = stmtListNode->getChildren();
			
			// std::cout << "a" << curr->getChildren().size() << endl;
			// std::cout << "b" << stmtListNode->getChildren().size() << endl;
			// std::cout << "c" << stmtList.size() << "\n";
			// for (int i=0; i<stmtList.size(); i++)
			// 	std::cout<< stmtList.at(i) << " ";
			// std::cout << "00\n" << endl;

			// link WHILE_NODE to first child of stmtList
			addLink(curr->getStmtNum(), stmtList[0]->getStmtNum());
			
			// link last child of stmtList to END_WHILE sentinel
			addLink(stmtList.at(stmtList.size()-1)->getStmtNum(), 0-curr->getStmtNum());
			
			// link END_WHILE sentinel back to WHILE_NODE
			addLink(0-curr->getStmtNum(), curr->getStmtNum());
			
			// link all children in stmtList
			linkStmtList(stmtList);
			// push stmtList onto stack
			pushStmtListOntoStack(&pq, stmtList);
		
			// std::cout << "done with this while-node\n";
		}

		// straightforward: assignment, call, 
		else {

		}
	}

  // end DFS


	// after all nodes have been populated and processed
  // handle end sentinels linking
	for (std::map<int, set<int>>::iterator it=NextListFwd.begin(); it!=NextListFwd.end(); it++) {
		set<int> list = (*it).second;
		std::stack<int> stack; set<int> visited;

		// end of flow case
		if (list.empty()) break;

		else {
			// handle endSentinel neighbour of line1
			for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
				if (*it2<0) stack.push(*it2);
			}
			
      // by enqueuing all positive neighbours of endSentinels
			while (!stack.empty()) {
				int endSentinel = stack.top(); stack.pop(); visited.insert(endSentinel);
					for (std::set<int>::iterator it3=NextListFwd[endSentinel].begin(); it3!=NextListFwd[endSentinel].end(); it3++) {
						if (*it3<0 && visited.find(endSentinel)!=visited.end()) stack.push(*it3);
						else (*it).second.insert(*it3);
				}
			}
		}
	}
  // end handle end sentinels linking

  // AggNode Map
  stmtToAggNodeMap = populateAggNodeMap(firstStmtList, stmtToAggNodeMap, pk, NULL, NULL);

}

// CFG construction
void OptimizedCFG::addLink(int line1, int line2) {
	if (line1 != line2) {
		NextListFwd[line1].insert(line2);
		NextListBwd[line2].insert(line1);
	}

	// if line1 == line 2: raise error
	else std::cout << "Error! Line 1 must be different from Line 2!\n";
}

void OptimizedCFG::linkStmtList(vector<TNode*> stmtList) {
	for (int i=0; i<stmtList.size()-1; i++) {

		if (stmtList.at(i)->getNodeType()!="IF_NODE") {
			// std::cout << "linking non-if to next neighbour. line " << stmtList.at(i)->getStmtNum() <<" to line " << stmtList.at(i+1)->getStmtNum() <<"\n";
			addLink(stmtList.at(i)->getStmtNum(), stmtList.at(i+1)->getStmtNum());
		}
		// if IF_NODE, create an END_IF sentinel (encoded as negative of stmtNum of IF_NODE)
		// link END_IF sentinel to next neighbour
		else {
			// std::cout << "linking sentinel of if at line " << stmtList.at(i)->getStmtNum() <<" to next neighbour " << stmtList.at(i+1)->getStmtNum() << ".\n";
			addLink(0-stmtList.at(i)->getStmtNum(), stmtList.at(i+1)->getStmtNum());
		}
	}
}

void OptimizedCFG::pushStmtListOntoStack(std::stack<TNode*>* pq, vector<TNode*> stmtList) {
	for (int i=stmtList.size()-1; i>=0; i--) {
		pq->push(stmtList.at(i));
	}
}

// Next and NextStar getters and checkers
bool OptimizedCFG::isNext(int line1, int line2) {
	return !(NextListFwd[line1].find(line2)==NextListFwd[line1].end());
}

bool OptimizedCFG::isPrev(int line1, int line2) {
	if (NextListBwd[line1].find(line2)==NextListBwd[line1].end())
		return false;
	else return true;
}

bool OptimizedCFG::isNextStar(int line1, int line2) {

	// check for try/catch out_of_range exception
	try {
		NextListFwd.at(line1);
	}
	catch (const out_of_range& e) {
		cerr << "Error. First argument invalid.\n";
	}

	// DFS at line1
	// if encounter line 2 along the way, set ans to true

	std::queue<int> pq; 
	pq.push(line1);
	std::set<int> visited, temp;
	int curr; bool ans = false;

	while (!pq.empty()) {
		curr = pq.front(); pq.pop();

		if (visited.find(curr)==visited.end()) {
			visited.insert(curr);

			if (curr==line2) { ans = true; break; }

			// try to access linked nodes, check for errors
			try {
				temp = NextListFwd.at(curr);
			}
			catch (const out_of_range& e) {
				// cout << "Nothing after "<< curr <<". ";
			}

			//cout << "exploring list at position " << curr << " " << temp.size() << " ";
			// enqueue linked nodes
			for (std::set<int>::iterator it=temp.begin(); it!=temp.end(); it++) {
				// only enqueue unvisited nodes
				if (visited.find(*it)==visited.end()) { 
					pq.push(*it); //cout << "pushed "<<*it<<" onto pq"<< endl; 
				}
			}
		}
	}

	// return answer;
	return ans;
}

bool OptimizedCFG::isPrevStar(int line1, int line2) {
	return isNextStar(line2, line1);
}

set<int> OptimizedCFG::getNext(int line) {
	return NextListFwd[line];
}

set<int> OptimizedCFG::getPrev(int line) {
	return NextListBwd[line];
}

set<int> OptimizedCFG::getNextStar(int line1) {
	
	std::stack<int> pq; 
	pq.push(line1);
	std::set<int> visited, temp, ans;
	int curr;

	while (!pq.empty()) {
		curr = pq.top(); pq.pop();

		if (visited.find(curr)==visited.end()) {
			visited.insert(curr);

			// try to access linked nodes, check for errors
			try {
				temp = NextListFwd.at(curr);
			}
			catch (const out_of_range& e) {
				// cout << "Nothing after "<< curr <<". ";
			}

			// cout << "exploring list at position " << curr << " " << temp.size() << " ";
			// enqueue linked nodes
			for (std::set<int>::iterator it=temp.begin(); it!=temp.end(); it++) {
				// insert item
				ans.insert(*it);
				
				// only enqueue unvisited nodes
				if (visited.find(*it)==visited.end()) { 
					pq.push(*it); //cout << "pushed "<<*it<<" onto pq"<< endl; 
				}
			}
		}
	}
	
	return ans;
}

set<int> OptimizedCFG::getPrevStar(int line1) {

	std::stack<int> pq; 
	pq.push(line1);
	std::set<int> visited, temp, ans;
	int curr;

	while (!pq.empty()) {
		curr = pq.top(); pq.pop();

		if (visited.find(curr)==visited.end()) {
			visited.insert(curr);

			// try to access linked nodes, check for errors
			try {
				temp = NextListBwd.at(curr);
			}
			catch (const out_of_range& e) {
				// cout << "Nothing after "<< curr <<". ";
			}

			// cout << "exploring list at position " << curr << " " << temp.size() << " ";
			// enqueue linked nodes
			for (std::set<int>::iterator it=temp.begin(); it!=temp.end(); it++) {
				// insert item
				ans.insert(*it);
				
				// only enqueue unvisited nodes
				if (visited.find(*it)==visited.end()) { 
					pq.push(*it); //cout << "pushed "<<*it<<" onto pq"<< endl; 
				}
			}
		}
	}
	
	return ans;
}

// AggNodeMap accessors
AggNode* OptimizedCFG::getAggNodeOfStmt(int line) {
    return stmtToAggNodeMap[line];
}

// recursive
std::map<int, AggNode*> OptimizedCFG::populateAggNodeMap(vector<TNode*> stmtList, std::map<int, AggNode*> stmtToAggNodeMap, PKBController* pk, AggNode* prevNode, AggNode* nextNode) {

  int first_line_of_Agg_AC_Node = -1;
  AggNode* curr_ANode = NULL;

  // iterate over all children
  for (int i=0; i<stmtList.size(); i++) {
    string type = stmtList.at(i)->getNodeType();
    int currStmtNum = stmtList.at(i)->getStmtNum();
    TNode* curr_TNode = stmtList.at(i);

    // assignment & call
    if (type=="ASSIGN_NODE" || type=="CALL_NODE") {
      if (first_line_of_Agg_AC_Node == -1) {
        AggNode* temp = new AggNode();
        temp->setType(type);
        temp->addProgLine(currStmtNum);
        temp->addVarModifiedByThisNode(pk->modifiesTable->getModifiedVarStmt(currStmtNum));
        temp->addVarUsedByThisNode(pk->usesTable->getUsedVarStmt(currStmtNum));
        stmtToAggNodeMap[currStmtNum] = temp;
        first_line_of_Agg_AC_Node = currStmtNum;

        if (curr_ANode!=NULL) { 
          curr_ANode->setNextAggNode(temp);
          temp->setPrevAggNode(curr_ANode);
        }
        curr_ANode = temp;
      }

      else {
        curr_ANode->addProgLine(currStmtNum);
        stmtToAggNodeMap[currStmtNum] = curr_ANode;
        curr_ANode->addVarModifiedByThisNode(pk->modifiesTable->getModifiedVarStmt(currStmtNum));
        curr_ANode->addVarUsedByThisNode(pk->usesTable->getUsedVarStmt(currStmtNum));
        
      }
    }

    else {
      AggNode* temp = new AggNode();
      temp->addProgLine(currStmtNum);
      stmtToAggNodeMap[currStmtNum] = temp;

      temp->addVarModifiedByThisNode(pk->modifiesTable->getModifiedVarStmt(currStmtNum));
      temp->addVarUsedByThisNode(pk->usesTable->getUsedVarStmt(currStmtNum));
        

      if (curr_ANode!=NULL) { 
        curr_ANode->setNextAggNode(temp);
        temp->setPrevAggNode(curr_ANode);
      }
      curr_ANode = temp;

      first_line_of_Agg_AC_Node = -1;
    }
  }
   
  // link first child of stmtList to prevNode
  if (prevNode!=NULL) {
    AggNode* firstNode = stmtToAggNodeMap.at(stmtList.at(0)->getStmtNum());
    prevNode->setBranchingAggNode(firstNode);
    firstNode->setPrevAggNode(prevNode);
  }
  
  // link last child of stmtList to nextNode
  if (nextNode!=NULL) {
    AggNode* lastNode = stmtToAggNodeMap.at(stmtList.at(stmtList.size()-1)->getStmtNum());
    nextNode->setPrevAggNode(lastNode);
    lastNode->setNextAggNode(nextNode);
  }

  // populate child stmtLists of container stmts
  
  for (int i=0; i<stmtList.size(); i++) {
    string type = stmtList.at(i)->getNodeType();
    int currStmtNum = stmtList.at(i)->getStmtNum();
    TNode* curr_TNode = stmtList.at(i);
    AggNode* thisNode = stmtToAggNodeMap.at(currStmtNum);

    if (type=="WHILE_NODE") {
      vector<TNode*> while_stmtList = curr_TNode->getChild(0)->getChildren();
      stmtToAggNodeMap = populateAggNodeMap(while_stmtList, stmtToAggNodeMap, pk, thisNode, thisNode);
    }
    else {
      if (type=="IF_NODE") {
        vector<TNode*> then_stmtList = curr_TNode->getChild(0)->getChild(0)->getChildren();
        vector<TNode*> else_stmtList = curr_TNode->getChild(1)->getChild(0)->getChildren();
        
        stmtToAggNodeMap = populateAggNodeMap(then_stmtList, stmtToAggNodeMap, pk, thisNode, thisNode->getNextAggNode());
        stmtToAggNodeMap = populateAggNodeMap(else_stmtList, stmtToAggNodeMap, pk, thisNode, thisNode->getNextAggNode());

      }
    }
  }
  
  return stmtToAggNodeMap;
}
