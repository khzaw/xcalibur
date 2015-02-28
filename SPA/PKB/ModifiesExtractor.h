#pragma once
#include <iostream>
#include "Modifies.h"


using namespace std;

class ModifiesExtractor{

private:

	Modifies* modifies;

public:

		ModifiesExtractor(Modifies* modifies);
		ModifiesExtractor();
		void construct();

	//build stmt modifies table
	void buildStmtVarMod();  // done
	void buildVarStmtMod(); // done

	//build  proc modifies table
	void buildProcVarMod();  // done
	void buildVarProcMod();  // done

	//build stmt/proc  index table
	void buildStmtVarIndex(); // done
	void buildVarStmtIndex(); // done
    void buildProcVarIndex(); // done
	void buildVarProcIndex(); // done

	//build stmt/proc boolean matrix
	void buildStmtBool();
	void buildProcBool();


};

