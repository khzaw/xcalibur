#include <vector>
#include <list>

using namespace std;

class Modifies{

	private:
	vector<pair<int,int>> stmtMod;
	vector<pair<int,int>> procMod;
	int stmt;
	int varIndex;
	
	public:
	Modifies();
	//Stmt
	vector<int> getModifiersStmt(int);
	vector<int> getModifiedVarStmt(int);
	vector<pair<int,int>> getModifiesStmt();
	void insertModifiesStmt(int,int);
	bool isModifiesStmt(int,int);
	//Procedure
	vector<int> getModifiersProc(int);
	vector<int> getModifiedVarProc(int);
	vector<pair<int,int>> getModifiesProc();
	void insertModifiesProc(int,int);
	bool isModifiesProc(int,int);
};