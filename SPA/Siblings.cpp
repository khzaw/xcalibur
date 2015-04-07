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



//functions to insert
void Sibling::insertProcProc(int proc, int proc1) {
	pair<int,int> pair1(proc,proc1);
	procProc.push_back(pair1);
}

void Sibling::insertStmtLstStmtLst(int stmtLst1, int stmtLst2){
	pair<int,int> pair1(stmtLst1,stmtLst2);
	stmtLstStmtLst.push_back(pair1);
}

void Sibling::insertStmtStmt(int stmt1, int stmt2){
	pair<int,int> pair1(stmt1,stmt2);
	stmtStmt.push_back(pair1);
}

void Sibling::inserVarStmtLst(int var, int stmtLst) {
	pair<int,int> pair1(var,stmtLst);
	varStmtLst.push_back(pair1);
}

void Sibling::insertVarConst(int var, int constant){
	pair<int,int> pair1(var,constant);
	varConst.push_back(pair1);
}

void Sibling::insertVarPlus(int var, int plus){
	pair<int,int> pair1(var,plus);
	varPlus.push_back(pair1);
}

void Sibling::insertVarMinus(int var,int minus){
	pair<int,int> pair1(var, minus);
	varMinus.push_back(pair1);
}

void Sibling::insertVarTimes(int var, int times){
	pair<int,int> pair1(var,times);
	varTimes.push_back(pair1);
}

void Sibling::insertConstStmtLst(int constant, int stmtLst){
	pair<int,int> pair1(constant, stmtLst);
	constStmtLst.push_back(pair1);
}

void Sibling::insertConstConst(int const1, int const2){
	pair<int,int> pair1(const1, const2);
	constConst.push_back(pair1);
}

void Sibling::insertConstPlus(int constant, int plus){
	pair<int,int> pair1(constant,plus);
	constPlus.push_back(pair1);
}

void Sibling::insertConstMinus(int constant, int minus){
	pair<int,int> pair1(constant, minus);
	constMinus.push_back(pair1);
}

void Sibling::insertConstTimes(int constant, int times){
	pair<int,int> pair1(constant, times);
	constTimes.push_back(pair1);
}

void Sibling::insertPlusPlus(int plus1, int plus2){
	pair<int,int> pair1(plus1,plus2);
	plusPlus.push_back(pair1);
}
void Sibling::insertPlusMinus(int plus, int minus){
	pair<int,int> pair1(plus, minus);
	plusMinus.push_back(pair1);
}

void Sibling::insertPlusTimes(int plus1, int times){
	pair<int,int> pair1(plus1,times);
	plusTimes.push_back(pair1);
}

void Sibling::insertMinusMinus(int minus1, int minus2){
	pair<int,int> pair1(minus1, minus2);
	minusMinus.push_back(pair1);
}

void Sibling::insertMinusTimes(int minus, int times){
	pair<int,int> pair1(minus,times);
	minusTimes.push_back(pair1);
}

void Sibling::insertTimesTimes(int times1, int times2){
	pair<int,int> pair1(times1,times2);
	timesTimes.push_back(pair1);
}

void Sibling::insertVarVar(int var1, int var2){
	pair<int,int> pair1(var1,var2);
	varVar.push_back(pair1);
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
