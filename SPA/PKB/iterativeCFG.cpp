#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <stdexcept>

#include "iterativeCFG.h"
#include "..\Frontend\TNode.h"

iterativeCFG::iterativeCFG() {
}

bool iterativeCFG::isNext(int line1, int line2) {
	return !(AdjListFwd[line1].find(line2)==AdjListFwd[line1].end());
}

bool iterativeCFG::isPrev(int line1, int line2) {
	if (AdjListBwd[line1].find(line2)==AdjListBwd[line1].end())
		return false;
	else return true;
}

bool iterativeCFG::isNextStar(int line1, int line2) {

	// check for try/catch out_of_range exception
	try {
		AdjListFwd.at(line1);
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
				temp = AdjListFwd.at(curr);
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

bool iterativeCFG::isPrevStar(int line1, int line2) {
	return isNextStar(line2, line1);
}

set<int> iterativeCFG::getNext(int line) {
	return AdjListFwd[line];
}

set<int> iterativeCFG::getPrev(int line) {
	return AdjListBwd[line];
}

set<int> iterativeCFG::getNextStar(int line1) {
	
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
				temp = AdjListFwd.at(curr);
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

set<int> iterativeCFG::getPrevStar(int line1) {

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
				temp = AdjListBwd.at(curr);
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

// build iterativeCFG from AST root
iterativeCFG::iterativeCFG(TNode* root) {

	std::stack<TNode*> pq;

	vector<TNode*> firstStmtList = root->getChild(0)->getChildren();
	// link all children of stmtList and push them onto stack
	linkStmtList(firstStmtList);
	pushStmtListOntoStack(&pq, firstStmtList);

	// std::cout << "pushed first stmtList onto stack\n";
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

	// after all nodes have been populated and processed
	for (std::map<int, set<int>>::iterator it=AdjListFwd.begin(); it!=AdjListFwd.end(); it++) {
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
					for (std::set<int>::iterator it3=AdjListFwd[endSentinel].begin(); it3!=AdjListFwd[endSentinel].end(); it3++) {
						if (*it3<0 && visited.find(endSentinel)!=visited.end()) stack.push(*it3);
						else (*it).second.insert(*it3);
				}
			}
		}
	}
}


void iterativeCFG::addLink(int line1, int line2) {
	if (line1 != line2) {
		AdjListFwd[line1].insert(line2);
		AdjListBwd[line2].insert(line1);
	}

	// if line1 == line 2: raise error
	else std::cout << "Error! Line 1 must be different from Line 2!\n";
}

void iterativeCFG::linkStmtList(vector<TNode*> stmtList) {
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

void iterativeCFG::pushStmtListOntoStack(std::stack<TNode*>* pq, vector<TNode*> stmtList) {
	for (int i=stmtList.size()-1; i>=0; i--) {
		pq->push(stmtList.at(i));
	}
}