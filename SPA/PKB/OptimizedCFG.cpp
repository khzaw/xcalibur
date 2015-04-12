#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <Windows.h>

#include "OptimizedCFG.h"
#include "..\Frontend\TNode.h"

// Constructor
OptimizedCFG::OptimizedCFG() {
}

// build OptimizedCFG from AST root
OptimizedCFG::OptimizedCFG(TNode* root, PKBController* pk_) {
  pk = pk_;

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
  stmtToAggNodeMap = populateAggNodeMap(firstStmtList, stmtToAggNodeMap, NULL, NULL);

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
std::map<int, AggNode*> OptimizedCFG::populateAggNodeMap(vector<TNode*> stmtList, std::map<int, AggNode*> stmtToAggNodeMap, AggNode* prevNode, AggNode* nextNode) {

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

        if (curr_ANode!=NULL && curr_ANode->getType()!="IF_NODE") { 
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
      temp->setType(type);
      stmtToAggNodeMap[currStmtNum] = temp;

      temp->addVarModifiedByThisNode(pk->modifiesTable->getModifiedVarStmt(currStmtNum));
      temp->addVarUsedByThisNode(pk->usesTable->getUsedVarStmt(currStmtNum));
        
      if (curr_ANode!=NULL && curr_ANode->getType()!="IF_NODE") { 
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
    prevNode->setNextAggNode(firstNode);
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
      stmtToAggNodeMap = populateAggNodeMap(while_stmtList, stmtToAggNodeMap, thisNode, thisNode);
    }
    else {
      if (type=="IF_NODE") {
        vector<TNode*> then_stmtList = curr_TNode->getChild(0)->getChild(0)->getChildren();
        vector<TNode*> else_stmtList = curr_TNode->getChild(1)->getChild(0)->getChildren();
        
        AggNode* nodeAfterThisNode;
        if (curr_TNode->getRightSibling()!=NULL) {
          int neighbour = curr_TNode->getRightSibling()->getStmtNum();
          nodeAfterThisNode = stmtToAggNodeMap.at(neighbour);
        }
        else nodeAfterThisNode = NULL;

        stmtToAggNodeMap = populateAggNodeMap(then_stmtList, stmtToAggNodeMap, thisNode, nodeAfterThisNode);
        stmtToAggNodeMap = populateAggNodeMap(else_stmtList, stmtToAggNodeMap, thisNode, nodeAfterThisNode);

      }
    }
  }
  
  return stmtToAggNodeMap;
}

void OptimizedCFG::printAggNodeMap() {
  AggNode* first = stmtToAggNodeMap.begin()->second;

  std::stack<AggNode*> stack_print;
  stack_print.push(first);
  std::set<AggNode*> visited_nodes;

  while (!stack_print.empty()) {
    AggNode* curr = stack_print.top(); 
    
    if (visited_nodes.find(curr)!=visited_nodes.end()) {
      cout << "already visited this node at line " << *(curr->getProgLines().begin()) << endl;
      stack_print.pop();
      continue;
    }
    else {
    visited_nodes.insert(curr);
    }
    
    stack_print.pop();

    // get lines in this node
    cout << curr->getType() << " ";
    std::set<int> lines = curr->getProgLines();
    for (std::set<int>::iterator it=lines.begin(); it!=lines.end(); it++) {
      cout << *it << " ";
    }
    cout <<endl;

    // push nextNode onto stack      
    if (!curr->getNextAggNodes().empty()) {
      set<AggNode*> next = curr->getNextAggNodes();
      for (std::set<AggNode*>::iterator it=next.begin(); it!=next.end(); it++) {
        stack_print.push(*it);
      }
    }
  }

  cout << "last line of printing " << endl;
}

bool OptimizedCFG::isAffects(int line1, int line2) {
  bool ans = false;

  // OutputDebugString("printing AggNodeMap");
  // printAggNodeMap();
  // cout << "after printing " << endl; 


  std::set<int> modified_by_line1 = pk->modifiesTable->getModifiedVarStmt(line1);
  std::set<int> used_by_line2 = pk->usesTable->getUsedVarStmt(line2);

  int common_var = *modified_by_line1.begin();
  cout << "lines: " << line1 << " " << line2 << " var: " << common_var << endl;

  // line2 doesnt use var modified by line1
  if (used_by_line2.find(common_var)==used_by_line2.end()) { return false; }
  
  // if no control flow path
  if (!isNextStar(line1, line2)) { return false; }
  
  else {

    cout << "check within containing nodes" << endl;

    // check within the nodes

    AggNode* ANode1 = stmtToAggNodeMap.at(line1);
    AggNode* ANode2 = stmtToAggNodeMap.at(line2);
  
    cout << ANode1->getType() << endl;
    
    std::set<int> lines1 = ANode1->getProgLines();
    for (std::set<int>::iterator it=lines1.begin(); it!=lines1.end(); it++) {
      cout << *it << " ";
    }
    cout<<endl;
    
    cout << ANode2->getType() << endl;
    std::set<int> lines2 = ANode2->getProgLines();
    for (std::set<int>::iterator it=lines2.begin(); it!=lines2.end(); it++) {
      cout << *it << " ";
    }
    cout<<endl;


    std::set<int> those_lines;
    // if different nodes
    if (ANode1!=ANode2) {
      std::set<int> lines_in_ANode1 = ANode1->getProgLines();
      std::set<int> lines_in_ANode2 = ANode2->getProgLines();
    
      lines_in_ANode1.erase(lines_in_ANode1.begin(), lines_in_ANode1.upper_bound(line1));
      lines_in_ANode2.erase(lines_in_ANode2.lower_bound(line2), lines_in_ANode2.end());
    
      those_lines.insert(lines_in_ANode1.begin(), lines_in_ANode1.end()); 
      those_lines.insert(lines_in_ANode2.begin(), lines_in_ANode2.end()); 
    }
    // if same node
    else {
      std::set<int> lines_in_ANode1 = ANode1->getProgLines();
      if(line2>line1) {
        lines_in_ANode1.erase(lines_in_ANode1.lower_bound(line1), lines_in_ANode1.upper_bound(line2));
        those_lines.insert(lines_in_ANode1.begin(), lines_in_ANode1.end());
      }
      else {
        those_lines.insert(lines_in_ANode1.lower_bound(line1), lines_in_ANode1.upper_bound(line2));
      }
    }

    for (std::set<int>::iterator it1=those_lines.begin(); it1!=those_lines.end(); it1++) {
      std::set<int> foo = pk->modifiesTable->getModifiedVarStmt(*it1);
      if (foo.find(common_var)!=foo.end()) {
        // flag
        cout << "returning false here" << endl;
        return false;
      }
    }
  
    
    // check in-between nodes on the path

    cout << "checking in-between nodes" << endl;
    std::stack<AggNode*> stack_;
    std::set<AggNode*> visited_nodes;
    visited_nodes.insert(ANode1);
    visited_nodes.insert(ANode2);


    // push nextNode of ANode1 onto stack
    if (!ANode1->getNextAggNodes().empty()) {
      set<AggNode*> next1 = ANode1->getNextAggNodes();
      for (std::set<AggNode*>::iterator it=next1.begin(); it!=next1.end(); it++) {
        stack_.push(*it);
      } 
    }


    while(!stack_.empty()) {
      AggNode* curr = stack_.top(); 
      if (visited_nodes.find(curr)!=visited_nodes.end()) {
        stack_.pop();
        continue;
      }
      else {
      visited_nodes.insert(curr);
      }
     
      stack_.pop();
    
      if (curr==ANode2) {
        cout << "reached node of line 2." << endl;
        break;
      }

      if (!isNextStar(*(curr->getProgLines().begin()),line2)) {
        cout << "this path no longer leads to line " << line2 << endl;
        continue;
      }


      std::set<int> modified_by_curr = curr->getVarModifiedByThisNode();
      
      cout << curr->getType() << " ";
      std::set<int> lines3 = curr->getProgLines();
      for (std::set<int>::iterator it=lines3.begin(); it!=lines3.end(); it++) {
        cout << *it << " ";
      }
      cout<<endl;


      if ( !pk->parentTable->evaluateIsParentStar(*(curr->getProgLines().begin()), line2)
        && !pk->parentTable->evaluateIsParentStar(*(curr->getProgLines().begin()), line1)
        && modified_by_curr.find(common_var)!=modified_by_curr.end()) {
        // flag
        cout << "this node does not contain either lines and it modifies var "<<common_var<<". false." << endl;
        return false;
      }


      // push nextNode onto stack      
      if (!curr->getNextAggNodes().empty()) {
        set<AggNode*> next = curr->getNextAggNodes();
        for (std::set<AggNode*>::iterator it=next.begin(); it!=next.end(); it++) {
          stack_.push(*it);
        } 
      }
    }
  }
  
  return true;
}

bool OptimizedCFG::isAffectsStar(int line1, int line2) {
  return false;
}
