#pragma once
#include <utility>
#include <vector>
#include <vector>
#include <iostream>
#include <set>

using namespace std;

class Contains {

private:
	
	//contains() relationships
	
	vector<pair<int,int>> procStmtLst; //contains the procedure and the statement list the the procedure contains
	vector<pair<int,int>> stmtLstStmt; //contains the stmt and stmt list that the stmt contains (eg while has stmtlist)
	vector<pair<int,int>> stmtVar;  //contains the statements and the variables that the statement contains (eg : if/while/assign stmt)
	vector<pair<int,int>> stmtConst; //contains the statements and the constants that the statement contains (eg : assign stmt )
	vector<pair<int,int>> stmtPlus; //contains the statement and the plus node that the statement contains (eg : assign stmt)
	vector<pair<int,int>> stmtMinus; //contains the statement and the minus node that the statement contains (eg : assign stmt)
	vector<pair<int,int>> stmtTimes; //contains the statement and the times node that the statement contains (eg : assign stmt)
	vector<pair<int,int>> stmtStmtLst;  //contains the statement and the statement that the statement contains
	vector<pair<int,int>> plusVar ; //contains the plus nodes and the variable that the plus node contains
	vector<pair<int,int>> minusVar; //contains the minus nodes and the variable that the minus node contains
	vector<pair<int,int>> timesVar; //contains the times nodes and the variable that the times node contains
	vector<pair<int,int>> plusConst; //contains the plus node and the constant that the plus node contains
	vector<pair<int,int>> minusConst; //contains the minus node and the constant that the minus node contains
	vector<pair<int,int>> timesConst; //contains the times node and the constant that the times node contains
	vector<pair<int,int>> plusPlus ; //contains the plus nodes and the plus node that the plus node contains
	vector<pair<int,int>> plusMinus ; //contains the plus nodes and the minus node that the plus node contains
	vector<pair<int,int>> plusTimes; //contains the plus nodes and the times node that the times node contains
	vector<pair<int,int>> minusPlus; //contains the minus nodes and the plus node that the minus node contains
	vector<pair<int,int>> minusMinus; //conatins the minus nodes and the minus nodes that the minus node contains
	vector<pair<int,int>> minusTimes; //contains the minus nodes and the times nodes that the minus node contains
	vector<pair<int,int>> timesPlus ; //conatins the times node and the plus node that the times node contains
	vector<pair<int,int>> timesMinus; //contains the times node and the minus node that the times node contains
	vector<pair<int,int>> timesTimes; //contains the times and the times node that the times node contains


	// all design entities

	set<int> allPlus;
	set<int> allMinus;
	set<int> allTimes;
	set<int> allStmtLsts;
	set<int> allStmts;
	set<int> allVars;
	set<int> allConsts;
	set<int> allProcs;



public:

	//containers
	Contains();

	set<int> getAllPlus();
	set<int> getAllMinus();
	set<int> getAllTimes();
	set<int> getAllStmtLsts();
	set<int> getAllStmts();
	set<int> getAllVars();
	set<int> getAllConsts();
	set<int> getAllProcs();
	
	void insertProcStmtLst(int,int); 
	void insertStmtLstStmt(int,int); 
	void insertStmtVar(int,int);  
	void insertStmtConst(int,int); 
	void insertStmtPlus(int,int); 
	void insertStmtMinus(int,int); 
	void insertStmtTimes(int,int); 
	void insertStmtStmtLst(int,int);  
	void insertPlusVar(int,int); 
	void insertPlusConst(int,int);
	void insertMinusVar(int,int);
	void insertMinusConst(int,int);
	void insertTimesVar(int,int);
	void insertTimesConst(int,int);
	void insertPlusPlus(int,int);
	void insertPlusMinus(int,int);
	void insertPlusTimes(int,int);
	void insertMinusTimes(int,int);
	void insertMinusPlus(int,int);
	void insertMinusMinus(int,int);
	void insertTimesPlus (int,int); 
	void insertTimesMinus(int,int); 
	void insertTimesTimes(int,int); 

	//getters
	
	//for procedures as containers
	set<int>  getStmtLstContainedInProc(int); //returns the statement list contained in proc (WILL NEVER BE QUERIED !!!)
	set<int>  getProcContainingStmtLst(int); //returns the procedure which contains the given stmtLst

