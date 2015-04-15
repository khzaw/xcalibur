#include <cppunit/config/SourcePrefix.h>
#include "testOptimizedCFG.h"
#include "..\SPA\PKB\OptimizedCFG.h"
#include "..\SPA\PKB\AST.h"
#include "..\SPA\Frontend\TNode.h"
#include "..\SPA\PKB\PKBController.h"

#include <iostream>
#include <string>

void OptimizedCFGTest::setUp()
{
}

void OptimizedCFGTest::tearDown()
{
}	

CPPUNIT_TEST_SUITE_REGISTRATION( OptimizedCFGTest );
// method to test insertion of procedures

void OptimizedCFGTest::testSourceProgram() {
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

  pk = new PKBController();
	synonymTable = map<string, string>();

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

  
	pk->ast->insertRoot(&rootNode1);
	pk->ast->insertRoot(&rootNode2);
	pk->ast->insertRoot(&rootNode3);
	pk->procTable->insertASTRootNode(0, &rootNode1);
	pk->procTable->insertASTRootNode(1, &rootNode2);
	pk->procTable->insertASTRootNode(2, &rootNode3);
	
	pk->statementTable->insertStatement(&stmt1);
	pk->statementTable->insertStatement(&stmt2);
	pk->statementTable->insertStatement(&stmt3);
	pk->statementTable->insertStatement(&stmt4);
	pk->statementTable->insertStatement(&stmt5);
	pk->statementTable->insertStatement(&stmt6);
	pk->statementTable->insertStatement(&stmt7);
	pk->statementTable->insertStatement(&stmt8);
	pk->statementTable->insertStatement(&stmt9);
	pk->statementTable->insertStatement(&stmt10);
	pk->statementTable->insertStatement(&stmt11);
	pk->statementTable->insertStatement(&stmt12);
	pk->statementTable->insertStatement(&stmt13);
	pk->statementTable->insertStatement(&stmt14);
	pk->statementTable->insertStatement(&stmt15);
	pk->statementTable->insertStatement(&stmt16);
	pk->statementTable->insertStatement(&stmt17);
	pk->statementTable->insertStatement(&stmt18);
	pk->statementTable->insertStatement(&stmt19);
	pk->statementTable->insertStatement(&stmt20);
	pk->statementTable->insertStatement(&stmt21);
	pk->statementTable->insertStatement(&stmt22);
	
	pk->procTable->insertProc("First");  // 0
	pk->procTable->insertProc("Second"); // 1
	pk->procTable->insertProc("Third");  // 2

	pk->varTable->insertVar("x");        // 0
	pk->varTable->insertVar("z");        // 1
	pk->varTable->insertVar("i");		   // 2
	pk->varTable->insertVar("y");        // 3
	pk->varTable->insertVar("m");        // 4
	pk->varTable->insertVar("n");        // 5
	pk->varTable->insertVar("Second");   // 6
	pk->varTable->insertVar("v");        // 7

	pk->constantTable->insertConst(2);
	pk->constantTable->insertConst(3);
	pk->constantTable->insertConst(0);
	pk->constantTable->insertConst(5);
	pk->constantTable->insertConst(1);

	pk->followsTable->insertFollows(1, 2);
	pk->followsTable->insertFollows(2, 3);
	pk->followsTable->insertFollows(4, 5);
	pk->followsTable->insertFollows(5, 6);
	pk->followsTable->insertFollows(6, 13);
	pk->followsTable->insertFollows(13, 18);
	pk->followsTable->insertFollows(18, 19);
	pk->followsTable->insertFollows(19, 20);
	pk->followsTable->insertFollows(21, 22);
	pk->followsTable->insertFollows(7, 8);
	pk->followsTable->insertFollows(8, 11);
	pk->followsTable->insertFollows(11, 12);
	pk->followsTable->insertFollows(14, 15);

	pk->parentTable->insertParent(6, 7);
	pk->parentTable->insertParent(6, 8);
	pk->parentTable->insertParent(6, 11);
	pk->parentTable->insertParent(6, 12);
	pk->parentTable->insertParent(8, 9);
	pk->parentTable->insertParent(8, 10);
	pk->parentTable->insertParent(13, 14);
	pk->parentTable->insertParent(13, 15);
	pk->parentTable->insertParent(13, 17);
	pk->parentTable->insertParent(15, 16);

	pk->callsTable->insertCalls(0, 1);
	pk->callsTable->insertCalls(1, 2);

	pk->modifiesTable->insertModifiesProc(0, 0);
	pk->modifiesTable->insertModifiesProc(0, 1);
	pk->modifiesTable->insertModifiesProc(0, 2);
	pk->modifiesTable->insertModifiesProc(0, 3);
	pk->modifiesTable->insertModifiesProc(0, 4);
	pk->modifiesTable->insertModifiesProc(0, 5);
	pk->modifiesTable->insertModifiesProc(0, 7);
	pk->modifiesTable->insertModifiesProc(1, 0);
	pk->modifiesTable->insertModifiesProc(1, 1);
	pk->modifiesTable->insertModifiesProc(1, 2);
	pk->modifiesTable->insertModifiesProc(1, 3);
	pk->modifiesTable->insertModifiesProc(1, 4);
	pk->modifiesTable->insertModifiesProc(1, 5);
	pk->modifiesTable->insertModifiesProc(1, 7);
	pk->modifiesTable->insertModifiesProc(2, 1);
	pk->modifiesTable->insertModifiesProc(2, 7);
	
	pk->modifiesTable->insertModifiesStmt(1, 0);
	pk->modifiesTable->insertModifiesStmt(2, 1);
	pk->modifiesTable->insertModifiesStmt(3, 0);
	pk->modifiesTable->insertModifiesStmt(3, 2);
	pk->modifiesTable->insertModifiesStmt(3, 4);
	pk->modifiesTable->insertModifiesStmt(3, 5);
	pk->modifiesTable->insertModifiesStmt(3, 1);
	pk->modifiesTable->insertModifiesStmt(3, 3);
	pk->modifiesTable->insertModifiesStmt(3, 7);
	pk->modifiesTable->insertModifiesStmt(4, 0);
	pk->modifiesTable->insertModifiesStmt(5, 2);
	pk->modifiesTable->insertModifiesStmt(6, 0);
	pk->modifiesTable->insertModifiesStmt(6, 4);
	pk->modifiesTable->insertModifiesStmt(6, 5);
	pk->modifiesTable->insertModifiesStmt(6, 1);
	pk->modifiesTable->insertModifiesStmt(6, 7);
	pk->modifiesTable->insertModifiesStmt(6, 2);
	pk->modifiesTable->insertModifiesStmt(7, 0);
	pk->modifiesTable->insertModifiesStmt(8, 4);
	pk->modifiesTable->insertModifiesStmt(8, 5);
	pk->modifiesTable->insertModifiesStmt(9, 4);
	pk->modifiesTable->insertModifiesStmt(10, 5);
	pk->modifiesTable->insertModifiesStmt(11, 1);
	pk->modifiesTable->insertModifiesStmt(11, 7);
	pk->modifiesTable->insertModifiesStmt(12, 2);
	pk->modifiesTable->insertModifiesStmt(13, 0);
	pk->modifiesTable->insertModifiesStmt(13, 4);
	pk->modifiesTable->insertModifiesStmt(13, 1);
	pk->modifiesTable->insertModifiesStmt(14, 0);
	pk->modifiesTable->insertModifiesStmt(15, 4);
	pk->modifiesTable->insertModifiesStmt(16, 4);
	pk->modifiesTable->insertModifiesStmt(17, 1);
	pk->modifiesTable->insertModifiesStmt(18, 1);
	pk->modifiesTable->insertModifiesStmt(19, 3);
	pk->modifiesTable->insertModifiesStmt(20, 0);
	pk->modifiesTable->insertModifiesStmt(21, 1);
	pk->modifiesTable->insertModifiesStmt(22, 7);

	pk->usesTable->insertUsesProc(0, 0);
	pk->usesTable->insertUsesProc(0, 1);
	pk->usesTable->insertUsesProc(0, 2);
	pk->usesTable->insertUsesProc(0, 3);
	pk->usesTable->insertUsesProc(0, 4);
	pk->usesTable->insertUsesProc(0, 5);
	pk->usesTable->insertUsesProc(0, 6);
	pk->usesTable->insertUsesProc(1, 0);
	pk->usesTable->insertUsesProc(1, 1);
	pk->usesTable->insertUsesProc(1, 2);
	pk->usesTable->insertUsesProc(1, 3);
	pk->usesTable->insertUsesProc(1, 4);
	pk->usesTable->insertUsesProc(1, 5);
	pk->usesTable->insertUsesProc(1, 6);
	pk->usesTable->insertUsesProc(2, 1);
	
	pk->usesTable->insertUsesStmt(3, 0);
	pk->usesTable->insertUsesStmt(3, 1);
	pk->usesTable->insertUsesStmt(3, 2);
	pk->usesTable->insertUsesStmt(3, 3);
	pk->usesTable->insertUsesStmt(3, 4);
	pk->usesTable->insertUsesStmt(3, 5);
	pk->usesTable->insertUsesStmt(3, 6);
	pk->usesTable->insertUsesStmt(6, 2);
	pk->usesTable->insertUsesStmt(6, 0);
	pk->usesTable->insertUsesStmt(6, 3);
	pk->usesTable->insertUsesStmt(6, 4);
	pk->usesTable->insertUsesStmt(6, 5);
	pk->usesTable->insertUsesStmt(6, 6);
	pk->usesTable->insertUsesStmt(6, 1);
	pk->usesTable->insertUsesStmt(7, 0);
	pk->usesTable->insertUsesStmt(7, 3);
	pk->usesTable->insertUsesStmt(8, 4);
	pk->usesTable->insertUsesStmt(8, 5);
	pk->usesTable->insertUsesStmt(8, 6);
	pk->usesTable->insertUsesStmt(9, 5);
	pk->usesTable->insertUsesStmt(10, 6);
	pk->usesTable->insertUsesStmt(11, 1);
	pk->usesTable->insertUsesStmt(12, 2);
	pk->usesTable->insertUsesStmt(13, 0);
	pk->usesTable->insertUsesStmt(13, 4);
	pk->usesTable->insertUsesStmt(14, 0);
	pk->usesTable->insertUsesStmt(15, 4);
	pk->usesTable->insertUsesStmt(16, 4);
	pk->usesTable->insertUsesStmt(18, 1);
	pk->usesTable->insertUsesStmt(18, 0);
	pk->usesTable->insertUsesStmt(18, 2);
	pk->usesTable->insertUsesStmt(19, 1);
	pk->usesTable->insertUsesStmt(20, 0);
	pk->usesTable->insertUsesStmt(20, 1);
	pk->usesTable->insertUsesStmt(20, 3);
	pk->usesTable->insertUsesStmt(22, 1);
	/*
	pk->statementTable->insertStatement(&stmt1);
	pk->statementTable->insertStatement(&stmt2);
	pk->statementTable->insertStatement(&stmt3);
	pk->statementTable->insertStatement(&stmt4);
	pk->statementTable->insertStatement(&stmt5);
	pk->statementTable->insertStatement(&stmt6);
	pk->statementTable->insertStatement(&stmt7);
	pk->statementTable->insertStatement(&stmt8);
	pk->statementTable->insertStatement(&stmt9);
	pk->statementTable->insertStatement(&stmt10);
	pk->statementTable->insertStatement(&stmt11);
	pk->statementTable->insertStatement(&stmt12);
	pk->statementTable->insertStatement(&stmt13);
	pk->statementTable->insertStatement(&stmt14);
	pk->statementTable->insertStatement(&stmt15);
	pk->statementTable->insertStatement(&stmt16);
	pk->statementTable->insertStatement(&stmt17);
	pk->statementTable->insertStatement(&stmt18);
	pk->statementTable->insertStatement(&stmt19);
	pk->statementTable->insertStatement(&stmt20);
	pk->statementTable->insertStatement(&stmt21);
	pk->statementTable->insertStatement(&stmt22);
	*/
	pk->constructCalls();
	pk->constructFollows();
	pk->constructModifies();
	pk->constructParent();
	pk->constructNext();
  pk->constructOptimizedCFG();
	pk->constructUses();

	synonymTable["s1"]="stmt";
	synonymTable["s2"]="stmt";
	synonymTable["a1"]="assign";
	synonymTable["a2"]="assign";
	synonymTable["a3"]="assign";
	synonymTable["w1"]="while";
	synonymTable["w2"]="while";
	synonymTable["i1"]="if";
	synonymTable["i2"]="if";
	synonymTable["v1"]="variable";
	synonymTable["v2"]="variable";
	synonymTable["proc1"]="procedure";
	synonymTable["proc2"]="procedure";
	synonymTable["c1"]="call";
	synonymTable["c2"]="call";
	synonymTable["l1"]="prog_line";
	synonymTable["l2"]="prog_line";
	synonymTable["const1"]="constant";
	synonymTable["const2"]="constant";

  //OptimizedCFG CFG2(pk->procTable, pk->statementTable, pk->parentTable, pk->followsTable, pk->);

  OptimizedCFG* CFG2 = pk->optimizedCFG;

  CPPUNIT_ASSERT(CFG2->isNext(1,2));
  CPPUNIT_ASSERT(CFG2->isNext(2,3));
  CPPUNIT_ASSERT(CFG2->isNextStar(1,3));
  CPPUNIT_ASSERT(!CFG2->isNext(3,1));

  CPPUNIT_ASSERT(CFG2->isNext(4,5));
  CPPUNIT_ASSERT(CFG2->isNext(6,7));
  CPPUNIT_ASSERT(CFG2->isNext(8,9));
  CPPUNIT_ASSERT(CFG2->isNext(8,10));
  CPPUNIT_ASSERT(CFG2->isNext(9,11));
  CPPUNIT_ASSERT(CFG2->isNext(10,11));

  CPPUNIT_ASSERT(CFG2->isNext(6,13));
  CPPUNIT_ASSERT(CFG2->isNext(16,15));
  CPPUNIT_ASSERT(CFG2->isNext(15,18));
  CPPUNIT_ASSERT(CFG2->isNext(17,18));

  // testing is next star

  
  CPPUNIT_ASSERT(CFG2->isNextStar(4,7));
  CPPUNIT_ASSERT(CFG2->isNextStar(4,20));
  CPPUNIT_ASSERT(CFG2->isNextStar(9,20));
  CPPUNIT_ASSERT(CFG2->isNextStar(10,20));
  CPPUNIT_ASSERT(CFG2->isNextStar(12,20));
  CPPUNIT_ASSERT(CFG2->isNextStar(16,20));
  CPPUNIT_ASSERT(CFG2->isNextStar(14,20));
  CPPUNIT_ASSERT(CFG2->isNextStar(17,20));
  
  CPPUNIT_ASSERT(CFG2->isNextStar(8,9));
  CPPUNIT_ASSERT(CFG2->isNextStar(8,12));
  CPPUNIT_ASSERT(CFG2->isNextStar(9,12));
  CPPUNIT_ASSERT(CFG2->isNextStar(10,12));
  CPPUNIT_ASSERT(CFG2->isNextStar(9,16));
  CPPUNIT_ASSERT(CFG2->isNextStar(10,17));
  
  CPPUNIT_ASSERT(CFG2->isNextStar(9,10));

  CPPUNIT_ASSERT(CFG2->isNextStar(9,8));
  CPPUNIT_ASSERT(CFG2->isNextStar(10,8));
  CPPUNIT_ASSERT(CFG2->isNextStar(11,8));
  
  CPPUNIT_ASSERT(CFG2->isNextStar(13,14));
  CPPUNIT_ASSERT(CFG2->isNextStar(13,15));
  CPPUNIT_ASSERT(CFG2->isNextStar(13,16));
  CPPUNIT_ASSERT(CFG2->isNextStar(13,17));

  CPPUNIT_ASSERT(!CFG2->isNextStar(14,13));
  CPPUNIT_ASSERT(!CFG2->isNextStar(15,13));
  CPPUNIT_ASSERT(!CFG2->isNextStar(16,13));
  CPPUNIT_ASSERT(!CFG2->isNextStar(17,13));

  CPPUNIT_ASSERT(!CFG2->isNextStar(14,17));
  CPPUNIT_ASSERT(!CFG2->isNextStar(15,17));
  CPPUNIT_ASSERT(!CFG2->isNextStar(16,17));
  CPPUNIT_ASSERT(!CFG2->isNextStar(17,14));
  CPPUNIT_ASSERT(!CFG2->isNextStar(17,15));
  CPPUNIT_ASSERT(!CFG2->isNextStar(17,16));
  

  // Affects
  CPPUNIT_ASSERT(!CFG2->isAffects(4,5));
  CPPUNIT_ASSERT(!CFG2->isAffects(5,7));
  CPPUNIT_ASSERT(!CFG2->isAffects(7,9));
  CPPUNIT_ASSERT(!CFG2->isAffects(9,10));
  CPPUNIT_ASSERT(!CFG2->isAffects(12,14));
  CPPUNIT_ASSERT(!CFG2->isAffects(14,16));


  // CFG2->printAggNodeMap();
  //cout << endl << "printing out NextList for proc 2 " << endl;
  
  CPPUNIT_ASSERT(CFG2->isAffects(4,7));
  
  CPPUNIT_ASSERT(CFG2->isAffects(4,14));
  CPPUNIT_ASSERT(CFG2->isAffects(5,12));
  CPPUNIT_ASSERT(CFG2->isAffects(17,18));
  CPPUNIT_ASSERT(CFG2->isAffects(18,19));
  CPPUNIT_ASSERT(CFG2->isAffects(19,20));

  CPPUNIT_ASSERT(CFG2->isAffects(12,18));
  CPPUNIT_ASSERT(!CFG2->isAffects(17, 19));
  
  cout << endl << "printing out NextList for proc 2 " << endl;
  
  for (std::map<int, set<int>>::iterator it=CFG2->NextListFwd.begin(); it!=CFG2->NextListFwd.end(); it++) {
		std::cout << "for line " << (*it).first << ": ";
		set<int> list = (*it).second;
		for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << "" << endl;
  }

  cout << endl << "printing BackList "<< endl;
  for (std::map<int, set<int>>::iterator it=CFG2->NextListBwd.begin(); it!=CFG2->NextListBwd.end(); it++) {
		std::cout << "for line " << (*it).first << ": ";
		set<int> list = (*it).second;
		for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << "" << endl;
  }

  std::set<int> allNext = CFG2->getAllNext(); 
  std::set<int> allPrev = CFG2->getAllPrev();
  cout << "why2" << endl;
  
  std::cout << endl << "printing allNext" << endl;
  for (std::set<int>::iterator it=allNext.begin(); it!=allNext.end(); it++){ 
    std::cout << *it << " ";
  }
  std::cout << endl;

  std::cout << endl << "printing allPrev" << endl;
  for (std::set<int>::iterator it=allPrev.begin(); it!=allPrev.end(); it++){ 
    std::cout << *it << " ";
  }
  std::cout << endl << " why3." << endl;

  std::set<int> NextStar4 = CFG2->getNextStar(4); 
  std::set<int> PrevStar20 = CFG2->getPrevStar(20);
  std::cout << "why4" << endl;
  
  std::cout << endl << "printing NextStar4: " << NextStar4.size() << endl;
  for (std::set<int>::iterator it=NextStar4.begin(); it!=NextStar4.end(); it++){ 
    std::cout << *it << " ";
  }
  std::cout << endl;

  std::cout << endl << "printing PrevStar20: " << PrevStar20.size() << endl;
  for (std::set<int>::iterator it=PrevStar20.begin(); it!=PrevStar20.end(); it++){ 
    std::cout << *it << " ";
  }
  std::cout << endl << " why5." << endl;

  CPPUNIT_ASSERT(CFG2->isNextStar(16,16));
  CPPUNIT_ASSERT(!CFG2->isNextStar(18,18));

  CPPUNIT_ASSERT(CFG2->isNextStar(12,12));


  // should fail to show that unit test has indeed been run
  CPPUNIT_ASSERT(!CFG2->isNextStar(12,8));

  /*
  for (std::map<int, set<int>>::iterator it=CFG2->getNextListFwd().begin(); it!=CFG2->getNextListFwd().end(); it++) {
		std::cout << "for line " << (*it).first << ": ";
		set<int> list = (*it).second;
		for (std::set<int>::iterator it2=list.begin(); it2!=list.end(); it2++) {
			std::cout << *it2 << " ";
		}
		std::cout << endl;
	}
  */
}  