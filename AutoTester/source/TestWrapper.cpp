#include "TestWrapper.h"
#include "Frontend\Parser.h"
#include "QueryProcessor\QE.h"
#include "QueryProcessor\NewQueryParser.h"
#include <iostream>
#include <iterator>

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

PKBController* controller;
Parser* parser;

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
	// call your parser to do the parsing
  // ...rest of your code...
	 parser = new Parser(filename);
	 controller = &(parser->controller);
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
// call your evaluator to evaluate the query here
  // ...code to evaluate query...

  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
	//qe->evaluato

	//string t;
	//QueryParser* qp = new QueryParser(query);
	/*cout << endl;*/
	//QueryEvaluator* qe = new QueryEvaluator(controller);
	//results = qe->evaluate(&(qp->getSynonyms()), qp->getQueryTree());
	/*cout << "RESULT" << endl;
	cout << result << endl;*/
	NewQueryParser* qp = new NewQueryParser(query, controller);
	string resultsVector = qp->evaluator->solve();
	results.push_back(resultsVector);
	//std::copy(resultsVector.begin(), resultsVector.end(), std::back_inserter(results));
}
