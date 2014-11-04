#ifndef testStatement_h
#define testStatement_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class StatementTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( StatementTest ); // Note 3 
	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST( testGetNodesMatchingNodeType );
	CPPUNIT_TEST( testGetStmtNumUsingNodeType);
	CPPUNIT_TEST( testIfContainsStmt);
	CPPUNIT_TEST( testIfContainsNode );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();

	// method to test insertion of stmt and its node
	void testInsert();

	// method to test getting nodes / stmt num using node type
	void testGetNodesMatchingNodeType ();
	void testGetStmtNumUsingNodeType ();

	// method to test the checking of stmt table to see if it contains the specified nodetype
	void testIfContainsStmt();
	// method to test the checking of stmt table for nodes with matching node type at specified index
	void testIfContainsNode();
};
#endif
    