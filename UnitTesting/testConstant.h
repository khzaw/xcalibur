#ifndef testConstant_h
#define testConstant_h

// Note 1
#include <cppunit/extensions/HelperMacros.h>

class ConstantTest : public CPPUNIT_NS::TestFixture // Note 2 
{ 
	CPPUNIT_TEST_SUITE( ConstantTest ); // Note 3 
	CPPUNIT_TEST(testInsert);
	CPPUNIT_TEST( testGetConstant);
	CPPUNIT_TEST( testGetConstantIndex);
	CPPUNIT_TEST( testGetAllConstant );
	CPPUNIT_TEST( testIfContainsConst);
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();
	void tearDown();
	
	// method to test assigning of duplicate variables
	void testInsert();

	// method to test the retrieval of constant and its index
	void testGetConstant();
	void testGetConstantIndex();

	//method to get all constants in the const table
	void testGetAllConstant();

	// method to test the checking of var table to see if it contains the specified constant
	void testIfContainsConst();

};
#endif
    