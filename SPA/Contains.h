#pragma once
#include <utility>
#include <vector>
#include <vector>
#include <iostream>

using namespace std;

class Contains {

private:
	
	//contains() relationships
	vector<pair<int,int>> progProc; //contains the program and the procedure that the program contains
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


	

public:

	//containers
	Contains();
	void insertProgProc(int,int); 
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
	//for program ContainerStar
	vector<int>  getProcContainedInProg (int);  //returns the procedures Contained within a program
	vector<int>  getProgContainingProc (int);  //return the program which contains the procedure
	
	//for procedures as containers
	vector<int>  getStmtLstContainedInProc(int); //returns the statement list contained in proc (WILL NEVER BE QUERIED !!!)
	vector<int>  getProcContainingStmtLst(int); //returns the procedure which contains the given stmtLst

	//for statementlist as containers
	vector<int>  getStmtContainedInStmtLst(int) ; //returns the statements contained in statement list
	vector<int>  getStmtLstContainingStmt(int); //returns the statementlist containing statements

	//for statements as containers
	vector<int>  getVarContainedInStmt (int);   //returns the variables contained in a stmt
	vector<int>  getStmtContainingVar (int);   //returns the statements which conatins the variable
	vector<int>  getConstContainedInStmt (int);  //returns the constants which are conatined within a statement
	vector<int>  getStmtContainingConst(int);  //returns the statements which contain the constant
	vector<int>  getStmtLstContainedInStmt (int) ; //returns the statementList which are contained in statement (WILL NEVER APPEAR AS QUERY!!!)
	vector<int>  getStmtContainingStmtLst (int); //returns the statements contain statementList 
	vector<int>  getPlusContainedInStmt(int); //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtContainingPlus(int); //returns the statements containing plus 
	vector<int>  getMinusContainedInStmt(int); //returns the minus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtContainingMinus(int); //returns the statements containing minus
	vector<int>  getTimesContainedInStmt(int); //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtContainingTimes(int); //returns the statements containing plus 


	//for plus node as container 
	vector<int>  getVarContainedInPlus(int); //returns all those variables which are children of the plus node in the AST
	vector<int>  getPlusContainingVar(int); //returns all those pluses which contain the variable node
	vector<int>  getConstContainedInPlus(int); //returns all those constants which are children of the plus node in the AST
	vector<int>  getPlusContainingConst(int); //returns all those pluses which contain the constant
	vector<int>  getPlusContainedInPlus(int); //returns all those plus which are children of the plus node in the AST
	vector<int>  getPlusContainingPlus(int); //returns all those pluses which contain the plus node
	vector<int>  getMinusContainedInPlus(int); //returns all those minus which are children of the plus node in the AST
	vector<int>  getPlusContainingMinus(int); //returns all those pluses which contain the minus node
	vector<int>  getTimesContainedInPlus(int); //returns all those times which are children of the plus node in the AST
	vector<int>  getPlusContainingTimes(int); //returns all those pluses which contain the times node

	//for minus node as container
	vector<int>  getVarContainedInMinus(int); //returns all those variables which are children of the minus node in the AST
	vector<int>  getMinusContainingVar(int); //returns all those minus which contain the variable node
	vector<int>  getConstContainedInMinus(int); //returns all those constants which are children of the minus node in the AST
	vector<int>  getMinusContainingConst(int); //returns all those minus which contain the constant
	vector<int>  getPlusContainedInMius(int); //returns all those plus which are children of the minus node in the AST
	vector<int>  getMinusContainingPlus(int); //returns all those minuses which contain the plus node
	vector<int>  getMinusContainedInMinus(int); //returns all those minus which are children of the minus node in the AST
	vector<int>  getMinusContainingMinus(int); //returns all those minus which contain the minus node
	vector<int>  getTimesContainedInMinus(int); //returns all those times which are children of the minus node in the AST
	vector<int>  getMinusContainingTimes(int); //returns all those minuses which contain the times node