	//for statementlist as containers
	set<int>  getStmtContainedInStmtLst(int) ; //returns the statements contained in statement list
	set<int>  getStmtLstContainingStmt(int); //returns the statementlist containing statements

	//for statements as containers
	set<int>  getVarContainedInStmt (int);   //returns the variables contained in a stmt
	set<int>  getStmtContainingVar (int);   //returns the statements which conatins the variable
	set<int>  getConstContainedInStmt (int);  //returns the constants which are conatined within a statement
	set<int>  getStmtContainingConst(int);  //returns the statements which contain the constant
	set<int>  getStmtLstContainedInStmt (int) ; //returns the statementList which are contained in statement (WILL NEVER APPEAR AS QUERY!!!)
	set<int>  getStmtContainingStmtLst (int); //returns the statements contain statementList 
	set<int>  getPlusContainedInStmt(int); //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtContainingPlus(int); //returns the statements containing plus 
	set<int>  getMinusContainedInStmt(int); //returns the minus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtContainingMinus(int); //returns the statements containing minus
	set<int>  getTimesContainedInStmt(int); //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtContainingTimes(int); //returns the statements containing plus 


	//for plus node as container 
	set<int>  getVarContainedInPlus(int); //returns all those variables which are children of the plus node in the AST
	set<int>  getPlusContainingVar(int); //returns all those pluses which contain the variable node
	set<int>  getConstContainedInPlus(int); //returns all those constants which are children of the plus node in the AST
	set<int>  getPlusContainingConst(int); //returns all those pluses which contain the constant
	set<int>  getPlusContainedInPlus(int); //returns all those plus which are children of the plus node in the AST
	set<int>  getPlusContainingPlus(int); //returns all those pluses which contain the plus node
	set<int>  getMinusContainedInPlus(int); //returns all those minus which are children of the plus node in the AST
	set<int>  getPlusContainingMinus(int); //returns all those pluses which contain the minus node
	set<int>  getTimesContainedInPlus(int); //returns all those times which are children of the plus node in the AST
	set<int>  getPlusContainingTimes(int); //returns all those pluses which contain the times node

	//for minus node as container
	set<int>  getVarContainedInMinus(int); //returns all those variables which are children of the minus node in the AST
	set<int>  getMinusContainingVar(int); //returns all those minus which contain the variable node
	set<int>  getConstContainedInMinus(int); //returns all those constants which are children of the minus node in the AST
	set<int>  getMinusContainingConst(int); //returns all those minus which contain the constant
	set<int>  getPlusContainedInMinus(int); //returns all those plus which are children of the minus node in the AST
	set<int>  getMinusContainingPlus(int); //returns all those minuses which contain the plus node
	set<int>  getMinusContainedInMinus(int); //returns all those minus which are children of the minus node in the AST
	set<int>  getMinusContainingMinus(int); //returns all those minus which contain the minus node
	set<int>  getTimesContainedInMinus(int); //returns all those times which are children of the minus node in the AST
	set<int>  getMinusContainingTimes(int); //returns all those minuses which contain the times node

	//for times node as container
	set<int>  getVarContainedInTimes(int); //returns all those variables which are children of the times node in the AST
	set<int>  getTimesContainingVar(int); //returns all those times which contain the variable node
	set<int>  getConstContainedInTimes(int); //returns all those constants which are children of the times node in the AST
	set<int>  getTimesContainingConst(int); //returns all those times which contain the constant
	set<int>  getPlusContainedInTimes(int); //returns all those plus which are children of the times node in the AST
	set<int>  getTimesContainingPlus(int); //returns all those times which contain the plus node
	set<int>  getMinusContainedInTimes(int); //returns all those minus which are children of the times node in the AST
	set<int>  getTimesContainingMinus(int); //returns all those times which contain the minus node
	set<int>  getTimesContainedInTimes(int); //returns all those times which are children of the times node in the AST
	set<int>  getTimesContainingTimes(int); //returns all those times which contain the times node

	//get all container and Containees
	
	//for procedure as container
	set<int>  getAllProcStmtLstContainers(); //returns the procedures which contain statement list
	set<int>  getAllProcStmtLstContainees(); //return the statement list which are ocntained in some procedure

