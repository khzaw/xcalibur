#include "ParentRecord.h" 

using namespace std;

ParentRecord::ParentRecord(int stmt1, int stmt2){
	this->stmt1 = stmt1;
	this->stmt2 = stmt2;
}

int ParentRecord::getChild(){
	return stmt2;
}
	
int ParentRecord::getParent(){
	return stmt1;
}