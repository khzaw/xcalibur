#pragma once
#include <iostream>
#include "Calls.h"

using namespace std;

class CallsExtractor{

private:

	Calls* calls;

public:
	CallsExtractor();
	CallsExtractor(Calls* call);
	void construct();

	//build caller/callee table
	void buildCallerTable();  // done
	void buildCalleeTable(); // done

	//build caller/callee star table
	void buildCallerStarTable();  // done
	void buildCalleeStarTable();  // done

	//build caller/callee index table
	void buildCallerIndex(); // done
	void buildCalleeIndex(); // done


};

