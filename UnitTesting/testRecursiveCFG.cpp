#include <cppunit/config/SourcePrefix.h>
#include "testRecursiveCFG.h"
#include "..\SPA\PKB\NextExtractor.h"
#include "..\SPA\PKB\AST.h"
#include "..\SPA\Frontend\TNode.h"
#include "..\SPA\PKB\ProcTable.h"
#include "..\SPA\PKB\StatementTable.h"


#include <iostream>
#include <string>

void recursiveCFGTest::setUp()
{
}

void recursiveCFGTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( recursiveCFGTest );
// method to test insertion of procedures

void recursiveCFGTest::testNoLoops(){
	
	//	manually create AST
	//	NoLoops
	//	procedure NoLoops {
	//	a = 1;
	//	b = 2;
	//	c = 3;
	//	d = 4; }

	TNode rootNode = TNode("PROC_NODE", "value", 0, 1);

	ProcTable procTable; procTable.insertASTRootNode(0, &rootNode);
	StatementTable stmtTable;

	TNode stmtListNode = TNode("STMTLIST_NODE", "value", 0, 0); stmtListNode.addParent(&rootNode); rootNode.addChild(&stmtListNode);
	TNode aNode = TNode("ASSIGN_NODE", "a", 1, 0); aNode.addParent(&stmtListNode); stmtListNode.addChild(&aNode); stmtTable.insertStatement(&aNode);
	TNode bNode = TNode("ASSIGN_NODE", "b", 2, 0); bNode.addParent(&stmtListNode); stmtListNode.addChild(&bNode); aNode.addRightSibling(&bNode); stmtTable.insertStatement(&bNode);
	TNode cNode = TNode("ASSIGN_NODE", "c", 3, 0); cNode.addParent(&stmtListNode); stmtListNode.addChild(&cNode); bNode.addRightSibling(&cNode); stmtTable.insertStatement(&cNode);
	TNode dNode = TNode("ASSIGN_NODE", "d", 4, 0); dNode.addParent(&stmtListNode); stmtListNode.addChild(&dNode); cNode.addRightSibling(&dNode); stmtTable.insertStatement(&dNode);

	//std::cout << "Constructing CFG from rootNode.\n";
	// create CFG
	NextExtractor newCFG(&procTable, &stmtTable);	
	//std::cout << "Done building CFG.\n";

	// should be true
	CPPUNIT_ASSERT(newCFG.isNext(1,2));
	CPPUNIT_ASSERT(newCFG.isNext(2,3));
	CPPUNIT_ASSERT(newCFG.isNext(3,4));

	// should be false
	CPPUNIT_ASSERT(!newCFG.isNext(1,3));

	// supposed to fail
	CPPUNIT_ASSERT(newCFG.isNext(2,4));

	return;
}

