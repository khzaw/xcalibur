#pragma once
#include <utility>
#include <vector>
#include <iostream>

using namespace std;

class Sibling {

private :

	vector<pair<int,int>> procProc;
	vector<pair<int,int>> stmtLstStmtLst; // then-else
	vector<pair<int,int>> varStmtLst;  // var-then, var-else
	vector<pair<int,int>> varConst; //assign 
	vector<pair<int,int>> varPlus;
	vector<pair<int,int>> varMinus;
	vector<pair<int,int>> varTimes;
	vector<pair<int,int>> constPlus;
	vector<pair<int,int>> constMinus;
	vector<pair<int,int>> constTimes;
	vector<pair<int,int>> plusPlus;
	vector<pair<int,int>> plusMinus;
	vector<pair<int,int>> plusTimes;
	vector<pair<int,int>> minusMinus;
	vector<pair<int,int>> minusTimes;
	vector<pair<int,int>> timesTimes;

public :
	
	//functions to insert into the siblings table
	void insertProcProc(int,int);
	void insertStmtLstStmtLst(int,int);
	void inserVarStmtLst(int,int);
	void insertVarConst(int,int);
	void insertVarPlus(int,int);
	void insertVarMinus(int,int);
	void insertVarTimes(int,int);
	void insertConstStmtLst(int,int);
	void insertConstConst(int,int);
	void insertConstPlus(int,int);
	void insertConstMinus(int,int);
	void insertConstTimes(int,int);
	void insertPlusPlus(int,int);
	void insertPlusMinus(int,int);
	void insertPlusTimes(int,int);
	void insertMinusMinus(int,int);
	void insertMinusTimes(int,int);
	void insertTimesTimes(int,int);

	//accessors
	vector<int> getProcSiblingOfProc(int);
	vector<int> getStmtLstSiblingOfStmtLst(int);
	vector<int> getVarSiblingOfStmtLst(int);
	vector<int> getStmtLstSiblingOfVar(int);




	

};