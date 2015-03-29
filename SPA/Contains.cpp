#pragma once

#include<iostream>
#include "Contains.h"

using namespace std;

//contains() relationships
	vector<pair<int, int>> progProc; //contains the program and the procedure that the program contains
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

	//vectorters

	//insert contains(prog,proc)
	static void insertProgProc(int progNum, int proc) {
		pair<int,int> record(progNum, proc);
		if(!isContainsProgProc(progNum, proc))
			progProc.push_back(record);
	}

	//insert contains(proc,stmtLst)
	static void insertProcStmtLst(int proc, int stmtLst){
		pair<int,int> record(proc, stmtLst);
		if(!isContainsProcStmtLst(proc,stmtLst))
			procStmtLst.push_back(record);
	}

	//insert contains(stmtLst,stmt)
	static void insertStmtLstStmt(int stmtLst,int stmt){
		pair<int,int> record(stmtLst,stmt);
		if(!isContainsStmtLstStmt(stmtLst,stmt))
			stmtLstStmt.push_back(record);

	}

	//insert contains(stmt,var)
	static void insertStmtVar(int stmt, int var){
		pair<int,int> record(stmt, var);
		if(!isContainsStmtVar(stmt, var))
			stmtVar.push_back(record);

	}

	//insert contains(stmt, const)
	static void insertStmtConst(int stmt, int constant){
		pair<int,int> record(stmt, constant);
		if(!isContainsStmtConst(stmt, constant))
			stmtConst.push_back(record);

	}

	//insert contains(stmt, plus)
	static void insertStmtPlus(int stmt, int plus){
		pair<int,int> record(stmt,plus);
		if(!isContainsStmtPlus(stmt,plus))
			stmtPlus.push_back(record);
	}

	//insert contains(stmt, minus)
	static void insertStmtMinus(int stmt, int minus) {
		pair<int,int> record(stmt,minus);
		if(!isContainsStmtMinus(stmt,minus))
			stmtMinus.push_back(record);
	}

	//insert contains(stmt,times)
	static void insertStmtTimes(int stmt, int times) {
		pair<int,int> record(stmt,times);
		if(!isContainsStmtTimes(stmt,times))
			stmtTimes.push_back(record);
	}

	//insert contains(stmt, stmtLst)
	static void insertStmtStmtLst(int stmt,int stmtLst){
		pair<int,int> record(stmt,stmtLst);
		if(!isContainsStmtStmtLst(stmt,stmtLst))
			stmtStmtLst.push_back(record);
	}

	// insert contains(plus,var)
	static void insertPlusVar(int plus, int var){
		pair<int,int> record(plus,var);
		if(!isContainsPlusVar(plus,var))
			plusVar.push_back(record);
	}

	//insert contains(plus,const)
	static void insertPlusConst(int plus, int constant){
		pair<int,int> record(plus,constant);
		if(!isContainsPlusConst(plus,constant))
			plusConst.push_back(record);
	}

	//insert contains(minus,var)
	static void insertMinusVar(int minus, int var){
		pair<int,int> record(minus,var);
		if(!isContainsMinusVar(minus,var))
			minusVar.push_back(record);
	}

	//insert contains(minus,contant)
	static void insertMinusConst(int minus, int constant) {
		pair<int,int> record(minus, constant);
		if(!isContainsMinusConst(minus,constant))
			minusConst.push_back(record);
	}

	//insert contains(times,var)
	static void insertTimesVar(int times, int var) {
		pair<int,int> record(times,var);
		if(!isContainsTimesVar(times,var))
			timesVar.push_back(record);
	}

	//insert contains(times,const)
	static void insertTimesConst(int times, int constant) {
		pair<int,int> record(times,constant);
		if(!isContainsTimesConst(times,constant))
			timesConst.push_back(record);
	}

	//insert contains(plus,plus)
	static void insertPlusPlus(int plus, int plus1){
		pair<int,int> record(plus,plus1);
		if(!isContainsPlusPlus(plus,plus1))
			plusPlus.push_back(record);
	}

	//insert contains(plus,minus)
	static void insertPlusMinus(int plus, int minus){
		pair<int,int> record(plus,minus);
		if(!isContainsPlusMinus(plus,minus))
			plusMinus.push_back(record);
	}

	//insert contains(Plus,Times)
	static void insertPlusTimes(int plus, int times){
		pair<int,int> record(plus,times);
		if(!isContainsPlusTimes(plus,times))
			plusTimes.push_back(record);
	}


	//insert contains(Minus,Times)
	static void insertMinusTimes(int minus, int times){
		pair<int,int> record(minus,times);
		if(!isContainsMinusTimes(minus,times))
			minusTimes.push_back(record);
	}

	//insert contains(Minus,plus)
	static void insertMinusPlus(int minus,int plus){
		pair<int,int> record(minus,plus);
		if(!isContainsMinusPlus(minus,plus))
			minusPlus.push_back(record);
	}

	//insert contains(minus,minus)
	static void insertMinusMinus(int minus, int minus1){
		pair<int,int> record(minus,minus1);
		if(!isContainsMinusMinus(minus,minus1))
			minusMinus.push_back(record);
	}

	//insert contains(times,plus)
	static void insertTimesPlus (int times, int plus){
		pair<int,int> record(times,plus);
		if(!isContainsTimesPlus(times,plus))
			timesPlus.push_back(record);
	}

	//insert contains(times,minus)
	static void insertTimesMinus(int times, int plus){
		pair<int,int> record(times,plus);
		if(!isContainsTimesMinus(times,plus))
			timesMinus.push_back(record);
	}

	//insert contains(times,times)
	static void insertTimesTimes(int times, int times1){
		pair<int,int> record(times,times1);
		if(!isContainsTimesTimes(times,times1))
			timesTimes.push_back(record);
	}

	//getters

	//for program ContainerStar
	//returns the procedures Contained within a program
	static vector<int> getProcContainedInProg (int) { 
		 

	}
	
	static vector<int> getProgContainingProc (int);  //return the program which contains the procedure
	
	//for procedures as containers
	static vector<int> getStmtLstContainedInProc(int); //returns the statement list contained in proc (WILL NEVER BE QUERIED !!!)
	static vector<int> getProcContainingStmtLst(int); //returns the procedure which contains the given stmtLst

	//for statementlist as containers
	static vector<int> getStmtContainedInStmtLst(int) ; //returns the statements contained in statement list
	static vector<int> getStmtLstContainingStmt(int); //returns the statementlist containing statements

	//for statements as containers
	static vector<int> getVarContainedInStmt (int);   //returns the variables contained in a stmt
	static vector<int> getStmtContainingVar (int);   //returns the statements which conatins the variable
	static vector<int> getConstContainedInStmt (int);  //returns the constants which are conatined within a statement
	static vector<int> getStmtContainingConst(int);  //returns the statements which contain the constant
	static vector<int> getStmtLstContainedInStmt (int) ; //returns the statementList which are contained in statement (WILL NEVER APPEAR AS QUERY!!!)
	static vector<int> getStmtContainingStmtLst (int); //returns the statements contain statementList 
	static vector<int> getPlusContainedInStmt(int); //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtContainingPlus(int); //returns the statements containing plus 
	static vector<int> getMinusContainedInStmt(int); //returns the minus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtContainingMinus(int); //returns the statements containing minus
	static vector<int> getTimesContainedInStmt(int); //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtContainingTimes(int); //returns the statements containing plus 


	//for plus node as container 
	static vector<int> getVarContainedInPlus(int); //returns all those variables which are children of the plus node in the AST
	static vector<int> getPlusContainingVar(int); //returns all those pluses which contain the variable node
	static vector<int> getConstContainedInPlus(int); //returns all those constants which are children of the plus node in the AST
	static vector<int> getPlusContainingConst(int); //returns all those pluses which contain the constant
	static vector<int> getPlusContainedInPlus(int); //returns all those plus which are children of the plus node in the AST
	static vector<int> getPlusContainingPlus(int); //returns all those pluses which contain the plus node
	static vector<int> getMinusContainedInPlus(int); //returns all those minus which are children of the plus node in the AST
	static vector<int> getPlusContainingMinus(int); //returns all those pluses which contain the minus node
	static vector<int> getTimesContainedInPlus(int); //returns all those times which are children of the plus node in the AST
	static vector<int> getPlusContainingTimes(int); //returns all those pluses which contain the times node

	//for minus node as container
	static vector<int> getVarContainedInMinus(int); //returns all those variables which are children of the minus node in the AST
	static vector<int> getMinusContainingVar(int); //returns all those minus which contain the variable node
	static vector<int> getConstContainedInMinus(int); //returns all those constants which are children of the minus node in the AST
	static vector<int> getMinusContainingConst(int); //returns all those minus which contain the constant
	static vector<int> getPlusContainedInMius(int); //returns all those plus which are children of the minus node in the AST
	static vector<int> getMinusContainingPlus(int); //returns all those minuses which contain the plus node
	static vector<int> getMinusContainedInMinus(int); //returns all those minus which are children of the minus node in the AST
	static vector<int> getMinusContainingMinus(int); //returns all those minus which contain the minus node
	static vector<int> getTimesContainedInMinus(int); //returns all those times which are children of the minus node in the AST
	static vector<int> getMinusContainingTimes(int); //returns all those minuses which contain the times node

	//for times node as container
	static vector<int> getVarContainedInTimes(int); //returns all those variables which are children of the times node in the AST
	static vector<int> getTimesContainingVar(int); //returns all those times which contain the variable node
	static vector<int> getConstContainedInTimes(int); //returns all those constants which are children of the times node in the AST
	static vector<int> getTimesContainingConst(int); //returns all those times which contain the constant
	static vector<int> getPlusContainedInTimes(int); //returns all those plus which are children of the times node in the AST
	static vector<int> getTimesContainingPlus(int); //returns all those times which contain the plus node
	static vector<int> getMinusContainedInTimes(int); //returns all those minus which are children of the times node in the AST
	static vector<int> getTimesContainingMinus(int); //returns all those times which contain the minus node
	static vector<int> getTimesContainedInTimes(int); //returns all those times which are children of the times node in the AST
	static vector<int> getTimesContainingTimes(int); //returns all those times which contain the times node

	//get all container and Containees
	//for program as container
	static vector<int> getAllProgProcContainers();  //returns all the programs which contain some procedure
	static vector<int> getAllProgProcContainees(); //returns all the procedures which are contained within some program

	//for procedure as container
	static vector<int> getAllProcStmtLstContainers(); //returns the procedures which contain statement list
	static vector<int> getAllProcStmtLstContainees(); //return the statement list which are ocntained in some procedure

	//for statement list as container
	static vector<int> getAllStmtLstStmtContainers(); //returns the statementList which contain some statement
	static vector<int> getAllStmtLstStmtContainees(); //returns the statements which are contained withing a statement list

	//for statement as container
	static vector<int> getAllStmtStmtLstContainers(); // returns all the statements which contain some statementlist
	static vector<int> getAllStmtStmtLstContainees(); //returns all the statement list conatained within some statement
	static vector<int> getAllStmtVarContainers();  //returns all the statements which contain some variable
	static vector<int> getAllStmtVarContainees();  //returns all the variables contained within some statement
	static vector<int> getAllStmtConstContainers(); //returns all the statements which contain some constants
	static vector<int> getAllStmtConstContainees(); //returns all the constants conatained within some statement
	static vector<int> getAllStmtPlusContainers(); //returns all the statements which contain some plus
	static vector<int> getAllStmtPlusContainees(); //return all the pluses which are contained within a statement
	static vector<int> getAllStmtMinusContainers(); //return all the statements which contain some minus
	static vector<int> getAllStmtMinusContainees(); //return all the minuses which are contained in some statement
	static vector<int> getAllStmtTimesContainers(); //return all the statements which contain some times node
	static vector<int> getAllStmtTimesContainees(); //return all the times nodes which are contained within a statement

	// for plus node as container 
	static vector<int> getAllPlusVarContainers(); //returns the list of all plus nodes which contain some variable
	static vector<int> getAllPlusVarContainees(); //returns the list of all variables which are contained in some plus node
	static vector<int> getAllPlusConstContainers(); //returns the list of all plus nodes which contain some constant
	static vector<int> getAllPlusConstContainees(); //returns the list of all constants which are contained in some plus node
	static vector<int> getAllPlusPlusContainers(); //returns the list of all plus nodes which contain some plus nodes
	static vector<int> getAllPlusPlusContainees(); //returns the list of all pluses which are contained in some plus node
	static vector<int> getAllPlusMinusContainers(); //returns the list of all plus nodes which contain some minus
	static vector<int> getAllPlusMinusContainees(); //returns the list of all minuses which are contained in some plus node
	static vector<int> getAllPlusTimesContainers(); //returns the list of all plus nodes which contain some times nose
	static vector<int> getAllPlusTimesContainees(); //returns the list of all times which are contained in some plus node
	
	//for minus node as container
	static vector<int> getAllMinusVarContainers(); //returns the list of all minus nodes which contain some variable
	static vector<int> getAllMinusVarContainees(); //returns the list of all variables which are contained in some minus node
	static vector<int> getAllMinusConstContainers(); //returns the list of all minus nodes which contain some constant
	static vector<int> getAllMinusConstContainees(); //returns the list of all constants which are contained in some minus node
	static vector<int> getAllMinusPlusContainers(); //returns the list of all minus nodes which contain some minus nodes
	static vector<int> getAllMinusPlusContainees(); //returns the list of all minuses which are contained in some minus node
	static vector<int> getAllMinusMinusContainers(); //returns the list of all minus nodes which contain some minus
	static vector<int> getAllMinusMinusContainees(); //returns the list of all minuses which are contained in some minus node
	static vector<int> getAllMinusTimesContainers(); //returns the list of all minus nodes which contain some times nose
	static vector<int> getAllMinusTimesContainees(); //returns the list of all times which are contained in some minus node
	
	//for times node as container
	static vector<int> getAllTimesVarContainers(); //returns the list of all Times nodes which contain some variable
	static vector<int> getAllTimesVarContainees(); //returns the list of all variables which are contained in some Times node
	static vector<int> getAllTimesConstContainers(); //returns the list of all Times nodes which contain some constant
	static vector<int> getAllTimesConstContainees(); //returns the list of all constants which are contained in some Times node
	static vector<int> getAllTimesPlusContainers(); //returns the list of all Times nodes which contain some Times nodes
	static vector<int> getAllTimesPlusContainees(); //returns the list of all Timeses which are contained in some Times node
	static vector<int> getAllTimesMinusContainers(); //returns the list of all Times nodes which contain some minus
	static vector<int> getAllTimesMinusContainees(); //returns the list of all minuses which are contained in some Times node
	static vector<int> getAllTimesTimesContainers(); //returns the list of all Times nodes which contain some times nose
	static vector<int> getAllTimesTimesContainees(); //returns the list of all times which are contained in some Times node
	

	//boolean functions
	static bool isContainsProgProc(int, int); //returns true if contains(prog,proc) holds
	static bool isContainsProcStmtLst(int, int); //returns true if contains(proc,stmtlst) holds
	static bool isContainsStmtLstStmt(int,int); //returns true if contains(stmtLst, stmt) holds
	static bool isContainsStmtVar(int,int); //returns true if contains(Stmt,var) holds  
	static bool isContainsStmtConst(int,int); //returns true if contains(Stmt,Const) holds 
	static bool isContainsStmtPlus(int,int); //returns true if contains(stmt,plus) holds
	static bool isContainsStmtMinus(int,int); //returns true if contains(stmt,minus) holds 
	static bool isContainsStmtTimes(int,int); //returns true if contains(stmt, times) holds 
	static bool isContainsStmtStmtLst(int,int); //returns true if contains(stmt,stmtlst) holds 
	static bool isContainsPlusVar(int,int); //returns true if contains(plus,var) holds 
	static bool isContainsPlusConst(int,int); //returns true if contains(plus,const) holds
	static bool isContainsMinusVar(int,int); //returns true if contains(minus,var) holds
	static bool isContainsMinusConst(int,int); //returns true if contains(minus,const) holds
	static bool isContainsTimesVar(int,int); //returns true if contains(times,var) holds
	static bool isContainsTimesConst(int,int); //returns true if contains(times,const) holds
	static bool isContainsPlusPlus(int,int); //returns true if contains(plus,plus) holds
	static bool isContainsPlusMinus(int,int); //return true if contains(plus,minus) holds
	static bool isContainsPlusTimes(int,int); //returns true if contains(plus,plus) holds
	static bool isContainsMinusTimes(int,int); //return true if contains(minus,times) holds
	static bool isContainsMinusPlus(int,int); //returns true if contains(minus,plus) holds
	static bool isContainsMinusMinus(int,int); //return true if contains(minus,minus) holds
	static bool isContainsTimesPlus (int,int); //return true if contains(times,plus) holds 
	static bool isContainsTimesMinus(int,int); // return true if contains(times,minus) holds
	static bool isContainsTimesTimes(int,int); // return true if contains(times,times) holds 


	
	//***********************************************************************************************************************************************************************************************************
	//contains *
	//***********************************************************************************************************************************************************************************************************

	//for program containers
	static vector<int> getProcContainedStarInProg (int);  //returns the procedures contained within a program
	static vector<int> getProgContainingStarProc (int);  //return the program which contains* the procedure
	
	//for procedures as containers
	static vector<int> getStmtLstContainedStarInProc(int); //returns the statement list ContainedStar in proc (WILL NEVER BE QUERIED !!!)
	static vector<int> getProcContainingStarStmtLst(int); //returns the procedure which contains the given stmtLst directly/indirectly
	static vector<int> getStmtContainedStarInProc(int) ; //returns statement which is contained in a proc directly/indirectly
	static vector<int> getProcContainingStarStmt(int); //returns the proc which contains statements directly/indirectly
	static vector<int> getVarContainedStarInProc (int);   //returns the variables ContainedStar in a proc
	static vector<int> getProcsContainingStarVar (int);   //returns the procedures which conatins the variable
	static vector<int> getConstContainedStarInProc (int);  //returns the constants which are contained within a procedure
	static vector<int> getProcContainingStarConst(int);  //returns the procedures which contain the constant
	static vector<int> getPlusContainedStarInProc(int); //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getProcContainingStarPlus(int); //returns the procedure ContainingStar plus 
	static vector<int> getMinusContainedStarInProc(int); //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getProcContainingStarMinus(int); //returns the procedure ContainingStar minus
	static vector<int> getTimesContainedStarInProc(int); //returns the times ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getProcContainingStarTimes(int); //returns the procedures ContainingStartimes

	//for statementlist as containers
	static vector<int> getStmtContainedStarInStmtLst(int) ; //returns the statements ContainedStar in statement list
	static vector<int> getStmtLstContainingStarStmt(int); //returns the statementlist ContainingStar statements
	static vector<int> getVarContainedStarInStmtLst (int);   //returns the variables ContainedStar in a stmtlist
	static vector<int> getStmtLstContainingStarVar (int);   //returns the statementlist which conatins the variable
	static vector<int> getConstContainedStarInStmtLst (int);  //returns the constants which are contained within a statementlist
	static vector<int> getStmtLstContainingStarConst(int);  //returns the statementlist which contain the constant
	static vector<int> getPlusContainedStarInStmtLst(int); //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtLstContainingStarPlus(int); //returns the statementlist ContainingStar plus 
	static vector<int> getMinusContainedStarInStmtLst(int); //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtLstContainingStarMinus(int); //returns the statementlist ContainingStar minus
	static vector<int> getTimesContainedStarInStmtLst(int); //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtLstContainingStarTimes(int); //returns the statementlist ContainingStar times
	static vector<int> getStmtLstContainingStarStmtLst(int);  //returns the statementlist which contain the statementList
	static vector<int> getStmtLstContainedStarInStmtLst (int) ; //returns the statementList which are ContainedStar in statementLst 
	
	
	//for statements as containers
	static vector<int> getVarContainedStarInStmt (int);   //returns the variables ContainedStar in a stmt
	static vector<int> getStmtContainingStarVar (int);   //returns the statements which conatins the variable
	static vector<int> getConstContainedStarInStmt (int);  //returns the constants which are contained within a statement
	static vector<int> getStmtContainingStarConst(int);  //returns the statements which contain the constant
	static vector<int> getStmtLstContainedStarInStmt (int) ; //returns the statementList which are ContainedStar in statement (WILL NEVER APPEAR AS QUERY!!!)
	static vector<int> getStmtContainingStarStmtLst (int); //returns the statements contain statementList 
	static vector<int> getPlusContainedStarInStmt(int); //returns the plus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtContainingStarPlus(int); //returns the statements ContainingStar plus 
	static vector<int> getMinusContainedStarInStmt(int); //returns the minus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtContainingStarMinus(int); //returns the statements ContainingStar minus
	static vector<int> getTimesContainedStarInStmt(int); //returns the times ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getStmtContainingStarTimes(int); //returns the statements ContainingStar times 


	//for plus node as container 
	static vector<int> getVarContainedStarInPlus(int); //returns all those variables which are children of the plus node in the AST
	static vector<int> getPlusContainingStarVar(int); //returns all those pluses which contain the variable node
	static vector<int> getConstContainedStarInPlus(int); //returns all those constants which are children of the plus node in the AST
	static vector<int> getPlusContainingStarConst(int); //returns all those pluses which contain the constant
	static vector<int> getPlusContainedStarInPlus(int); //returns all those plus which are children of the plus node in the AST
	static vector<int> getPlusContainingStarPlus(int); //returns all those pluses which contain the plus node
	static vector<int> getMinusContainedStarInPlus(int); //returns all those minus which are children of the plus node in the AST
	static vector<int> getPlusContainingStarMinus(int); //returns all those pluses which contain the minus node
	static vector<int> getTimesContainedStarInPlus(int); //returns all those times which are children of the plus node in the AST
	static vector<int> getPlusContainingStarTimes(int); //returns all those pluses which contain the times node

	//for minus node as container
	static vector<int> getVarContainedStarInMinus(int); //returns all those variables which are children of the minus node in the AST
	static vector<int> getMinusContainingStarVar(int); //returns all those minus which contain the variable node
	static vector<int> getConstContainedStarInMinus(int); //returns all those constants which are children of the minus node in the AST
	static vector<int> getMinusContainingStarConst(int); //returns all those minus which contain the constant
	static vector<int> getPlusContainedStarInMius(int); //returns all those plus which are children of the minus node in the AST
	static vector<int> getMinusContainingStarPlus(int); //returns all those minuses which contain the plus node
	static vector<int> getMinusContainedStarInMinus(int); //returns all those minus which are children of the minus node in the AST
	static vector<int> getMinusContainingStarMinus(int); //returns all those minus which contain the minus node
	static vector<int> getTimesContainedStarInMinus(int); //returns all those times which are children of the minus node in the AST
	static vector<int> getMinusContainingStarTimes(int); //returns all those minuses which contain the times node

	//for times node as container
	static vector<int> getVarContainedStarInTimes(int); //returns all those variables which are children of the times node in the AST
	static vector<int> getTimesContainingStarVar(int); //returns all those times which contain the variable node
	static vector<int> getConstContainedStarInTimes(int); //returns all those constants which are children of the times node in the AST
	static vector<int> getTimesContainingStarConst(int); //returns all those times which contain the constant
	static vector<int> getPlusContainedStarInTimes(int); //returns all those plus which are children of the times node in the AST
	static vector<int> getTimesContainingStarPlus(int); //returns all those times which contain the plus node
	static vector<int> getMinusContainedStarInTimes(int); //returns all those minus which are children of the times node in the AST
	static vector<int> getTimesContainingStarMinus(int); //returns all those times which contain the minus node
	static vector<int> getTimesContainedStarInTimes(int); //returns all those times which are children of the times node in the AST
	static vector<int> getTimesContainingStarTimes(int); //returns all those times which contain the times node

	//get all container and containees 
	//for program as container
	static vector<int> getAllProgProcContainersStar();  //returns all the programs which contain* some procedure
	static vector<int> getAllProgProcContaineesStar(); //returns all the procedures which are ContainedStar within some program

	//for procedure as container
	static vector<int> getAllProcStmtLstContainersStar(); //returns the procedures which contain* statement list
	static vector<int> getAllProcStmtLstContaineesStar(); //return the statement list which are contained* in some procedure
	static vector<int> getALLProcStmtContaineesStar() ; //returns all the statements which is contained in a proc directly/indirectly
	static vector<int> getAllProcStmtContainersStar(); //returns all the procs which contains statements directly/indirectly
	static vector<int> getAllProcVarContaineesStar();   //returns all the variables ContainedStar in a proc
	static vector<int> getAllProcVarContainersStar();   //returns all the procedures which contains* the variable
	static vector<int> getAllProcConstContainees();  //returns all the constants which are contained* within a procedure
	static vector<int> getAllProcConstContainers();  //returns all the procedures which contain* the constant
	static vector<int> getAllProcPlusContainees(); //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getAllProcPlusContainers(); //returns the procedure ContainingStar plus 
	static vector<int> getAllProcMinusContainees(); //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getAllProcMinusContainers(); //returns the procedure ContainingStar minus
	static vector<int> getAllProcTimesContainees(int); //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getAllProcTimesContainers(int); //returns the procedures ContainingStar times


	//for statement list as container
	static vector<int> getAllStmtLstStmtContainersStar(); //returns the statementList which contain* some statement
	static vector<int> getAllStmtLstStmtContaineesStar(); //returns the statements which are ContainedStar withing a statement list
	static vector<int> getAllStmtLstVarContainees();   //returns all the variables ContainedStar in a stmtlist
	static vector<int> getAllStmtLstVarContainers();   //returns the statementlist which conatins the variable
	static vector<int> getAllStmtLstConstContainees();  //returns the constants which are contained within a statementlist
	static vector<int> getAllStmtLstConstContainers();  //returns the statementlist which contain the constant
	static vector<int> getAllStmtLstPlusContainees(); //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getAllStmtLstPlusContainers(); //returns the statementlist ContainingStar plus 
	static vector<int> getAllStmtLstMinusContainees(); //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getAllStmtLstMinusContainers(); //returns the statementlist ContainingStar minus
	static vector<int> getAllStmtLstTimesContainees(); //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	static vector<int> getAllStmtLstTimesContainers(); //returns the statementlist ContainingStar times
	static vector<int> getAllStmtLstStmtLstContainees();  //returns the statementlist which contain the statementList
	static vector<int> getAllStmtLstStmtLstContainers(); //returns the statementList which are ContainedStar in statementLst 
	


	//for statement as container
	static vector<int> getAllStmtStmtLstContainersStar(); // returns all the statements which contain* some statementlist
	static vector<int> getAllStmtStmtLstContaineesStar(); //returns all the statement list conatained within some statement
	static vector<int> getAllStmtVarContaineesStar();  //returns all the statements which contain* some variable
	static vector<int> getAllStmtVarContainersStar();  //returns all the variables ContainedStar within some statement
	static vector<int> getAllStmtConstContaineesStar(); //returns all the statements which contain* some constants
	static vector<int> getAllStmtConstContainersStar(); //returns all the constants conatained within some statement
	static vector<int> getAllStmtPlusContaineesStar(); //returns all the statements which contain* some plus
	static vector<int> getAllStmtPlusContainersStar(); //return all the pluses which are ContainedStar within a statement
	static vector<int> getAllStmtMinusContainersStar(); //return all the statements which contain* some minus
	static vector<int> getAllStmtMinusContaineesStar(); //return all the minuses which are ContainedStar in some statement
	static vector<int> getAllStmtTimesContainersStar(); //return all the statements which contain* some times node
	static vector<int> getAllStmtTimesContaineesStar(); //return all the times nodes which are ContainedStar within a statement

	// for plus node as container 
	static vector<int> getAllPlusVarContainersStar(); //returns the list of all plus nodes which contain* some variable
	static vector<int> getAllPlusVarContaineesStar(); //returns the list of all variables which are ContainedStar in some plus node
	static vector<int> getAllPlusConstContainersStar(); //returns the list of all plus nodes which contain* some constant
	static vector<int> getAllPlusConstContaineesStar(); //returns the list of all constants which are ContainedStar in some plus node
	static vector<int> getAllPlusPlusContainersStar(); //returns the list of all plus nodes which contain* some plus nodes
	static vector<int> getAllPlusPlusContaineesStar(); //returns the list of all pluses which are ContainedStar in some plus node
	static vector<int> getAllPlusMinusContainersStar(); //returns the list of all plus nodes which contain* some minus
	static vector<int> getAllPlusMinusContaineesStar(); //returns the list of all minuses which are ContainedStar in some plus node
	static vector<int> getAllPlusTimesContainersStar(); //returns the list of all plus nodes which contain* some times nose
	static vector<int> getAllPlusTimesContaineesStar(); //returns the list of all times which are ContainedStar in some plus node
	
	//for minus node as container
	static vector<int> getAllMinusVarContainersStar(); //returns the list of all minus nodes which contain* some variable
	static vector<int> getAllMinusVarContaineesStar(); //returns the list of all variables which are ContainedStar in some minus node
	static vector<int> getAllMinusConstContainersStar(); //returns the list of all minus nodes which contain* some constant
	static vector<int> getAllMinusConstContaineesStar(); //returns the list of all constants which are ContainedStar in some minus node
	static vector<int> getAllMinusPlusContainersStar(); //returns the list of all minus nodes which contain* some minus nodes
	static vector<int> getAllMinusPlusContaineesStar(); //returns the list of all minuses which are ContainedStar in some minus node
	static vector<int> getAllMinusMinusContainersStar(); //returns the list of all minus nodes which contain* some minus
	static vector<int> getAllMinusMinusContaineesStar(); //returns the list of all minuses which are ContainedStar in some minus node
	static vector<int> getAllMinusTimesContainersStar(); //returns the list of all minus nodes which contain* some times nose
	static vector<int> getAllMinusTimesContaineesStar(); //returns the list of all times which are ContainedStar in some minus node
	
	//for times node as container
	static vector<int> getAllTimesVarContainersStar(); //returns the list of all Times nodes which contain* some variable
	static vector<int> getAllTimesVarContaineesStar(); //returns the list of all variables which are ContainedStar in some Times node
	static vector<int> getAllTimesConstContainersStar(); //returns the list of all Times nodes which contain* some constant
	static vector<int> getAllTimesConstContaineesStar(); //returns the list of all constants which are ContainedStar in some Times node
	static vector<int> getAllTimesPlusContainersStar(); //returns the list of all Times nodes which contain* some Times nodes
	static vector<int> getAllTimesPlusContaineesStar(); //returns the list of all Timeses which are ContainedStar in some Times node
	static vector<int> getAllTimesMinusContainersStar(); //returns the list of all Times nodes which contain* some minus
	static vector<int> getAllTimesMinusContaineesStar(); //returns the list of all minuses which are ContainedStar in some Times node
	static vector<int> getAllTimesTimesContainersStar(); //returns the list of all Times nodes which contain* some times nose
	static vector<int> getAllTimesTimesContaineesStar(); //returns the list of all times which are ContainedStar in some Times node
	

	//boolean functions
	static bool isContainsStarProgProc(int, int); //returns true if contains*(prog,proc) holds
	static bool isContainsStarProcStmtLst(int, int); //returns true if contains*(proc,stmtlst) holds
	static bool isContainsStarProcStmt(int, int); //returns true if contains*(proc,stmt) holds
	static bool isContainsStarProcVar(int, int); //returns true if contains*(proc,var) holds
	static bool isContainsStarProcPlus(int, int); //returns true if contains*(proc,plus) holds
	static bool isContainsStarProcConst(int, int); //returns true if contains*(proc,const) holds
	static bool isContainsStarProcMinus(int, int); //returns true if contains*(proc,minus) holds
	static bool isContainsStarProcTimes(int, int); //returns true if contains*(proc,times) holds
	static bool isContainsStarStmtLstStmt(int,int); //returns true if contains*(stmtLst, stmt) holds
	static bool isContainsStarStmtLstVar(int,int); //returns true if contains*(stmtLst, var) holds
	static bool isContainsStarStmtLstConst(int,int); //returns true if contains*(stmtLst, const) holds
	static bool isContainsStarStmtLstPlus(int,int); //returns true if contains*(stmtLst, plus) holds
	static bool isContainsStarStmtLstMinus(int,int); //returns true if contains*(stmtLst, minus) holds
	static bool isContainsStarStmtLstTimes(int,int); //returns true if contains*(stmtLst, times) holds
	static bool isContainsStarStmtLstStmtLst(int,int); //returns true if contains*(stmtLst,stmtLst) hold
	static bool isContainsStarStmtVar(int,int); //returns true if contains*(Stmt,var) holds  
	static bool isContainsStarStmtConst(int,int); //returns true if contains*(Stmt,Const) holds 
	static bool isContainsStarStmtPlus(int,int); //returns true if contains*(stmt,plus) holds
	static bool isContainsStarStmtMinus(int,int); //returns true if contains*(stmt,minus) holds 
	static bool isContainsStarStmtTimes(int,int); //returns true if contains*(stmt, times) holds 
	static bool isContainsStarStmtStmtLst(int,int); //returns true if contains*(stmt,stmtlst) holds 
	static bool isContainsStarPlusVar(int,int); //returns true if contains*(plus,var) holds 
	static bool isContainsStarPlusConst(int,int); //returns true if contains*(plus,const) holds
	static bool isContainsStarMinusVar(int,int); //returns true if contains*(minus,var) holds
	static bool isContainsStarMinusConst(int,int); //returns true if contains*(minus,const) holds
	static bool isContainsStarTimesVar(int,int); //returns true if contains*(times,var) holds
	static bool isContainsStarTimesConst(int,int); //returns true if contains*(times,const) holds
	static bool isContainsStarPlusPlus(int,int); //returns true if contains*(plus,plus) holds
	static bool isContainsStarPlusMinus(int,int); //return true if contains*(plus,minus) holds
	static bool isContainsStarPlusTimes(int,int); //returns true if contains*(plus,plus) holds
	static bool isContainsStarMinusTimes(int,int); //return true if contains*(minus,times) holds
	static bool isContainsStarMinusPlus(int,int); //returns true if contains*(minus,plus) holds
	static bool isContainsStarMinusMinus(int,int); //return true if contains*(minus,minus) holds
	static bool isContainsStarTimesPlus (int,int); //return true if contains*(times,plus) holds 
	static bool isContainsStarTimesMinus(int,int); // return true if contains*(times,minus) holds
	static bool isContainsStarTimesTimes(int,int); // return true if contains*(times,times) holds 

