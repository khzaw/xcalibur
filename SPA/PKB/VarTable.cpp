#pragma once
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "VarTable.h"


using namespace std;

/************** Constructors **********************/
// constructor 
VarTable::VarTable(){
}

// insert variable into VarTable
int VarTable::insertVar(string s){
	if (VarTable::containsVar(s)){
		return getVarIndex(s);
	}else{
		int size = varMap.size();
		varMap.insert(std::pair<string,int>(s,size));
		varVec.push_back(s);
		return size;
	}
}

// get variable name using its index
string VarTable::getVarName(int n){
	return varVec[n];
}

vector<string> VarTable::getAllVar(){
	vector<string> var;
	for(size_t i =0; i <varVec.size();i ++){
		var.push_back(varVec[i]);
	}
	return var;
}

// get variable index using its string
int VarTable::getVarIndex(string s){
	std::map<string, int>::iterator it = varMap.find(s);
	if(it == varMap.end()) {	// var not found, return -1
		return -1;
	} else {	// var found, return its index
		return it->second;
	}
}


int VarTable::getSize(){
return varMap.size();
}

/*
void VarTable::printTable(){
	for (vector<string>::iterator i = varVec.begin(); i != varVec.end(); i++) {
		cout<< "here"<<endl;
   cout << *i << endl;
}
}
 
 */

// return a vector of all statement numbers
vector<int> VarTable::getAllVarNum() {
	vector<int> vars(getSize());
	iota(vars.begin(), vars.end(), 0);
	return vars;
}




bool VarTable::containsVar(string s){
	int n = VarTable::getVarIndex(s);
	if(n == -1){
		return false;
	}else{
		return true;
	}
}