	//for statement list as container
	set<int>  getAllStmtLstStmtContainers(); //returns the statementList which contain some statement
	set<int>  getAllStmtLstStmtContainees(); //returns the statements which are contained withing a statement list

	//for statement as container
	set<int>  getAllStmtStmtLstContainers(); // returns all the statements which contain some statementlist
	set<int>  getAllStmtStmtLstContainees(); //returns all the statement list conatained within some statement
	set<int>  getAllStmtVarContainers();  //returns all the statements which contain some variable
	set<int>  getAllStmtVarContainees();  //returns all the variables contained within some statement
	set<int>  getAllStmtConstContainers(); //returns all the statements which contain some constants
	set<int>  getAllStmtConstContainees(); //returns all the constants conatained within some statement
	set<int>  getAllStmtPlusContainers(); //returns all the statements which contain some plus
	set<int>  getAllStmtPlusContainees(); //return all the pluses which are contained within a statement
	set<int>  getAllStmtMinusContainers(); //return all the statements which contain some minus
	set<int>  getAllStmtMinusContainees(); //return all the minuses which are contained in some statement
	set<int>  getAllStmtTimesContainers(); //return all the statements which contain some times node
	set<int>  getAllStmtTimesContainees(); //return all the times nodes which are contained within a statement

	// for plus node as container 
	set<int>  getAllPlusVarContainers(); //returns the list of all plus nodes which contain some variable
	set<int>  getAllPlusVarContainees(); //returns the list of all variables which are contained in some plus node
	set<int>  getAllPlusConstContainers(); //returns the list of all plus nodes which contain some constant
	set<int>  getAllPlusConstContainees(); //returns the list of all constants which are contained in some plus node
	set<int>  getAllPlusPlusContainers(); //returns the list of all plus nodes which contain some plus nodes
	set<int>  getAllPlusPlusContainees(); //returns the list of all pluses which are contained in some plus node
	set<int>  getAllPlusMinusContainers(); //returns the list of all plus nodes which contain some minus
	set<int>  getAllPlusMinusContainees(); //returns the list of all minuses which are contained in some plus node
	set<int>  getAllPlusTimesContainers(); //returns the list of all plus nodes which contain some times nose
	set<int>  getAllPlusTimesContainees(); //returns the list of all times which are contained in some plus node
	
	//for minus node as container
	set<int>  getAllMinusVarContainers(); //returns the list of all minus nodes which contain some variable
	set<int>  getAllMinusVarContainees(); //returns the list of all variables which are contained in some minus node
	set<int>  getAllMinusConstContainers(); //returns the list of all minus nodes which contain some constant
	set<int>  getAllMinusConstContainees(); //returns the list of all constants which are contained in some minus node
	set<int>  getAllMinusPlusContainers(); //returns the list of all minus nodes which contain some minus nodes
	set<int>  getAllMinusPlusContainees(); //returns the list of all minuses which are contained in some minus node
	set<int>  getAllMinusMinusContainers(); //returns the list of all minus nodes which contain some minus
	set<int>  getAllMinusMinusContainees(); //returns the list of all minuses which are contained in some minus node
	set<int>  getAllMinusTimesContainers(); //returns the list of all minus nodes which contain some times nose
	set<int>  getAllMinusTimesContainees(); //returns the list of all times which are contained in some minus node
	
	//for times node as container
	set<int>  getAllTimesVarContainers(); //returns the list of all Times nodes which contain some variable
	set<int>  getAllTimesVarContainees(); //returns the list of all variables which are contained in some Times node
	set<int>  getAllTimesConstContainers(); //returns the list of all Times nodes which contain some constant
	set<int>  getAllTimesConstContainees(); //returns the list of all constants which are contained in some Times node
	set<int>  getAllTimesPlusContainers(); //returns the list of all Times nodes which contain some Times nodes
	set<int>  getAllTimesPlusContainees(); //returns the list of all Timeses which are contained in some Times node
	set<int>  getAllTimesMinusContainers(); //returns the list of all Times nodes which contain some minus
	set<int>  getAllTimesMinusContainees(); //returns the list of all minuses which are contained in some Times node
	set<int>  getAllTimesTimesContainers(); //returns the list of all Times nodes which contain some times nose
	set<int>  getAllTimesTimesContainees(); //returns the list of all times which are contained in some Times node
	

