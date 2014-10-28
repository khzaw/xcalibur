#pragma once
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "VarTable.h"

using namespace std;

/************** Constructors **********************/
// constructor 
VarTable::VarTable(){
}

// insert variable into VarTable
void VarTable::insertVar(string s){
 if (std::find(varVec.begin(), varVec.end(), s) != varVec.end()){
}else{
	varVec.push_back(s);
 }
}

// get variable name using its index
string VarTable::getVarName(int n){
return varVec.at(n);
}


// get variable index using its string
int VarTable::getVarIndex(string s){
for(int i=0; i< varVec.size(); i++){
if(varVec.at(i) == s){
return i;
}
}
return -1;
}


void VarTable::printTable(){
	for (vector<string>::iterator i = varVec.begin(); i != varVec.end(); i++) {
		cout<< "here"<<endl;
   cout << *i << endl;
}
}
int VarTable::getSize(){
return varVec.size();
} 


bool VarTable::containsVar(string s){
	if (std::find(varVec.begin(), varVec.end(), s) != varVec.end()){
		return true;
	}
	return false;
}