	//for times node as container
	vector<int>  getVarContainedInTimes(int); //returns all those variables which are children of the times node in the AST
	vector<int>  getTimesContainingVar(int); //returns all those times which contain the variable node
	vector<int>  getConstContainedInTimes(int); //returns all those constants which are children of the times node in the AST
	vector<int>  getTimesContainingConst(int); //returns all those times which contain the constant
	vector<int>  getPlusContainedInTimes(int); //returns all those plus which are children of the times node in the AST
	vector<int>  getTimesContainingPlus(int); //returns all those times which contain the plus node
	vector<int>  getMinusContainedInTimes(int); //returns all those minus which are children of the times node in the AST
	vector<int>  getTimesContainingMinus(int); //returns all those times which contain the minus node
	vector<int>  getTimesContainedInTimes(int); //returns all those times which are children of the times node in the AST
	vector<int>  getTimesContainingTimes(int); //returns all those times which contain the times node

	//get all container and Containees
	//for program as container
	vector<int>  getAllProgProcContainers();  //returns all the programs which contain some procedure
	vector<int>  getAllProgProcContainees(); //returns all the procedures which are contained within some program

	//for procedure as container
	vector<int>  getAllProcStmtLstContainers(); //returns the procedures which contain statement list
	vector<int>  getAllProcStmtLstContainees(); //return the statement list which are ocntained in some procedure

	//for statement list as container
	vector<int>  getAllStmtLstStmtContainers(); //returns the statementList which contain some statement
	vector<int>  getAllStmtLstStmtContainees(); //returns the statements which are contained withing a statement list

	//for statement as container
	vector<int>  getAllStmtStmtLstContainers(); // returns all the statements which contain some statementlist
	vector<int>  getAllStmtStmtLstContainees(); //returns all the statement list conatained within some statement
	vector<int>  getAllStmtVarContainers();  //returns all the statements which contain some variable
	vector<int>  getAllStmtVarContainees();  //returns all the variables contained within some statement
	vector<int>  getAllStmtConstContainers(); //returns all the statements which contain some constants
	vector<int>  getAllStmtConstContainees(); //returns all the constants conatained within some statement
	vector<int>  getAllStmtPlusContainers(); //returns all the statements which contain some plus
	vector<int>  getAllStmtPlusContainees(); //return all the pluses which are contained within a statement
	vector<int>  getAllStmtMinusContainers(); //return all the statements which contain some minus
	vector<int>  getAllStmtMinusContainees(); //return all the minuses which are contained in some statement
	vector<int>  getAllStmtTimesContainers(); //return all the statements which contain some times node
	vector<int>  getAllStmtTimesContainees(); //return all the times nodes which are contained within a statement

	// for plus node as container 
	vector<int>  getAllPlusVarContainers(); //returns the list of all plus nodes which contain some variable
	vector<int>  getAllPlusVarContainees(); //returns the list of all variables which are contained in some plus node
	vector<int>  getAllPlusConstContainers(); //returns the list of all plus nodes which contain some constant
	vector<int>  getAllPlusConstContainees(); //returns the list of all constants which are contained in some plus node
	vector<int>  getAllPlusPlusContainers(); //returns the list of all plus nodes which contain some plus nodes
	vector<int>  getAllPlusPlusContainees(); //returns the list of all pluses which are contained in some plus node
	vector<int>  getAllPlusMinusContainers(); //returns the list of all plus nodes which contain some minus
	vector<int>  getAllPlusMinusContainees(); //returns the list of all minuses which are contained in some plus node
	vector<int>  getAllPlusTimesContainers(); //returns the list of all plus nodes which contain some times nose
	vector<int>  getAllPlusTimesContainees(); //returns the list of all times which are contained in some plus node
	
