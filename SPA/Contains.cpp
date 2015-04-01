#pragma once
#include "Contains.h" 
#include<iostream>

using namespace std;
	
Contains::Contains(){

}
		
	//containers

	//insert contains(prog,proc)
	void Contains::insertProgProc(int progNum, int proc) {
		pair<int,int> record(progNum, proc);
		if(isContainsProgProc(progNum, proc)==false)
			progProc.push_back(record);
	}

	//insert contains(proc,stmtLst)
	void Contains::insertProcStmtLst(int proc, int stmtLst){
		pair<int,int> record(proc, stmtLst);
		if(isContainsProcStmtLst(proc,stmtLst)==false)
			procStmtLst.push_back(record);
	}

	//insert contains(stmtLst,stmt)
	void Contains::insertStmtLstStmt(int stmtLst,int stmt){
		pair<int,int> record(stmtLst,stmt);
		if(!isContainsStmtLstStmt(stmtLst,stmt))
			stmtLstStmt.push_back(record);

	}

	//insert contains(stmt,var)
	void Contains::insertStmtVar(int stmt, int var){
		pair<int,int> record(stmt, var);
		if(isContainsStmtVar(stmt, var)==false)
			stmtVar.push_back(record);

	}

	//insert contains(stmt, const)
	void Contains::insertStmtConst(int stmt, int constant){
		pair<int,int> record(stmt, constant);
		if(isContainsStmtConst(stmt, constant)==false)
			stmtConst.push_back(record);

	}

	//insert contains(stmt, plus)
	void Contains::insertStmtPlus(int stmt, int plus){
		pair<int,int> record(stmt,plus);
		if(isContainsStmtPlus(stmt,plus)==false)
			stmtPlus.push_back(record);
	}

	//insert contains(stmt, minus)
	void Contains::insertStmtMinus(int stmt, int minus) {
		pair<int,int> record(stmt,minus);
		if(isContainsStmtMinus(stmt,minus)==false)
			stmtMinus.push_back(record);
	}

	//insert contains(stmt,times)
	void Contains::insertStmtTimes(int stmt, int times) {
		pair<int,int> record(stmt,times);
		if(isContainsStmtTimes(stmt,times)==false)
			stmtTimes.push_back(record);
	}

	//insert contains(stmt, stmtLst)
	void Contains::insertStmtStmtLst(int stmt,int stmtLst){
		pair<int,int> record(stmt,stmtLst);
		if(isContainsStmtStmtLst(stmt,stmtLst)==false)
			stmtStmtLst.push_back(record);
	}

	// insert contains(plus,var)
	void Contains::insertPlusVar(int plus, int var){
		pair<int,int> record(plus,var);
		if(isContainsPlusVar(plus,var)==false)
			plusVar.push_back(record);
	}

	//insert contains(plus,const)
	void Contains::insertPlusConst(int plus, int constant){
		pair<int,int> record(plus,constant);
		if(isContainsPlusConst(plus,constant)==false)
			plusConst.push_back(record);
	}

	//insert contains(minus,var)
	void Contains::insertMinusVar(int minus, int var){
		pair<int,int> record(minus,var);
		if(isContainsMinusVar(minus,var)==false)
			minusVar.push_back(record);
	}

	//insert contains(minus,contant)
	void Contains::insertMinusConst(int minus, int constant) {
		pair<int,int> record(minus, constant);
		if(isContainsMinusConst(minus,constant)==false)
			minusConst.push_back(record);
	}

	//insert contains(times,var)
	void Contains::insertTimesVar(int times, int var) {
		pair<int,int> record(times,var);
		if(isContainsTimesVar(times,var)==false)
			timesVar.push_back(record);
	}

	//insert contains(times,const)
	void Contains::insertTimesConst(int times, int constant) {
		pair<int,int> record(times,constant);
		if(isContainsTimesConst(times,constant)==false)
			timesConst.push_back(record);
	}

	//insert contains(plus,plus)
	void Contains::insertPlusPlus(int plus, int plus1){
		pair<int,int> record(plus,plus1);
		if(isContainsPlusPlus(plus,plus1)==false)
			plusPlus.push_back(record);
	}

	//insert contains(plus,minus)
	void Contains::insertPlusMinus(int plus, int minus){
		pair<int,int> record(plus,minus);
		if(isContainsPlusMinus(plus,minus)==false)
			plusMinus.push_back(record);
	}

	//insert contains(Plus,Times)
	void Contains::insertPlusTimes(int plus, int times){
		pair<int,int> record(plus,times);
		if(isContainsPlusTimes(plus,times)==false)
			plusTimes.push_back(record);
	}


	//insert contains(Minus,Times)
	void Contains::insertMinusTimes(int minus, int times){
		pair<int,int> record(minus,times);
		if(isContainsMinusTimes(minus,times)==false)
			minusTimes.push_back(record);
	}

	//insert contains(Minus,plus)
	void Contains::insertMinusPlus(int minus,int plus){
		pair<int,int> record(minus,plus);
		if(isContainsMinusPlus(minus,plus)==false)
			minusPlus.push_back(record);
	}

	//insert contains(minus,minus)
	void Contains::insertMinusMinus(int minus, int minus1){
		pair<int,int> record(minus,minus1);
		if(isContainsMinusMinus(minus,minus1)==false)
			minusMinus.push_back(record);
	}

	//insert contains(times,plus)
	void Contains::insertTimesPlus (int times, int plus){
		pair<int,int> record(times,plus);
		if(isContainsTimesPlus(times,plus)==false)
			timesPlus.push_back(record);
	}

	//insert contains(times,minus)
	void Contains::insertTimesMinus(int times, int plus){
		pair<int,int> record(times,plus);
		if(isContainsTimesMinus(times,plus)==false)
			timesMinus.push_back(record);
	}

	//insert contains(times,times)
	void Contains::insertTimesTimes(int times, int times1){
		pair<int,int> record(times,times1);
		if(isContainsTimesTimes(times,times1)==false)
			timesTimes.push_back(record);
	}

	//getters

	//for program ContainerStar
	//returns the procedures Contained within a program
	vector<int> Contains::getProcContainedInProg (int prog) {  
		vector<int> result;
		for(int i =0; i<progProc.size(); i++) {
			if(progProc[i].first == prog)
				result.push_back(progProc[i].second);
		}
		return result;
	}
	
	vector<int> Contains::getProgContainingProc (int proc) {  //return the program which contains the procedure
		vector<int> result;
		for(int i =0; i<progProc.size(); i++) {
			if(progProc[i].second == proc)
				result.push_back(progProc[i].first);
		}
		return result;
	}
	
	//for procedures as containers
	vector<int> Contains::getStmtLstContainedInProc(int proc) { //returns the statement list contained in proc (WILL NEVER BE QUERIED !!!)
		vector<int> result;
		for(int i =0; i<procStmtLst.size(); i++) {
			if(procStmtLst[i].first == proc)
				result.push_back(procStmtLst[i].second);
		}
		return result;
	}


	vector<int> Contains::getProcContainingStmtLst(int stmtLst) { //returns the procedure which contains the given stmtLst
		vector<int> result;
		for(int i =0; i<procStmtLst.size(); i++) {
			if(procStmtLst[i].second == stmtLst)
				result.push_back(procStmtLst[i].first);
		}
		return result;

	}

	//for statementlist as containers
	vector<int> Contains::getStmtContainedInStmtLst(int stmtLst) { //returns the statements contained in statement list
		vector<int> result;
		for(int i =0; i<stmtLstStmt.size(); i++) {
			if(stmtLstStmt[i].first == stmtLst)
				result.push_back(stmtLstStmt[i].second);
		}
		return result;

	}

	vector<int> Contains::getStmtLstContainingStmt(int stmt) { //returns the statementlist containing statements
		vector<int> result;
		for(int i =0; i<stmtLstStmt.size(); i++) {
			if(stmtLstStmt[i].second == stmt)
				result.push_back(stmtLstStmt[i].first);
		}
		return result;
	}


	//for statements as containers
	vector<int> Contains::getVarContainedInStmt (int stmt) {   //returns the variables contained in a stmt
		vector<int> result;
		for(int i=0; i<stmtVar.size(); i ++){
			if(stmtVar[i].first == stmt)
				result.push_back(stmtVar[i].second);
		}
		return result;

	}

	vector<int> Contains::getStmtContainingVar (int var) {   //returns the statements which conatins the variable
		vector<int> result;
		for(int i=0; i<stmtVar.size(); i ++){
			if(stmtVar[i].second == var)
				result.push_back(stmtVar[i].first);
		}
		return result;

	}

	vector<int> Contains::getConstContainedInStmt (int stmt) {  //returns the constants which are conatined within a statement
		vector<int> result;
		for(int i=0; i<stmtConst.size(); i++){
			if(stmtConst[i].first==stmt)
				result.push_back(stmtConst[i].second);
		}
		return result; 
	}

	vector<int> Contains::getStmtContainingConst(int constant ) {  //returns the statements which contain the constant
		vector<int> result;
		for(int i=0; i<stmtConst.size(); i++){
			if(stmtConst[i].second==constant)
				result.push_back(stmtConst[i].first);
		}
		return result;

	}

	vector<int> Contains::getStmtLstContainedInStmt (int stmt) { //returns the statementList which are contained in statement (WILL NEVER APPEAR AS QUERY!!!)
		vector<int> result;
		for(int i=0; i<stmtStmtLst.size(); i++){
			if(stmtStmtLst[i].first==stmt)
				result.push_back(stmtStmtLst[i].second);
		}
		return result;

	}

	vector<int> Contains::getStmtContainingStmtLst (int stmtLst) { //returns the statements contain statementList 
		vector<int> result;
		for(int i=0; i<stmtStmtLst.size(); i++){
			if(stmtStmtLst[i].second==stmtLst)
				result.push_back(stmtStmtLst[i].first);
		}
		return result;
	}

	vector<int> Contains::getPlusContainedInStmt(int stmt) { //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
		vector<int> result;
		for(int i=0; i<stmtPlus.size();i++){
			if(stmtPlus[i].first==stmt)
				result.push_back(stmtPlus[i].second);
		}
		return result;
	}


	vector<int> Contains::getStmtContainingPlus(int plus) { //returns the statements containing plus 
		vector<int> result;
		for(int i=0; i<stmtPlus.size();i++){
			if(stmtPlus[i].second==plus)
				result.push_back(stmtPlus[i].first);
		}
		return result;
	}


	vector<int> Contains::getMinusContainedInStmt(int stmt) { //returns the minus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
		vector<int> result;
		for(int i=0; i<stmtMinus.size();i++){
			if(stmtMinus[i].first==stmt)
				result.push_back(stmtMinus[i].second);
		}
		return result;
	}

	vector<int> Contains::getStmtContainingMinus(int minus) { //returns the statements containing minus
		vector<int> result;
		for(int i=0; i<stmtMinus.size();i++){
			if(stmtMinus[i].second==minus)
				result.push_back(stmtMinus[i].first);
		}
		return result;
	}

	vector<int> Contains::getTimesContainedInStmt(int stmt) { //returns the  imescontained in statement (WILL NEVER APPEAR AS QUERY !!!)
		vector<int> result;
		for(int i=0; i<stmtTimes.size();i++){
			if(stmtTimes[i].first==stmt)
				result.push_back(stmtTimes[i].second);
		}
		return result;
	}

	vector<int> Contains::getStmtContainingTimes(int times) { //returns the statements containing times
		vector<int> result;
		for(int i=0; i<stmtTimes.size();i++){
			if(stmtTimes[i].second==times)
				result.push_back(stmtTimes[i].first);
		}
		return result;
	}


	//for plus node as container 
	vector<int> Contains::getVarContainedInPlus(int plus) { //returns all those variables which are children of the plus node in the AST
		vector<int> result;
		for(int i=0; i<plusVar.size(); i++){
			if(plusVar[i].first==plus)
				result.push_back(plusVar[i].second);
		}
	return result;
	}

	vector<int> Contains::getPlusContainingVar(int var) { //returns all those pluses which contain the variable node
		vector<int> result;
		for(int i=0; i<plusVar.size(); i++){
			if(plusVar[i].second==var)
				result.push_back(plusVar[i].first);
		}
	return result;
	}

	vector<int> Contains::getConstContainedInPlus(int plus) { //returns all those constants which are children of the plus node in the AST
		vector<int> result;
		for(int i=0; i<plusConst.size(); i++){
			if(plusConst[i].first==plus)
				result.push_back(plusConst[i].second);
		}
	return result;
	}


	vector<int> Contains::getPlusContainingConst(int constant) { //returns all those pluses which contain the constant
		vector<int> result;
		for(int i=0; i<plusConst.size(); i++){
			if(plusConst[i].second==constant)
				result.push_back(plusConst[i].first);
		}
		return result;
	}

	vector<int> Contains::getPlusContainedInPlus(int plus) { //returns all those plus which are children of the plus node in the AST
		vector<int> result;
		for(int i=0; i<plusPlus.size(); i++){
			if(plusPlus[i].first==plus)
				result.push_back(plusPlus[i].second);
		}
		return result;
	}

	vector<int> Contains::getPlusContainingPlus(int plus) { //returns all those pluses which contain the plus node
		vector<int> result;
		for(int i=0; i<plusPlus.size(); i++){
			if(plusPlus[i].second==plus)
				result.push_back(plusPlus[i].first);
		}
		return result;
	}

	vector<int> Contains::getMinusContainedInPlus(int plus) { //returns all those minus which are children of the plus node in the AST
		vector<int> result;
		for(int i=0; i<plusMinus.size(); i++){
			if(plusMinus[i].first==plus)
				result.push_back(plusMinus[i].second);
		}
		return result;
	}

	vector<int> Contains::getPlusContainingMinus(int minus) { //returns all those pluses which contain the minus node
		vector<int> result;
		for(int i=0; i<plusMinus.size(); i++){
			if(plusMinus[i].second==minus)
				result.push_back(plusMinus[i].first);
		}
		return result;
	}

	vector<int> Contains::getTimesContainedInPlus(int plus) { //returns all those times which are children of the plus node in the AST
		vector<int> result;
		for(int i=0; i<timesPlus.size(); i++){
			if(timesPlus[i].first==plus)
				result.push_back(plusTimes[i].second);
		}
		return result;
	}

	vector<int> Contains::getPlusContainingTimes(int times) { //returns all those pluses which contain the times node
		vector<int> result;
		for(int i=0; i<timesPlus.size(); i++) {
			if(timesPlus[i].second==times)
				result.push_back(plusTimes[i].first);
		}
		return result;

	}

	//for minus node as container
	vector<int> Contains::getVarContainedInMinus(int minus) { //returns all those variables which are children of the minus node in the AST
		vector<int> result;
		for(int i=0; i<minusVar.size(); i++){
			if(minusVar[i].first==minus)
				result.push_back(minusVar[i].second);
		}
		return result;
	}

	vector<int> Contains::getMinusContainingVar(int var) { //returns all those minus which contain the variable node
		vector<int> result;
		for(int i=0; i<minusVar.size(); i++){
			if(minusVar[i].second==var)
				result.push_back(minusVar[i].first);
		}
		return result;
	}
	
	vector<int> Contains::getConstContainedInMinus(int minus) { //returns all those constants which are children of the minus node in the AST
		vector<int> result;
		for(int i=0; i<minusConst.size(); i++){
			if(minusConst[i].first==minus)
				result.push_back(minusConst[i].second);
		}
		return result;
	}

	vector<int> Contains::getMinusContainingConst(int constant) { //returns all those minus which contain the constant
		 vector<int> result;
		for(int i=0; i<minusConst.size(); i++){
			if(minusConst[i].second==constant)
				result.push_back(minusConst[i].first);
		}
		return result;
	}
	
	vector<int> Contains::getPlusContainedInMius(int minus) { //returns all those plus which are children of the minus node in the AST
		vector<int> result;
		for(int i=0; i<minusPlus.size(); i++){
			if(minusPlus[i].first==minus)
				result.push_back(minusPlus[i].second);
		}
		return result;
	}

	vector<int> Contains::getMinusContainingPlus(int plus) { //returns all those minuses which contain the plus node
		 vector<int> result;
		for(int i=0; i<minusPlus.size(); i++){
			if(minusPlus[i].second==plus)
				result.push_back(minusPlus[i].first);
		}
		return result;
	}

	vector<int> Contains::getMinusContainedInMinus(int minus) { //returns all those minus which are children of the minus node in the AST
		vector<int> result;
		for(int i=0; i<minusMinus.size(); i++) {
			if(minusMinus[i].first==minus)
				result.push_back(minusMinus[i].second);
		}
		return result;
	}

	vector<int> Contains::getMinusContainingMinus(int minus) { //returns all those minus which contain the minus node
		vector<int> result;
		for(int i=0; i<minusMinus.size(); i++){
			if(minusMinus[i].second==minus)
				result.push_back(minusMinus[i].first);
		}
		return result;
	}

	vector<int> Contains::getTimesContainedInMinus(int minus) { //returns all those times which are children of the minus node in the AST
		vector<int> result;
		for(int i=0; i<minusTimes.size(); i++) {
			if(minusTimes[i].first==minus)
				result.push_back(minusTimes[i].second);
		}
		return result;
	}

	vector<int> Contains::getMinusContainingTimes(int times) { //returns all those minuses which contain the times node
		vector<int> result;
		for(int i=0; i<minusTimes.size(); i++) {
			if(minusTimes[i].second==times)
				result.push_back(minusTimes[i].first);
		}
		return result;
	}

	//for times node as container
	vector<int> Contains::getVarContainedInTimes(int times) { //returns all those variables which are children of the times node in the AST
		vector<int> result;
		for(int i=0; i<timesVar.size(); i++){
			if(timesVar[i].first==times)
				result.push_back(timesVar[i].second);
		}
		return result;

	}

	vector<int> Contains::getTimesContainingVar(int var) { //returns all those times which contain the variable node
		vector<int> result;
		for(int i=0; i<timesVar.size(); i++){
			if(timesVar[i].second==var)
				result.push_back(timesVar[i].first);
		}
		return result;
	}

	vector<int> Contains::getConstContainedInTimes(int times) { //returns all those constants which are children of the times node in the AST
		vector<int> result;
		for(int i=0; i<timesConst.size(); i++){
			if(timesConst[i].first==times)
				result.push_back(timesConst[i].second);
		}
		return result;

	}
	
	vector<int> Contains::getTimesContainingConst(int constant) { //returns all those times which contain the constant
		vector<int> result;
		for(int i=0; i<timesConst.size(); i++){
			if(timesConst[i].second==constant)
				result.push_back(timesConst[i].first);
		}
		return result;

	}

	vector<int> Contains::getPlusContainedInTimes(int times) { //returns all those plus which are children of the times node in the AST
		vector<int> result;
		for(int i=0; i<timesPlus.size(); i++){
			if(timesPlus[i].first==times)
				result.push_back(timesPlus[i].second);
		}
		return result;
	}


	vector<int> Contains::getTimesContainingPlus(int plus) { //returns all those times which contain the plus node
		vector<int> result;
		for(int i=0; i<timesPlus.size(); i++){
			if(timesPlus[i].second==plus)
				result.push_back(timesPlus[i].first);
		}
		return result;
	}

	vector<int> Contains::getMinusContainedInTimes(int times) { //returns all those minus which are children of the times node in the AST
		vector<int> result;
		for(int i=0; i<timesMinus.size(); i++) {
			if(timesMinus[i].first==times)
				result.push_back(timesMinus[i].second);
		}
		return result;
	}


	vector<int> Contains::getTimesContainingMinus(int minus) { //returns all those times which contain the minus node
		vector<int> result;
		for(int i=0; i<timesMinus.size(); i++) {
			if(timesMinus[i].first==minus)
				result.push_back(timesMinus[i].second);
		}
		return result;
	}

	vector<int> Contains::getTimesContainedInTimes(int times) { //returns all those times which are children of the times node in the AST
		vector<int> result;
		for(int i=0; i<timesTimes.size(); i++) {
			if(timesTimes[i].first==times)
				result.push_back(timesTimes[i].second);
		}
		return result;
	}

	vector<int> Contains::getTimesContainingTimes(int times) { //returns all those times which contain the times node
		vector<int> result;
		for(int i=0; i<timesTimes.size(); i++) {
			if(timesTimes[i].second==times)
				result.push_back(timesTimes[i].first);
		}
		return result;
	}


	//get all container and Containees
	//for program as container
	vector<int> Contains::getAllProgProcContainers(){  //returns all the programs which contain some procedure
		vector<int> results;
		for(int i=0; i<progProc.size(); i++)
			results.push_back(progProc[i].first);
		return results;
	}

	vector<int> Contains::getAllProgProcContainees(){ //returns all the procedures which are contained within some program
		vector<int> results;
		for(int i=0; i<progProc.size(); i++)
			results.push_back(progProc[i].second);
		return results;
	}

	//for procedure as container
	vector<int> Contains::getAllProcStmtLstContainers(){ //returns the procedures which contain statement list
		vector<int> results;
		for(int i=0; i<procStmtLst.size(); i++)
			results.push_back(procStmtLst[i].first);
		return results;
	}

	vector<int> Contains::getAllProcStmtLstContainees(){ //return the statement list which are ocntained in some procedure
		vector<int> results;
		for(int i=0; i<procStmtLst.size(); i++)
			results.push_back(procStmtLst[i].second);
		return results;
	}

	//for statement list as container
	vector<int> Contains::getAllStmtLstStmtContainers(){ //returns the statementList which contain some statement
		vector<int> results;
		for(int i=0; i<stmtLstStmt.size(); i++)
			results.push_back(stmtLstStmt[i].first);
		return results;
	}

	vector<int> Contains::getAllStmtLstStmtContainees(){ //returns the statements which are contained withing a statement list
		vector<int> results;
		for(int i=0; i<stmtLstStmt.size(); i++)
			results.push_back(stmtLstStmt[i].second);
		return results;
	}

	//for statement as container
	vector<int> Contains::getAllStmtStmtLstContainers(){ // returns all the statements which contain some statementlist
		vector<int> results;
		for(int i=0; i<stmtStmtLst.size(); i++)
			results.push_back(stmtStmtLst[i].first);
		return results;
	}

	vector<int> Contains::getAllStmtStmtLstContainees(){ //returns all the statement list conatained within some statement
		vector<int> results;
		for(int i=0; i<stmtStmtLst.size(); i++)
			results.push_back(stmtStmtLst[i].second);
		return results;
	}

	vector<int> Contains::getAllStmtVarContainers(){  //returns all the statements which contain some variable
		vector<int> results;
		for(int i=0; i<stmtVar.size(); i++)
			results.push_back(stmtVar[i].first);
		return results;
	}

	vector<int> Contains::getAllStmtVarContainees(){  //returns all the variables contained within some statement
		vector<int> results;
		for(int i=0; i<stmtVar.size(); i++)
			results.push_back(stmtVar[i].second);
		return results;
	}

	vector<int> Contains::getAllStmtConstContainers(){ //returns all the statements which contain some constants
		vector<int> results;
		for(int i=0; i<stmtConst.size(); i++)
			results.push_back(stmtConst[i].first);
		return results;
	}

	vector<int> Contains::getAllStmtConstContainees(){ //returns all the constants conatained within some statement
		vector<int> results;
		for(int i=0; i<stmtConst.size(); i++)
			results.push_back(stmtConst[i].second);
		return results;
	}

	vector<int> Contains::getAllStmtPlusContainers(){ //returns all the statements which contain some plus
		vector<int> results;
		for(int i=0; i<stmtPlus.size(); i++)
			results.push_back(stmtPlus[i].first);
		return results;
	}

	vector<int> Contains::getAllStmtPlusContainees(){ //return all the pluses which are contained within a statement
		vector<int> results;
		for(int i=0; i<stmtPlus.size(); i++)
			results.push_back(stmtPlus[i].second);
		return results;
	}

	vector<int> Contains::getAllStmtMinusContainers(){ //return all the statements which contain some minus
		vector<int> results;
		for(int i=0; i<stmtMinus.size(); i++)
			results.push_back(stmtMinus[i].first);
		return results;
	}

	vector<int> Contains::getAllStmtMinusContainees(){ //return all the minuses which are contained in some statement
		vector<int> results;
		for(int i=0; i<stmtMinus.size(); i++)
			results.push_back(stmtMinus[i].second);
		return results;
	}

	vector<int> Contains::getAllStmtTimesContainers(){ //return all the statements which contain some times node
		vector<int> results;
		for(int i=0; i<stmtTimes.size(); i++)
			results.push_back(stmtTimes[i].first);
		return results;
	}

	vector<int> Contains::getAllStmtTimesContainees(){ //return all the times nodes which are contained within a statement
		vector<int> results;
		for(int i=0; i<stmtTimes.size(); i++)
			results.push_back(stmtTimes[i].second);
		return results;
	}

	// for plus node as container 
	vector<int> Contains::getAllPlusVarContainers(){ //returns the list of all plus nodes which contain some variable
		vector<int> results;
		for(int i=0; i<plusVar.size(); i++)
			results.push_back(plusVar[i].first);
		return results;
	}

	vector<int> Contains::getAllPlusVarContainees(){ //returns the list of all variables which are contained in some plus node
		vector<int> results;
		for(int i=0; i<plusVar.size(); i++)
			results.push_back(plusVar[i].second);
		return results;
	}

	vector<int> Contains::getAllPlusConstContainers(){ //returns the list of all plus nodes which contain some constant
		vector<int> results;
		for(int i=0; i<plusConst.size(); i++)
			results.push_back(plusConst[i].first);
		return results;
	}

	vector<int> Contains::getAllPlusConstContainees(){ //returns the list of all constants which are contained in some plus node
		vector<int> results;
		for(int i=0; i<plusConst.size(); i++)
			results.push_back(plusConst[i].second);
		return results;
	}

	vector<int> Contains::getAllPlusPlusContainers(){ //returns the list of all plus nodes which contain some plus nodes
		vector<int> results;
		for(int i=0; i<plusPlus.size(); i++)
			results.push_back(plusPlus[i].first);
		return results;
	}

	vector<int> Contains::getAllPlusPlusContainees(){ //returns the list of all pluses which are contained in some plus node
		vector<int> results;
		for(int i=0; i<plusPlus.size(); i++)
			results.push_back(plusPlus[i].second);
		return results;
	}

	vector<int> Contains::getAllPlusMinusContainers(){ //returns the list of all plus nodes which contain some minus
		vector<int> results;
		for(int i=0; i<plusMinus.size(); i++)
			results.push_back(plusMinus[i].first);
		return results;
	}

	vector<int> Contains::getAllPlusMinusContainees(){ //returns the list of all minuses which are contained in some plus node
		vector<int> results;
		for(int i=0; i<plusMinus.size(); i++)
			results.push_back(plusMinus[i].second);
		return results;
	}

	vector<int> Contains::getAllPlusTimesContainers(){ //returns the list of all plus nodes which contain some times nose
		vector<int> results;
		for(int i=0; i<plusTimes.size(); i++)
			results.push_back(plusTimes[i].first);
		return results;
	}

	vector<int> Contains::getAllPlusTimesContainees(){ //returns the list of all times which are contained in some plus node
		vector<int> results;
		for(int i=0; i<plusTimes.size(); i++)
			results.push_back(plusTimes[i].second);
		return results;
	}
	
	//for minus node as container
	vector<int> Contains::getAllMinusVarContainers(){ //returns the list of all minus nodes which contain some variable
		vector<int> results;
		for(int i=0; i<minusVar.size(); i++)
			results.push_back(minusVar[i].first);
		return results;
	}

	vector<int> Contains::getAllMinusVarContainees(){ //returns the list of all variables which are contained in some minus node
		vector<int> results;
		for(int i=0; i<minusVar.size(); i++)
			results.push_back(minusVar[i].second);
		return results;
	}

	vector<int> Contains::getAllMinusConstContainers(){ //returns the list of all minus nodes which contain some constant
		vector<int> results;
		for(int i=0; i<minusConst.size(); i++)
			results.push_back(minusVar[i].first);
		return results;
	}

	vector<int> Contains::getAllMinusConstContainees(){ //returns the list of all constants which are contained in some minus node
		vector<int> results;
		for(int i=0; i<minusConst.size(); i++)
			results.push_back(minusConst[i].second);
		return results;
	}

	vector<int> Contains::getAllMinusPlusContainers(){ //returns the list of all minus nodes which contain some minus nodes
		vector<int> results;
		for(int i=0; i<minusPlus.size(); i++)
			results.push_back(minusPlus[i].first);
		return results;
	}

	vector<int> Contains::getAllMinusPlusContainees(){ //returns the list of all minuses which are contained in some minus node
		vector<int> results;
		for(int i=0; i<minusPlus.size(); i++)
			results.push_back(minusPlus[i].second);
		return results;
	}

	vector<int> Contains::getAllMinusMinusContainers(){ //returns the list of all minus nodes which contain some minus
		vector<int> results;
		for(int i=0; i<minusMinus.size(); i++)
			results.push_back(minusMinus[i].first);
		return results;
	}

	vector<int> Contains::getAllMinusMinusContainees(){ //returns the list of all minuses which are contained in some minus node
		vector<int> results;
		for(int i=0; i<minusMinus.size(); i++)
			results.push_back(minusMinus[i].second);
		return results;
	}

	vector<int> Contains::getAllMinusTimesContainers(){ //returns the list of all minus nodes which contain some times node
		vector<int> results;
		for(int i=0; i<minusTimes.size(); i++)
			results.push_back(minusTimes[i].first);
		return results;
	}
	vector<int> Contains::getAllMinusTimesContainees(){ //returns the list of all times which are contained in some minus node
		vector<int> results;
		for(int i=0; i<minusTimes.size(); i++)
			results.push_back(minusTimes[i].second);
		return results;
	}

	
	//for times node as container
	vector<int> Contains::getAllTimesVarContainers(){ //returns the list of all Times nodes which contain some variable
		vector<int> results;
		for(int i=0; i<timesVar.size(); i++)
			results.push_back(timesVar[i].first);
		return results;
	}

	vector<int> Contains::getAllTimesVarContainees(){ //returns the list of all variables which are contained in some Times node
		vector<int> results;
		for(int i=0; i<timesVar.size(); i++)
			results.push_back(timesVar[i].second);
		return results;
	}

	vector<int> Contains::getAllTimesConstContainers(){ //returns the list of all Times nodes which contain some constant
		vector<int> results;
		for(int i=0; i<timesConst.size(); i++)
			results.push_back(timesConst[i].first);
		return results;
	}

	vector<int> Contains::getAllTimesConstContainees(){ //returns the list of all constants which are contained in some Times node
		vector<int> results;
		for(int i=0; i<timesConst.size(); i++)
			results.push_back(timesConst[i].second);
		return results;
	}

	vector<int> Contains::getAllTimesPlusContainers(){  //returns the list of all Times nodes which contain some Times nodes
		vector<int> results;
		for(int i=0; i<timesPlus.size(); i++)
			results.push_back(timesPlus[i].first);
		return results;
	}

	vector<int> Contains::getAllTimesPlusContainees(){ //returns the list of all Timeses which are contained in some Times node
		vector<int> results;
		for(int i=0; i<timesPlus.size(); i++)
			results.push_back(timesPlus[i].second);
		return results;
	}

	vector<int> Contains::getAllTimesMinusContainers(){ //returns the list of all Times nodes which contain some minus
		vector<int> results;
		for(int i=0; i<timesMinus.size(); i++)
			results.push_back(timesMinus[i].first);
		return results;
	}

	vector<int> Contains::getAllTimesMinusContainees(){ //returns the list of all minuses which are contained in some Times node
		vector<int> results;
		for(int i=0; i<timesMinus.size(); i++)
			results.push_back(timesMinus[i].second);
		return results;
	}

	vector<int> Contains::getAllTimesTimesContainers(){ //returns the list of all Times nodes which contain some times node
		vector<int> results;
		for(int i=0; i<timesTimes.size(); i++)
			results.push_back(timesTimes[i].first);
		return results;
	}

	vector<int> Contains::getAllTimesTimesContainees(){ //returns the list of all times which are contained in some Times node
		vector<int> results;
		for(int i=0; i<timesTimes.size(); i++)
			results.push_back(timesTimes[i].first);
		return results;
	}
	

	 
	//boolean functions
	bool Contains::isContainsProgProc(int prog, int proc){ //returns true if contains(prog,proc) holds
		for(int i=0; i<progProc.size(); i++){
			if(progProc[i].first==prog && progProc[i].second==proc)
				return true;
		}
		return false;

	}
	bool Contains::isContainsProcStmtLst(int proc, int stmtLst){ //returns true if contains(proc,stmtlst) holds
		for(int i=0; i<procStmtLst.size(); i++){
			if(procStmtLst[i].first==proc && procStmtLst[i].second==stmtLst)
				return true;
		}
		return false;
	}

	bool Contains::isContainsStmtLstStmt(int stmtLst,int stmt) {//returns true if contains(stmtLst, stmt) holds
		for(int i=0; i<stmtLstStmt.size(); i++){
			if(stmtLstStmt[i].first==stmtLst && stmtLstStmt[i].second==stmt)
				return true;
		}
		return false;
	}

	bool Contains::isContainsStmtVar(int stmt, int var) {//returns true if contains(Stmt,var) holds  
		for(int i=0; i<stmtVar.size(); i++){
			if(stmtVar[i].first==stmt && stmtVar[i].second==var)
				return true;
		}
		return false;
	}

	bool Contains::isContainsStmtConst(int stmt ,int constant){ //returns true if contains(Stmt,Const) holds 
		for(int i=0; i<stmtConst.size(); i++){
			if(stmtConst[i].first==stmt && stmtConst[i].second==constant)
				return true;
		}
		return false;
	}

	bool Contains::isContainsStmtPlus(int stmt, int plus){ //returns true if contains(stmt,plus) holds
		for(int i=0; i<stmtPlus.size(); i++){
			if(stmtPlus[i].first==stmt && stmtPlus[i].second==plus)
				return true;
		}
		return false;
	}

	bool Contains::isContainsStmtMinus(int stmt, int minus){ //returns true if contains(stmt,minus) holds 
		for(int i=0; i<stmtMinus.size(); i++){
			if(stmtMinus[i].first==stmt && stmtMinus[i].second==minus)
				return true;
		}
		return false;
	}

	bool Contains::isContainsStmtTimes(int stmt, int times){ //returns true if contains(stmt, times) holds
		for(int i=0; i<stmtTimes.size();i++){
			if(stmtTimes[i].first==stmt && stmtTimes[i].second==times)
				return true;
		}
		return false;

	}

	bool Contains::isContainsStmtStmtLst(int stmt, int stmtLst){ //returns true if contains(stmt,stmtlst) holds 
		for(int i=0; i<stmtStmtLst.size(); i++){
			if(stmtStmtLst[i].first==stmt && stmtStmtLst[i].second==stmtLst)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsPlusVar(int plus, int var){ //returns true if contains(plus,var) holds 
		for(int i=0; i<plusVar.size(); i++){
			if(plusVar[i].first==plus && plusVar[i].second==var)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsPlusConst(int plus, int constant){ //returns true if contains(plus,const) holds
		for(int i=0; i<plusConst.size(); i++){
			if(plusConst[i].first==plus && plusConst[i].second==constant)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsMinusVar(int minus, int var){//returns true if contains(minus,var) holds {
		for(int i=0; i<minusVar.size(); i++){
			if(minusVar[i].first==minus && minusVar[i].second==var)
				return true;
		}
		return false;
	}
	bool Contains:: isContainsMinusConst(int minus, int constant){ //returns true if contains(minus,const) holds
		for(int i=0; i<minusConst.size(); i++){
			if(minusConst[i].first==minus && minusConst[i].second==constant)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsTimesVar(int times, int var){ //returns true if contains(times,var) holds
		for(int i=0; i<timesVar.size(); i++){
			if(timesVar[i].first==times && timesVar[i].second==var)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsTimesConst(int times, int constant){ //returns true if contains(times,const) holds
		for(int i=0; i<timesConst.size(); i++){
			if(timesConst[i].first==times && timesConst[i].second==constant)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsPlusPlus(int plus, int plus1){ //returns true if contains(plus,plus) holds
		for(int i=0; i<plusPlus.size(); i++){
			if(plusPlus[i].first==plus && plusPlus[i].second==plus1)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsPlusMinus(int plus, int minus){ //return true if contains(plus,minus) holds
		for(int i=0; i<plusMinus.size(); i++){
			if(plusMinus[i].first==plus && plusMinus[i].second==minus)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsPlusTimes(int plus, int times){ //returns true if contains(plus,plus) holds
		for(int i=0; i<plusTimes.size(); i++){
			if(plusTimes[i].first==plus && plusTimes[i].second==times)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsMinusTimes(int minus, int times){ //return true if contains(minus,times) holds
		for(int i=0; i<minusTimes.size(); i++){
			if(minusTimes[i].first==minus && minusTimes[i].second==times)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsMinusPlus(int minus, int plus){ //returns true if contains(minus,plus) holds
		for(int i=0; i<minusPlus.size(); i++){
			if(minusPlus[i].first==minus && minusPlus[i].second==plus)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsMinusMinus(int minus, int minus1){ //return true if contains(minus,minus) holds
		for(int i=0; i<minusMinus.size(); i++){
			if(minusMinus[i].first==minus && minusMinus[i].second==minus1)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsTimesPlus (int times, int plus){ //return true if contains(times,plus) holds 
		for(int i=0; i<timesPlus.size(); i++){
			if(timesPlus[i].first==times && timesPlus[i].second==plus)
				return true;
		}
		return false;
	}
	bool Contains:: isContainsTimesMinus(int times, int minus){ // return true if contains(times,minus) holds
		for(int i=0; i<timesMinus.size(); i++){
			if(timesMinus[i].first==times && timesMinus[i].second==minus)
				return true;
		}
		return false;
	}

	bool Contains:: isContainsTimesTimes(int times, int times1){ // return true if contains(times,times) holds
		for(int i=0; i<timesTimes.size(); i++){
			if(timesTimes[i].first==times && timesTimes[i].second==times1)
				return true;
		}
		return false;
	}

	
	//***********************************************************************************************************************************************************************************************************
	//contains *
	//***********************************************************************************************************************************************************************************************************

	/* COMMENTING OUT TO PREVENT BUILD ERRORS AT THE MOMENT


	//for program containers
	vector<int> Contains::getProcContainedStarInProg (int) {}  //returns the procedures contained within a program
	vector<int> Contains::getProgContainingStarProc (int) {}  //return the program which contains* the procedure
	
	//for procedures as containers
	vector<int> Contains::getStmtLstContainedStarInProc(int) {} //returns the statement list ContainedStar in proc (WILL NEVER BE QUERIED !!!)
	vector<int> Contains::getProcContainingStarStmtLst(int) {} //returns the procedure which contains the given stmtLst directly/indirectly
	vector<int> Contains::getStmtContainedStarInProc(int) {} //returns statement which is contained in a proc directly/indirectly
	vector<int> Contains::getProcContainingStarStmt(int) {} //returns the proc which contains statements directly/indirectly
	vector<int> Contains::getVarContainedStarInProc (int) {}   //returns the variables ContainedStar in a proc
	vector<int> Contains::getProcsContainingStarVar (int) {}   //returns the procedures which conatins the variable
	vector<int> Contains::getConstContainedStarInProc (int) {}  //returns the constants which are contained within a procedure
	vector<int> Contains::getProcContainingStarConst(int) {}  //returns the procedures which contain the constant
	vector<int> Contains::getPlusContainedStarInProc(int) {} //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getProcContainingStarPlus(int) {} //returns the procedure ContainingStar plus 
	vector<int> Contains::getMinusContainedStarInProc(int) {} //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getProcContainingStarMinus(int) {} //returns the procedure ContainingStar minus
	vector<int> Contains::getTimesContainedStarInProc(int) {} //returns the times ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getProcContainingStarTimes(int) {} //returns the procedures ContainingStartimes

	//for statementlist as containers
	vector<int> Contains::getStmtContainedStarInStmtLst(int) {} //returns the statements ContainedStar in statement list
	vector<int> Contains::getStmtLstContainingStarStmt(int) {} //returns the statementlist ContainingStar statements
	vector<int> Contains::getVarContainedStarInStmtLst (int) {}   //returns the variables ContainedStar in a stmtlist
	vector<int> Contains::getStmtLstContainingStarVar (int) {}   //returns the statementlist which conatins the variable
	vector<int> Contains::getConstContainedStarInStmtLst (int) {}  //returns the constants which are contained within a statementlist
	vector<int> Contains::getStmtLstContainingStarConst(int) {}  //returns the statementlist which contain the constant
	vector<int> Contains::getPlusContainedStarInStmtLst(int) {} //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getStmtLstContainingStarPlus(int) {} //returns the statementlist ContainingStar plus 
	vector<int> Contains::getMinusContainedStarInStmtLst(int) {} //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getStmtLstContainingStarMinus(int) {} //returns the statementlist ContainingStar minus
	vector<int> Contains::getTimesContainedStarInStmtLst(int) {} //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getStmtLstContainingStarTimes(int) {} //returns the statementlist ContainingStar times
	vector<int> Contains::getStmtLstContainingStarStmtLst(int) {}  //returns the statementlist which contain the statementList
	vector<int> Contains::getStmtLstContainedStarInStmtLst (int) {} //returns the statementList which are ContainedStar in statementLst 
	
	
	//for statements as containers
	vector<int> Contains::getVarContainedStarInStmt (int) {}   //returns the variables ContainedStar in a stmt
	vector<int> Contains::getStmtContainingStarVar (int) {}   //returns the statements which conatins the variable
	vector<int> Contains::getConstContainedStarInStmt (int) {}  //returns the constants which are contained within a statement
	vector<int> Contains::getStmtContainingStarConst(int) {}  //returns the statements which contain the constant
	vector<int> Contains::getStmtLstContainedStarInStmt (int) {}//returns the statementList which are ContainedStar in statement (WILL NEVER APPEAR AS QUERY!!!)
	vector<int> Contains::getStmtContainingStarStmtLst (int) {} //returns the statements contain statementList 
	vector<int> Contains::getPlusContainedStarInStmt(int) {} //returns the plus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getStmtContainingStarPlus(int) {} //returns the statements ContainingStar plus 
	vector<int> Contains::getMinusContainedStarInStmt(int) {} //returns the minus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getStmtContainingStarMinus(int) {} //returns the statements ContainingStar minus
	vector<int> Contains::getTimesContainedStarInStmt(int) {} //returns the times ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getStmtContainingStarTimes(int) {} //returns the statements ContainingStar times 


	//for plus node as container 
	vector<int> Contains::getVarContainedStarInPlus(int) {} //returns all those variables which are children of the plus node in the AST
	vector<int> Contains::getPlusContainingStarVar(int) {} //returns all those pluses which contain the variable node
	vector<int> Contains::getConstContainedStarInPlus(int) {} //returns all those constants which are children of the plus node in the AST
	vector<int> Contains::getPlusContainingStarConst(int) {} //returns all those pluses which contain the constant
	vector<int> Contains::getPlusContainedStarInPlus(int) {} //returns all those plus which are children of the plus node in the AST
	vector<int> Contains::getPlusContainingStarPlus(int) {} //returns all those pluses which contain the plus node
	vector<int> Contains::getMinusContainedStarInPlus(int) {} //returns all those minus which are children of the plus node in the AST
	vector<int> Contains::getPlusContainingStarMinus(int) {} //returns all those pluses which contain the minus node
	vector<int> Contains::getTimesContainedStarInPlus(int) {} //returns all those times which are children of the plus node in the AST
	vector<int> Contains::getPlusContainingStarTimes(int) {} //returns all those pluses which contain the times node

	//for minus node as container
	vector<int> Contains::getVarContainedStarInMinus(int) {} //returns all those variables which are children of the minus node in the AST
	vector<int> Contains::getMinusContainingStarVar(int) {} //returns all those minus which contain the variable node
	vector<int> Contains::getConstContainedStarInMinus(int) {} //returns all those constants which are children of the minus node in the AST
	vector<int> Contains::getMinusContainingStarConst(int) {} //returns all those minus which contain the constant
	vector<int> Contains::getPlusContainedStarInMius(int) {} //returns all those plus which are children of the minus node in the AST
	vector<int> Contains::getMinusContainingStarPlus(int) {} //returns all those minuses which contain the plus node
	vector<int> Contains::getMinusContainedStarInMinus(int) {} //returns all those minus which are children of the minus node in the AST
	vector<int> Contains::getMinusContainingStarMinus(int) {} //returns all those minus which contain the minus node
	vector<int> Contains::getTimesContainedStarInMinus(int) {} //returns all those times which are children of the minus node in the AST
	vector<int> Contains::getMinusContainingStarTimes(int) {} //returns all those minuses which contain the times node

	//for times node as container
	vector<int> Contains::getVarContainedStarInTimes(int) {} //returns all those variables which are children of the times node in the AST
	vector<int> Contains::getTimesContainingStarVar(int) {} //returns all those times which contain the variable node
	vector<int> Contains::getConstContainedStarInTimes(int) {} //returns all those constants which are children of the times node in the AST
	vector<int> Contains::getTimesContainingStarConst(int) {} //returns all those times which contain the constant
	vector<int> Contains::getPlusContainedStarInTimes(int) {} //returns all those plus which are children of the times node in the AST
	vector<int> Contains::getTimesContainingStarPlus(int) {} //returns all those times which contain the plus node
	vector<int> Contains::getMinusContainedStarInTimes(int) {} //returns all those minus which are children of the times node in the AST
	vector<int> Contains::getTimesContainingStarMinus(int) {} //returns all those times which contain the minus node
	vector<int> Contains::getTimesContainedStarInTimes(int) {} //returns all those times which are children of the times node in the AST
	vector<int> Contains::getTimesContainingStarTimes(int) {} //returns all those times which contain the times node

	//get all container and containees 
	//for program as container
	vector<int> Contains::getAllProgProcContainersStar(){}  //returns all the programs which contain* some procedure
	vector<int> Contains::getAllProgProcContaineesStar(){} //returns all the procedures which are ContainedStar within some program

	//for procedure as container
	vector<int> Contains::getAllProcStmtLstContainersStar(){} //returns the procedures which contain* statement list
	vector<int> Contains::getAllProcStmtLstContaineesStar(){} //return the statement list which are contained* in some procedure
	vector<int> Contains::getALLProcStmtContaineesStar() {} //returns all the statements which is contained in a proc directly/indirectly
	vector<int> Contains::getAllProcStmtContainersStar(){} //returns all the procs which contains statements directly/indirectly
	vector<int> Contains::getAllProcVarContaineesStar(){}   //returns all the variables ContainedStar in a proc
	vector<int> Contains::getAllProcVarContainersStar(){}   //returns all the procedures which contains* the variable
	vector<int> Contains::getAllProcConstContainees(){}  //returns all the constants which are contained* within a procedure
	vector<int> Contains::getAllProcConstContainers(){}  //returns all the procedures which contain* the constant
	vector<int> Contains::getAllProcPlusContainees(){} //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getAllProcPlusContainers(){} //returns the procedure ContainingStar plus 
	vector<int> Contains::getAllProcMinusContainees(){} //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getAllProcMinusContainers(){} //returns the procedure ContainingStar minus
	vector<int> Contains::getAllProcTimesContainees(int) {} //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getAllProcTimesContainers(int) {} //returns the procedures ContainingStar times


	//for statement list as container
	vector<int> Contains::getAllStmtLstStmtContainersStar(){} //returns the statementList which contain* some statement
	vector<int> Contains::getAllStmtLstStmtContaineesStar(){} //returns the statements which are ContainedStar withing a statement list
	vector<int> Contains::getAllStmtLstVarContainees(){}   //returns all the variables ContainedStar in a stmtlist
	vector<int> Contains::getAllStmtLstVarContainers(){}   //returns the statementlist which conatins the variable
	vector<int> Contains::getAllStmtLstConstContainees(){}  //returns the constants which are contained within a statementlist
	vector<int> Contains::getAllStmtLstConstContainers(){}  //returns the statementlist which contain the constant
	vector<int> Contains::getAllStmtLstPlusContainees(){} //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getAllStmtLstPlusContainers(){} //returns the statementlist ContainingStar plus 
	vector<int> Contains::getAllStmtLstMinusContainees(){} //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getAllStmtLstMinusContainers(){} //returns the statementlist ContainingStar minus
	vector<int> Contains::getAllStmtLstTimesContainees(){} //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
	vector<int> Contains::getAllStmtLstTimesContainers(){} //returns the statementlist ContainingStar times
	vector<int> Contains::getAllStmtLstStmtLstContainees(){}  //returns the statementlist which contain the statementList
	vector<int> Contains::getAllStmtLstStmtLstContainers(){} //returns the statementList which are ContainedStar in statementLst 
	


	//for statement as container
	vector<int> Contains::getAllStmtStmtLstContainersStar(){} // returns all the statements which contain* some statementlist
	vector<int> Contains::getAllStmtStmtLstContaineesStar(){} //returns all the statement list conatained within some statement
	vector<int> Contains::getAllStmtVarContaineesStar(){}  //returns all the statements which contain* some variable
	vector<int> Contains::getAllStmtVarContainersStar(){}  //returns all the variables ContainedStar within some statement
	vector<int> Contains::getAllStmtConstContaineesStar(){} //returns all the statements which contain* some constants
	vector<int> Contains::getAllStmtConstContainersStar(){} //returns all the constants conatained within some statement
	vector<int> Contains::getAllStmtPlusContaineesStar(){} //returns all the statements which contain* some plus
	vector<int> Contains::getAllStmtPlusContainersStar(){} //return all the pluses which are ContainedStar within a statement
	vector<int> Contains::getAllStmtMinusContainersStar(){} //return all the statements which contain* some minus
	vector<int> Contains::getAllStmtMinusContaineesStar(){} //return all the minuses which are ContainedStar in some statement
	vector<int> Contains::getAllStmtTimesContainersStar(){} //return all the statements which contain* some times node
	vector<int> Contains::getAllStmtTimesContaineesStar(){} //return all the times nodes which are ContainedStar within a statement

	// for plus node as container 
	vector<int> Contains::getAllPlusVarContainersStar(){} //returns the list of all plus nodes which contain* some variable
	vector<int> Contains::getAllPlusVarContaineesStar(){} //returns the list of all variables which are ContainedStar in some plus node
	vector<int> Contains::getAllPlusConstContainersStar(){} //returns the list of all plus nodes which contain* some constant
	vector<int> Contains::getAllPlusConstContaineesStar(){} //returns the list of all constants which are ContainedStar in some plus node
	vector<int> Contains::getAllPlusPlusContainersStar(){} //returns the list of all plus nodes which contain* some plus nodes
	vector<int> Contains::getAllPlusPlusContaineesStar(){} //returns the list of all pluses which are ContainedStar in some plus node
	vector<int> Contains::getAllPlusMinusContainersStar(){} //returns the list of all plus nodes which contain* some minus
	vector<int> Contains::getAllPlusMinusContaineesStar(){} //returns the list of all minuses which are ContainedStar in some plus node
	vector<int> Contains::getAllPlusTimesContainersStar(){} //returns the list of all plus nodes which contain* some times nose
	vector<int> Contains::getAllPlusTimesContaineesStar(){} //returns the list of all times which are ContainedStar in some plus node
	
	//for minus node as container
	vector<int> Contains::getAllMinusVarContainersStar(){} //returns the list of all minus nodes which contain* some variable
	vector<int> Contains::getAllMinusVarContaineesStar(){} //returns the list of all variables which are ContainedStar in some minus node
	vector<int> Contains::getAllMinusConstContainersStar(){} //returns the list of all minus nodes which contain* some constant
	vector<int> Contains::getAllMinusConstContaineesStar(){} //returns the list of all constants which are ContainedStar in some minus node
	vector<int> Contains::getAllMinusPlusContainersStar(){} //returns the list of all minus nodes which contain* some minus nodes
	vector<int> Contains::getAllMinusPlusContaineesStar(){} //returns the list of all minuses which are ContainedStar in some minus node
	vector<int> Contains::getAllMinusMinusContainersStar(){} //returns the list of all minus nodes which contain* some minus
	vector<int> Contains::getAllMinusMinusContaineesStar(){} //returns the list of all minuses which are ContainedStar in some minus node
	vector<int> Contains::getAllMinusTimesContainersStar(){} //returns the list of all minus nodes which contain* some times nose
	vector<int> Contains::getAllMinusTimesContaineesStar(){} //returns the list of all times which are ContainedStar in some minus node
	
	//for times node as container
	vector<int> Contains::getAllTimesVarContainersStar(){} //returns the list of all Times nodes which contain* some variable
	vector<int> Contains::getAllTimesVarContaineesStar(){} //returns the list of all variables which are ContainedStar in some Times node
	vector<int> Contains::getAllTimesConstContainersStar(){} //returns the list of all Times nodes which contain* some constant
	vector<int> Contains::getAllTimesConstContaineesStar(){} //returns the list of all constants which are ContainedStar in some Times node
	vector<int> Contains::getAllTimesPlusContainersStar(){} //returns the list of all Times nodes which contain* some Times nodes
	vector<int> Contains::getAllTimesPlusContaineesStar(){} //returns the list of all Timeses which are ContainedStar in some Times node
	vector<int> Contains::getAllTimesMinusContainersStar(){} //returns the list of all Times nodes which contain* some minus
	vector<int> Contains::getAllTimesMinusContaineesStar(){} //returns the list of all minuses which are ContainedStar in some Times node
	vector<int> Contains::getAllTimesTimesContainersStar(){} //returns the list of all Times nodes which contain* some times nose
	vector<int> Contains::getAllTimesTimesContaineesStar(){} //returns the list of all times which are ContainedStar in some Times node
	

	//boolean functions
	bool Contains:: isContainsStarProgProc(int, int){} //returns true if contains*(prog,proc) holds
	bool Contains:: isContainsStarProcStmtLst(int, int){} //returns true if contains*(proc,stmtlst) holds
	bool Contains:: isContainsStarProcStmt(int, int){} //returns true if contains*(proc,stmt) holds
	bool Contains:: isContainsStarProcVar(int, int){} //returns true if contains*(proc,var) holds
	bool Contains:: isContainsStarProcPlus(int, int){} //returns true if contains*(proc,plus) holds
	bool Contains:: isContainsStarProcConst(int, int){} //returns true if contains*(proc,const) holds
	bool Contains:: isContainsStarProcMinus(int, int){} //returns true if contains*(proc,minus) holds
	bool Contains:: isContainsStarProcTimes(int, int){} //returns true if contains*(proc,times) holds
	bool Contains:: isContainsStarStmtLstStmt(int,int){} //returns true if contains*(stmtLst, stmt) holds
	bool Contains:: isContainsStarStmtLstVar(int,int){} //returns true if contains*(stmtLst, var) holds
	bool Contains:: isContainsStarStmtLstConst(int,int){} //returns true if contains*(stmtLst, const) holds
	bool Contains:: isContainsStarStmtLstPlus(int,int){} //returns true if contains*(stmtLst, plus) holds
	bool Contains:: isContainsStarStmtLstMinus(int,int){} //returns true if contains*(stmtLst, minus) holds
	bool Contains:: isContainsStarStmtLstTimes(int,int){} //returns true if contains*(stmtLst, times) holds
	bool Contains:: isContainsStarStmtLstStmtLst(int,int){} //returns true if contains*(stmtLst,stmtLst) hold
	bool Contains:: isContainsStarStmtVar(int,int){} //returns true if contains*(Stmt,var) holds  
	bool Contains:: isContainsStarStmtConst(int,int){} //returns true if contains*(Stmt,Const) holds 
	bool Contains:: isContainsStarStmtPlus(int,int){} //returns true if contains*(stmt,plus) holds
	bool Contains:: isContainsStarStmtMinus(int,int){} //returns true if contains*(stmt,minus) holds 
	bool Contains:: isContainsStarStmtTimes(int,int){} //returns true if contains*(stmt, times) holds 
	bool Contains:: isContainsStarStmtStmtLst(int,int){} //returns true if contains*(stmt,stmtlst) holds 
	bool Contains:: isContainsStarPlusVar(int,int){} //returns true if contains*(plus,var) holds 
	bool Contains:: isContainsStarPlusConst(int,int){} //returns true if contains*(plus,const) holds
	bool Contains:: isContainsStarMinusVar(int,int){} //returns true if contains*(minus,var) holds
	bool Contains:: isContainsStarMinusConst(int,int){} //returns true if contains*(minus,const) holds
	bool Contains:: isContainsStarTimesVar(int,int){} //returns true if contains*(times,var) holds
	bool Contains:: isContainsStarTimesConst(int,int){} //returns true if contains*(times,const) holds
	bool Contains:: isContainsStarPlusPlus(int,int){} //returns true if contains*(plus,plus) holds
	bool Contains:: isContainsStarPlusMinus(int,int){} //return true if contains*(plus,minus) holds
	bool Contains:: isContainsStarPlusTimes(int,int){} //returns true if contains*(plus,plus) holds
	bool Contains:: isContainsStarMinusTimes(int,int){} //return true if contains*(minus,times) holds
	bool Contains:: isContainsStarMinusPlus(int,int){} //returns true if contains*(minus,plus) holds
	bool Contains:: isContainsStarMinusMinus(int,int){} //return true if contains*(minus,minus) holds
	bool Contains:: isContainsStarTimesPlus (int,int){} //return true if contains*(times,plus) holds 
	bool Contains:: isContainsStarTimesMinus(int,int){} // return true if contains*(times,minus) holds
	bool Contains:: isContainsStarTimesTimes(int,int){} // return true if contains*(times,times) holds 

	*/