void recursiveCFGTest::testIfElseLoop(){
	//	manually create AST
	//	IfElseLoop
	//	procedure IfElseLoop {
	//		a = 1;
	//		b = 2;
	//		if (a == 1) {
	//			c = 3;
	//			d = 4;
	//		}
	//		else {
	//			e = 5;
	//			f = 6;
	//		}	
	//		g = 7; 
	//  }
	
	TNode rootNode = TNode("PROC_NODE", "value", 0, 1);

	ProcTable procTable; procTable.insertASTRootNode(0, &rootNode);
	StatementTable stmtTable;

	TNode stmtListNode = TNode("STMTLIST_NODE", "value", 0, 0); stmtListNode.addParent(&rootNode); rootNode.addChild(&stmtListNode);
	TNode aNode = TNode("ASSIGN_NODE", "a", 1, 0); aNode.addParent(&stmtListNode); stmtListNode.addChild(&aNode); stmtTable.insertStatement(&aNode);
	TNode bNode = TNode("ASSIGN_NODE", "b", 2, 0); bNode.addParent(&stmtListNode); stmtListNode.addChild(&bNode); stmtTable.insertStatement(&bNode);
	TNode ifNode = TNode("IF_NODE", "value", 3, 0); ifNode.addParent(&stmtListNode); stmtListNode.addChild(&ifNode); stmtTable.insertStatement(&ifNode);
	TNode ifVarNode = TNode("VAR_NODE", "a", 3, 0); ifVarNode.addParent(&ifNode); ifNode.addChild(&ifVarNode); 
	TNode thenNode = TNode("STMTLIST_NODE", "value", 3, 0); thenNode.addParent(&ifNode); ifNode.addChild(&thenNode);
	TNode then1Node = TNode("ASSIGN_NODE", "c", 4, 0); then1Node.addParent(&thenNode); thenNode.addChild(&then1Node); stmtTable.insertStatement(&then1Node);
	TNode then2Node = TNode("ASSIGN_NODE", "d", 5, 0); then2Node.addParent(&thenNode); thenNode.addChild(&then2Node); stmtTable.insertStatement(&then2Node);
	TNode elseNode = TNode("STMTLIST_NODE", "value", 3, 0); elseNode.addParent(&ifNode); ifNode.addChild(&elseNode);
	TNode else1Node = TNode("ASSIGN_NODE", "e", 6, 0); else1Node.addParent(&elseNode); elseNode.addChild(&else1Node); stmtTable.insertStatement(&else1Node);
	TNode else2Node = TNode("ASSIGN_NODE", "f", 7, 0); else2Node.addParent(&thenNode); elseNode.addChild(&else2Node); stmtTable.insertStatement(&else2Node);
	TNode gNode = TNode("ASSIGN_NODE", "g", 8, 0); gNode.addParent(&stmtListNode); stmtListNode.addChild(&gNode); stmtTable.insertStatement(&gNode);


	// create CFG
	//std::cout << "Creating CFG.\n";	
	NextExtractor newCFG(&procTable, &stmtTable);
	//std::cout << "Done building CFG.\n";
	
	// test basic linking
	CPPUNIT_ASSERT(newCFG.isNext(1,2));
	CPPUNIT_ASSERT(newCFG.isNext(2,3));

	// testing link from if to child
	CPPUNIT_ASSERT(newCFG.isNext(3,4));
	CPPUNIT_ASSERT(newCFG.isNext(3,6));

	// testing link from last child to if
	CPPUNIT_ASSERT(newCFG.isNext(5,8));
	CPPUNIT_ASSERT(newCFG.isNext(7,8));

	// test nextT
	CPPUNIT_ASSERT(newCFG.isNextStar(2,4));
	CPPUNIT_ASSERT(newCFG.isNextStar(2,5));
	CPPUNIT_ASSERT(newCFG.isNextStar(2,6));

	// should be false
	CPPUNIT_ASSERT(!newCFG.isNext(4,3));
	
	// supposed to fail
	CPPUNIT_ASSERT(newCFG.isNext(5,3));

	return;
}