	//for minus node as container
	vector<int>  getAllMinusVarContainers(); //returns the list of all minus nodes which contain some variable
	vector<int>  getAllMinusVarContainees(); //returns the list of all variables which are contained in some minus node
	vector<int>  getAllMinusConstContainers(); //returns the list of all minus nodes which contain some constant
	vector<int>  getAllMinusConstContainees(); //returns the list of all constants which are contained in some minus node
	vector<int>  getAllMinusPlusContainers(); //returns the list of all minus nodes which contain some minus nodes
	vector<int>  getAllMinusPlusContainees(); //returns the list of all minuses which are contained in some minus node
	vector<int>  getAllMinusMinusContainers(); //returns the list of all minus nodes which contain some minus
	vector<int>  getAllMinusMinusContainees(); //returns the list of all minuses which are contained in some minus node
	vector<int>  getAllMinusTimesContainers(); //returns the list of all minus nodes which contain some times nose
	vector<int>  getAllMinusTimesContainees(); //returns the list of all times which are contained in some minus node
	
	//for times node as container
	vector<int>  getAllTimesVarContainers(); //returns the list of all Times nodes which contain some variable
	vector<int>  getAllTimesVarContainees(); //returns the list of all variables which are contained in some Times node
	vector<int>  getAllTimesConstContainers(); //returns the list of all Times nodes which contain some constant
	vector<int>  getAllTimesConstContainees(); //returns the list of all constants which are contained in some Times node
	vector<int>  getAllTimesPlusContainers(); //returns the list of all Times nodes which contain some Times nodes
	vector<int>  getAllTimesPlusContainees(); //returns the list of all Timeses which are contained in some Times node
	vector<int>  getAllTimesMinusContainers(); //returns the list of all Times nodes which contain some minus
	vector<int>  getAllTimesMinusContainees(); //returns the list of all minuses which are contained in some Times node
	vector<int>  getAllTimesTimesContainers(); //returns the list of all Times nodes which contain some times nose
	vector<int>  getAllTimesTimesContainees(); //returns the list of all times which are contained in some Times node
	

	//boolean functions
	bool isContainsProgProc(int, int); //returns true if contains(prog,proc) holds
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

	//for program containers
	vector<int>  getProcContainedStarInProg (int);  //returns the procedures contained within a program
	vector<int>  getProgContainingStarProc (int);  //return the program which contains* the procedure
	
	//for procedures as containers
	vector<int>  getStmtLstContainedStarInProc(int); //returns the statement list ContainedStar in proc (WILL NEVER BE QUERIED !!!)
	vector<int>  getProcContainingStarStmtLst(int); //returns the procedure which contains the given stmtLst directly/indirectly
	vector<int>  getStmtContainedStarInProc(int) ; //returns statement which is contained in a proc directly/indirectly
	vector<int>  getProcContainingStarStmt(int); //returns the proc which contains statements directly/indirectly
	vector<int>  getVarContainedStarInProc (int);   //returns the variables ContainedStar in a proc
	vector<int>  getProcsContainingStarVar (int);   //returns the procedures which conatins the variable
	vector<int>  getConstContainedStarInProc (int);  //returns the constants which are contained within a procedure
	vector<int>  getProcContainingStarConst(int);  //returns the procedures which contain the constant
	vector<int>  getPlusContainedStarInProc(int); //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getProcContainingStarPlus(int); //returns the procedure ContainingStar plus 
	vector<int>  getMinusContainedStarInProc(int); //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getProcContainingStarMinus(int); //returns the procedure ContainingStar minus
	vector<int>  getTimesContainedStarInProc(int); //returns the times ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getProcContainingStarTimes(int); //returns the procedures ContainingStartimes

