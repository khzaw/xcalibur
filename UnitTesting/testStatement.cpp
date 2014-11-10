#include <cppunit/config/SourcePrefix.h>
#include "testStatement.h"
#include "StatementTable.h"

#include <iostream>
#include <string>

void 
StatementTest::setUp()
{
}

void 
StatementTest::tearDown()
{
}

CPPUNIT_TEST_SUITE_REGISTRATION( StatementTest );

// method to test insertion of procedures
void 
StatementTest::testInsert(){
	//inserting non duplicates procedures
	TNode stmt1("assign","a = y", 1,0);
	TNode stmt2("while","b", 2,0);
	TNode stmt3("assign","b = z", 3,0);
	StatementTable s;
	s.insertStatement(&stmt1);
	CPPUNIT_ASSERT_EQUAL(1,s.getSize());
	s.insertStatement(&stmt2);
	CPPUNIT_ASSERT_EQUAL(2,s.getSize());
	s.insertStatement(&stmt3);
	CPPUNIT_ASSERT_EQUAL(3,s.getSize());
	CPPUNIT_ASSERT(s.getTNode(1)->getData() == "a = y");
	CPPUNIT_ASSERT(s.getTNode(1)->getNodeType() == "assign");
	CPPUNIT_ASSERT_EQUAL(1, s.getTNode(1)->getStmtNum());
	CPPUNIT_ASSERT_EQUAL(0, s.getTNode(1)->getProcIndex());
	return;
}

// method to test getting nodes / stmt num using node type
void 
StatementTest::testGetNodesMatchingNodeType (){
    TNode stmt1("assign","a = y", 1,0);
	TNode stmt2("while","b", 2,0);
	TNode stmt3("assign","b = z", 3,0);
	StatementTable s;
	s.insertStatement(&stmt1);
	s.insertStatement(&stmt2);
	s.insertStatement(&stmt3);
	vector<TNode *> nodes = s.getNodesMatchingNodeType("assign");
	CPPUNIT_ASSERT(nodes[0]->getData() == "a = y");
	CPPUNIT_ASSERT_EQUAL(1,nodes[0]->getStmtNum());
	CPPUNIT_ASSERT(nodes[0]->getNodeType() == "assign");
	CPPUNIT_ASSERT(nodes[1]->getData() == "b = z");
	CPPUNIT_ASSERT_EQUAL(3,nodes[1]->getStmtNum());
	CPPUNIT_ASSERT(nodes[1]->getNodeType() == "assign");
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	CPPUNIT_ASSERT(v.size() == s.getAllStmtNum().size());
	return;
}

void 
StatementTest::testGetStmtNumUsingNodeType(){
    TNode stmt1("assign","a = y", 1,0);
	TNode stmt2("while","b", 2,0);
	TNode stmt3("assign","b = z", 3,0);
	StatementTable s;
	s.insertStatement(&stmt1);
	s.insertStatement(&stmt2);
	s.insertStatement(&stmt3);
	vector<int> stmt = s.getStmtNumUsingNodeType("assign");
	CPPUNIT_ASSERT_EQUAL(1,stmt[0]);
	CPPUNIT_ASSERT_EQUAL(3,stmt[1]);
	return;
}

// method to test the checking of stmt table to see if it contains the specified nodetype
void
StatementTest::testIfContainsStmt(){
   TNode stmt1("assign","a = y", 1,0);
	TNode stmt2("while","b", 2,0);
	TNode stmt3("assign","b = z", 3,0);
	StatementTable s;
	s.insertStatement(&stmt1);
	s.insertStatement(&stmt2);
	s.insertStatement(&stmt3);
	CPPUNIT_ASSERT(s.containsStatement("assign"));
	CPPUNIT_ASSERT(s.containsStatement("while"));
	CPPUNIT_ASSERT(!(s.containsStatement("if")));
	return;
}

// method to test the checking of stmt table for nodes with matching node type at specified index
void	
StatementTest::testIfContainsNode(){
	TNode stmt1("assign","a = y", 1,0);
	TNode stmt2("while","b", 2,0);
	TNode stmt3("assign","b = z", 3,0);
	StatementTable s;
	s.insertStatement(&stmt1);
	s.insertStatement(&stmt2);
	s.insertStatement(&stmt3);
	CPPUNIT_ASSERT(s.containsNodeOfStmtAndNodeType("assign",1));
	CPPUNIT_ASSERT(s.containsNodeOfStmtAndNodeType("assign",3));
	CPPUNIT_ASSERT(s.containsNodeOfStmtAndNodeType("while",2));
	CPPUNIT_ASSERT(!(s.containsNodeOfStmtAndNodeType("while",3)));
	return;
}