void recursiveCFGTest::testWhileLoop() {
	//  manually create AST
	//	ProgramWithWhileLoop
	//	procedure ProgramWithWhileLoop {
	//		a = 1;
	//		b = 2;
	//		while (a < 10) {
	//			a = a + 1;
	//			c = a + 1; }
	//		d = 4; 
	//  }
		
	TNode rootNode = TNode("PROC_NODE", "value", 0, 1);
	
	ProcTable procTable; procTable.insertASTRootNode(0, &rootNode);
	StatementTable stmtTable;

	TNode stmtListNode = TNode("STMTLIST_NODE", "value", 0, 0); stmtListNode.addParent(&rootNode); rootNode.addChild(&stmtListNode);
	TNode aNode = TNode("ASSIGN_NODE", "a", 1, 0); aNode.addParent(&stmtListNode); stmtListNode.addChild(&aNode);  stmtTable.insertStatement(&aNode);
	TNode bNode = TNode("ASSIGN_NODE", "b", 2, 0); bNode.addParent(&stmtListNode); stmtListNode.addChild(&bNode);  stmtTable.insertStatement(&bNode);
	TNode whileNode = TNode("WHILE_NODE", "value", 3, 0); whileNode.addParent(&stmtListNode); stmtListNode.addChild(&whileNode); stmtTable.insertStatement(&whileNode);
	TNode whileVarNode = TNode("VAR_NODE", "a", 3, 0); whileVarNode.addParent(&whileNode); whileNode.addChild(&whileVarNode);	
	TNode whileListNode = TNode("STMTLIST_NODE", "value", 3, 0); whileListNode.addParent(&whileNode); whileNode.addChild(&whileListNode);
	TNode w1Node = TNode("ASSIGN_NODE", "a", 4, 0); w1Node.addParent(&whileListNode); whileListNode.addChild(&w1Node); stmtTable.insertStatement(&w1Node);
	TNode w2Node = TNode("ASSIGN_NODE", "c", 5, 0); w2Node.addParent(&whileListNode); whileListNode.addChild(&w2Node); stmtTable.insertStatement(&w2Node);
	TNode dNode = TNode("ASSIGN_NODE", "d", 6, 0); dNode.addParent(&stmtListNode); stmtListNode.addChild(&dNode); stmtTable.insertStatement(&dNode);
	
	// create CFG
	//std::cout << "Creating CFG.\n";
	NextExtractor newCFG(&procTable, &stmtTable);
	//std::cout << "Done building CFG.\n";

	// test basic linking
	CPPUNIT_ASSERT(newCFG.isNext(1,2));
	CPPUNIT_ASSERT(newCFG.isNext(2,3));

	// test linking while to child
	CPPUNIT_ASSERT(newCFG.isNext(3,4));
	CPPUNIT_ASSERT(newCFG.isNext(4,5));

	// test linking last child to while
	CPPUNIT_ASSERT(newCFG.isNext(5,3));

	// test NextT
	CPPUNIT_ASSERT(newCFG.isNextStar(1,4));
	CPPUNIT_ASSERT(newCFG.isNextStar(2,5));
	CPPUNIT_ASSERT(newCFG.isNextStar(4,6));
	CPPUNIT_ASSERT(newCFG.isNextStar(5,6));

	// should fail
	CPPUNIT_ASSERT(newCFG.isNext(2,5));

	return;
}

