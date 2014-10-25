#include <vector>
#include <list>


using namespace std;

class Uses{

	private:
	vector<pair<int,int>> stmtUses;
	vector<pair<int,int>> procUses;
	
	public:
	Uses();
    //Stmt
	vector<int> getUsersStmt(int);
	vector<int> getUsedVarStmt(int);
	vector<pair<int,int>> getUsesStmt();
	void insertUsesStmt(int,int);
	bool isUsesStmt(int,int);
	//Procedure
	vector<int> getUsersProc(int);
	vector<int> getUsedVarProc(int);
	vector<pair<int,int>> getUsesProc();
	void insertUsesProc(int,int);
	bool isUsesProc(int,int);
};