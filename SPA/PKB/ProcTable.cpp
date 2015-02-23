#include <string>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include "ProcTable.h"
#include <stdexcpt.h>
using namespace std;

/************** Constructors **********************/

ProcTable::ProcTable(){

}

int ProcTable::insertProc(string p){
 if (ProcTable::containsProc(p)){
		return getProcIndex(p);
	}else{
		int size = pMap.size();
		pMap.insert(std::pair<string,int>(p,size));
	    pTable.push_back(p);
		return size;
	}
}

int ProcTable::getSize(){
return pMap.size();
} 

bool ProcTable::containsProc(string p){
	int n = ProcTable::getProcIndex(p);
	if(n == -1){
		return false;
	}else{
		return true;
	}
}

// get procedure name using its index
string ProcTable::getProcName(int n){
	return pTable[n];
}

// get variable index using its string
int ProcTable::getProcIndex(string p){
	std::map<string, int>::iterator it = pMap.find(p);
	if(it == pMap.end()) {	// var not found, return -1
		return -1;
	} else {	// var found, return its index
		return it->second;
	}
}
