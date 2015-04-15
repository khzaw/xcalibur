#pragma once
#include "Siblings.h" 
#include<iostream>

using namespace std;

Sibling::Sibling() {
}

//accessors
vector<pair<int,int>> Sibling::getProcProcSibling(){
	return procProc;
}
vector<pair<int,int>> Sibling::getStmtLstStmtLstSibling(){
	return stmtLstStmtLst;
}

vector<pair<int,int>> Sibling::getStmtStmtSibling(){
	return stmtStmt;
}

vector<pair<int,int>> Sibling::getVarStmtLstSibling(){
	return varStmtLst;
}  // var-then, var-else

vector<pair<int,int>> Sibling::getVarConstSibling(){
	return varConst; 
} //assign 

vector<pair<int,int>> Sibling::getVarPlusSibling(){
	return varPlus;
}

vector<pair<int,int>> Sibling::getVarMinusSibling(){
	return varMinus;
}

vector<pair<int,int>> Sibling::getVarTimesSibling(){
	return varTimes;
}

vector<pair<int,int>> Sibling::getConstPlusSibling(){
	return constPlus;
}

vector<pair<int,int>> Sibling::getConstMinusSibling(){
	return constMinus;
}

vector<pair<int,int>> Sibling::getConstTimesSibling(){
	return constTimes;
}

vector<pair<int,int>> Sibling::getPlusPlusSibling(){
	return plusPlus;
}

vector<pair<int,int>> Sibling::getPlusMinusSibling(){
	return plusMinus;
}

vector<pair<int,int>> Sibling::getPlusTimesSibling(){
	return plusTimes;
}

vector<pair<int,int>> Sibling::getMinusMinusSibling(){
	return minusMinus;
}

vector<pair<int,int>> Sibling::getMinusTimesSibling(){
	return minusTimes;
}

vector<pair<int,int>> Sibling::getTimesTimesSibling(){
	return timesTimes;
}

vector<pair<int,int>> Sibling::getVarVarSibling(){
	return varVar;
}

vector<pair<int,int>> Sibling::getConstConstSibling(){
	return constConst;
}

vector<pair<int,int>> Sibling::getConstStmtLstSibling(){
	return constStmtLst;
}


//functions to insert
void Sibling::insertProcProc(int proc, int proc1) {
	pair<int,int> pair1(proc,proc1);
	if(isSiblingProcProc(proc,proc)==false)
		procProc.push_back(pair1);
}

void Sibling::insertStmtLstStmtLst(int stmtLst1, int stmtLst2){
	pair<int,int> pair1(stmtLst1,stmtLst2);
	if(isSiblingStmtLstStmtLst(stmtLst1,stmtLst2)==false)
		stmtLstStmtLst.push_back(pair1);
}

void Sibling::insertStmtStmt(int stmt1, int stmt2){
	pair<int,int> pair1(stmt1,stmt2);
	if(isSiblingStmtStmt(stmt1,stmt2)==false)
		stmtStmt.push_back(pair1);
}

void Sibling::inserVarStmtLst(int var, int stmtLst) {
	pair<int,int> pair1(var,stmtLst);
	if(isSiblingVarStmtLst(var,stmtLst)==false)
		varStmtLst.push_back(pair1);
}

void Sibling::insertVarConst(int var, int constant){
	pair<int,int> pair1(var,constant);
	if(isSiblingVarConst(var,constant)==false)
		varConst.push_back(pair1);
}

void Sibling::insertVarPlus(int var, int plus){
	pair<int,int> pair1(var,plus);
	if(isSiblingVarPlus(var,plus)==false)
		varPlus.push_back(pair1);
}

void Sibling::insertVarMinus(int var,int minus){
	pair<int,int> pair1(var, minus);
	if(isSiblingVarMinus(var,minus)==false)
		varMinus.push_back(pair1);
}

void Sibling::insertVarTimes(int var, int times){
	pair<int,int> pair1(var,times);
	if(isSiblingVarTimes(var,times)==false)
		varTimes.push_back(pair1);
}

void Sibling::insertConstStmtLst(int constant, int stmtLst){
	pair<int,int> pair1(constant, stmtLst);
	if(isSiblingConstStmtLst(constant,stmtLst)==false)
		constStmtLst.push_back(pair1);
}

