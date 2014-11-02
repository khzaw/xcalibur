#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "ConstantTable.h"

using namespace std;

/************** Constructors **********************/
// constructor 
ConstantTable::ConstantTable(){
}

// insert variable into VarTable
void ConstantTable::insertConst(int n){
	if (std::find(constVec.begin(), constVec.end(), n) != constVec.end()){
	}else{
		constVec.push_back(n);
	}
}

// get constant using its index
int ConstantTable::getConstant(int n){
	return constVec[n];
}


// get constant index using its value
int ConstantTable::getConstIndex(int n){
	for(int i=0; i< constVec.size(); i++){
		if(constVec[i] == n){

			return i;
		}else{
		}
	}
	return -1;
}

vector<int> ConstantTable::getAllConstant(){
	vector<int> constants;
	for(int i =0; i <constVec.size();i ++){
		constants.push_back(constVec[i]);
	}
	return constants;
}

int ConstantTable::getSize(){
	return constVec.size();
} 


bool ConstantTable::containsConst(int n){
	if (std::find(constVec.begin(), constVec.end(), n) != constVec.end()){
		return true;
	}
	return false;
}