	//boolean functions
	
	bool isContainsProcStmtLst(int, int); //returns true if contains(proc,stmtlst) holds
	bool isContainsStmtLstStmt(int,int); //returns true if contains(stmtLst, stmt) holds
	bool isContainsStmtVar(int,int); //returns true if contains(Stmt,var) holds  
	bool isContainsStmtConst(int,int); //returns true if contains(Stmt,Const) holds 
	bool isContainsStmtPlus(int,int); //returns true if contains(stmt,plus) holds
	bool isContainsStmtMinus(int,int); //returns true if contains(stmt,minus) holds 
	bool isContainsStmtTimes(int,int); //returns true if contains(stmt, times) holds 
	bool isContainsStmtStmtLst(int,int); //returns true if contains(stmt,stmtlst) holds 
	bool isContainsPlusVar(int,int); //returns true if contains(plus,var) holds 
	bool isContainsPlusConst(int,int); //returns true if contains(plus,const) holds
	bool isContainsMinusVar(int,int); //returns true if contains(minus,var) holds
	bool isContainsMinusConst(int,int); //returns true if contains(minus,const) holds
	bool isContainsTimesVar(int,int); //returns true if contains(times,var) holds
	bool isContainsTimesConst(int,int); //returns true if contains(times,const) holds
	bool isContainsPlusPlus(int,int); //returns true if contains(plus,plus) holds
	bool isContainsPlusMinus(int,int); //return true if contains(plus,minus) holds
	bool isContainsPlusTimes(int,int); //returns true if contains(plus,plus) holds
	bool isContainsMinusTimes(int,int); //return true if contains(minus,times) holds
	bool isContainsMinusPlus(int,int); //returns true if contains(minus,plus) holds
	bool isContainsMinusMinus(int,int); //return true if contains(minus,minus) holds
	bool isContainsTimesPlus (int,int); //return true if contains(times,plus) holds 
	bool isContainsTimesMinus(int,int); // return true if contains(times,minus) holds
	bool isContainsTimesTimes(int,int); // return true if contains(times,times) holds 


	
	//***********************************************************************************************************************************************************************************************************
	//contains *
	//***********************************************************************************************************************************************************************************************************

	//for procedures as containers
	set<int>  getStmtLstContainedStarInProc(int); //returns the statement list ContainedStar in proc (WILL NEVER BE QUERIED !!!)
	set<int>  getProcContainingStarStmtLst(int); //returns the procedure which contains the given stmtLst directly/indirectly
	set<int>  getStmtContainedStarInProc(int) ; //returns statement which is contained in a proc directly/indirectly
	set<int>  getProcContainingStarStmt(int); //returns the proc which contains statements directly/indirectly
	set<int>  getVarContainedStarInProc (int);   //returns the variables ContainedStar in a proc
	set<int>  getProcsContainingStarVar (int);   //returns the procedures which conatins the variable
	set<int>  getConstContainedStarInProc (int);  //returns the constants which are contained within a procedure
	set<int>  getProcContainingStarConst(int);  //returns the procedures which contain the constant
	set<int>  getPlusContainedStarInProc(int); //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getProcContainingStarPlus(int); //returns the procedure ContainingStar plus 
	set<int>  getMinusContainedStarInProc(int); //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getProcContainingStarMinus(int); //returns the procedure ContainingStar minus
	set<int>  getTimesContainedStarInProc(int); //returns the times ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getProcContainingStarTimes(int); //returns the procedures ContainingStartimes