void recursiveCFGTest::testIfIfLoop() {
	//	manually create AST
	//	IfIfLoop
	//	procedure IfIfLoop {
	//		a = 1;
	//		b = 2;
	//		if (a == 1) {
	//			c = 3;
	//			if (c==3) {
	//				d = 4; 
	//				e = 5; }
	//			else { 
	//				d =	14;
	//				e = 15; }
	//			f = 6;
	//		}
	//		else {
	//			c = 23;
	//			if (c==23) {
	//				d = 24; 
	//				e = 25;}
	//			else { 
	//				d = 34;
	//				e = 35; }
	//			f = 16;
	//		}
	//		g =8 ; 
	//  }

	TNode rootNode = TNode("PROC_NODE", "value", 0, 1);

	ProcTable procTable; procTable.insertASTRootNode(0, &rootNode);
	StatementTable stmtTable;

	TNode stmtListNode = TNode("STMTLIST_NODE", "value", 0, 0); stmtListNode.addParent(&rootNode); rootNode.addChild(&stmtListNode);
	TNode aNode = TNode("ASSIGN_NODE", "a", 1, 0); aNode.addParent(&stmtListNode); stmtListNode.addChild(&aNode); stmtTable.insertStatement(&aNode);
	TNode bNode = TNode("ASSIGN_NODE", "b", 2, 0); bNode.addParent(&stmtListNode); stmtListNode.addChild(&bNode);  stmtTable.insertStatement(&bNode);
	
	TNode if1Node = TNode("IF_NODE", "value", 3, 0); if1Node.addParent(&stmtListNode); stmtListNode.addChild(&if1Node); stmtTable.insertStatement(&if1Node);
		TNode if1VarNode = TNode("VAR_NODE", "a", 3, 0); if1VarNode.addParent(&if1Node); if1Node.addChild(&if1VarNode);
		TNode then1Node = TNode("STMTLIST_NODE", "value", 3, 0); then1Node.addParent(&if1Node); if1Node.addChild(&then1Node);
			TNode c1Node = TNode("ASSIGN_NODE", "c", 4, 0); c1Node.addParent(&then1Node); then1Node.addChild(&c1Node); stmtTable.insertStatement(&c1Node);
	
			TNode if2Node = TNode("IF_NODE", "value", 5, 0); if2Node.addParent(&then1Node); then1Node.addChild(&if2Node); stmtTable.insertStatement(&if2Node);
				TNode if2VarNode = TNode("VAR_NODE", "c", 5, 0); if2VarNode.addParent(&if2Node); if2Node.addChild(&if2VarNode);
				TNode then2Node = TNode("STMTLIST_NODE", "value", 5, 0); then2Node.addParent(&if2Node); if2Node.addChild(&then2Node);
					TNode d1Node = TNode("ASSIGN_NODE", "d", 6, 0); d1Node.addParent(&then2Node); then2Node.addChild(&d1Node); stmtTable.insertStatement(&d1Node);
					TNode e1Node = TNode("ASSIGN_NODE", "e", 7, 0); e1Node.addParent(&then2Node); then2Node.addChild(&e1Node); stmtTable.insertStatement(&e1Node);
	
				TNode else2Node = TNode("STMTLIST_NODE", "value", 5, 0); else2Node.addParent(&if2Node); if2Node.addChild(&else2Node);
					TNode d2Node = TNode("ASSIGN_NODE", "d", 8, 0); d2Node.addParent(&else2Node); else2Node.addChild(&d2Node); stmtTable.insertStatement(&d2Node);
					TNode e2Node = TNode("ASSIGN_NODE", "e", 9, 0); e2Node.addParent(&else2Node); else2Node.addChild(&e2Node); stmtTable.insertStatement(&e2Node);

			TNode f1Node = TNode("ASSIGN_NODE", "f", 10, 0); f1Node.addParent(&then1Node); then1Node.addChild(&f1Node); stmtTable.insertStatement(&f1Node);

		TNode else1Node = TNode("STMTLIST_NODE", "value", 3, 0); else1Node.addParent(&if1Node); if1Node.addChild(&else1Node);
	
			TNode c2Node = TNode("ASSIGN_NODE", "c", 11, 0); c2Node.addParent(&else1Node); else1Node.addChild(&c2Node); stmtTable.insertStatement(&c2Node);
			TNode if3Node = TNode("IF_NODE", "value", 12, 0); if3Node.addParent(&else1Node); else1Node.addChild(&if3Node); stmtTable.insertStatement(&if3Node);
				TNode if3VarNode = TNode("VAR_NODE", "c", 12, 0); if3VarNode.addParent(&if3Node); if3Node.addChild(&if3VarNode);
				TNode then3Node = TNode("STMTLIST_NODE", "value", 12, 0); then3Node.addParent(&if3Node); if3Node.addChild(&then3Node);
					TNode d3Node = TNode("ASSIGN_NODE", "d", 13, 0); d3Node.addParent(&then3Node); then3Node.addChild(&d3Node); stmtTable.insertStatement(&d3Node);
					TNode e3Node = TNode("ASSIGN_NODE", "e", 14, 0); e3Node.addParent(&then3Node); then3Node.addChild(&e3Node); stmtTable.insertStatement(&e3Node);
	
				TNode else3Node = TNode("STMTLIST_NODE", "value", 12, 0); else3Node.addParent(&if3Node); if3Node.addChild(&else3Node);
					TNode d4Node = TNode("ASSIGN_NODE", "d", 15, 0); d4Node.addParent(&else3Node); else3Node.addChild(&d4Node); stmtTable.insertStatement(&d4Node);
					TNode e4Node = TNode("ASSIGN_NODE", "e", 16, 0); e4Node.addParent(&else3Node); else3Node.addChild(&e4Node); stmtTable.insertStatement(&e4Node);

			TNode f2Node = TNode("ASSIGN_NODE", "f", 17, 0); f1Node.addParent(&else1Node); else1Node.addChild(&f2Node); stmtTable.insertStatement(&f2Node);

	TNode gNode = TNode("ASSIGN_NODE", "g", 18, 0); gNode.addParent(&stmtListNode); stmtListNode.addChild(&gNode); stmtTable.insertStatement(&gNode);

	// create CFG
	//std::cout << "Creating CFG.\n";
	NextExtractor newCFG(&procTable, &stmtTable);
	//std::cout << "Done building CFG.\n";
	
	//std::cout << "testing ifif\n";
	/*
	// print out ds
	for (std::map<int, set<int>>::iterator it=newCFG.AdjListFwd.begin(); it!=newCFG.AdjListFwd.end(); it++) {
		std::cout << "for line " << (*it).first << ": ";
		set<int> list = (*it).second;
		for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << endl;
	}
	*/

	// test basic linking
	CPPUNIT_ASSERT(newCFG.isNext(1,2));

	// test if block
	CPPUNIT_ASSERT(newCFG.isNext(3,4));
	CPPUNIT_ASSERT(newCFG.isNext(5,6));
	CPPUNIT_ASSERT(newCFG.isNext(5,8));
	CPPUNIT_ASSERT(newCFG.isNext(7,10));
	CPPUNIT_ASSERT(newCFG.isNext(9,10));
	
	// test else block
	CPPUNIT_ASSERT(newCFG.isNext(3,11));
	CPPUNIT_ASSERT(newCFG.isNext(12,13));
	CPPUNIT_ASSERT(newCFG.isNext(12,15));
	CPPUNIT_ASSERT(newCFG.isNext(14,17));
	CPPUNIT_ASSERT(newCFG.isNext(16,17));
	
	CPPUNIT_ASSERT(newCFG.isNext(10,18));
	CPPUNIT_ASSERT(newCFG.isNext(17,18));

	// test NextT
	CPPUNIT_ASSERT(newCFG.isNextStar(2,18));
	
	// should fail
	CPPUNIT_ASSERT(!newCFG.isNext(1,2));
}