void Sibling::insertConstConst(int const1, int const2){
	pair<int,int> pair1(const1, const2);
	if(isSiblingConstConst(const1,const2)==false)
		constConst.push_back(pair1);
}

void Sibling::insertConstPlus(int constant, int plus){
	pair<int,int> pair1(constant,plus);
	if(isSiblingConstPlus(constant,plus)==false)
		constPlus.push_back(pair1);
}

void Sibling::insertConstMinus(int constant, int minus){
	pair<int,int> pair1(constant, minus);
	if(isSiblingConstMinus(constant,minus)==false)
		constMinus.push_back(pair1);
}

void Sibling::insertConstTimes(int constant, int times){
	pair<int,int> pair1(constant, times);
	if(isSiblingConstTimes(constant,times)==false)
		constTimes.push_back(pair1);
}

void Sibling::insertPlusPlus(int plus1, int plus2){
	pair<int,int> pair1(plus1,plus2);
	if(isSiblingPlusPlus(plus1,plus2)==false)
		plusPlus.push_back(pair1);
}
void Sibling::insertPlusMinus(int plus, int minus){
	pair<int,int> pair1(plus, minus);
	if(isSiblingPlusMinus(plus,minus)==false)
		plusMinus.push_back(pair1);
}

void Sibling::insertPlusTimes(int plus1, int times){
	pair<int,int> pair1(plus1,times);
	if(isSiblingPlusTimes(plus1,times)==false)
		plusTimes.push_back(pair1);
}

void Sibling::insertMinusMinus(int minus1, int minus2){
	pair<int,int> pair1(minus1, minus2);
	if(isSiblingMinusMinus(minus1,minus2)==false)
		minusMinus.push_back(pair1);
}

void Sibling::insertMinusTimes(int minus, int times){
	pair<int,int> pair1(minus,times);
	if(isSiblingMinusTimes(minus,times)==false)
		minusTimes.push_back(pair1);
}

void Sibling::insertTimesTimes(int times1, int times2){
	pair<int,int> pair1(times1,times2);
	if(isSiblingTimesTimes(times1,times2)==false)
		timesTimes.push_back(pair1);
}

void Sibling::insertVarVar(int var1, int var2){
	pair<int,int> pair1(var1,var2);
	if(isSiblingVarVar(var1,var2)==false)
		varVar.push_back(pair1);
}



//functions to return siblings

set<int> Sibling::getProcsSiblingOfProc(int proc){
	set<int> results;
	for(int i=0; i<procProc.size(); i++){
		if(procProc.at(i).first==proc)
			results.insert(procProc.at(i).second);
		if(procProc.at(i).second==proc)
			results.insert(procProc.at(i).first);
	}
	return results;
}

set<int> Sibling::getStmtLstSiblingOfStmtLst(int stmtLst){
	set<int> results;
	for(int i=0; i<stmtLstStmtLst.size(); i++){
		if(stmtLstStmtLst.at(i).first==stmtLst)
			results.insert(stmtLstStmtLst.at(i).second);
		if(stmtLstStmtLst.at(i).second==stmtLst)
			results.insert(stmtLstStmtLst.at(i).first);
	}
	return results;
}

set<int> Sibling::getStmtSiblingOfStmt(int stmt){
	set<int> results;
	for(int i=0; i<stmtStmt.size(); i++){
		if(stmtStmt.at(i).first==stmt)
			results.insert(stmtStmt.at(i).second);
		if(stmtStmt.at(i).second==stmt)
			results.insert(stmtStmt.at(i).first);
	}
	return results;
}

set<int> Sibling::getVarSiblingOfConst(int constant){
	set<int> results;
	for(int i=0; i<varConst.size(); i++){
		if(varConst.at(i).second==constant)
			results.insert(varConst.at(i).first);
	}
	return results;
}

set<int> Sibling::getConstSiblingOfVar(int var){
	set<int> results;
	for(int i=0; i<varConst.size(); i++){
		if(varConst.at(i).first==var)
			results.insert(varConst.at(i).second);
	}
	return results;
}

set<int> Sibling::getVarSiblingOfVar(int var){
	set<int> results;
	for(int i=0; i<varVar.size(); i++){
		if(varVar.at(i).first==var)
			results.insert(varVar.at(i).second);
		if(varVar.at(i).second==var)
			results.insert(varVar.at(i).first);
	}
	return results;
}

