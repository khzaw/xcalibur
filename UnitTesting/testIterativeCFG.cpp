#include <cppunit/config/SourcePrefix.h>
#include "testIterativeCFG.h"
#include "..\SPA\PKB\iterativeCFG.h"
#include "..\SPA\PKB\AST.h"
#include "..\SPA\Frontend\TNode.h"

#include <iostream>
#include <string>

void iterativeCFGTest::setUp()
{
}

void iterativeCFGTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( iterativeCFGTest );
// method to test insertion of procedures

void iterativeCFGTest::testSourceProgram() {
  /** SIMPLE source code
	procedure First{
		x = 2;					// 1
		z = 3;					// 2
		call Second;}			// 3
	procedure Second{
		x = 0;					// 4
		i = 5;					// 5
		while i {				// 6
			x = x + 2 * y		// 7
			if m then {			// 8
				m = n;}			// 9
			else {
				n = Second;}	// 10
			call Third;			// 11
			i = i - 1;}			// 12
		if x then {				// 13
			x = x + 1;			// 14
			while m {			// 15
				m = m - 1;}}	// 16
		else {
			z = 1;}				// 17
		z = z + x + i;			// 18
		y = z + 2;				// 19
		x = x * y + z;}			// 20
	procedure Third{
		z = 5;					// 21
		v = z;}					// 22
	**/

	TNode stmt1("ASSIGN_NODE", "2 ", 1, 0); // x = 2
	TNode stmt2("ASSIGN_NODE", "3 ", 2, 0); // z = 3
	TNode stmt3("CALL_NODE", "Second", 3, 0);
	TNode stmt4("ASSIGN_NODE", "0 ", 4, 1); // x = 0
	TNode stmt5("ASSIGN_NODE", "5 ", 5, 1); // i = 5
	TNode stmt6("WHILE_NODE", "i", 6, 1);
	TNode stmt7("ASSIGN_NODE", "x 2 y * + ", 7, 1); //x = x + 2 * y
	TNode stmt8("IF_NODE", "m", 8, 1);
	TNode stmt9("ASSIGN_NODE", "n ", 9, 1); // m = n
	TNode stmt10("ASSIGN_NODE", "Second ", 10, 1); // n = Second
	TNode stmt11("CALL_NODE", "Third", 11, 1);
	TNode stmt12("ASSIGN_NODE", "i 1 - ", 12, 1); // i = i - 1
	TNode stmt13("IF_NODE", "x", 13, 1);
	TNode stmt14("ASSIGN_NODE", "x 1 + ", 14, 1); //x = x + 1
	TNode stmt15("WHILE_NODE", "m", 15, 1);
	TNode stmt16("ASSIGN_NODE", "m 1 - ", 16, 1); // m = m - 1
	TNode stmt17("ASSIGN_NODE", "1 ", 17, 1); // z = 1
	TNode stmt18("ASSIGN_NODE", "z x + i + ", 18, 1); //z = z + x + i
	TNode stmt19("ASSIGN_NODE", "z 2 + ", 19, 1); // y = z + 2
	TNode stmt20("ASSIGN_NODE", "x y * z + ", 20, 1); // x = x * y + z
	TNode stmt21("ASSIGN_NODE", "5 ", 21, 2); // z = 5
	TNode stmt22("ASSIGN_NODE", "z ", 22, 2); // v = z
	
	TNode rootNode1("PROC_NODE", "First", -1, 0);
	TNode stmtListNode1("STMTLST_NODE", "", 0, 0); 
	stmtListNode1.addParent(&rootNode1); 
	rootNode1.addChild(&stmtListNode1);
	stmt1.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt1); stmt1.addRightSibling(&stmt2);
	stmt2.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt2); stmt2.addRightSibling(&stmt3);
	stmt3.addParent(&stmtListNode1); stmtListNode1.addChild(&stmt3);

	TNode rootNode2("PROC_NODE", "Second", -1, 1);
	TNode stmtListNode2("STMTLST_NODE", "", 0, 1); 
	stmtListNode2.addParent(&rootNode2); 
	rootNode2.addChild(&stmtListNode2);
	// base
	stmt4.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt4); stmt4.addRightSibling(&stmt5);
	stmt5.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt5); stmt5.addRightSibling(&stmt6);
	stmt6.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt6); stmt6.addRightSibling(&stmt13);
	stmt13.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt13); stmt13.addRightSibling(&stmt18);
	stmt18.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt18); stmt18.addRightSibling(&stmt19);
	stmt19.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt19); stmt19.addRightSibling(&stmt20);
	stmt20.addParent(&stmtListNode2); stmtListNode2.addChild(&stmt20);
	// statement 6 nesting
	TNode stmtListNode2_1("STMTLST_NODE", "", 0, 1); 
	stmtListNode2_1.addParent(&stmt6); stmt6.addChild(&stmtListNode2_1);
	stmt7.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt7); stmt7.addRightSibling(&stmt8);
	stmt8.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt8); stmt8.addRightSibling(&stmt11);
	stmt11.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt11); stmt11.addRightSibling(&stmt12);
	stmt12.addParent(&stmtListNode2_1); stmtListNode2_1.addChild(&stmt12);
		// statement 8 nesting
		TNode stmtListNode2_1_1("STMTLST_NODE", "", 0, 1); TNode thennode211("THEN_NODE", "then", 0, 1);
		TNode stmtListNode2_1_2("STMTLST_NODE", "", 0, 1); TNode elsenode212("ELSE_NODE", "else", 0, 1);
		thennode211.addParent(&stmt8); stmt8.addChild(&thennode211); thennode211.addRightSibling(&elsenode212);
		elsenode212.addParent(&stmt8); stmt8.addChild(&elsenode212);
		stmtListNode2_1_1.addParent(&thennode211); thennode211.addChild(&stmtListNode2_1_1);
		stmtListNode2_1_2.addParent(&elsenode212); elsenode212.addChild(&stmtListNode2_1_2);
		stmt9.addParent(&stmtListNode2_1_1); stmtListNode2_1_1.addChild(&stmt9);
		stmt10.addParent(&stmtListNode2_1_2); stmtListNode2_1_2.addChild(&stmt10);
	// statement 13 nesting
	TNode stmtListNode2_2("STMTLST_NODE", "", 0, 1); TNode thennode222("THEN_NODE", "then", 0, 1);
	TNode stmtListNode2_3("STMTLST_NODE", "", 0, 1); TNode elsenode223("ELSE_NODE", "else", 0, 1);
	thennode222.addParent(&stmt13); stmt13.addChild(&thennode222); thennode222.addRightSibling(&elsenode223);
	elsenode223.addParent(&stmt13); stmt13.addChild(&elsenode223);
	stmtListNode2_2.addParent(&thennode222); thennode222.addChild(&stmtListNode2_2);
	stmtListNode2_3.addParent(&elsenode223); elsenode223.addChild(&stmtListNode2_3);
	stmt14.addParent(&stmtListNode2_2); stmtListNode2_2.addChild(&stmt14); stmt14.addRightSibling(&stmt15);
	stmt15.addParent(&stmtListNode2_2); stmtListNode2_2.addChild(&stmt15);
		// statement 15 nesting
		TNode stmtListNode2_2_1("STMTLST_NODE", "", 0, 1); 
		stmtListNode2_2_1.addParent(&stmt15); stmt15.addChild(&stmtListNode2_2_1);
		stmt16.addParent(&stmtListNode2_2_1); stmtListNode2_2_1.addChild(&stmt16);
	stmtListNode2_3.addParent(&stmt13); stmt13.addChild(&stmtListNode2_3);
	stmt17.addParent(&stmtListNode2_3); stmtListNode2_3.addChild(&stmt17);

	TNode rootNode3("PROC_NODE", "Third", -1, 2);
	TNode stmtListNode3("STMTLST_NODE", "", 0, 2); 
	stmtListNode3.addParent(&rootNode3); 
	rootNode3.addChild(&stmtListNode3);
	stmt21.addParent(&stmtListNode3); stmtListNode3.addChild(&stmt21); stmt21.addRightSibling(&stmt22);
	stmt22.addParent(&stmtListNode3); stmtListNode3.addChild(&stmt22);


  iterativeCFG CFG1(&rootNode1);
  iterativeCFG CFG2(&rootNode2);
  iterativeCFG CFG3(&rootNode3);


  CPPUNIT_ASSERT(CFG1.isNext(1,2));
  CPPUNIT_ASSERT(CFG1.isNext(2,3));
  CPPUNIT_ASSERT(CFG1.isNextStar(1,3));
  CPPUNIT_ASSERT(!CFG1.isNext(3,1));

  CPPUNIT_ASSERT(CFG2.isNext(4,5));
  CPPUNIT_ASSERT(CFG2.isNext(6,7));
  CPPUNIT_ASSERT(CFG2.isNext(8,9));
  CPPUNIT_ASSERT(CFG2.isNext(8,10));
  CPPUNIT_ASSERT(CFG2.isNext(9,11));
  CPPUNIT_ASSERT(CFG2.isNext(10,11));

  CPPUNIT_ASSERT(CFG2.isNext(6,13));
  CPPUNIT_ASSERT(CFG2.isNext(16,15));
  CPPUNIT_ASSERT(CFG2.isNext(15,18));
  CPPUNIT_ASSERT(CFG2.isNext(17,18));

  
  CPPUNIT_ASSERT(CFG2.isNextStar(4,20));
  CPPUNIT_ASSERT(CFG2.isNextStar(9,20));
  CPPUNIT_ASSERT(CFG2.isNextStar(10,20));
  CPPUNIT_ASSERT(CFG2.isNextStar(12,20));
  CPPUNIT_ASSERT(CFG2.isNextStar(16,20));
  CPPUNIT_ASSERT(CFG2.isNextStar(17,20));
  
  CPPUNIT_ASSERT(CFG2.isNextStar(9,8));
  CPPUNIT_ASSERT(CFG2.isNextStar(10,8));
  CPPUNIT_ASSERT(CFG2.isNextStar(11,8));
  CPPUNIT_ASSERT(CFG2.isNextStar(12,8));
  /*
  std::cout << endl << "printing out AdjList for proc 2 " << endl;
  for (std::map<int, set<int>>::iterator it=CFG2.AdjListFwd.begin(); it!=CFG2.AdjListFwd.end(); it++) {
		std::cout << "for line " << (*it).first << ": ";
		set<int> list = (*it).second;
		for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << endl;
	}
  */
}