	//for statementlist as containers
	set<int>  getStmtContainedStarInStmtLst(int) ; //returns the statements ContainedStar in statement list
	set<int>  getStmtLstContainingStarStmt(int); //returns the statementlist ContainingStar statements
	set<int>  getVarContainedStarInStmtLst (int);   //returns the variables ContainedStar in a stmtlist
	set<int>  getStmtLstContainingStarVar (int);   //returns the statementlist which conatins the variable
	set<int>  getConstContainedStarInStmtLst (int);  //returns the constants which are contained within a statementlist
	set<int>  getStmtLstContainingStarConst(int);  //returns the statementlist which contain the constant
	set<int>  getPlusContainedStarInStmtLst(int); //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtLstContainingStarPlus(int); //returns the statementlist ContainingStar plus 
	set<int>  getMinusContainedStarInStmtLst(int); //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtLstContainingStarMinus(int); //returns the statementlist ContainingStar minus
	set<int>  getTimesContainedStarInStmtLst(int); //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtLstContainingStarTimes(int); //returns the statementlist ContainingStar times
	set<int>  getStmtLstContainingStarStmtLst(int);  //returns the statementlist which contain the statementList
	set<int>  getStmtLstContainedStarInStmtLst (int) ; //returns the statementList which are ContainedStar in statementLst 
	
	
	//for statements as containers
	set<int>  getVarContainedStarInStmt (int);   //returns the variables ContainedStar in a stmt
	set<int>  getStmtContainingStarVar (int);   //returns the statements which conatins the variable
	set<int>  getConstContainedStarInStmt (int);  //returns the constants which are contained within a statement
	set<int>  getStmtContainingStarConst(int);  //returns the statements which contain the constant
	set<int>  getStmtLstContainedStarInStmt (int) ; //returns the statementList which are ContainedStar in statement (WILL NEVER APPEAR AS QUERY!!!)
	set<int>  getStmtContainingStarStmtLst (int); //returns the statements contain statementList 
	set<int>  getPlusContainedStarInStmt(int); //returns the plus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtContainingStarPlus(int); //returns the statements ContainingStar plus 
	set<int>  getMinusContainedStarInStmt(int); //returns the minus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtContainingStarMinus(int); //returns the statements ContainingStar minus
	set<int>  getTimesContainedStarInStmt(int); //returns the times ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	set<int>  getStmtContainingStarTimes(int); //returns the statements ContainingStar times 
	set<int>  getStmtContainingStarStmt(int);
	set<int>  getStmtContainedStarInStmt(int);


	//for plus node as container 
	set<int>  getVarContainedStarInPlus(int); //returns all those variables which are children of the plus node in the AST
	set<int>  getPlusContainingStarVar(int); //returns all those pluses which contain the variable node
	set<int>  getConstContainedStarInPlus(int); //returns all those constants which are children of the plus node in the AST
	set<int>  getPlusContainingStarConst(int); //returns all those pluses which contain the constant
	set<int>  getPlusContainedStarInPlus(int); //returns all those plus which are children of the plus node in the AST
	set<int>  getPlusContainingStarPlus(int); //returns all those pluses which contain the plus node
	set<int>  getMinusContainedStarInPlus(int); //returns all those minus which are children of the plus node in the AST
	set<int>  getPlusContainingStarMinus(int); //returns all those pluses which contain the minus node
	set<int>  getTimesContainedStarInPlus(int); //returns all those times which are children of the plus node in the AST
	set<int>  getPlusContainingStarTimes(int); //returns all those pluses which contain the times node

	//for minus node as container
	set<int>  getVarContainedStarInMinus(int); //returns all those variables which are children of the minus node in the AST
	set<int>  getMinusContainingStarVar(int); //returns all those minus which contain the variable node
	set<int>  getConstContainedStarInMinus(int); //returns all those constants which are children of the minus node in the AST
	set<int>  getMinusContainingStarConst(int); //returns all those minus which contain the constant
	set<int>  getPlusContainedStarInMinus(int); //returns all those plus which are children of the minus node in the AST
	set<int>  getMinusContainingStarPlus(int); //returns all those minuses which contain the plus node
	set<int>  getMinusContainedStarInMinus(int); //returns all those minus which are children of the minus node in the AST
	set<int>  getMinusContainingStarMinus(int); //returns all those minus which contain the minus node
	set<int>  getTimesContainedStarInMinus(int); //returns all those times which are children of the minus node in the AST
	set<int>  getMinusContainingStarTimes(int); //returns all those minuses which contain the times node