	//for statementlist as containers
	vector<int>  getStmtContainedStarInStmtLst(int) ; //returns the statements ContainedStar in statement list
	vector<int>  getStmtLstContainingStarStmt(int); //returns the statementlist ContainingStar statements
	vector<int>  getVarContainedStarInStmtLst (int);   //returns the variables ContainedStar in a stmtlist
	vector<int>  getStmtLstContainingStarVar (int);   //returns the statementlist which conatins the variable
	vector<int>  getConstContainedStarInStmtLst (int);  //returns the constants which are contained within a statementlist
	vector<int>  getStmtLstContainingStarConst(int);  //returns the statementlist which contain the constant
	vector<int>  getPlusContainedStarInStmtLst(int); //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtLstContainingStarPlus(int); //returns the statementlist ContainingStar plus 
	vector<int>  getMinusContainedStarInStmtLst(int); //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtLstContainingStarMinus(int); //returns the statementlist ContainingStar minus
	vector<int>  getTimesContainedStarInStmtLst(int); //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtLstContainingStarTimes(int); //returns the statementlist ContainingStar times
	vector<int>  getStmtLstContainingStarStmtLst(int);  //returns the statementlist which contain the statementList
	vector<int>  getStmtLstContainedStarInStmtLst (int) ; //returns the statementList which are ContainedStar in statementLst 
	
	
	//for statements as containers
	vector<int>  getVarContainedStarInStmt (int);   //returns the variables ContainedStar in a stmt
	vector<int>  getStmtContainingStarVar (int);   //returns the statements which conatins the variable
	vector<int>  getConstContainedStarInStmt (int);  //returns the constants which are contained within a statement
	vector<int>  getStmtContainingStarConst(int);  //returns the statements which contain the constant
	vector<int>  getStmtLstContainedStarInStmt (int) ; //returns the statementList which are ContainedStar in statement (WILL NEVER APPEAR AS QUERY!!!)
	vector<int>  getStmtContainingStarStmtLst (int); //returns the statements contain statementList 
	vector<int>  getPlusContainedStarInStmt(int); //returns the plus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtContainingStarPlus(int); //returns the statements ContainingStar plus 
	vector<int>  getMinusContainedStarInStmt(int); //returns the minus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtContainingStarMinus(int); //returns the statements ContainingStar minus
	vector<int>  getTimesContainedStarInStmt(int); //returns the times ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getStmtContainingStarTimes(int); //returns the statements ContainingStar times 


	//for plus node as container 
	vector<int>  getVarContainedStarInPlus(int); //returns all those variables which are children of the plus node in the AST
	vector<int>  getPlusContainingStarVar(int); //returns all those pluses which contain the variable node
	vector<int>  getConstContainedStarInPlus(int); //returns all those constants which are children of the plus node in the AST
	vector<int>  getPlusContainingStarConst(int); //returns all those pluses which contain the constant
	vector<int>  getPlusContainedStarInPlus(int); //returns all those plus which are children of the plus node in the AST
	vector<int>  getPlusContainingStarPlus(int); //returns all those pluses which contain the plus node
	vector<int>  getMinusContainedStarInPlus(int); //returns all those minus which are children of the plus node in the AST
	vector<int>  getPlusContainingStarMinus(int); //returns all those pluses which contain the minus node
	vector<int>  getTimesContainedStarInPlus(int); //returns all those times which are children of the plus node in the AST
	vector<int>  getPlusContainingStarTimes(int); //returns all those pluses which contain the times node

	//for minus node as container
	vector<int>  getVarContainedStarInMinus(int); //returns all those variables which are children of the minus node in the AST
	vector<int>  getMinusContainingStarVar(int); //returns all those minus which contain the variable node
	vector<int>  getConstContainedStarInMinus(int); //returns all those constants which are children of the minus node in the AST
	vector<int>  getMinusContainingStarConst(int); //returns all those minus which contain the constant
	vector<int>  getPlusContainedStarInMius(int); //returns all those plus which are children of the minus node in the AST
	vector<int>  getMinusContainingStarPlus(int); //returns all those minuses which contain the plus node
	vector<int>  getMinusContainedStarInMinus(int); //returns all those minus which are children of the minus node in the AST
	vector<int>  getMinusContainingStarMinus(int); //returns all those minus which contain the minus node
	vector<int>  getTimesContainedStarInMinus(int); //returns all those times which are children of the minus node in the AST
	vector<int>  getMinusContainingStarTimes(int); //returns all those minuses which contain the times node