void recursiveCFGTest::testIfWhileLoop() {
	//	manually create AST
	//	IfWhileLoop
	//	procedure IfWhileLoop {
	//		a = 1;
	//		b = 2;
	//		if (a == 1) {
	//			c = 3;
	//			while (c < 13) {
	//			c = c + 1; }
	//			f = 6;
	//		}
	//		else {
	//			c = 23;
	//			while (c < 33) {
	//			c = c + 1; }
	//			f = 16;
	//		}
	//		g = 8 ; 
	//  }

	TNode rootNode = TNode("PROC_NODE", "value", 0, 1);

	ProcTable procTable; procTable.insertASTRootNode(0, &rootNode);
	StatementTable stmtTable;

	TNode stmtListNode = TNode("STMTLIST_NODE", "value", 0, 0); stmtListNode.addParent(&rootNode); rootNode.addChild(&stmtListNode);
	TNode aNode = TNode("ASSIGN_NODE", "a", 1, 0); aNode.addParent(&stmtListNode); stmtListNode.addChild(&aNode); stmtTable.insertStatement(&aNode);
	TNode bNode = TNode("ASSIGN_NODE", "b", 2, 0); bNode.addParent(&stmtListNode); stmtListNode.addChild(&bNode); stmtTable.insertStatement(&bNode); 
	
	TNode if1Node = TNode("IF_NODE", "value", 3, 0); if1Node.addParent(&stmtListNode); stmtListNode.addChild(&if1Node); stmtTable.insertStatement(&if1Node);
		TNode if1VarNode = TNode("VAR_NODE", "a", 3, 0); if1VarNode.addParent(&if1Node); if1Node.addChild(&if1VarNode);
		TNode then1Node = TNode("STMTLIST_NODE", "value", 3, 0); then1Node.addParent(&if1Node); if1Node.addChild(&then1Node);
			TNode c1Node = TNode("ASSIGN_NODE", "c", 4, 0); c1Node.addParent(&then1Node); then1Node.addChild(&c1Node); stmtTable.insertStatement(&c1Node);
	
			TNode while1Node = TNode("WHILE_NODE", "value", 5, 0); while1Node.addParent(&then1Node); then1Node.addChild(&while1Node); stmtTable.insertStatement(&while1Node);
				TNode while1VarNode = TNode("VAR_NODE", "c", 5, 0) ; while1VarNode.addParent(&while1Node); while1Node.addChild(&while1VarNode); 
				TNode while1ListNode = TNode("STMTLIST_NODE", "value", 5, 0); while1ListNode.addParent(&while1Node); while1Node.addChild(&while1ListNode);
					TNode c2Node = TNode("ASSIGN_NODE", "c", 6, 0); c2Node.addParent(&while1ListNode); while1ListNode.addChild(&c2Node); stmtTable.insertStatement(&c2Node);

			TNode f1Node = TNode("ASSIGN_NODE", "f", 7, 0); f1Node.addParent(&then1Node); then1Node.addChild(&f1Node); stmtTable.insertStatement(&f1Node);

		TNode else1Node = TNode("STMTLIST_NODE", "value", 3, 0); else1Node.addParent(&if1Node); if1Node.addChild(&else1Node);
	
			TNode c3Node = TNode("ASSIGN_NODE", "c", 8, 0); c3Node.addParent(&else1Node); else1Node.addChild(&c3Node); stmtTable.insertStatement(&c3Node);
			TNode while2Node = TNode("WHILE_NODE", "value", 9, 0); while2Node.addParent(&else1Node); else1Node.addChild(&while2Node); stmtTable.insertStatement(&while2Node);
				TNode while2VarNode = TNode("ASSIGN_NODE", "c", 9, 0) ; while2VarNode.addParent(&while2Node); while2Node.addChild(&while2VarNode);
				TNode while2ListNode = TNode("STMTLIST_NODE", "value", 9, 0); while2ListNode.addParent(&while2Node); while2Node.addChild(&while2ListNode);
					TNode c4Node = TNode("ASSIGN_NODE", "c", 10, 0); c4Node.addParent(&while2ListNode); while2ListNode.addChild(&c4Node); stmtTable.insertStatement(&c4Node);

			TNode f2Node = TNode("ASSIGN_NODE", "f", 11, 0); f1Node.addParent(&else1Node); else1Node.addChild(&f2Node); stmtTable.insertStatement(&f2Node);

	TNode gNode = TNode("ASSIGN_NODE", "g", 12, 0); gNode.addParent(&stmtListNode); stmtListNode.addChild(&gNode); stmtTable.insertStatement(&gNode);

	// create CFG
	//std::cout << "Creating CFG 5.\n\n\n\n\n\n";
	NextExtractor newCFG(&procTable, &stmtTable);
	//std::cout << "Done building CFG 5.\n\n";
	/*
	std::cout << "testing ifwhile\n";
	// print out ds
	for (std::map<int, set<int>>::iterator it=newCFG.AdjListFwd.begin(); it!=newCFG.AdjListFwd.end(); it++) {
		std::cout << "for line " << (*it).first << ": ";
		set<int> list = (*it).second;
		for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << endl;
	}
	*/
	// test basic linking
	CPPUNIT_ASSERT(newCFG.isNext(1,2));

	// test while in if
	CPPUNIT_ASSERT(newCFG.isNext(3,4));
	CPPUNIT_ASSERT(newCFG.isNext(4,5));
	CPPUNIT_ASSERT(newCFG.isNext(5,6));
	CPPUNIT_ASSERT(newCFG.isNext(6,5));
	CPPUNIT_ASSERT(newCFG.isNext(5,7));

	// test while in else
	CPPUNIT_ASSERT(newCFG.isNext(8,9));	
	CPPUNIT_ASSERT(newCFG.isNext(9,10));
	CPPUNIT_ASSERT(newCFG.isNext(10,9));
	CPPUNIT_ASSERT(newCFG.isNext(9,11));

	CPPUNIT_ASSERT(newCFG.isNext(7,12));
	CPPUNIT_ASSERT(newCFG.isNext(11,12));

	// should fail
	CPPUNIT_ASSERT(!newCFG.isNext(1,2));
	
}

