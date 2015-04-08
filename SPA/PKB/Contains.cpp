#pragma once
#include "Contains.h" 
#include<iostream>

using namespace std;
	
Contains::Contains(){

}
		
	//containers

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

	//for procedures as containers
	set<int> Contains::getStmtLstContainedInProc(int proc) { //returns the statement list contained in proc (WILL NEVER BE QUERIED !!!)
		set<int> result;
		for(int i =0; i<procStmtLst.size(); i++) {
			if(procStmtLst[i].first == proc)
				result.insert(procStmtLst[i].second);
		}
		return result;
	}


	set<int> Contains::getProcContainingStmtLst(int stmtLst) { //returns the procedure which contains the given stmtLst
		set<int> result;
		for(int i =0; i<procStmtLst.size(); i++) {
			if(procStmtLst[i].second == stmtLst)
				result.insert(procStmtLst[i].first);
		}
		return result;

	}

	//for statementlist as containers
	set<int> Contains::getStmtContainedInStmtLst(int stmtLst) { //returns the statements contained in statement list
		set<int> result;
		for(int i =0; i<stmtLstStmt.size(); i++) {
			if(stmtLstStmt[i].first == stmtLst)
				result.insert(stmtLstStmt[i].second);
		}
		return result;

	}

	set<int> Contains::getStmtLstContainingStmt(int stmt) { //returns the statementlist containing statements
		set<int> result;
		for(int i =0; i<stmtLstStmt.size(); i++) {
			if(stmtLstStmt[i].second == stmt)
				result.insert(stmtLstStmt[i].first);
		}
		return result;
	}


	//for statements as containers
	set<int> Contains::getVarContainedInStmt (int stmt) {   //returns the variables contained in a stmt
		set<int> result;
		for(int i=0; i<stmtVar.size(); i ++){
			if(stmtVar[i].first == stmt)
				result.insert(stmtVar[i].second);
		}
		return result;

	}

	set<int> Contains::getStmtContainingVar (int var) {   //returns the statements which conatins the variable
		set<int> result;
		for(int i=0; i<stmtVar.size(); i ++){
			if(stmtVar[i].second == var)
				result.insert(stmtVar[i].first);
		}
		return result;

	}

	set<int> Contains::getConstContainedInStmt (int stmt) {  //returns the constants which are conatined within a statement
		set<int> result;
		for(int i=0; i<stmtConst.size(); i++){
			if(stmtConst[i].first==stmt)
				result.insert(stmtConst[i].second);
		}
		return result; 
	}

	set<int> Contains::getStmtContainingConst(int constant ) {  //returns the statements which contain the constant
		set<int> result;
		for(int i=0; i<stmtConst.size(); i++){
			if(stmtConst[i].second==constant)
				result.insert(stmtConst[i].first);
		}
		return result;

	}

	set<int> Contains::getStmtLstContainedInStmt (int stmt) { //returns the statementList which are contained in statement (WILL NEVER APPEAR AS QUERY!!!)
		set<int> result;
		for(int i=0; i<stmtStmtLst.size(); i++){
			if(stmtStmtLst[i].first==stmt)
				result.insert(stmtStmtLst[i].second);
		}
		return result;

	}

	set<int> Contains::getStmtContainingStmtLst (int stmtLst) { //returns the statements contain statementList 
		set<int> result;
		for(int i=0; i<stmtStmtLst.size(); i++){
			if(stmtStmtLst[i].second==stmtLst)
				result.insert(stmtStmtLst[i].first);
		}
		return result;
	}

	set<int> Contains::getPlusContainedInStmt(int stmt) { //returns the plus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
		set<int> result;
		for(int i=0; i<stmtPlus.size();i++){
			if(stmtPlus[i].first==stmt)
				result.insert(stmtPlus[i].second);
		}
		return result;
	}


	set<int> Contains::getStmtContainingPlus(int plus) { //returns the statements containing plus 
		set<int> result;
		for(int i=0; i<stmtPlus.size();i++){
			if(stmtPlus[i].second==plus)
				result.insert(stmtPlus[i].first);
		}
		return result;
	}


	set<int> Contains::getMinusContainedInStmt(int stmt) { //returns the minus contained in statement (WILL NEVER APPEAR AS QUERY !!!)
		set<int> result;
		for(int i=0; i<stmtMinus.size();i++){
			if(stmtMinus[i].first==stmt)
				result.insert(stmtMinus[i].second);
		}
		return result;
	}

	set<int> Contains::getStmtContainingMinus(int minus) { //returns the statements containing minus
		set<int> result;
		for(int i=0; i<stmtMinus.size();i++){
			if(stmtMinus[i].second==minus)
				result.insert(stmtMinus[i].first);
		}
		return result;
	}

	set<int> Contains::getTimesContainedInStmt(int stmt) { //returns the  imescontained in statement (WILL NEVER APPEAR AS QUERY !!!)
		set<int> result;
		for(int i=0; i<stmtTimes.size();i++){
			if(stmtTimes[i].first==stmt)
				result.insert(stmtTimes[i].second);
		}
		return result;
	}

	set<int> Contains::getStmtContainingTimes(int times) { //returns the statements containing times
		set<int> result;
		for(int i=0; i<stmtTimes.size();i++){
			if(stmtTimes[i].second==times)
				result.insert(stmtTimes[i].first);
		}
		return result;
	}


	//for plus node as container 
	set<int> Contains::getVarContainedInPlus(int plus) { //returns all those variables which are children of the plus node in the AST
		set<int> result;
		for(int i=0; i<plusVar.size(); i++){
			if(plusVar[i].first==plus)
				result.insert(plusVar[i].second);
		}
	return result;
	}

	set<int> Contains::getPlusContainingVar(int var) { //returns all those pluses which contain the variable node
		set<int> result;
		for(int i=0; i<plusVar.size(); i++){
			if(plusVar[i].second==var)
				result.insert(plusVar[i].first);
		}
	return result;
	}

	set<int> Contains::getConstContainedInPlus(int plus) { //returns all those constants which are children of the plus node in the AST
		set<int> result;
		for(int i=0; i<plusConst.size(); i++){
			if(plusConst[i].first==plus)
				result.insert(plusConst[i].second);
		}
	return result;
	}


	set<int> Contains::getPlusContainingConst(int constant) { //returns all those pluses which contain the constant
		set<int> result;
		for(int i=0; i<plusConst.size(); i++){
			if(plusConst[i].second==constant)
				result.insert(plusConst[i].first);
		}
		return result;
	}

	set<int> Contains::getPlusContainedInPlus(int plus) { //returns all those plus which are children of the plus node in the AST
		set<int> result;
		for(int i=0; i<plusPlus.size(); i++){
			if(plusPlus[i].first==plus)
				result.insert(plusPlus[i].second);
		}
		return result;
	}

	set<int> Contains::getPlusContainingPlus(int plus) { //returns all those pluses which contain the plus node
		set<int> result;
		for(int i=0; i<plusPlus.size(); i++){
			if(plusPlus[i].second==plus)
				result.insert(plusPlus[i].first);
		}
		return result;
	}

	set<int> Contains::getMinusContainedInPlus(int plus) { //returns all those minus which are children of the plus node in the AST
		set<int> result;
		for(int i=0; i<plusMinus.size(); i++){
			if(plusMinus[i].first==plus)
				result.insert(plusMinus[i].second);
		}
		return result;
	}

	set<int> Contains::getPlusContainingMinus(int minus) { //returns all those pluses which contain the minus node
		set<int> result;
		for(int i=0; i<plusMinus.size(); i++){
			if(plusMinus[i].second==minus)
				result.insert(plusMinus[i].first);
		}
		return result;
	}

	set<int> Contains::getTimesContainedInPlus(int plus) { //returns all those times which are children of the plus node in the AST
		set<int> result;
		for(int i=0; i<timesPlus.size(); i++){
			if(timesPlus[i].first==plus)
				result.insert(plusTimes[i].second);
		}
		return result;
	}

	set<int> Contains::getPlusContainingTimes(int times) { //returns all those pluses which contain the times node
		set<int> result;
		for(int i=0; i<timesPlus.size(); i++) {
			if(timesPlus[i].second==times)
				result.insert(plusTimes[i].first);
		}
		return result;

	}

	//for minus node as container
	set<int> Contains::getVarContainedInMinus(int minus) { //returns all those variables which are children of the minus node in the AST
		set<int> result;
		for(int i=0; i<minusVar.size(); i++){
			if(minusVar[i].first==minus)
				result.insert(minusVar[i].second);
		}
		return result;
	}

	set<int> Contains::getMinusContainingVar(int var) { //returns all those minus which contain the variable node
		set<int> result;
		for(int i=0; i<minusVar.size(); i++){
			if(minusVar[i].second==var)
				result.insert(minusVar[i].first);
		}
		return result;
	}
	
	set<int> Contains::getConstContainedInMinus(int minus) { //returns all those constants which are children of the minus node in the AST
		set<int> result;
		for(int i=0; i<minusConst.size(); i++){
			if(minusConst[i].first==minus)
				result.insert(minusConst[i].second);
		}
		return result;
	}

	set<int> Contains::getMinusContainingConst(int constant) { //returns all those minus which contain the constant
		 set<int> result;
		for(int i=0; i<minusConst.size(); i++){
			if(minusConst[i].second==constant)
				result.insert(minusConst[i].first);
		}
		return result;
	}
	
	set<int> Contains::getPlusContainedInMinus(int minus) { //returns all those plus which are children of the minus node in the AST
		set<int> result;
		for(int i=0; i<minusPlus.size(); i++){
			if(minusPlus[i].first==minus)
				result.insert(minusPlus[i].second);
		}
		return result;
	}

	set<int> Contains::getMinusContainingPlus(int plus) { //returns all those minuses which contain the plus node
		 set<int> result;
		for(int i=0; i<minusPlus.size(); i++){
			if(minusPlus[i].second==plus)
				result.insert(minusPlus[i].first);
		}
		return result;
	}

	set<int> Contains::getMinusContainedInMinus(int minus) { //returns all those minus which are children of the minus node in the AST
		set<int> result;
		for(int i=0; i<minusMinus.size(); i++) {
			if(minusMinus[i].first==minus)
				result.insert(minusMinus[i].second);
		}
		return result;
	}

	set<int> Contains::getMinusContainingMinus(int minus) { //returns all those minus which contain the minus node
		set<int> result;
		for(int i=0; i<minusMinus.size(); i++){
			if(minusMinus[i].second==minus)
				result.insert(minusMinus[i].first);
		}
		return result;
	}

	set<int> Contains::getTimesContainedInMinus(int minus) { //returns all those times which are children of the minus node in the AST
		set<int> result;
		for(int i=0; i<minusTimes.size(); i++) {
			if(minusTimes[i].first==minus)
				result.insert(minusTimes[i].second);
		}
		return result;
	}

	set<int> Contains::getMinusContainingTimes(int times) { //returns all those minuses which contain the times node
		set<int> result;
		for(int i=0; i<minusTimes.size(); i++) {
			if(minusTimes[i].second==times)
				result.insert(minusTimes[i].first);
		}
		return result;
	}

	//for times node as container
	set<int> Contains::getVarContainedInTimes(int times) { //returns all those variables which are children of the times node in the AST
		set<int> result;
		for(int i=0; i<timesVar.size(); i++){
			if(timesVar[i].first==times)
				result.insert(timesVar[i].second);
		}
		return result;

	}

	set<int> Contains::getTimesContainingVar(int var) { //returns all those times which contain the variable node
		set<int> result;
		for(int i=0; i<timesVar.size(); i++){
			if(timesVar[i].second==var)
				result.insert(timesVar[i].first);
		}
		return result;
	}

	set<int> Contains::getConstContainedInTimes(int times) { //returns all those constants which are children of the times node in the AST
		set<int> result;
		for(int i=0; i<timesConst.size(); i++){
			if(timesConst[i].first==times)
				result.insert(timesConst[i].second);
		}
		return result;

	}
	
	set<int> Contains::getTimesContainingConst(int constant) { //returns all those times which contain the constant
		set<int> result;
		for(int i=0; i<timesConst.size(); i++){
			if(timesConst[i].second==constant)
				result.insert(timesConst[i].first);
		}
		return result;

	}

	set<int> Contains::getPlusContainedInTimes(int times) { //returns all those plus which are children of the times node in the AST
		set<int> result;
		for(int i=0; i<timesPlus.size(); i++){
			if(timesPlus[i].first==times)
				result.insert(timesPlus[i].second);
		}
		return result;
	}


	set<int> Contains::getTimesContainingPlus(int plus) { //returns all those times which contain the plus node
		set<int> result;
		for(int i=0; i<timesPlus.size(); i++){
			if(timesPlus[i].second==plus)
				result.insert(timesPlus[i].first);
		}
		return result;
	}

	set<int> Contains::getMinusContainedInTimes(int times) { //returns all those minus which are children of the times node in the AST
		set<int> result;
		for(int i=0; i<timesMinus.size(); i++) {
			if(timesMinus[i].first==times)
				result.insert(timesMinus[i].second);
		}
		return result;
	}


	set<int> Contains::getTimesContainingMinus(int minus) { //returns all those times which contain the minus node
		set<int> result;
		for(int i=0; i<timesMinus.size(); i++) {
			if(timesMinus[i].first==minus)
				result.insert(timesMinus[i].second);
		}
		return result;
	}

	set<int> Contains::getTimesContainedInTimes(int times) { //returns all those times which are children of the times node in the AST
		set<int> result;
		for(int i=0; i<timesTimes.size(); i++) {
			if(timesTimes[i].first==times)
				result.insert(timesTimes[i].second);
		}
		return result;
	}

	set<int> Contains::getTimesContainingTimes(int times) { //returns all those times which contain the times node
		set<int> result;
		for(int i=0; i<timesTimes.size(); i++) {
			if(timesTimes[i].second==times)
				result.insert(timesTimes[i].first);
		}
		return result;
	}


	//get all container and Containees
	//for procedure as container
	set<int> Contains::getAllProcStmtLstContainers(){ //returns the procedures which contain statement list
		set<int> results;
		for(int i=0; i<procStmtLst.size(); i++)
			results.insert(procStmtLst[i].first);
		return results;
	}

	set<int> Contains::getAllProcStmtLstContainees(){ //return the statement list which are ocntained in some procedure
		set<int> results;
		for(int i=0; i<procStmtLst.size(); i++)
			results.insert(procStmtLst[i].second);
		return results;
	}

	//for statement list as container
	set<int> Contains::getAllStmtLstStmtContainers(){ //returns the statementList which contain some statement
		set<int> results;
		for(int i=0; i<stmtLstStmt.size(); i++)
			results.insert(stmtLstStmt[i].first);
		return results;
	}

	set<int> Contains::getAllStmtLstStmtContainees(){ //returns the statements which are contained withing a statement list
		set<int> results;
		for(int i=0; i<stmtLstStmt.size(); i++)
			results.insert(stmtLstStmt[i].second);
		return results;
	}

	//for statement as container
	set<int> Contains::getAllStmtStmtLstContainers(){ // returns all the statements which contain some statementlist
		set<int> results;
		for(int i=0; i<stmtStmtLst.size(); i++)
			results.insert(stmtStmtLst[i].first);
		return results;
	}

	set<int> Contains::getAllStmtStmtLstContainees(){ //returns all the statement list conatained within some statement
		set<int> results;
		for(int i=0; i<stmtStmtLst.size(); i++)
			results.insert(stmtStmtLst[i].second);
		return results;
	}

	set<int> Contains::getAllStmtVarContainers(){  //returns all the statements which contain some variable
		set<int> results;
		for(int i=0; i<stmtVar.size(); i++)
			results.insert(stmtVar[i].first);
		return results;
	}

	set<int> Contains::getAllStmtVarContainees(){  //returns all the variables contained within some statement
		set<int> results;
		for(int i=0; i<stmtVar.size(); i++)
			results.insert(stmtVar[i].second);
		return results;
	}

	set<int> Contains::getAllStmtConstContainers(){ //returns all the statements which contain some constants
		set<int> results;
		for(int i=0; i<stmtConst.size(); i++)
			results.insert(stmtConst[i].first);
		return results;
	}

	set<int> Contains::getAllStmtConstContainees(){ //returns all the constants conatained within some statement
		set<int> results;
		for(int i=0; i<stmtConst.size(); i++)
			results.insert(stmtConst[i].second);
		return results;
	}

	set<int> Contains::getAllStmtPlusContainers(){ //returns all the statements which contain some plus
		set<int> results;
		for(int i=0; i<stmtPlus.size(); i++)
			results.insert(stmtPlus[i].first);
		return results;
	}

	set<int> Contains::getAllStmtPlusContainees(){ //return all the pluses which are contained within a statement
		set<int> results;
		for(int i=0; i<stmtPlus.size(); i++)
			results.insert(stmtPlus[i].second);
		return results;
	}

	set<int> Contains::getAllStmtMinusContainers(){ //return all the statements which contain some minus
		set<int> results;
		for(int i=0; i<stmtMinus.size(); i++)
			results.insert(stmtMinus[i].first);
		return results;
	}

	set<int> Contains::getAllStmtMinusContainees(){ //return all the minuses which are contained in some statement
		set<int> results;
		for(int i=0; i<stmtMinus.size(); i++)
			results.insert(stmtMinus[i].second);
		return results;
	}

	set<int> Contains::getAllStmtTimesContainers(){ //return all the statements which contain some times node
		set<int> results;
		for(int i=0; i<stmtTimes.size(); i++)
			results.insert(stmtTimes[i].first);
		return results;
	}

	set<int> Contains::getAllStmtTimesContainees(){ //return all the times nodes which are contained within a statement
		set<int> results;
		for(int i=0; i<stmtTimes.size(); i++)
			results.insert(stmtTimes[i].second);
		return results;
	}

	// for plus node as container 
	set<int> Contains::getAllPlusVarContainers(){ //returns the list of all plus nodes which contain some variable
		set<int> results;
		for(int i=0; i<plusVar.size(); i++)
			results.insert(plusVar[i].first);
		return results;
	}

	set<int> Contains::getAllPlusVarContainees(){ //returns the list of all variables which are contained in some plus node
		set<int> results;
		for(int i=0; i<plusVar.size(); i++)
			results.insert(plusVar[i].second);
		return results;
	}

	set<int> Contains::getAllPlusConstContainers(){ //returns the list of all plus nodes which contain some constant
		set<int> results;
		for(int i=0; i<plusConst.size(); i++)
			results.insert(plusConst[i].first);
		return results;
	}

	set<int> Contains::getAllPlusConstContainees(){ //returns the list of all constants which are contained in some plus node
		set<int> results;
		for(int i=0; i<plusConst.size(); i++)
			results.insert(plusConst[i].second);
		return results;
	}

	set<int> Contains::getAllPlusPlusContainers(){ //returns the list of all plus nodes which contain some plus nodes
		set<int> results;
		for(int i=0; i<plusPlus.size(); i++)
			results.insert(plusPlus[i].first);
		return results;
	}

	set<int> Contains::getAllPlusPlusContainees(){ //returns the list of all pluses which are contained in some plus node
		set<int> results;
		for(int i=0; i<plusPlus.size(); i++)
			results.insert(plusPlus[i].second);
		return results;
	}

	set<int> Contains::getAllPlusMinusContainers(){ //returns the list of all plus nodes which contain some minus
		set<int> results;
		for(int i=0; i<plusMinus.size(); i++)
			results.insert(plusMinus[i].first);
		return results;
	}

	set<int> Contains::getAllPlusMinusContainees(){ //returns the list of all minuses which are contained in some plus node
		set<int> results;
		for(int i=0; i<plusMinus.size(); i++)
			results.insert(plusMinus[i].second);
		return results;
	}

	set<int> Contains::getAllPlusTimesContainers(){ //returns the list of all plus nodes which contain some times nose
		set<int> results;
		for(int i=0; i<plusTimes.size(); i++)
			results.insert(plusTimes[i].first);
		return results;
	}

	set<int> Contains::getAllPlusTimesContainees(){ //returns the list of all times which are contained in some plus node
		set<int> results;
		for(int i=0; i<plusTimes.size(); i++)
			results.insert(plusTimes[i].second);
		return results;
	}
	
	//for minus node as container
	set<int> Contains::getAllMinusVarContainers(){ //returns the list of all minus nodes which contain some variable
		set<int> results;
		for(int i=0; i<minusVar.size(); i++)
			results.insert(minusVar[i].first);
		return results;
	}

	set<int> Contains::getAllMinusVarContainees(){ //returns the list of all variables which are contained in some minus node
		set<int> results;
		for(int i=0; i<minusVar.size(); i++)
			results.insert(minusVar[i].second);
		return results;
	}

	set<int> Contains::getAllMinusConstContainers(){ //returns the list of all minus nodes which contain some constant
		set<int> results;
		for(int i=0; i<minusConst.size(); i++)
			results.insert(minusVar[i].first);
		return results;
	}

	set<int> Contains::getAllMinusConstContainees(){ //returns the list of all constants which are contained in some minus node
		set<int> results;
		for(int i=0; i<minusConst.size(); i++)
			results.insert(minusConst[i].second);
		return results;
	}

	set<int> Contains::getAllMinusPlusContainers(){ //returns the list of all minus nodes which contain some minus nodes
		set<int> results;
		for(int i=0; i<minusPlus.size(); i++)
			results.insert(minusPlus[i].first);
		return results;
	}

	set<int> Contains::getAllMinusPlusContainees(){ //returns the list of all minuses which are contained in some minus node
		set<int> results;
		for(int i=0; i<minusPlus.size(); i++)
			results.insert(minusPlus[i].second);
		return results;
	}

	set<int> Contains::getAllMinusMinusContainers(){ //returns the list of all minus nodes which contain some minus
		set<int> results;
		for(int i=0; i<minusMinus.size(); i++)
			results.insert(minusMinus[i].first);
		return results;
	}

	set<int> Contains::getAllMinusMinusContainees(){ //returns the list of all minuses which are contained in some minus node
		set<int> results;
		for(int i=0; i<minusMinus.size(); i++)
			results.insert(minusMinus[i].second);
		return results;
	}

	set<int> Contains::getAllMinusTimesContainers(){ //returns the list of all minus nodes which contain some times node
		set<int> results;
		for(int i=0; i<minusTimes.size(); i++)
			results.insert(minusTimes[i].first);
		return results;
	}
	set<int> Contains::getAllMinusTimesContainees(){ //returns the list of all times which are contained in some minus node
		set<int> results;
		for(int i=0; i<minusTimes.size(); i++)
			results.insert(minusTimes[i].second);
		return results;
	}

	
	//for times node as container
	set<int> Contains::getAllTimesVarContainers(){ //returns the list of all Times nodes which contain some variable
		set<int> results;
		for(int i=0; i<timesVar.size(); i++)
			results.insert(timesVar[i].first);
		return results;
	}

	set<int> Contains::getAllTimesVarContainees(){ //returns the list of all variables which are contained in some Times node
		set<int> results;
		for(int i=0; i<timesVar.size(); i++)
			results.insert(timesVar[i].second);
		return results;
	}

	set<int> Contains::getAllTimesConstContainers(){ //returns the list of all Times nodes which contain some constant
		set<int> results;
		for(int i=0; i<timesConst.size(); i++)
			results.insert(timesConst[i].first);
		return results;
	}

	set<int> Contains::getAllTimesConstContainees(){ //returns the list of all constants which are contained in some Times node
		set<int> results;
		for(int i=0; i<timesConst.size(); i++)
			results.insert(timesConst[i].second);
		return results;
	}

	set<int> Contains::getAllTimesPlusContainers(){  //returns the list of all Times nodes which contain some Times nodes
		set<int> results;
		for(int i=0; i<timesPlus.size(); i++)
			results.insert(timesPlus[i].first);
		return results;
	}

	set<int> Contains::getAllTimesPlusContainees(){ //returns the list of all Timeses which are contained in some Times node
		set<int> results;
		for(int i=0; i<timesPlus.size(); i++)
			results.insert(timesPlus[i].second);
		return results;
	}

	set<int> Contains::getAllTimesMinusContainers(){ //returns the list of all Times nodes which contain some minus
		set<int> results;
		for(int i=0; i<timesMinus.size(); i++)
			results.insert(timesMinus[i].first);
		return results;
	}

	set<int> Contains::getAllTimesMinusContainees(){ //returns the list of all minuses which are contained in some Times node
		set<int> results;
		for(int i=0; i<timesMinus.size(); i++)
			results.insert(timesMinus[i].second);
		return results;
	}

	set<int> Contains::getAllTimesTimesContainers(){ //returns the list of all Times nodes which contain some times node
		set<int> results;
		for(int i=0; i<timesTimes.size(); i++)
			results.insert(timesTimes[i].first);
		return results;
	}

	set<int> Contains::getAllTimesTimesContainees(){ //returns the list of all times which are contained in some Times node
		set<int> results;
		for(int i=0; i<timesTimes.size(); i++)
			results.insert(timesTimes[i].first);
		return results;
	}
	

	 
	//boolean functions
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

	

	//for procedures as containers
	set<int> Contains::getStmtLstContainedStarInProc(int proc) { //returns the statement list ContainedStar in proc (WILL NEVER BE QUERIED !!!)
		set<int> results;
		set<int> stmtLstInProc = getStmtLstContainedInProc(proc);
		results.insert(stmtLstInProc.begin(), stmtLstInProc.end());
		for(std::set<int>::iterator i = stmtLstInProc.begin(); i!=stmtLstInProc.end(); i++) {
			set<int> stmtLstContainedStarInStmtLst = getStmtLstContainedStarInStmtLst(*i);
			results.insert(stmtLstContainedStarInStmtLst.begin(), stmtLstContainedStarInStmtLst.end());
		}
		return results;
	}

	set<int> Contains::getProcContainingStarStmtLst(int stmtLst) { //returns the procedure which contains the given stmtLst directly/indirectly
		set<int> results;
		set<int> procs = getProcContainingStmtLst(stmtLst);
		set<int> stmts = getStmtContainingStmtLst(stmtLst);
		for(std::set<int>::iterator it=stmts.begin(); it!=stmts.end(); it++){
			set<int> procs1 = getProcContainingStarStmt(*it);
			results.insert(procs1.begin(),procs.end());
		}
		return results;
	}

	set<int> Contains::getStmtContainedStarInProc(int proc) { //returns statement which is contained in a proc directly/indirectly
		set<int> results;
		set<int> stmtLst = getStmtLstContainedInProc(proc);
		for(std::set<int>::iterator i = stmtLst.begin(); i!=stmtLst.end(); i++) {
			set<int> stmtContainedStarInStmtLst = getStmtContainedStarInStmtLst(*i);
			results.insert(stmtContainedStarInStmtLst.begin(), stmtContainedStarInStmtLst.end());
		}
		return results;
	}

	set<int> Contains::getProcContainingStarStmt(int stmt) { //returns the proc which contains statements directly/indirectly
		set<int> results;
		set<int> stmtLst = getStmtLstContainingStmt(stmt);
		for(std::set<int>::iterator i = stmtLst.begin(); i!=stmtLst.end(); i++) {
			set<int> procs = getProcContainingStarStmtLst(*i);
			results.insert(procs.begin(), procs.end());
		}
		return results;
	}

	set<int> Contains::getVarContainedStarInProc (int proc) {   //returns the variables ContainedStar in a proc
		set<int> results;
		set<int> stmtLst = getStmtLstContainedStarInProc(proc);
		for(std::set<int>::iterator i = stmtLst.begin(); i!=stmtLst.end(); i++) {
			set<int> vars = getVarContainedStarInStmtLst(*i);
			results.insert(vars.begin(), vars.end());
		}
		return results;
	}

	set<int> Contains::getProcsContainingStarVar (int var) {  //returns the procedures which contains the variable
		set<int> results;
		set<int> stmt = getStmtContainingVar(var);
		set<int> plus1 = getPlusContainingVar(var);
		set<int> minus1 = getMinusContainingVar(var);
		set<int> times1 = getTimesContainingVar(var);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> procs = getProcContainingStarStmt(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> procs = getProcContainingStarPlus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> procs = getProcContainingStarMinus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> procs = getProcContainingStarTimes(*i);
			results.insert(procs.begin(), procs.end());
		}

		return results;
	}

	set<int> Contains::getConstContainedStarInProc (int proc) {  //returns the constants which are contained within a procedure
		set<int> results;
		set<int> stmtLst = getStmtLstContainedStarInProc(proc);
		for(std::set<int>::iterator i = stmtLst.begin(); i!=stmtLst.end(); i++) {
			set<int> consts = getConstContainedStarInStmtLst(*i);
			results.insert(consts.begin(), consts.end());
		}
		return results;

	}

	set<int> Contains::getProcContainingStarConst(int constant) {  //returns the procedures which contain the constant
		set<int> results;
		set<int> stmt = getStmtContainingConst(constant);
		set<int> plus1 = getPlusContainingConst(constant);
		set<int> minus1 = getMinusContainingConst(constant);
		set<int> times1 = getTimesContainingConst(constant);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> procs = getProcContainingStarStmt(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> procs = getProcContainingStarPlus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> procs = getProcContainingStarMinus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> procs = getProcContainingStarTimes(*i);
			results.insert(procs.begin(), procs.end());
		}

		
		return results;
	}

	set<int> Contains::getPlusContainedStarInProc(int proc) { //returns the plus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> stmtLst = getStmtLstContainedInProc(proc);
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> plus = getPlusContainedStarInStmtLst(*i);
			results.insert(plus.begin(), plus.end());
		}
		return results;

	}

	set<int> Contains::getProcContainingStarPlus(int plus) { //returns the procedure ContainingStar plus 
		set<int> results;
		set<int> stmt = getStmtContainingPlus(plus);
		set<int> plus1 = getPlusContainingPlus(plus);
		set<int> minus1 = getMinusContainingPlus(plus);
		set<int> times1 = getTimesContainingPlus(plus);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> procs = getProcContainingStarStmt(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> procs = getProcContainingStarPlus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> procs = getProcContainingStarMinus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> procs = getProcContainingStarTimes(*i);
			results.insert(procs.begin(), procs.end());
		}

		return results;
	}

	set<int> Contains::getMinusContainedStarInProc(int proc) { //returns the minus ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> stmtLst = getStmtLstContainedInProc(proc);
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> minus = getMinusContainedStarInStmtLst(*i);
			results.insert(minus.begin(), minus.end());
		}
		return results;
	}

	set<int> Contains::getProcContainingStarMinus(int minus) { //returns the procedure ContainingStar minus
		set<int> results;
		set<int> stmt = getStmtContainingMinus(minus);
		set<int> plus1 = getPlusContainingMinus(minus);
		set<int> minus1 = getMinusContainingMinus(minus);
		set<int> times1 = getTimesContainingMinus(minus);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> procs = getProcContainingStarStmt(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> procs = getProcContainingStarPlus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> procs = getProcContainingStarMinus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> procs = getProcContainingStarTimes(*i);
			results.insert(procs.begin(), procs.end());
		}

		return results;
	}

	set<int> Contains::getTimesContainedStarInProc(int proc) { //returns the times ContainedStar in procedure (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> stmtLst = getStmtLstContainedInProc(proc);
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> times = getTimesContainedStarInStmtLst(*i);
			results.insert(times.begin(), times.end());
		}
		return results;
	}

	set<int> Contains::getProcContainingStarTimes(int times) { //returns the procedures ContainingStartimes
		set<int> results;
		set<int> stmt = getStmtContainingTimes(times);
		set<int> plus1 = getPlusContainingTimes(times);
		set<int> minus1 = getMinusContainingTimes(times);
		set<int> times1 = getTimesContainingTimes(times);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> procs = getProcContainingStarStmt(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> procs = getProcContainingStarPlus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> procs = getProcContainingStarMinus(*i);
			results.insert(procs.begin(), procs.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> procs = getProcContainingStarTimes(*i);
			results.insert(procs.begin(), procs.end());
		}

		return results;
	}


	//for statementlist as containers
	set<int> Contains::getStmtContainedStarInStmtLst(int stmtLst) { //returns the statements ContainedStar in statement list
		set<int> results;
		set<int> stmts = getStmtContainedInStmtLst(stmtLst);
		results.insert(stmts.begin(), stmts.end());
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> stmts1 = getStmtContainedStarInStmt(*i);
			results.insert(stmts1.begin(), stmts1.end());
		}
		return results;
	}

	set<int> Contains::getStmtLstContainingStarStmt(int stmt) { //returns the statementlist ContainingStar statements
		set<int> results;
		set<int> stmtLst = getStmtLstContainingStmt(stmt);
		results.insert(stmtLst.begin(), stmtLst.end());
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> stmtLst1 = getStmtLstContainingStarStmtLst(*i);
			results.insert(stmtLst1.begin(), stmtLst1.end());
		}
		return results;
	}

	set<int> Contains::getVarContainedStarInStmtLst (int stmtLst) {   //returns the variables ContainedStar in a stmtlist
		set<int> results;
		set<int> stmts = getStmtContainedInStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> vars = getVarContainedStarInStmt(*i);
			results.insert(vars.begin(), vars.end());
		}
		return results;
	}

	set<int> Contains::getStmtLstContainingStarVar (int var) {   //returns the statementlist which conatins the variable
		set<int> results;
		set<int> stmts = getStmtContainingVar(var);
		set<int> plus1 = getPlusContainingVar(var);
		set<int> minus1 = getMinusContainingVar(var);
		set<int> times1 = getTimesContainingVar(var);

		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarStmt(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarPlus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarMinus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarTimes(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		return results;
	}

	set<int> Contains::getConstContainedStarInStmtLst (int stmtLst) {  //returns the constants which are contained within a statementlist
		set<int> results;
		set<int> stmts = getStmtContainedInStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> constant = getConstContainedStarInStmt(*i);
			results.insert(constant.begin(), constant.end());
		}
		return results;
	}

	set<int> Contains::getStmtLstContainingStarConst(int constant) {  //returns the statementlist which contain the constant
		set<int> results;
		set<int> stmts = getStmtContainingConst(constant);
		set<int> plus1 = getPlusContainingConst(constant);
		set<int> minus1 = getMinusContainingConst(constant);
		set<int> times1 = getTimesContainingConst(constant);

		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarStmt(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarPlus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarMinus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarTimes(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}
		return results;
	}


	set<int> Contains::getPlusContainedStarInStmtLst(int stmtLst) { //returns the plus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> stmts = getStmtContainedInStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> plus = getPlusContainedStarInStmt(*i);
			results.insert(plus.begin(), plus.end());
		}
		return results;
	}
	set<int> Contains::getStmtLstContainingStarPlus(int plus) { //returns the statementlist ContainingStar plus 
		set<int> results;
		set<int> stmt = getStmtContainingPlus(plus);
		set<int> plus1 = getPlusContainingPlus(plus);
		set<int> minus1 = getMinusContainingPlus(plus);
		set<int> times1 = getTimesContainingPlus(plus);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> stmtLst1 = getStmtLstContainingStarStmt(*i);
			results.insert(stmtLst1.begin(), stmtLst1.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> stmtLst1 = getStmtLstContainingStarPlus(*i);
			results.insert(stmtLst1.begin(), stmtLst1.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmtLst1 = getStmtLstContainingStarMinus(*i);
			results.insert(stmtLst1.begin(), stmtLst1.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmtLst1 = getStmtLstContainingStarTimes(*i);
			results.insert(stmtLst1.begin(), stmtLst1.end());
		}

		return results;
	}
	set<int> Contains::getMinusContainedStarInStmtLst(int stmtLst) { //returns the minus ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> stmts = getStmtContainedInStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> minus = getMinusContainedStarInStmt(*i);
			results.insert(minus.begin(), minus.end());
		}
		return results;
	}
	set<int> Contains::getStmtLstContainingStarMinus(int minus) { //returns the statementlist ContainingStar minus
		set<int> results;
		set<int> stmt = getStmtContainingMinus(minus);
		set<int> plus1 = getPlusContainingMinus(minus);
		set<int> minus1 = getMinusContainingMinus(minus);
		set<int> times1 = getTimesContainingMinus(minus);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarStmt(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarPlus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarMinus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarTimes(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		return results;
	}
	set<int> Contains::getTimesContainedStarInStmtLst(int stmtLst) { //returns the times ContainedStar in statementlist (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> stmts = getStmtContainedInStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> times = getTimesContainedStarInStmt(*i);
			results.insert(times.begin(), times.end());
		}
		return results;
	}
	set<int> Contains::getStmtLstContainingStarTimes(int times) { //returns the statementlist ContainingStar times
		set<int> results;
		set<int> stmt = getStmtContainingTimes(times);
		set<int> plus1 = getPlusContainingTimes(times);
		set<int> minus1 = getMinusContainingTimes(times);
		set<int> times1 = getTimesContainingTimes(times);

		for(std::set<int>::iterator i=stmt.begin(); i!=stmt.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarStmt(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarPlus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarMinus(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmtLst = getStmtLstContainingStarTimes(*i);
			results.insert(stmtLst.begin(), stmtLst.end());
		}

		return results;
	}
	set<int> Contains::getStmtLstContainingStarStmtLst(int stmtLst) {  //returns the statementlist which contain the statementList
		set<int> results;
		set<int> stmts = getStmtContainingStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> stmtLst1 = getStmtLstContainingStarStmt(*i);
			results.insert(stmtLst1.begin(), stmtLst1.end());
		}
		return results;
	}
	set<int> Contains::getStmtLstContainedStarInStmtLst (int stmtLst) { //returns the statementList which are ContainedStar in statementLst 
		set<int> results;
		set<int> stmts = getStmtContainedInStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> stmtLst1 = getStmtLstContainedStarInStmt(*i);
			results.insert(stmtLst1.begin(), stmtLst1.end());
		}
		return results;
	}
	
	
	//for statements as containers
	set<int> Contains::getVarContainedStarInStmt (int stmt) {   //returns the variables ContainedStar in a stmt
		set<int> results;
		set<int> var = getVarContainedInStmt(stmt);
		results.insert(var.begin(), var.end());

		set<int> stmtLst = getStmtLstContainedInStmt(stmt);
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> var2 = getVarContainedStarInStmtLst(*i);
			results.insert(var2.begin(),var2.end());
		}

		set<int> plus = getPlusContainedInStmt(stmt);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> var2 = getVarContainedStarInPlus(*i);
			results.insert(var2.begin(),var2.end());
		}

		set<int> minus = getMinusContainedInStmt(stmt);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> var2 = getVarContainedStarInMinus(*i);
			results.insert(var2.begin(),var2.end());
		}

		set<int> times = getTimesContainedInStmt(stmt);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> var2 = getVarContainedStarInTimes(*i);
			results.insert(var2.begin(),var2.end());
		}

		return results;
	}
	set<int> Contains::getStmtContainingStarVar (int var) {   //returns the statements which conatins the variable
		set<int> results;
		set<int> stmts = getStmtContainingVar(var);
		set<int> plus1 = getPlusContainingVar(var);
		set<int> minus1 = getMinusContainingVar(var);
		set<int> times1 = getTimesContainingVar(var);
		results.insert(stmts.begin(), stmts.end());

		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> stmt1 = getStmtContainingStarStmt(*i);
			results.insert(stmt1.begin(), stmt1.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> stmt = getStmtContainingStarPlus(*i);
			results.insert(stmt.begin(), stmt.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmt = getStmtContainingStarMinus(*i);
			results.insert(stmt.begin(), stmt.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmt = getStmtContainingStarTimes(*i);
			results.insert(stmt.begin(), stmt.end());
		}

		return results;
	}
	set<int> Contains::getConstContainedStarInStmt (int stmt) {  //returns the constants which are contained within a statement
		set<int> results;
		set<int> constant = getConstContainedInStmt(stmt);
		results.insert(constant.begin(), constant.end());

		set<int> stmtLst = getStmtLstContainedInStmt(stmt);
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> constant2 = getConstContainedStarInStmtLst(*i);
			results.insert(constant2.begin(),constant2.end());
		}

		set<int> plus = getPlusContainedInStmt(stmt);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> constant2 = getConstContainedStarInPlus(*i);
			results.insert(constant2.begin(),constant2.end());
		}

		set<int> minus = getMinusContainedInStmt(stmt);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> constant2 = getConstContainedStarInMinus(*i);
			results.insert(constant2.begin(),constant2.end());
		}

		set<int> times = getTimesContainedInStmt(stmt);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> constant2 = getConstContainedStarInTimes(*i);
			results.insert(constant2.begin(),constant2.end());
		}
		return results;
	}
	set<int> Contains::getStmtContainingStarConst(int constant) {  //returns the statements which contain the constant
		set<int> results;
		set<int> stmts = getStmtContainingConst(constant);
		set<int> plus1 = getPlusContainingConst(constant);
		set<int> minus1 = getMinusContainingConst(constant);
		set<int> times1 = getTimesContainingConst(constant);

		results.insert(stmts.begin(), stmts.end());

		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++){
			set<int> stmt = getStmtContainingStarStmt(*i);
			results.insert(stmt.begin(), stmt.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> stmt = getStmtContainingStarPlus(*i);
			results.insert(stmt.begin(), stmt.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmt = getStmtContainingStarMinus(*i);
			results.insert(stmt.begin(), stmt.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmt = getStmtContainingStarTimes(*i);
			results.insert(stmt.begin(), stmt.end());
		}
		return results;
	}
	set<int> Contains::getStmtLstContainedStarInStmt (int stmt) {//returns the statementList which are ContainedStar in statement (WILL NEVER APPEAR AS QUERY!!!)
		set<int> results;
		set<int> stmtLst1 = getStmtLstContainedInStmt(stmt);
		for(std::set<int>::iterator i=stmtLst1.begin(); i!=stmtLst1.end(); i++) {
			set<int> stmtLsts = getStmtLstContainedStarInStmtLst(*i);
			results.insert(stmtLsts.begin(), stmtLsts.end());
		}
		return results;
	}
	set<int> Contains::getStmtContainingStarStmtLst (int stmtLst) { //returns the statements contain statementList 
		set<int> results;
		set<int> stmts = getStmtContainingStmtLst(stmtLst);
		for(std::set<int>::iterator i=stmts.begin(); i!=stmts.end(); i++) {
			set<int> stmts = getStmtContainingStarStmt(*i);
			results.insert(stmts.begin(), stmts.end());
		}
		return results;
	}
	set<int> Contains::getPlusContainedStarInStmt(int stmt) { //returns the plus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> plus1 = getPlusContainedInStmt(stmt);
		set<int> stmtLst = getStmtLstContainedInStmt(stmt);
		set<int> minus1 = getMinusContainedInStmt(stmt);
		set<int> times1 = getTimesContainedInStmt(stmt);

		results.insert(plus1.begin(), plus1.end());

		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> plus2 = getPlusContainedStarInStmtLst(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> plus2 = getPlusContainedStarInMinus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> plus2 = getPlusContainedStarInTimes(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> plus2 = getPlusContainedStarInPlus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		return results;
	}

	set<int> Contains::getStmtContainingStarPlus(int plus) { //returns the statements ContainingStar plus 
		set<int> results;
		set<int> stmt1 = getStmtContainingPlus(plus);
		set<int> plus1 = getPlusContainingPlus(plus);
		set<int> minus1 = getMinusContainingPlus(plus);
		set<int> times1 = getTimesContainingPlus(plus);

		for(std::set<int>::iterator i=stmt1.begin(); i!=stmt1.end(); i++){
			set<int> stmt2 = getStmtContainingStarStmt(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++) {
			set<int> stmt2 = getStmtContainingStarPlus(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmt2 = getStmtContainingStarMinus(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmt2 = getStmtContainingStarTimes(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		results.insert(stmt1.begin(), stmt1.end());

		return results;
	}

	set<int> Contains::getMinusContainedStarInStmt(int stmt) { //returns the minus ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> plus1 = getPlusContainedInStmt(stmt);
		set<int> stmtLst = getStmtLstContainedInStmt(stmt);
		set<int> minus1 = getMinusContainedInStmt(stmt);
		set<int> times1 = getTimesContainedInStmt(stmt);

		results.insert(minus1.begin(), minus1.end());

		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> minus2 = getMinusContainedStarInStmtLst(*i);
			results.insert(minus2.begin(), minus2.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> minus2 = getMinusContainedStarInMinus(*i);
			results.insert(minus2.begin(), minus2.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> minus2 = getMinusContainedStarInTimes(*i);
			results.insert(minus2.begin(), minus2.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> minus2 = getMinusContainedStarInPlus(*i);
			results.insert(minus2.begin(), minus2.end());
		}
		return results;
	}
	set<int> Contains::getStmtContainingStarMinus(int minus) { //returns the statements ContainingStar minus
		set<int> results;
		set<int> stmt1 = getStmtContainingMinus(minus);
		set<int> plus1 = getPlusContainingMinus(minus);
		set<int> minus1 = getMinusContainingMinus(minus);
		set<int> times1 = getTimesContainingMinus(minus);

		for(std::set<int>::iterator i=stmt1.begin(); i!=stmt1.end(); i++){
			set<int> stmt2 = getStmtContainingStarStmt(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++) {
			set<int> stmt2 = getStmtContainingStarPlus(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmt2 = getStmtContainingStarMinus(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmt2 = getStmtContainingStarTimes(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		results.insert(stmt1.begin(), stmt1.end());
		return results;
	}
	set<int> Contains::getTimesContainedStarInStmt(int stmt) { //returns the times ContainedStar in statement (WILL NEVER APPEAR AS QUERY !!!)
		set<int> results;
		set<int> plus1 = getPlusContainedInStmt(stmt);
		set<int> stmtLst = getStmtLstContainedInStmt(stmt);
		set<int> minus1 = getMinusContainedInStmt(stmt);
		set<int> times1 = getTimesContainedInStmt(stmt);

		results.insert(times1.begin(), times1.end());

		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> times2 = getTimesContainedStarInStmtLst(*i);
			results.insert(times2.begin(), times2.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> times2 = getTimesContainedStarInMinus(*i);
			results.insert(times2.begin(), times2.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> times2 = getTimesContainedStarInTimes(*i);
			results.insert(times2.begin(), times2.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> times2 = getTimesContainedStarInPlus(*i);
			results.insert(times2.begin(), times2.end());
		}
		return results;
	}

	set<int> Contains::getStmtContainingStarTimes(int times) { //returns the statements ContainingStar times 
		set<int> results;
		set<int> stmt1 = getStmtContainingTimes(times);
		set<int> plus1 = getPlusContainingTimes(times);
		set<int> minus1 = getMinusContainingTimes(times);
		set<int> times1 = getTimesContainingTimes(times);

		for(std::set<int>::iterator i=stmt1.begin(); i!=stmt1.end(); i++){
			set<int> stmt2 = getStmtContainingStarStmt(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++) {
			set<int> stmt2 = getStmtContainingStarPlus(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> stmt2 = getStmtContainingStarMinus(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> stmt2 = getStmtContainingStarTimes(*i);
			results.insert(stmt2.begin(), stmt2.end());
		}

		results.insert(stmt1.begin(), stmt1.end());
		return results;
	}
	set<int> Contains::getStmtContainedStarInStmt(int stmt){
		set<int> results;
		set<int> stmtLst = getStmtLstContainedInStmt(stmt);
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> stmts = getStmtContainedStarInStmtLst(*i);
			results.insert(stmts.begin(), stmts.end());
		}
		return results;
	}
	
	set<int> Contains::getStmtContainingStarStmt(int stmt){
		set<int> results;
		set<int> stmtLst = getStmtLstContainingStmt(stmt);
		for(std::set<int>::iterator i=stmtLst.begin(); i!=stmtLst.end(); i++){
			set<int> stmts = getStmtContainingStarStmtLst(*i);
			results.insert(stmts.begin(), stmts.end());
		}
		return results;
	}

	//for plus node as container 
	set<int> Contains::getVarContainedStarInPlus(int plus) { //returns all those variables which are children of the plus node in the AST
		set<int> results;
		set<int> vars = getVarContainedInPlus(plus);
		results.insert( vars.begin(), vars.end());

		if(getTimesContainedInPlus(plus).size()!=0){
			set<int> times = getTimesContainedInPlus(plus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> vars1 = getVarContainedStarInTimes(*i);
				results.insert(vars1.begin(), vars1.end());
			}
		}
		if(getPlusContainedInPlus(plus).size()!=0){
			set<int> plus1 = getPlusContainedInPlus(plus);
			for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
				set<int> vars2 = getVarContainedStarInPlus(*i);
				results.insert(vars2.begin(), vars2.end());
			}
		}
		if(getMinusContainedInPlus(plus).size()!=0){
			set<int> minus1 = getMinusContainedInPlus(plus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> vars3 = getVarContainedStarInMinus(*i);
				results.insert(vars3.begin(), vars3.end());
			}
		}
		return results;
	}

	set<int> Contains::getPlusContainingStarVar(int var) { //returns all those pluses which contain the variable node
		set<int> results;
		set<int> plus = getPlusContainingVar(var);
		results.insert(plus.begin(), plus.end());
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> plus1 = getPlusContainingStarPlus(*i);
			results.insert(plus1.begin(), plus1.end());
		}
		set<int> minus = getMinusContainingVar(var);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> plus2 = getPlusContainingStarMinus(*i);
			results.insert(plus2.begin(), plus2.end());
		}
		set<int> times = getTimesContainingVar(var);
		for(std::set<int>::iterator i=times.begin(); i!=times.end();i++){
			set<int> plus3 = getPlusContainingStarTimes(*i);
			results.insert(plus3.begin(), plus3.end());
		}

		return results;
	}

	set<int> Contains::getConstContainedStarInPlus(int plus) { //returns all those constants which are children of the plus node in the AST
		set<int> results;
		set<int> constants = getConstContainedInPlus(plus);
		results.insert( constants.begin(), constants.end());

		if(getTimesContainedInPlus(plus).size()!=0){
			set<int> times = getTimesContainedInPlus(plus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> constants1 = getConstContainedStarInTimes(*i);
				results.insert(constants1.begin(), constants1.end());
			}
		}
		if(getPlusContainedInPlus(plus).size()!=0){
			set<int> plus1 = getPlusContainedInPlus(plus);
			for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
				set<int> constants2 = getConstContainedStarInPlus(*i);
				results.insert(constants2.begin(), constants2.end());
			}
		}
		if(getMinusContainedInPlus(plus).size()!=0){
			set<int> minus1 = getMinusContainedInPlus(plus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> constants3 = getConstContainedStarInMinus(*i);
				results.insert(constants3.begin(), constants3.end());
			}
		}
		return results;
	}

	set<int> Contains::getPlusContainingStarConst(int constant) { //returns all those pluses which contain the constant
		set<int> results;
		set<int> plus = getPlusContainingConst(constant);
		results.insert(plus.begin(), plus.end());
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> plus1 = getPlusContainingStarPlus(*i);
			results.insert(plus1.begin(), plus1.end());
		}

		set<int> minus = getMinusContainingConst(constant);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> plus2 = getPlusContainingStarMinus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		set<int> times = getTimesContainingConst(constant);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> plus3 = getPlusContainingStarTimes(*i);
			results.insert(plus3.begin(), plus3.end());
		}
		return results;
	}

	set<int> Contains::getPlusContainedStarInPlus(int plus) { //returns all those plus which are children of the plus node in the AST
		set<int> results;
		set<int> plus1 = getPlusContainedInPlus(plus);
		results.insert( plus1.begin(), plus1.end());

		if(getTimesContainedInPlus(plus).size()!=0){
			set<int> times = getTimesContainedInPlus(plus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> plus2 = getPlusContainedStarInTimes(*i);
				results.insert(plus2.begin(), plus2.end());
			}
		}
		if(getPlusContainedInPlus(plus).size()!=0){
			set<int> plus2 = getPlusContainedInPlus(plus);
			for(std::set<int>::iterator i=plus2.begin(); i!=plus2.end(); i++){
				set<int> plus3 = getPlusContainedStarInPlus(*i);
				results.insert(plus3.begin(), plus3.end());
			}
		}
		if(getMinusContainedInPlus(plus).size()!=0){
			set<int> minus1 = getMinusContainedInPlus(plus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> plus2 = getPlusContainedStarInMinus(*i);
				results.insert(plus2.begin(), plus2.end());
			}
		}
		return results;
	}


	set<int> Contains::getPlusContainingStarPlus(int plus) { //returns all those pluses which contain the plus node
		set<int> results;
		set<int> plus1 = getPlusContainingPlus(plus);
		results.insert(plus1.begin(), plus1.end());
		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> plus2 = getPlusContainingStarPlus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		set<int> minus = getMinusContainingPlus(plus);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> plus2 = getPlusContainingStarMinus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		set<int> times = getTimesContainingPlus(plus);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> plus3 = getPlusContainingStarTimes(*i);
			results.insert(plus3.begin(), plus3.end());
		}
		return results;

	}

	set<int> Contains::getMinusContainedStarInPlus(int plus) { //returns all those minus which are children of the plus node in the AST
		set<int> results;
		set<int> minus = getMinusContainedInPlus(plus);
		results.insert( minus.begin(), minus.end());

		if(getTimesContainedInPlus(plus).size()!=0){
			set<int> times = getTimesContainedInPlus(plus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> minus1 = getMinusContainedStarInTimes(*i);
				results.insert(minus1.begin(), minus1.end());
			}
		}
		if(getPlusContainedInPlus(plus).size()!=0){
			set<int> plus1 = getPlusContainedInPlus(plus);
			for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
				set<int> minus2 = getMinusContainedStarInPlus(*i);
				results.insert(minus2.begin(), minus2.end());
			}
		}
		if(getMinusContainedInPlus(plus).size()!=0){
			set<int> minus1 = getMinusContainedInPlus(plus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> minus3 = getMinusContainedStarInMinus(*i);
				results.insert(minus3.begin(), minus3.end());
			}
		}
		return results;
	}

	set<int> Contains::getPlusContainingStarMinus(int minus) { //returns all those pluses which contain the minus node
		set<int> results;
		set<int> plus1 = getPlusContainingMinus(minus);
		results.insert(plus1.begin(), plus1.end());
		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> plus2 = getPlusContainingStarPlus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		set<int> minus1 = getMinusContainingMinus(minus);
		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> plus2 = getPlusContainingStarMinus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		set<int> times = getTimesContainingMinus(minus);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> plus3 = getPlusContainingStarTimes(*i);
			results.insert(plus3.begin(), plus3.end());
		}
		return results;

	}

	set<int> Contains::getTimesContainedStarInPlus(int plus) { //returns all those times which are children of the plus node in the AST
		set<int> results;
		set<int> times = getTimesContainedInPlus(plus);
		results.insert( times.begin(), times.end());

		if(getTimesContainedInPlus(plus).size()!=0){
			set<int> times1 = getTimesContainedInPlus(plus);
			for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
				set<int> times2 = getTimesContainedStarInTimes(*i);
				results.insert(times2.begin(), times2.end());
			}
		}
		if(getPlusContainedInPlus(plus).size()!=0){
			set<int> plus1 = getPlusContainedInPlus(plus);
			for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
				set<int> times2 = getTimesContainedStarInPlus(*i);
				results.insert(times2.begin(), times2.end());
			}
		}
		if(getMinusContainedInPlus(plus).size()!=0){
			set<int> minus1 = getMinusContainedInPlus(plus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> times3 = getTimesContainedStarInMinus(*i);
				results.insert(times3.begin(), times3.end());
			}
		}
		return results;
	}

	set<int> Contains::getPlusContainingStarTimes(int times) { //returns all those pluses which contain the times node
		set<int> results;
		set<int> plus = getPlusContainingTimes(times);
		results.insert(plus.begin(), plus.end());
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> plus1 = getPlusContainingStarPlus(*i);
			results.insert(plus1.begin(), plus1.end());
		}

		set<int> minus = getMinusContainingTimes(times);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> plus2 = getPlusContainingStarMinus(*i);
			results.insert(plus2.begin(), plus2.end());
		}

		set<int> times1 = getTimesContainingTimes(times);
		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> plus3 = getPlusContainingStarTimes(*i);
			results.insert(plus3.begin(), plus3.end());
		}
		return results;
	}


	
	//for minus node as container
	set<int> Contains::getVarContainedStarInMinus(int minus) { //returns all those variables which are children of the minus node in the AST
		set<int> results;
		set<int> vars = getVarContainedInMinus(minus);
		results.insert( vars.begin(), vars.end());

		if(getTimesContainedInMinus(minus).size()!=0){
			set<int> times = getTimesContainedInMinus(minus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> vars1 = getVarContainedStarInTimes(*i);
				results.insert(vars1.begin(), vars1.end());
			}
		}
		if(getPlusContainedInMinus(minus).size()!=0){
			set<int> plus = getPlusContainedInMinus(minus);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> vars2 = getVarContainedStarInPlus(*i);
				results.insert(vars2.begin(), vars2.end());
			}
		}
		if(getMinusContainedInMinus(minus).size()!=0){
			set<int> minus1 = getMinusContainedInMinus(minus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> vars3 = getVarContainedStarInMinus(*i);
				results.insert(vars3.begin(), vars3.end());
			}
		}
		return results;
	}
		

	set<int> Contains::getMinusContainingStarVar(int var) { //returns all those minus which contain the variable node
		set<int> results;
		set<int> minus = getMinusContainingVar(var);
		results.insert(minus.begin(), minus.end());
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> minus1 = getMinusContainingStarMinus(*i);
			results.insert(minus1.begin(), minus1.end());
		}

		set<int> plus = getPlusContainingVar(var);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> minus2 = getMinusContainingStarPlus(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		set<int> times = getTimesContainingVar(var);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> minus2 = getMinusContainingStarTimes(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		return results;
	}

	set<int> Contains::getConstContainedStarInMinus(int minus) { //returns all those constants which are children of the minus node in the AST
		set<int> results;
		set<int> constants = getConstContainedInMinus(minus);
		results.insert( constants.begin(), constants.end());

		if(getTimesContainedInMinus(minus).size()!=0){
			set<int> times = getTimesContainedInMinus(minus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> constants1 = getConstContainedStarInTimes(*i);
				results.insert(constants1.begin(), constants1.end());
			}
		}
		if(getPlusContainedInMinus(minus).size()!=0){
			set<int> plus = getPlusContainedInMinus(minus);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> constants2 = getConstContainedStarInPlus(*i);
				results.insert(constants2.begin(), constants2.end());
			}
		}
		if(getMinusContainedInMinus(minus).size()!=0){
			set<int> minus1 = getMinusContainedInMinus(minus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> constants3 = getConstContainedStarInMinus(*i);
				results.insert(constants3.begin(), constants3.end());
			}
		}
		return results;
	}

	set<int> Contains::getMinusContainingStarConst(int constant) { //returns all those minus which contain the constant
		set<int> results;
		set<int> minus = getMinusContainingConst(constant);
		results.insert(minus.begin(), minus.end());
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> minus1 = getMinusContainingStarMinus(*i);
			results.insert(minus1.begin(), minus1.end());
		}
		set<int> plus = getPlusContainingConst(constant);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> minus2 = getMinusContainingStarPlus(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		set<int> times = getTimesContainingConst(constant);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> minus2 = getMinusContainingStarTimes(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		return results;
	}

	set<int> Contains::getPlusContainedStarInMinus(int minus) { //returns all those plus which are children of the minus node in the AST
		set<int> results;
		set<int> plus = getPlusContainedInMinus(minus);
		results.insert( plus.begin(), plus.end());

		if(getTimesContainedInMinus(minus).size()!=0){
			set<int> times = getTimesContainedInMinus(minus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> plus1 = getPlusContainedStarInTimes(*i);
				results.insert(plus1.begin(), plus1.end());
			}
		}
		if(getPlusContainedInMinus(minus).size()!=0){
			set<int> plus2 = getPlusContainedInMinus(minus);
			for(std::set<int>::iterator i=plus2.begin(); i!=plus2.end(); i++){
				set<int> plus3 = getPlusContainedStarInPlus(*i);
				results.insert(plus3.begin(), plus3.end());
			}
		}
		if(getMinusContainedInMinus(minus).size()!=0){
			set<int> minus1 = getMinusContainedInMinus(minus);
			for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
				set<int> plus1 = getPlusContainedStarInMinus(*i);
				results.insert(plus1.begin(), plus1.end());
			}
		}
		return results;
	}

	set<int> Contains::getMinusContainingStarPlus(int plus) { //returns all those minuses which contain the plus node
		set<int> results;
		set<int> minus = getMinusContainingPlus(plus);
		results.insert(minus.begin(), minus.end());
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> minus1 = getMinusContainingStarMinus(*i);
			results.insert(minus1.begin(), minus1.end());
		}
		set<int> plus1 = getPlusContainingPlus(plus);
		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> minus2 = getMinusContainingStarPlus(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		set<int> times = getTimesContainingPlus(plus);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> minus2 = getMinusContainingStarTimes(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		return results;
	}

	set<int> Contains::getMinusContainedStarInMinus(int minus) { //returns all those minus which are children of the minus node in the AST
		set<int> results;
		set<int> minus1 = getMinusContainedInMinus(minus);
		results.insert( minus1.begin(), minus1.end());

		if(getTimesContainedInMinus(minus).size()!=0){
			set<int> times = getTimesContainedInMinus(minus);
			for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
				set<int> minus2 = getMinusContainedStarInTimes(*i);
				results.insert(minus2.begin(), minus2.end());
			}
		}
		if(getPlusContainedInMinus(minus).size()!=0){
			set<int> plus = getPlusContainedInMinus(minus);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> minus2 = getMinusContainedStarInPlus(*i);
				results.insert(minus2.begin(), minus2.end());
			}
		}
		if(getMinusContainedInMinus(minus).size()!=0){
			set<int> minus2= getMinusContainedInMinus(minus);
			for(std::set<int>::iterator i=minus2.begin(); i!=minus2.end(); i++){
				set<int> minus3 = getMinusContainedStarInMinus(*i);
				results.insert(minus3.begin(), minus3.end());
			}
		}
		return results;
	}

	set<int> Contains::getMinusContainingStarMinus(int minus) { //returns all those minus which contain the minus node
		set<int> results;
		set<int> minus1 = getMinusContainingMinus(minus);
		results.insert(minus1.begin(), minus1.end());
		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> minus2 = getMinusContainingStarMinus(*i);
			results.insert(minus2.begin(), minus2.end());
		}
		set<int> plus = getPlusContainingMinus(minus);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> minus2 = getMinusContainingStarPlus(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		set<int> times = getTimesContainingMinus(minus);
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> minus2 = getMinusContainingStarTimes(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		return results;
	}
	

	set<int> Contains::getTimesContainedStarInMinus(int minus) { //returns all those times which are children of the minus node in the AST
		set<int> results;
		set<int> times = getTimesContainedInMinus(minus);
		results.insert( times.begin(), times.end());

		if(getTimesContainedInMinus(minus).size()!=0){
			set<int> times1 = getTimesContainedInMinus(minus);
			for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
				set<int> times2 = getTimesContainedStarInTimes(*i);
				results.insert(times2.begin(), times2.end());
			}
		}
		if(getPlusContainedInMinus(minus).size()!=0){
			set<int> plus = getPlusContainedInMinus(minus);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> times2 = getTimesContainedStarInPlus(*i);
				results.insert(times2.begin(), times2.end());
			}
		}
		if(getMinusContainedInMinus(minus).size()!=0){
			set<int> minus2= getMinusContainedInMinus(minus);
			for(std::set<int>::iterator i=minus2.begin(); i!=minus2.end(); i++){
				set<int> times2 = getTimesContainedStarInMinus(*i);
				results.insert(times2.begin(), times2.end());
			}
		}
		return results;

	}

	set<int> Contains::getMinusContainingStarTimes(int times) { //returns all those minuses which contain the times node
		set<int> results;
		set<int> minus1 = getMinusContainingTimes(times);
		results.insert(minus1.begin(), minus1.end());
		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> minus2 = getMinusContainingStarMinus(*i);
			results.insert(minus2.begin(), minus2.end());
		}

		set<int> plus = getPlusContainingTimes(times);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> minus2 = getMinusContainingStarPlus(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		set<int> times1 = getTimesContainingTimes(times);
		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> minus2 = getMinusContainingStarTimes(*i);
			results.insert(minus2.begin(),minus2.end());
		}

		return results;
	}

	//for times node as container
	set<int> Contains::getVarContainedStarInTimes(int times) { //returns all those variables which are children of the times node in the AST
		set<int> results;
		set<int> vars = getVarContainedInTimes(times);
		results.insert( vars.begin(), vars.end());
		if(getTimesContainedInTimes(times).size()!=0){
			set<int> times1 = getTimesContainedInTimes(times);
			for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
				set<int> vars1 = getVarContainedStarInTimes(*i);
				results.insert(vars1.begin(), vars1.end());
			}
		}
		if(getPlusContainedInTimes(times).size()!=0){
			set<int> plus = getPlusContainedInTimes(times);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> vars2 = getVarContainedStarInPlus(*i);
				results.insert(vars2.begin(), vars2.end());
			}
		}
		if(getMinusContainedInTimes(times).size()!=0){
			set<int> minus = getMinusContainedInTimes(times);
			for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
				set<int> vars3 = getVarContainedStarInMinus(*i);
				results.insert(vars3.begin(), vars3.end());
			}
		}
		return results;
	}


	set<int> Contains::getTimesContainingStarVar(int var) { //returns all those times which contain the variable node
		set<int> results;
		set<int> times = getTimesContainingVar(var);
		results.insert(times.begin(), times.end());
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> times1 = getTimesContainingStarTimes(*i);
			results.insert(times1.begin(), times1.end());
		}
		set<int> plus = getPlusContainingVar(var);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> times2 = getTimesContainingStarPlus(*i);
			results.insert(times2.begin(),times2.end());
		}

		set<int> minus = getMinusContainingVar(var);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> times2 = getTimesContainingStarMinus(*i);
			results.insert(times2.begin(),times2.end());
		}

		return results;
	}


	set<int> Contains::getConstContainedStarInTimes(int times) { //returns all those constants which are children of the times node in the AST
		set<int> results;
		set<int> constants = getConstContainedInTimes(times);
		results.insert( constants.begin(), constants.end());
		if(getTimesContainedInTimes(times).size()!=0){
			set<int> times1 = getTimesContainedInTimes(times);
			for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
				set<int> constants1 = getConstContainedStarInTimes(*i);
				results.insert(constants1.begin(), constants1.end());
			}
		}
		if(getPlusContainedInTimes(times).size()!=0){
			set<int> plus = getPlusContainedInTimes(times);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> const2 = getConstContainedStarInPlus(*i);
				results.insert(const2.begin(), const2.end());
			}
		}
		if(getMinusContainedInTimes(times).size()!=0){
			set<int> minus = getMinusContainedInTimes(times);
			for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
				set<int> const3 = getConstContainedStarInMinus(*i);
				results.insert(const3.begin(), const3.end());
			}
		}
		return results;

	}

	set<int> Contains::getTimesContainingStarConst(int constant) { //returns all those times which contain the constant
		set<int> results;
		set<int> times = getTimesContainingConst(constant);
		results.insert(times.begin(), times.end());
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> times1 = getTimesContainingStarTimes(*i);
			results.insert(times1.begin(), times1.end());
		}
		set<int> plus = getPlusContainingConst(constant);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> times2 = getTimesContainingStarPlus(*i);
			results.insert(times2.begin(),times2.end());
		}

		set<int> minus = getMinusContainingConst(constant);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> times2 = getTimesContainingStarMinus(*i);
			results.insert(times2.begin(),times2.end());
		}
		return results;
	}

	set<int> Contains::getPlusContainedStarInTimes(int times) { //returns all those plus which are children of the times node in the AST
		set<int> results;
		set<int> plus = getPlusContainedInTimes(times);
		results.insert( plus.begin(), plus.end());
		if(getTimesContainedInTimes(times).size()!=0){
			set<int> times1 = getTimesContainedInTimes(times);
			for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
				set<int> plus1 = getPlusContainedStarInTimes(*i);
				results.insert(plus1.begin(), plus1.end());
			}
		}
		if(getPlusContainedInTimes(times).size()!=0){
			set<int> plus = getPlusContainedInTimes(times);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> Plus2 = getPlusContainedStarInPlus(*i);
				results.insert(Plus2.begin(), Plus2.end());
			}
		}
		if(getMinusContainedInTimes(times).size()!=0){
			set<int> minus = getMinusContainedInTimes(times);
			for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
				set<int> Plus3 = getPlusContainedStarInMinus(*i);
				results.insert(Plus3.begin(), Plus3.end());
			}
		}
		return results;

	}

	set<int> Contains::getTimesContainingStarPlus(int plus) { //returns all those times which contain the plus node
		set<int> results;
		set<int> times = getTimesContainingPlus(plus);
		results.insert(times.begin(), times.end());
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> times1 = getTimesContainingStarTimes(*i);
			results.insert(times1.begin(), times1.end());
		}
		set<int> plus1 = getPlusContainingPlus(plus);
		for(std::set<int>::iterator i=plus1.begin(); i!=plus1.end(); i++){
			set<int> times2 = getTimesContainingStarPlus(*i);
			results.insert(times2.begin(),times2.end());
		}

		set<int> minus = getMinusContainingPlus(plus);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> times2 = getTimesContainingStarMinus(*i);
			results.insert(times2.begin(),times2.end());
		}
		return results;
	}

	set<int> Contains::getMinusContainedStarInTimes(int times) { //returns all those minus which are children of the times node in the AST
		set<int> results;
		set<int> minus = getMinusContainedInTimes(times);
		results.insert( minus.begin(), minus.end());
		if(getTimesContainedInTimes(times).size()!=0){
			set<int> times1 = getTimesContainedInTimes(times);
			for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
				set<int> minus1 = getMinusContainedStarInTimes(*i);
				results.insert(minus1.begin(), minus1.end());
			}
		}
		if(getPlusContainedInTimes(times).size()!=0){
			set<int> plus = getPlusContainedInTimes(times);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> minus2 = getMinusContainedStarInPlus(*i);
				results.insert(minus2.begin(), minus2.end());
			}
		}
		if(getMinusContainedInTimes(times).size()!=0){
			set<int> minus = getMinusContainedInTimes(times);
			for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
				set<int> minus3 = getMinusContainedStarInMinus(*i);
				results.insert(minus3.begin(), minus3.end());
			}
		}
		return results;
	}

	set<int> Contains::getTimesContainingStarMinus(int minus) { //returns all those times which contain the minus node
		set<int> results;
		set<int> times = getTimesContainingMinus(minus);
		results.insert(times.begin(), times.end());
		for(std::set<int>::iterator i=times.begin(); i!=times.end(); i++){
			set<int> times1 = getTimesContainingStarTimes(*i);
			results.insert(times1.begin(), times1.end());
		}
		set<int> plus = getPlusContainingMinus(minus);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> times2 = getTimesContainingStarPlus(*i);
			results.insert(times2.begin(),times2.end());
		}

		set<int> minus1 = getMinusContainingMinus(minus);
		for(std::set<int>::iterator i=minus1.begin(); i!=minus1.end(); i++){
			set<int> times2 = getTimesContainingStarMinus(*i);
			results.insert(times2.begin(),times2.end());
		}
		return results;
	}

	set<int> Contains::getTimesContainedStarInTimes(int times) { //returns all those times which are children of the times node in the AST
		set<int> results;
		set<int> times1 = getTimesContainedInTimes(times);
		results.insert( times1.begin(), times1.end());
		if(getTimesContainedInTimes(times).size()!=0){
			set<int> times2 = getTimesContainedInTimes(times);
			for(std::set<int>::iterator i=times2.begin(); i!=times2.end(); i++){
				set<int> times3 = getTimesContainedStarInTimes(*i);
				results.insert(times3.begin(), times3.end());
			}
		}
		if(getPlusContainedInTimes(times).size()!=0){
			set<int> plus = getPlusContainedInTimes(times);
			for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
				set<int> times1 = getTimesContainedStarInPlus(*i);
				results.insert(times1.begin(), times1.end());
			}
		}
		if(getMinusContainedInTimes(times).size()!=0){
			set<int> minus = getMinusContainedInTimes(times);
			for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
				set<int> times1 = getTimesContainedStarInMinus(*i);
				results.insert(times1.begin(), times1.end());
			}
		}
		return results;
	}

	set<int> Contains::getTimesContainingStarTimes(int times) { //returns all those times which contain the times node
		set<int> results;
		set<int> times1 = getTimesContainingTimes(times);
		results.insert(times1.begin(), times1.end());
		for(std::set<int>::iterator i=times1.begin(); i!=times1.end(); i++){
			set<int> times2 = getTimesContainingStarTimes(*i);
			results.insert(times2.begin(), times2.end());
		}
		set<int> plus = getPlusContainingTimes(times);
		for(std::set<int>::iterator i=plus.begin(); i!=plus.end(); i++){
			set<int> times2 = getTimesContainingStarPlus(*i);
			results.insert(times2.begin(),times2.end());
		}

		set<int> minus = getMinusContainingTimes(times);
		for(std::set<int>::iterator i=minus.begin(); i!=minus.end(); i++){
			set<int> times2 = getTimesContainingStarMinus(*i);
			results.insert(times2.begin(),times2.end());
		}
		return results;
	}


	//boolean functions

	bool Contains:: isContainsStarProcStmtLst(int proc, int stmtLst){ //returns true if contains*(proc,stmtlst) holds
		set<int> stmtLst1 = getStmtLstContainedStarInProc(proc);
		std::set<int>::iterator it = stmtLst1.find(stmtLst);
		if(it!=stmtLst1.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarProcStmt(int proc, int stmt){ //returns true if contains*(proc,stmt) holds
		set<int> stmts = getStmtContainedStarInProc(proc);
		std::set<int>::iterator it = stmts.find(stmt);
		if(it!=stmts.end())
			return true;
		else
			return false;
	}
	

	bool Contains:: isContainsStarProcVar(int proc, int var){ //returns true if contains*(proc,var) holds
		set<int> vars = getVarContainedStarInProc(proc);
		std::set<int>::iterator it = vars.find(var);
		if(it!=vars.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarProcPlus(int proc, int plus){ //returns true if contains*(proc,plus) holds
		set<int> pluses = getPlusContainedStarInProc(proc);
		std::set<int>::iterator it = pluses.find(plus);
		if(it!=pluses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarProcConst(int proc, int constant){ //returns true if contains*(proc,const) holds
		set<int> consts = getConstContainedStarInProc(proc);
		std::set<int>::iterator it = consts.find(constant);
		if(it!=consts.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarProcMinus(int proc, int minus){ //returns true if contains*(proc,minus) holds
		set<int> minuses = getMinusContainedStarInProc(proc);
		std::set<int>::iterator it = minuses.find(minus);
		if(it!=minuses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarProcTimes(int proc, int times){//returns true if contains*(proc,times) holds
		set<int> times1 = getTimesContainedStarInProc(proc);
		std::set<int>::iterator it = times1.find(times);
		if(it!=times1.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtLstStmt(int stmtLst, int stmt){ //returns true if contains*(stmtLst, stmt) holds
		set<int> stmts = getStmtContainedStarInStmtLst(stmtLst);
		std::set<int>::iterator it = stmts.find(stmt);
		if(it!=stmts.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtLstVar(int stmtLst, int var){ //returns true if contains*(stmtLst, var) holds
		set<int> vars = getVarContainedStarInStmtLst(stmtLst);
		std::set<int>::iterator it = vars.find(var);
		if(it!=vars.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtLstConst(int stmtLst, int constant){ //returns true if contains*(stmtLst, const) holds
		set<int> consts = getConstContainedStarInStmtLst(stmtLst);
		std::set<int>::iterator it = consts.find(constant);
		if(it!=consts.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtLstPlus(int stmtLst, int plus){ //returns true if contains*(stmtLst, plus) holds
		set<int> pluses = getPlusContainedStarInStmtLst(stmtLst);
		std::set<int>::iterator it = pluses.find(plus);
		if(it!=pluses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtLstMinus(int stmtLst, int minus){ //returns true if contains*(stmtLst, minus) holds
		set<int> minuses = getMinusContainedStarInStmtLst(stmtLst);
		std::set<int>::iterator it = minuses.find(minus);
		if(it!=minuses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtLstTimes(int stmtLst, int times){ //returns true if contains*(stmtLst, times) holds
		set<int> times1 = getTimesContainedStarInStmtLst(stmtLst);
		std::set<int>::iterator it = times1.find(times);
		if(it!=times1.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtLstStmtLst(int stmtLst1, int stmtLst2){ //returns true if contains*(stmtLst,stmtLst) hold
		set<int> stmtLst3 = getStmtLstContainedStarInStmtLst(stmtLst1);
		std::set<int>::iterator it = stmtLst3.find(stmtLst2);
		if(it!=stmtLst3.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtVar(int stmt, int var){ //returns true if contains*(Stmt,var) holds  
		set<int> vars = getVarContainedStarInStmt(stmt);
		std::set<int>::iterator it = vars.find(var);
		if(it!=vars.end())
			return true;
		else
			return false;
	}


	bool Contains:: isContainsStarStmtConst(int stmt, int constant){ //returns true if contains*(Stmt,Const) holds 
		set<int> consts = getConstContainedStarInStmt(stmt);
		std::set<int>::iterator it = consts.find(constant);
		if(it!=consts.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtPlus(int stmt, int plus){ //returns true if contains*(stmt,plus) holds
		set<int> pluses = getPlusContainedStarInStmt(stmt);
		std::set<int>::iterator it = pluses.find(plus);
		if(it!=pluses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtMinus(int stmt, int minus){ //returns true if contains*(stmt,minus) holds 
		set<int> minuses = getMinusContainedStarInStmt(stmt);
		std::set<int>::iterator it = minuses.find(minus);
		if(it!=minuses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtTimes(int stmt, int times){ //returns true if contains*(stmt, times) holds 
		set<int> times1 = getTimesContainedStarInStmt(stmt);
		std::set<int>::iterator it = times1.find(times);
		if(it!=times1.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarStmtStmtLst(int stmt, int stmtLst){ //returns true if contains*(stmt,stmtlst) holds 
		set<int> stmtLsts = getStmtLstContainedStarInStmt(stmt);
		std::set<int>::iterator it = stmtLsts.find(stmtLst);
		if(it!=stmtLsts.end())
			return true;
		else
			return false;
	}



	bool Contains:: isContainsStarPlusVar(int plus, int var){ //returns true if contains*(plus,var) holds 
		set<int> vars = getVarContainedStarInPlus(plus);
		std::set<int>::iterator it = vars.find(var);
		if(it!=vars.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarPlusConst(int plus, int constant){ //returns true if contains*(plus,const) holds
		set<int> constants = getConstContainedStarInPlus(plus);
		std::set<int>::iterator it = constants.find(constant);
		if(it!=constants.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarMinusVar(int minus,int var){ //returns true if contains*(minus,var) holds
		set<int> vars = getVarContainedStarInMinus(minus);
		std::set<int>::iterator it = vars.find(var);
		if(it!=vars.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarMinusConst(int minus, int constant){ //returns true if contains*(minus,const) holds
		set<int> constants = getConstContainedStarInMinus(minus);
		std::set<int>::iterator it = constants.find(constant);
		if(it!=constants.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarTimesVar(int times, int var){ //returns true if contains*(times,var) holds
		set<int> vars = getVarContainedStarInTimes(times);
		std::set<int>::iterator it = vars.find(var);
		if(it!=vars.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarTimesConst(int times, int constant){ //returns true if contains*(times,const) holds
		set<int> constants = getConstContainedStarInTimes(times);
		std::set<int>::iterator it = constants.find(constant);
		if(it!=constants.end())
			return true;
		else
			return false;
	}
	
	bool Contains:: isContainsStarPlusPlus(int plus1, int plus2){ //returns true if contains*(plus,plus) holds
		set<int> pluses = getPlusContainedStarInPlus(plus1);
		std::set<int>::iterator it = pluses.find(plus2);
		if(it!=pluses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarPlusMinus(int plus, int minus){ //return true if contains*(plus,minus) holds
		set<int> minuses = getMinusContainedStarInPlus(plus);
		std::set<int>::iterator it = minuses.find(minus);
		if(it!=minuses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarPlusTimes(int plus, int times){ //returns true if contains*(plus,plus) holds
		set<int> times1 = getTimesContainedStarInPlus(plus);
		std::set<int>::iterator it = times1.find(times);
		if(it!=times1.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarMinusTimes(int minus,int times){ //return true if contains*(minus,times) holds
		set<int> times1 = getTimesContainedStarInMinus(minus);
		std::set<int>::iterator it = times1.find(times);
		if(it!=times1.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarMinusPlus(int minus, int plus){ //returns true if contains*(minus,plus) holds
		set<int> pluses = getPlusContainedStarInMinus(minus);
		std::set<int>::iterator it = pluses.find(plus);
		if(it!=pluses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarMinusMinus(int minus1, int minus2){ //return true if contains*(minus,minus) holds
		set<int> minuses = getMinusContainedStarInMinus(minus1);
		std::set<int>::iterator it = minuses.find(minus2);
		if(it!=minuses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarTimesPlus (int times, int plus){ //return true if contains*(times,plus) holds 
		set<int> pluses = getPlusContainedStarInTimes(times);
		std::set<int>::iterator it = pluses.find(plus);
		if(it!=pluses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarTimesMinus(int times, int minus){ // return true if contains*(times,minus) holds
		set<int> minuses = getMinusContainedStarInTimes(times);
		std::set<int>::iterator it = minuses.find(minus);
		if(it!=minuses.end())
			return true;
		else
			return false;
	}

	bool Contains:: isContainsStarTimesTimes(int times1, int times2){ // return true if contains*(times,times) holds 
		set<int> times3 = getTimesContainedStarInTimes(times1);
		std::set<int>::iterator it = times3.find(times2);
		if(it!=times3.end())
			return true;
		else
			return false;
	}

	