#include <map>
#include <set>
#include <vector>
#include <stack>
#include <queue>
#include <iostream>
#include <stdexcept>

#include "iterativeCFG.h"
#include "..\Frontend\TNode.h"

CFG::CFG() {
}

bool CFG::isNext(int line1, int line2) {
	set<int> next = AdjListFwd[line1];
	std::stack<int> stack; set<int> visited;

	// end of flow case
	if (next.empty()) return false;

	else {
		// handle endSentinel neighbour of line1
		for (std::set<int>::iterator it=next.begin(); it!=next.end(); it++) {
			if (*it<0) stack.push(*it);
		}
		// by enqueuing all positive neighbours of endSentinels
		
		while (!stack.empty()) {
			int endSentinel = stack.top(); stack.pop(); visited.insert(endSentinel);
				for (std::set<int>::iterator it=AdjListFwd[endSentinel].begin(); it!=AdjListFwd[endSentinel].end(); it++) {
					if (*it<0 && visited.find(endSentinel)!=visited.end()) stack.push(*it);
					else next.insert(*it);
			}
		}
		
		// return find result
		return !(next.find(line2)==next.end());
	}

}

bool CFG::isPrev(int line1, int line2) {
	if (AdjListBwd[line1].find(line2)==AdjListBwd[line1].end())
		return false;
	else return true;
}

set<int> CFG::getNextOf(int line) {
	return AdjListFwd[line];
}

set<int> CFG::getPrevOf(int line) {
	return AdjListBwd[line];
}

// build CFG from AST root
CFG::CFG(TNode* root) {

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
			// vector of children must be of size 3
			if (curr->getChildren().size()!=3 ) {
				break; cout << "Error! If node has not exactly 3 children.  ";
			}
			if (curr->getChild(1)->getNodeType() != "STMTLIST_NODE"
				||curr->getChild(2)->getNodeType() != "STMTLIST_NODE") {
					break; cout << "Missing STMTLIST_NODE.  ";
			}

			// std::cout << "in if-node\n";

			// get if-else stmtLists
			vector<TNode*> thenStmtList = curr->getChild(1)->getChildren();
			vector<TNode*> elseStmtList = curr->getChild(2)->getChildren();

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
			// must have exaclty 2 children
			if (curr->getChildren().size()!=2 ) {
				break; cout << "Error! Vector has not only 2 children.\n";
			}
			TNode* stmtListNode = curr->getChild(1);
			if (stmtListNode->getNodeType() != "STMTLIST_NODE") {
				break; cout << "Expecting STMTLIST_NODE!";
			}
			
			// std::cout << "ín while-node\n";

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
}

bool CFG::isNextT(int line1, int line2) {

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
				cout << "Nothing after "<< curr <<". ";
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

void CFG::addLink(int line1, int line2) {
	if (line1 != line2) {
		AdjListFwd[line1].insert(line2);
		AdjListBwd[line2].insert(line1);
	}

	// if line1 == line 2: raise error
	else std::cout << "Error! Line 1 must be different from Line 2!\n";
}

void CFG::linkStmtList(vector<TNode*> stmtList) {
	for (int i=0; i<stmtList.size()-1; i++) {

		if (stmtList.at(i)->getNodeType()!="IF_NODE") {
			std::cout << "linking non-if to next neighbour. line " << stmtList.at(i)->getStmtNum() <<" to line " << stmtList.at(i+1)->getStmtNum() <<"\n";
			addLink(stmtList.at(i)->getStmtNum(), stmtList.at(i+1)->getStmtNum());
		}
		// if IF_NODE, create an END_IF sentinel (encoded as negative of stmtNum of IF_NODE)
		// link END_IF sentinel to next neighbour
		else {
			std::cout << "linking sentinel of if at line " << stmtList.at(i)->getStmtNum() <<" to next neighbour " << stmtList.at(i+1)->getStmtNum() << ".\n";
			addLink(0-stmtList.at(i)->getStmtNum(), stmtList.at(i+1)->getStmtNum());
		}
	}
}

void CFG::pushStmtListOntoStack(std::stack<TNode*>* pq, vector<TNode*> stmtList) {
	for (int i=stmtList.size()-1; i>=0; i--) {
		pq->push(stmtList.at(i));
	}
}