	//for times node as container
	vector<int>  getVarContainedStarInTimes(int); //returns all those variables which are children of the times node in the AST
	vector<int>  getTimesContainingStarVar(int); //returns all those times which contain the variable node
	vector<int>  getConstContainedStarInTimes(int); //returns all those constants which are children of the times node in the AST
	vector<int>  getTimesContainingStarConst(int); //returns all those times which contain the constant
	vector<int>  getPlusContainedStarInTimes(int); //returns all those plus which are children of the times node in the AST
	vector<int>  getTimesContainingStarPlus(int); //returns all those times which contain the plus node
	vector<int>  getMinusContainedStarInTimes(int); //returns all those minus which are children of the times node in the AST
	vector<int>  getTimesContainingStarMinus(int); //returns all those times which contain the minus node
	vector<int>  getTimesContainedStarInTimes(int); //returns all those times which are children of the times node in the AST
	vector<int>  getTimesContainingStarTimes(int); //returns all those times which contain the times node

	//get all container and containees 
	//for program as container
	vector<int>  getAllProgProcContainersStar();  //returns all the programs which contain* some procedure
	vector<int>  getAllProgProcContaineesStar(); //returns all the procedures which are ContainedStar within some program

	//for procedure as container
	vector<int>  getAllProcStmtLstContainersStar(); //returns the procedures which contain* statement list
	vector<int>  getAllProcStmtLstContaineesStar(); //return the statement list which are contained* in some procedure
	vector<int>  getALLProcStmtContaineesStar() ; //returns all the statements which is contained in a proc directly/indirectly
	vector<int>  getAllProcStmtContainersStar(); //returns all the procs which contains statements directly/indirectly
	vector<int>  getAllProcVarContaineesStar();   //returns all the variables ContainedStar in a proc
	vector<int>  getAllProcVarContainersStar();   //returns all the procedures which contains* the variable
	vector<int>  getAllProcConstContainees();  //returns all the constants which are contained* within a procedure
	vector<int>  getAllProcConstContainers();  //returns all the procedures which contain* the constant
	vector<int>  getAllProcPlusContainees(); //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getAllProcPlusContainers(); //returns the procedure ContainingStar plus 
	vector<int>  getAllProcMinusContainees(); //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getAllProcMinusContainers(); //returns the procedure ContainingStar minus
	vector<int>  getAllProcTimesContainees(int); //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getAllProcTimesContainers(int); //returns the procedures ContainingStar times


	//for statement list as container
	vector<int>  getAllStmtLstStmtContainersStar(); //returns the statementList which contain* some statement
	vector<int>  getAllStmtLstStmtContaineesStar(); //returns the statements which are ContainedStar withing a statement list
	vector<int>  getAllStmtLstVarContainees();   //returns all the variables ContainedStar in a stmtlist
	vector<int>  getAllStmtLstVarContainers();   //returns the statementlist which conatins the variable
	vector<int>  getAllStmtLstConstContainees();  //returns the constants which are contained within a statementlist
	vector<int>  getAllStmtLstConstContainers();  //returns the statementlist which contain the constant
	vector<int>  getAllStmtLstPlusContainees(); //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getAllStmtLstPlusContainers(); //returns the statementlist ContainingStar plus 
	vector<int>  getAllStmtLstMinusContainees(); //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getAllStmtLstMinusContainers(); //returns the statementlist ContainingStar minus
	vector<int>  getAllStmtLstTimesContainees(); //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int>  getAllStmtLstTimesContainers(); //returns the statementlist ContainingStar times
	vector<int>  getAllStmtLstStmtLstContainees();  //returns the statementlist which contain the statementList
	vector<int>  getAllStmtLstStmtLstContainers(); //returns the statementList which are ContainedStar in statementLst 
	


	//for statement as container
	vector<int>  getAllStmtStmtLstContainersStar(); // returns all the statements which contain* some statementlist
	vector<int>  getAllStmtStmtLstContaineesStar(); //returns all the statement list conatained within some statement
	vector<int>  getAllStmtVarContaineesStar();  //returns all the statements which contain* some variable
	vector<int>  getAllStmtVarContainersStar();  //returns all the variables ContainedStar within some statement
	vector<int>  getAllStmtConstContaineesStar(); //returns all the statements which contain* some constants
	vector<int>  getAllStmtConstContainersStar(); //returns all the constants conatained within some statement
	vector<int>  getAllStmtPlusContaineesStar(); //returns all the statements which contain* some plus
	vector<int>  getAllStmtPlusContainersStar(); //return all the pluses which are ContainedStar within a statement
	vector<int>  getAllStmtMinusContainersStar(); //return all the statements which contain* some minus
	vector<int>  getAllStmtMinusContaineesStar(); //return all the minuses which are ContainedStar in some statement
	vector<int>  getAllStmtTimesContainersStar(); //return all the statements which contain* some times node
	vector<int>  getAllStmtTimesContaineesStar(); //return all the times nodes which are ContainedStar within a statement