set<int> Sibling::getConstSiblingOfConst(int constant){
	set<int> results;
	for(int i=0; i<constConst.size(); i++){
		if(constConst.at(i).first==constant)
			results.insert(constConst.at(i).second);
		if(constConst.at(i).second==constant)
			results.insert(constConst.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllProcsSiblingOfProc(){
	set<int> results;
	for(int i=0; i<procProc.size(); i++){
		results.insert(procProc.at(i).second);
		results.insert(procProc.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllStmtLstSiblingOfStmtLst(){
	set<int> results;
	for(int i=0; i<stmtLstStmtLst.size(); i++){
		results.insert(stmtLstStmtLst.at(i).second);
		results.insert(stmtLstStmtLst.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllStmtSiblingOfStmt(){
	set<int> results;
	for(int i=0; i<stmtStmt.size(); i++){
		results.insert(stmtStmt.at(i).second);
		results.insert(stmtStmt.at(i).first);
	}
	return results;
}


set<int> Sibling::getAllVarSiblingOfConst(){
	set<int> results;
	for(int i=0; i<varConst.size(); i++){
		results.insert(varConst.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllConstSiblingOfVar(){
	set<int> results;
	for(int i=0; i<varConst.size(); i++){
		results.insert(varConst.at(i).second);
	}
	return results;
}

set<int> Sibling::getAllVarSiblingOfVar(){
	set<int> results;
	for(int i=0; i<varVar.size(); i++){
		results.insert(varVar.at(i).second);
		results.insert(varVar.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllVarSiblingOfMinus(){
	set<int> results;
	for(int i=0; i<varMinus.size(); i++){
		results.insert(varMinus.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllVarSiblingOfPlus(){
	set<int> results;
	for(int i=0; i<varMinus.size(); i++){
		results.insert(varMinus.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllVarSiblingOfTimes(){
	set<int> results;
	for(int i=0; i<varTimes.size(); i++){
		results.insert(varTimes.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllConstSiblingOfPlus(){
	set<int> results;
	for(int i=0; i<constPlus.size(); i++){
		results.insert(constPlus.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllConstSiblingOfMinus(){
	set<int> results;
	for(int i=0; i<constMinus.size(); i++){
		results.insert(constMinus.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllConstSiblingOfTimes(){
	set<int> results;
	for(int i=0; i<constTimes.size(); i++){
		results.insert(constTimes.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllConstSiblingOfConst(){
	set<int> results;
	for(int i=0; i<constConst.size(); i++){
		results.insert(constConst.at(i).second);
		results.insert(constConst.at(i).first);
	}
	return results;

}


set<int> Sibling::getAllVarSiblingOfStmtLst(){
	set<int> results;
	for(int i=0; i<varStmtLst.size(); i++){
		results.insert(varStmtLst.at(i).first);
	}
	return results;
}

set<int> Sibling::getAllStmtLstSiblingOfVar(){
	set<int> results;
	for(int i=0; i<varStmtLst.size(); i++){
		results.insert(varStmtLst.at(i).second);
	}
	return results;
}

//boolean functions
bool Sibling::isSiblingProcProc(int proc1,int proc2){
	vector<pair<int,int>> procProc = getProcProcSibling();
	for(int i=0; i<procProc.size(); i++){
		if(procProc.at(i).first==proc1 && procProc.at(i).second==proc2 )
			return true;
		if(procProc.at(i).second==proc1 && procProc.at(i).first==proc2 )
			return true;
	}
	return false;
}

bool Sibling::isSiblingStmtLstStmtLst(int stmtLst1,int stmtLst2){
	vector<pair<int,int>> stmtLstStmtLst = getStmtLstStmtLstSibling() ;
	for(int i=0; i<stmtLstStmtLst.size(); i++){
		if(stmtLstStmtLst.at(i).first==stmtLst1 && stmtLstStmtLst.at(i).second==stmtLst2 )
			return true;
		if(stmtLstStmtLst.at(i).second==stmtLst1 && stmtLstStmtLst.at(i).first==stmtLst2 )
			return true;
	}
	return false;
}

bool Sibling::isSiblingStmtStmt(int stmt1,int stmt2){
	vector<pair<int,int>> stmtStmt = getStmtStmtSibling();
	for(int i=0; i<stmtStmt.size(); i++){
		if(stmtStmt.at(i).first==stmt1 && stmtStmt.at(i).second==stmt2 )
			return true;
		if(stmtStmt.at(i).second==stmt1 && stmtStmt.at(i).first==stmt2 )
			return true;
	}
	return false;
}

bool Sibling::isSiblingVarStmtLst(int var,int stmtLst){
	vector<pair<int,int>> varStmtLst = getVarStmtLstSibling();
	for(int i=0; i<varStmtLst.size(); i++){
		if(varStmtLst.at(i).first==var && varStmtLst.at(i).second==stmtLst )
			return true;
	}
	return false;
}
bool Sibling::isSiblingVarConst(int var,int constant){
	vector<pair<int,int>> varConst = getVarConstSibling();
	for(int i=0; i<varConst.size(); i++){
		if(varConst.at(i).first==var && varConst.at(i).second==constant )
			return true;
	}
	return false;
}
bool Sibling::isSiblingVarPlus(int var,int plus){
	vector<pair<int,int>> varPlus = getVarPlusSibling();
	for(int i=0; i<varPlus.size(); i++){
		if(varPlus.at(i).first==var && varPlus.at(i).second==plus )
			return true;
	}
	return false;
}
bool Sibling::isSiblingVarMinus(int var,int minus){
	vector<pair<int,int>> varMinus = getVarMinusSibling();
	for(int i=0; i<varMinus.size(); i++){
		if(procProc.at(i).first==var && procProc.at(i).second==minus )
			return true;
	}
	return false;
}
bool Sibling::isSiblingVarTimes(int var,int times){
	vector<pair<int,int>> varTimes = getVarTimesSibling();
	for(int i=0; i<varTimes.size(); i++){
		if(varTimes.at(i).first==var && varTimes.at(i).second==times )
			return true;
	}
	return false;
}
bool Sibling::isSiblingConstPlus(int constant,int plus){
	vector<pair<int,int>> constPlus = getConstPlusSibling();
	for(int i=0; i<constPlus.size(); i++){
		if(constPlus.at(i).first==constant && constPlus.at(i).second==plus )
			return true;
	}
	return false;
}
bool Sibling::isSiblingConstMinus(int constant, int minus){
	vector<pair<int,int>> constMinus = getConstMinusSibling();
	for(int i=0; i<constMinus.size(); i++){
		if(constMinus.at(i).first==constant && constMinus.at(i).second==minus )
			return true;
	}
	return false;
}
bool Sibling::isSiblingConstTimes(int constant,int times){
	vector<pair<int,int>> constTimes = getConstTimesSibling();
	for(int i=0; i<constTimes.size(); i++){
		if(constTimes.at(i).first==constant && constTimes.at(i).second==times )
			return true;
	}
	return false;
}
bool Sibling::isSiblingPlusPlus(int plus1 ,int plus2){
	vector<pair<int,int>> plusPlus = getPlusPlusSibling();
	for(int i=0; i<plusPlus.size(); i++){
		if(plusPlus.at(i).first==plus1 && plusPlus.at(i).second==plus2 )
			return true;
		if(plusPlus.at(i).second==plus1 && plusPlus.at(i).first==plus2 )
			return true;
	}
	return false;
}
bool Sibling::isSiblingPlusMinus(int plus,int minus){
	vector<pair<int,int>> plusMinus = getPlusMinusSibling();
	for(int i=0; i<plusMinus.size(); i++){
		if(plusMinus.at(i).first==plus && plusMinus.at(i).second==minus )
			return true;
	}
	return false;
}
bool Sibling::isSiblingPlusTimes(int plus,int times){
	vector<pair<int,int>> plusTimes = getPlusTimesSibling();
	for(int i=0; i<plusTimes.size(); i++){
		if(plusTimes.at(i).first==plus && plusTimes.at(i).second==times )
			return true;
	}
	return false;
}
bool Sibling::isSiblingMinusMinus(int minus1,int minus2){
	vector<pair<int,int>> minusMinus = getMinusMinusSibling();
	for(int i=0; i<minusMinus.size(); i++){
		if(minusMinus.at(i).first==minus1 && minusMinus.at(i).second==minus2 )
			return true;
		if(minusMinus.at(i).second==minus1 && minusMinus.at(i).first==minus2 )
			return true;
	}
	return false;
}
bool Sibling::isSiblingMinusTimes(int minus,int times){
	vector<pair<int,int>> minusTimes = getMinusTimesSibling();
	for(int i=0; i<minusTimes.size(); i++){
		if(minusTimes.at(i).first==minus && minusTimes.at(i).second==times )
			return true;
	}
	return false;
}
bool Sibling::isSiblingTimesTimes(int times1,int times2){
	vector<pair<int,int>> timesTimes = getTimesTimesSibling();
	for(int i=0; i<timesTimes.size(); i++){
		if(timesTimes.at(i).first==times1 && timesTimes.at(i).second==times2 )
			return true;
		if(timesTimes.at(i).second==times1 && timesTimes.at(i).first==times2 )
			return true;
	}
	return false;
}

bool Sibling::isSiblingVarVar(int var1, int var2){
	vector<pair<int,int>> varVar = getVarVarSibling();
	for(int i=0; i<varVar.size();  i++) {
		if(varVar.at(i).first==var1 && varVar.at(i).second==var2)
			return true;
		if(varVar.at(i).second==var1 && varVar.at(i).first==var2)
			return true;
	}
	return false;
}

bool Sibling::isSiblingConstConst(int const1, int const2){
	vector<pair<int,int>> constConst = getConstConstSibling();
	for(int i=0; i<constConst.size(); i++) {
		if(constConst.at(i).first==const1 && constConst.at(i).second==const2)
			return true;
		if(constConst.at(i).second==const1 && constConst.at(i).first==const2)
			return true;
	}
	return false;
}

bool Sibling::isSiblingConstStmtLst(int const1, int stmtLst) {
	vector<pair<int,int>> constStmtLst = getConstStmtLstSibling();
	for(int i=0; i<constStmtLst.size(); i++) {
		if(constStmtLst.at(i).first==const1 && constStmtLst.at(i).second==stmtLst)
			return true;
	}
	return false;
}

set<int> Sibling::getVarSiblingOfStmtLst(int stmtLst){
	set<int> results;
	for(int i=0; i<varStmtLst.size(); i++){
		if(varStmtLst.at(i).second==stmtLst)
			results.insert(varStmtLst.at(i).first);
	}
	return results;
}

set<int> Sibling::getStmtLstSiblingOfVar(int var){
	set<int> results;
	for(int i=0; i<varStmtLst.size(); i++){
		if(varStmtLst.at(i).first==var)
			results.insert(varStmtLst.at(i).second);
	}
	return results;
}

set<int> Sibling::getPlusSiblingOfVar(int var){
	set<int> results;
	for(int i=0; i<varPlus.size(); i++){
		if(varPlus.at(i).first==var)
			results.insert(varPlus.at(i).second);
	}
	return results;
}

set<int> Sibling::getMinusSiblingOfVar(int var){
	set<int> results;
	for(int i=0; i<varMinus.size(); i++){
		if(varMinus.at(i).first==var)
			results.insert(varMinus.at(i).second);
	}
	return results;
}

set<int> Sibling::getTimesSiblingOfVar(int var){
	set<int> results;
	for(int i=0; i<varTimes.size(); i++){
		if(varTimes.at(i).first==var)
			results.insert(varTimes.at(i).second);
	}
	return results;
}

set<int> Sibling::getPlusSiblingOfConst(int constant){
	set<int> results;
	for(int i=0; i<constPlus.size(); i++){
		if(constPlus.at(i).first==constant)
			results.insert(constPlus.at(i).second);
	}
	return results;
}

set<int> Sibling::getMinusSiblingOfConst(int constant){
	set<int> results;
	for(int i=0; i<constMinus.size(); i++){
		if(constMinus.at(i).first==constant)
			results.insert(constMinus.at(i).second);
	}
	return results;
}

set<int> Sibling::getTimesSiblingOfConst(int constant){
	set<int> results;
	for(int i=0; i<constTimes.size(); i++){
		if(constTimes.at(i).first==constant)
			results.insert(constTimes.at(i).second);
	}
	return results;
}

set<int> Sibling::getVarSiblingOfPlus(int plus){
	set<int> results;
	for(int i=0; i<varPlus.size(); i++){
		if(varPlus.at(i).second==plus)
			results.insert(varPlus.at(i).first);
	}
	return results;
}

set<int> Sibling::getConstSiblingOfPlus(int plus){
	set<int> results;
	for(int i=0; i<constPlus.size(); i++){
		if(constPlus.at(i).second==plus)
			results.insert(constPlus.at(i).first);
	}
	return results;
}

set<int> Sibling::getPlusSiblingOfPlus(int plus){
	set<int> results;
	for(int i=0; i<plusPlus.size(); i++){
		if(plusPlus.at(i).second==plus)
			results.insert(plusPlus.at(i).first);
		if(plusPlus.at(i).first==plus)
			results.insert(plusPlus.at(i).second);
	}
	return results;
}

set<int> Sibling::getMinusSiblingOfPlus(int plus){
	set<int> results;
	for(int i=0; i<plusMinus.size(); i++){
		if(plusMinus.at(i).first==plus)
			results.insert(plusMinus.at(i).second);
	}
	return results;
}
set<int> Sibling::getTimesSiblingOfPlus(int plus){
	set<int> results;
	for(int i=0; i<plusTimes.size(); i++){
		if(plusTimes.at(i).first==plus)
			results.insert(plusTimes.at(i).second);
	}
	return results;
}

set<int> Sibling::getVarSiblingOfMinus(int minus){
	set<int> results;
	for(int i=0; i<varMinus.size(); i++){
		if(varMinus.at(i).second==minus)
			results.insert(varMinus.at(i).first);
	}
	return results;
}

set<int> Sibling::getConstSiblingOfMinus(int minus){
	set<int> results;
	for(int i=0; i<constMinus.size(); i++){
		if(constMinus.at(i).second==minus)
			results.insert(constMinus.at(i).first);
	}
	return results;
}

set<int> Sibling::getPlusSiblingOfMinus(int minus){
	set<int> results;
	for(int i=0; i<plusMinus.size(); i++){
		if(plusMinus.at(i).second==minus)
			results.insert(plusMinus.at(i).first);
	}
	return results;
}

set<int> Sibling::getMinusSiblingOfMinus(int minus){
	set<int> results;
	for(int i=0; i<minusMinus.size(); i++){
		if(minusMinus.at(i).second==minus)
			results.insert(minusMinus.at(i).first);
		if(minusMinus.at(i).first==minus)
			results.insert(minusMinus.at(i).second);
	}
	return results;
}

set<int> Sibling::getTimesSiblingOfMinus(int minus){
	set<int> results;
	for(int i=0; i<minusTimes.size(); i++){
		if(minusTimes.at(i).first==minus)
			results.insert(minusTimes.at(i).second);
	}
	return results;	
}

set<int> Sibling::getVarSiblingOfTimes(int times){
	set<int> results;
	for(int i=0; i<varTimes.size(); i++){
		if(varTimes.at(i).second==times)
			results.insert(varTimes.at(i).first);
	}
	return results;	
}

set<int> Sibling::getConstSiblingOfTimes(int times){
	set<int> results;
	for(int i=0; i<constTimes.size(); i++){
		if(constTimes.at(i).second==times)
			results.insert(constTimes.at(i).first);
	}
	return results;	
}

set<int> Sibling::getPlusSiblingOfTimes(int times){
	set<int> results;
	for(int i=0; i<plusTimes.size(); i++){
		if(plusTimes.at(i).second==times)
			results.insert(plusTimes.at(i).first);
	}
	return results;	
}

set<int> Sibling::getMinusSiblingOfTimes(int times){
	set<int> results;
	for(int i=0; i<minusTimes.size(); i++){
		if(minusTimes.at(i).second==times)
			results.insert(minusTimes.at(i).first);
	}
	return results;	
}

set<int> Sibling::getTimesSiblingOfTimes(int times){
	set<int> results;
	for(int i=0; i<timesTimes.size(); i++){
		if(timesTimes.at(i).second==times)
			results.insert(timesTimes.at(i).first);
		if(timesTimes.at(i).first==times)
			results.insert(timesTimes.at(i).second);
	}
	return results;	
}