	//for times node as container
	set<int>  getVarContainedStarInTimes(int); //returns all those variables which are children of the times node in the AST
	set<int>  getTimesContainingStarVar(int); //returns all those times which contain the variable node
	set<int>  getConstContainedStarInTimes(int); //returns all those constants which are children of the times node in the AST
	set<int>  getTimesContainingStarConst(int); //returns all those times which contain the constant
	set<int>  getPlusContainedStarInTimes(int); //returns all those plus which are children of the times node in the AST
	set<int>  getTimesContainingStarPlus(int); //returns all those times which contain the plus node
	set<int>  getMinusContainedStarInTimes(int); //returns all those minus which are children of the times node in the AST
	set<int>  getTimesContainingStarMinus(int); //returns all those times which contain the minus node
	set<int>  getTimesContainedStarInTimes(int); //returns all those times which are children of the times node in the AST
	set<int>  getTimesContainingStarTimes(int); //returns all those times which contain the times node



	//boolean functions
	
	bool isContainsStarProcStmtLst(int, int); //returns true if contains*(proc,stmtlst) holds
	bool isContainsStarProcStmt(int, int); //returns true if contains*(proc,stmt) holds
	bool isContainsStarProcVar(int, int); //returns true if contains*(proc,var) holds
	bool isContainsStarProcPlus(int, int); //returns true if contains*(proc,plus) holds
	bool isContainsStarProcConst(int, int); //returns true if contains*(proc,const) holds
	bool isContainsStarProcMinus(int, int); //returns true if contains*(proc,minus) holds
	bool isContainsStarProcTimes(int, int); //returns true if contains*(proc,times) holds
	bool isContainsStarStmtLstStmt(int,int); //returns true if contains*(stmtLst, stmt) holds
	bool isContainsStarStmtLstVar(int,int); //returns true if contains*(stmtLst, var) holds
	bool isContainsStarStmtLstConst(int,int); //returns true if contains*(stmtLst, const) holds
	bool isContainsStarStmtLstPlus(int,int); //returns true if contains*(stmtLst, plus) holds
	bool isContainsStarStmtLstMinus(int,int); //returns true if contains*(stmtLst, minus) holds
	bool isContainsStarStmtLstTimes(int,int); //returns true if contains*(stmtLst, times) holds
	bool isContainsStarStmtLstStmtLst(int,int); //returns true if contains*(stmtLst,stmtLst) hold
	bool isContainsStarStmtVar(int,int); //returns true if contains*(Stmt,var) holds  
	bool isContainsStarStmtConst(int,int); //returns true if contains*(Stmt,Const) holds 
	bool isContainsStarStmtPlus(int,int); //returns true if contains*(stmt,plus) holds
	bool isContainsStarStmtMinus(int,int); //returns true if contains*(stmt,minus) holds 
	bool isContainsStarStmtTimes(int,int); //returns true if contains*(stmt, times) holds 
	bool isContainsStarStmtStmtLst(int,int); //returns true if contains*(stmt,stmtlst) holds 
	
	bool isContainsStarPlusVar(int,int); //returns true if contains*(plus,var) holds 
	bool isContainsStarPlusConst(int,int); //returns true if contains*(plus,const) holds
	bool isContainsStarMinusVar(int,int); //returns true if contains*(minus,var) holds
	bool isContainsStarMinusConst(int,int); //returns true if contains*(minus,const) holds
	bool isContainsStarTimesVar(int,int); //returns true if contains*(times,var) holds
	bool isContainsStarTimesConst(int,int); //returns true if contains*(times,const) holds
	bool isContainsStarPlusPlus(int,int); //returns true if contains*(plus,plus) holds
	bool isContainsStarPlusMinus(int,int); //return true if contains*(plus,minus) holds
	bool isContainsStarPlusTimes(int,int); //returns true if contains*(plus,plus) holds
	bool isContainsStarMinusTimes(int,int); //return true if contains*(minus,times) holds
	bool isContainsStarMinusPlus(int,int); //returns true if contains*(minus,plus) holds
	bool isContainsStarMinusMinus(int,int); //return true if contains*(minus,minus) holds
	bool isContainsStarTimesPlus (int,int); //return true if contains*(times,plus) holds 
	bool isContainsStarTimesMinus(int,int); // return true if contains*(times,minus) holds
	bool isContainsStarTimesTimes(int,int); // return true if contains*(times,times) holds 
	bool isContainsStarStmtStmt(int,int); //returns true if contains*(stmt,stmt) holds;


	

};