	// for plus node as container 
	vector<int>  getAllPlusVarContainersStar(); //returns the list of all plus nodes which contain* some variable
	vector<int>  getAllPlusVarContaineesStar(); //returns the list of all variables which are ContainedStar in some plus node
	vector<int>  getAllPlusConstContainersStar(); //returns the list of all plus nodes which contain* some constant
	vector<int>  getAllPlusConstContaineesStar(); //returns the list of all constants which are ContainedStar in some plus node
	vector<int>  getAllPlusPlusContainersStar(); //returns the list of all plus nodes which contain* some plus nodes
	vector<int>  getAllPlusPlusContaineesStar(); //returns the list of all pluses which are ContainedStar in some plus node
	vector<int>  getAllPlusMinusContainersStar(); //returns the list of all plus nodes which contain* some minus
	vector<int>  getAllPlusMinusContaineesStar(); //returns the list of all minuses which are ContainedStar in some plus node
	vector<int>  getAllPlusTimesContainersStar(); //returns the list of all plus nodes which contain* some times nose
	vector<int>  getAllPlusTimesContaineesStar(); //returns the list of all times which are ContainedStar in some plus node
	
	//for minus node as container
	vector<int>  getAllMinusVarContainersStar(); //returns the list of all minus nodes which contain* some variable
	vector<int>  getAllMinusVarContaineesStar(); //returns the list of all variables which are ContainedStar in some minus node
	vector<int>  getAllMinusConstContainersStar(); //returns the list of all minus nodes which contain* some constant
	vector<int>  getAllMinusConstContaineesStar(); //returns the list of all constants which are ContainedStar in some minus node
	vector<int>  getAllMinusPlusContainersStar(); //returns the list of all minus nodes which contain* some minus nodes
	vector<int>  getAllMinusPlusContaineesStar(); //returns the list of all minuses which are ContainedStar in some minus node
	vector<int>  getAllMinusMinusContainersStar(); //returns the list of all minus nodes which contain* some minus
	vector<int>  getAllMinusMinusContaineesStar(); //returns the list of all minuses which are ContainedStar in some minus node
	vector<int>  getAllMinusTimesContainersStar(); //returns the list of all minus nodes which contain* some times nose
	vector<int>  getAllMinusTimesContaineesStar(); //returns the list of all times which are ContainedStar in some minus node
	
	//for times node as container
	vector<int>  getAllTimesVarContainersStar(); //returns the list of all Times nodes which contain* some variable
	vector<int>  getAllTimesVarContaineesStar(); //returns the list of all variables which are ContainedStar in some Times node
	vector<int>  getAllTimesConstContainersStar(); //returns the list of all Times nodes which contain* some constant
	vector<int>  getAllTimesConstContaineesStar(); //returns the list of all constants which are ContainedStar in some Times node
	vector<int>  getAllTimesPlusContainersStar(); //returns the list of all Times nodes which contain* some Times nodes
	vector<int>  getAllTimesPlusContaineesStar(); //returns the list of all Timeses which are ContainedStar in some Times node
	vector<int>  getAllTimesMinusContainersStar(); //returns the list of all Times nodes which contain* some minus
	vector<int>  getAllTimesMinusContaineesStar(); //returns the list of all minuses which are ContainedStar in some Times node
	vector<int>  getAllTimesTimesContainersStar(); //returns the list of all Times nodes which contain* some times nose
	vector<int>  getAllTimesTimesContaineesStar(); //returns the list of all times which are ContainedStar in some Times node
	

	//boolean functions
	bool isContainsStarProgProc(int, int); //returns true if contains*(prog,proc) holds
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


	

};