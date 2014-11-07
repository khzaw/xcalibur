
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
// Get the top level suite from the registry
//CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
CppUnit::TestSuite *unitSuite = new CppUnit::TestSuite( "All unit test" );
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("VarTableTest").makeTest());	
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ProcTableTest").makeTest());
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ModifiesTest").makeTest());
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("UsesTest").makeTest());	
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ParentTest").makeTest());	
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("FollowsTest").makeTest());	
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("ConstantTest").makeTest());	
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("StatementTest").makeTest());	
unitSuite->addTest(CppUnit::TestFactoryRegistry::getRegistry("QueryParserTest").makeTest());	
CppUnit::TestFactoryRegistry::getRegistry().addTestToSuite(unitSuite);
CppUnit::TextUi::TestRunner runner;


runner.addTest(unitSuite);
bool wasSucessful = runner.run();

//cin.get();
getchar();

return wasSucessful ? 0 : 1;
}
