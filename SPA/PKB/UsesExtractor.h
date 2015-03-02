#pragma once
#include <iostream>
#include "..\PKB\Uses.h"


using namespace std;

class UsesExtractor{

private:

	Uses* uses;

public:

		UsesExtractor(Uses* uses);
		UsesExtractor();
		void construct();

	//build stmt modifies table
	void buildStmtVarUses();  // done
	void buildVarStmtUses(); // done

	//build  proc modifies table
	void buildProcVarUses();  // done
	void buildVarProcUses();  // done

	//build stmt/proc  index table
	void buildStmtVarIndex(); // done
	void buildVarStmtIndex(); // done
    void buildProcVarIndex(); // done
	void buildVarProcIndex(); // done

	//build stmt/proc boolean matrix
	void buildStmtBool();
	void buildProcBool();


};

