#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "ProcTable.h"
using namespace std;

/************** Constructors **********************/

ProcTable::ProcTable(){

}

void ProcTable::insertProc(string p){
 if (std::find(pTable.begin(), pTable.end(), p) != pTable.end()){
}else{
	pTable.push_back(p);
 }
}

int ProcTable::getSize(){
return pTable.size();
} 

bool ProcTable::containsProc(string p){
	if (std::find(pTable.begin(), pTable.end(), p) != pTable.end()){
		return true;
	}
	return false;
}

// get procedure name using its index
string ProcTable::getProcName(int n){
	return pTable.at(n);
}

// get variable index using its string
int ProcTable::getProcIndex(string p){
	for(int i=0; i< pTable.size(); i++){
if(pTable.at(i) == p){
return i;
}
}
return -1;
}