void recursiveCFGTest::testWhileIfLoop() {
	//	manually create AST
	//	IfWhileLoop
	//	procedure IfWhileLoop {
	//		a = 1;
	//		b = 2;
	//		while (b < 10) {
	//			if (a == 1) {
	//				c = 3;
	//				d = 6;
	//			}
	//			else {
	//				c = 23;
	//				d = 16;
	//			}
	//			g = 8 ;
	//		}
	//		h = 9;
	//  }

	TNode rootNode = TNode("PROC_NODE", "value", 0, 0);
	
	ProcTable procTable; procTable.insertASTRootNode(0, &rootNode);
	StatementTable stmtTable;

	TNode stmtListNode = TNode("STMTLIST_NODE", "value", 0, 0); stmtListNode.addParent(&rootNode); rootNode.addChild(&stmtListNode);
	TNode aNode = TNode("ASSIGN_NODE", "a", 1, 0); aNode.addParent(&stmtListNode); stmtListNode.addChild(&aNode); stmtTable.insertStatement(&aNode);
	TNode bNode = TNode("ASSIGN_NODE", "b", 2, 0); bNode.addParent(&stmtListNode); stmtListNode.addChild(&bNode); stmtTable.insertStatement(&bNode);
	TNode whileNode = TNode("WHILE_NODE", "value", 3, 0); whileNode.addParent(&stmtListNode); stmtListNode.addChild(&whileNode); stmtTable.insertStatement(&whileNode);
	TNode whileVarNode = TNode("VAR_NODE", "a", 3, 0); whileVarNode.addParent(&whileNode); whileNode.addChild(&whileVarNode);	
	TNode whileListNode = TNode("STMTLIST_NODE", "value", 3, 0); whileListNode.addParent(&whileNode); whileNode.addChild(&whileListNode);
	TNode ifNode = TNode("IF_NODE", "value", 4, 0); ifNode.addParent(&whileListNode); whileListNode.addChild(&ifNode); stmtTable.insertStatement(&ifNode);
	TNode ifVarNode = TNode("VAR_NODE", "a", 3, 0); ifVarNode.addParent(&ifNode); ifNode.addChild(&ifVarNode);	
	TNode thenNode = TNode("STMTLIST_NODE", "value", 4, 0); thenNode.addParent(&ifNode); ifNode.addChild(&thenNode);
	TNode c1Node = TNode("ASSIGN_NODE", "c", 5, 0); c1Node.addParent(&thenNode); thenNode.addChild(&c1Node); stmtTable.insertStatement(&c1Node);
	TNode d1Node = TNode("ASSIGN_NODE", "d", 6, 0); d1Node.addParent(&thenNode); thenNode.addChild(&d1Node); stmtTable.insertStatement(&d1Node);
	TNode elseNode = TNode("STMTLIST_NODE", "value", 4, 0); elseNode.addParent(&ifNode); ifNode.addChild(&elseNode);
	TNode c2Node = TNode("ASSIGN_NODE", "c", 7, 0); c2Node.addParent(&elseNode); elseNode.addChild(&c2Node); stmtTable.insertStatement(&c2Node);
	TNode d2Node = TNode("ASSIGN_NODE", "d", 8, 0); d2Node.addParent(&elseNode); elseNode.addChild(&d2Node); stmtTable.insertStatement(&d2Node);
	
	TNode gNode = TNode("ASSIGN_NODE", "g", 9, 0); gNode.addParent(&whileListNode); whileListNode.addChild(&gNode); stmtTable.insertStatement(&gNode);
	TNode fNode = TNode("ASSIGN_NODE", "f", 10, 0); fNode.addParent(&stmtListNode); stmtListNode.addChild(&fNode); stmtTable.insertStatement(&fNode);
		
	// create CFG
	// std::cout << "Creating CFG 5.\n";
	NextExtractor newCFG(&procTable, &stmtTable);
	// std::cout << "Done building CFG 5.\n";

	// test basic linking
	CPPUNIT_ASSERT(newCFG.isNext(1,2));
	CPPUNIT_ASSERT(newCFG.isNext(2,3));

	// test if-else first child
	CPPUNIT_ASSERT(newCFG.isNext(3,4));
	CPPUNIT_ASSERT(newCFG.isNext(4,5));
	CPPUNIT_ASSERT(newCFG.isNext(4,7));

	// test if-else last child
	CPPUNIT_ASSERT(newCFG.isNext(6,9));
	CPPUNIT_ASSERT(newCFG.isNext(8,9));
	
	// test link from last child back to while
	CPPUNIT_ASSERT(newCFG.isNext(9,3));

	// test link from while to neighbour
	CPPUNIT_ASSERT(newCFG.isNext(3,10));

	// should fail
	CPPUNIT_ASSERT(!newCFG.isNext(1,2));
}

