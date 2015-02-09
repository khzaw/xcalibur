#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include "../SPA/QueryProcessor/QueryEvaluator.h"
#include "../SPA/QueryProcessor/QueryParser.h"
#include "Parser.h"


using namespace std;

int main(int argc, char* argv[])
{
// Get the top level suite from the registry
CPPUNIT_NS::Test *suite = CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest();
CppUnit::TextUi::TestRunner runner;

//parse the SIMPLE soource code into the parser
//Parse();
string t;
Parser* parser;
PKBController* controller;

parser = new Parser("../Debug/Sample-Source.txt");
controller = &(parser->controller);

//string query = "assign a; Select a pattern a(\"oSCar\", \"1 + beta + tmp\" )";
string query = "assign a; Select a pattern a(\"oSCar\", \"_\" )";

QueryParser* qp = new QueryParser(query);
QueryEvaluator* qe = new QueryEvaluator(controller);

qp->getQueryTree()->printTree();
cout << qp->getQueryTree()->getRootNode()->getChild(2)->getKey() << endl;;
cin >> t;



//Call of DesignExtractor
//Extract();

runner.addTest(suite);
bool wasSucessful = runner.run();


//getchar();

return wasSucessful ? 0 : 1;
}