void recursiveCFGTest::testWhileWhileLoop() {
	//	manually create AST
	//	IfWhileLoop
	//	procedure IfWhileLoop {
	//		a = 1;
	//		b = 2;
	//		while (b < 10) {
	//			while (a < 3) {
	//				a = a + 1;
	//				b = b + 1 ;
	//			}
	//		}
	//		c = 9;
	//  }

	TNode rootNode = TNode("PROC_NODE", "value", 0, 0);
	
	ProcTable procTable; procTable.insertASTRootNode(0, &rootNode);
	StatementTable stmtTable;
	
	TNode stmtListNode = TNode("STMTLIST_NODE", "value", 0, 0); stmtListNode.addParent(&rootNode); rootNode.addChild(&stmtListNode);
	TNode aNode = TNode("ASSIGN_NODE", "a", 1, 0); aNode.addParent(&stmtListNode); stmtListNode.addChild(&aNode);  stmtTable.insertStatement(&aNode);
	TNode bNode = TNode("ASSIGN_NODE", "b", 2, 0); bNode.addParent(&stmtListNode); stmtListNode.addChild(&bNode);  stmtTable.insertStatement(&bNode);
	TNode while1Node = TNode("WHILE_NODE", "value", 3, 0); while1Node.addParent(&stmtListNode); stmtListNode.addChild(&while1Node); stmtTable.insertStatement(&while1Node);
	TNode while1VarNode = TNode("VAR_NODE", "b", 3, 0); while1VarNode.addParent(&while1Node); while1Node.addChild(&while1VarNode); 
	TNode while1ListNode = TNode("STMTLIST_NODE", "value", 3, 0); while1ListNode.addParent(&while1Node); while1Node.addChild(&while1ListNode);
	
	TNode while2Node = TNode("WHILE_NODE", "value", 4, 0); while2Node.addParent(&while1ListNode); while1ListNode.addChild(&while2Node); stmtTable.insertStatement(&while2Node);
	TNode while2VarNode = TNode("VAR_NODE", "b", 4, 0); while2VarNode.addParent(&while2Node); while2Node.addChild(&while2VarNode);
	TNode while2ListNode = TNode("STMTLIST_NODE", "value", 4, 0); while2ListNode.addParent(&while2Node); while2Node.addChild(&while2ListNode);
	
	TNode a2Node = TNode("ASSIGN_NODE", "a", 5, 0); a2Node.addParent(&while2ListNode); while2ListNode.addChild(&a2Node); stmtTable.insertStatement(&a2Node);
	TNode b2Node = TNode("ASSIGN_NODE", "a", 6, 0); b2Node.addParent(&while2ListNode); while2ListNode.addChild(&b2Node); stmtTable.insertStatement(&b2Node);

	TNode cNode = TNode("ASSIGN_NODE", "c", 7, 0); cNode.addParent(&stmtListNode); stmtListNode.addChild(&cNode); stmtTable.insertStatement(&cNode);
	
	// create CFG
	// std::cout << "Creating CFG 6.\n";
	NextExtractor newCFG(&procTable, &stmtTable);
	// std::cout << "Done building CFG 6.\n\n\n\n\n\n";

	/*
	// print out ds
	for (std::map<int, set<int>>::iterator it=newCFG.AdjListFwd.begin(); it!=newCFG.AdjListFwd.end(); it++) {
		std::cout << "for line " << (*it).first << ": ";
		set<int> list = (*it).second;
		for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << endl;
	}
	*/

	// test basic linking
	CPPUNIT_ASSERT(newCFG.isNext(1,2));
	CPPUNIT_ASSERT(newCFG.isNext(2,3));

	// test link from while to first child
	CPPUNIT_ASSERT(newCFG.isNext(3,4));
	CPPUNIT_ASSERT(newCFG.isNext(4,5));

	// test link back
	CPPUNIT_ASSERT(newCFG.isNext(6,4));
	CPPUNIT_ASSERT(newCFG.isNext(4,3));

	// test neighbour of parent while
	CPPUNIT_ASSERT(newCFG.isNext(3,7));

	// should fail
	CPPUNIT_ASSERT(!newCFG.isNext(1,2));
}