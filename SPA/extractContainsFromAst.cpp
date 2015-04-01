#pragma once
#include <iostream>
#include "extractContainsFromAst.h"
#include "Frontend\TNode.h"
#include "Contains.h"
#include "PKB\ProcTable.h"

using namespace std;

ExtractContainsFromAST::ExtractContainsFromAST() {

}

ExtractContainsFromAST::ExtractContainsFromAST(Contains* contains, VarTable* varTable, ConstantTable* constTable, ProcTable* procTable) {
	this->contains = contains ;
	this->varTable = varTable;
	this->constTable = constTable;
	this->procTable = procTable;
	plusCount = 0;
	minusCount = 0;
	timesCount = 0;
}

void ExtractContainsFromAST::extractContains(){
	if(procTable->getSize()==0)
		return;
	else {
		for(int i=0; i< procTable->getProcRootTable().size();i++){
			recursiveExtractContains(procTable->getProcRootTable()[i]);
		}
	}
	return;
}

void ExtractContainsFromAST::recursiveExtractContains(TNode* root){
	if(root==NULL || root->getNodeType().compare("VAR_NODE")==0 || root->getNodeType().compare("CONSTANT_NODE")==0 || (root->getNodeType().compare("CALL_NODE")==0) )
		return;
	else {

		string nodeType = root->getNodeType();
		if(nodeType.compare("PROC_NODE")==0) {
			int stmtLstNum = root->getChild(0)->getChild(0)->getStmtNum();
			int procNum = root->getProcIndex();
			contains->insertProcStmtLst(procNum,stmtLstNum);
			for(int i=0; i<root->getNumChildren(); i++) {
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}

		if(nodeType.compare("STMTLST_NODE")==0 || nodeType.compare("ELSE_NODE")==0 || nodeType.compare("THEN_NODE")==0){
			int stmtLstNum = root->getChild(0)->getStmtNum();
			for(int i=0; i<root->getNumChildren(); i++) {
				contains->insertStmtLstStmt(root->getChild(0)->getStmtNum(),root->getChild(i)->getStmtNum());
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}

		if((nodeType.compare("ASSIGN_NODE")==0) || (nodeType.compare("IF_NODE")==0) || (nodeType.compare("WHILE_NODE")==0)){
			int stmtNum = root->getStmtNum();
			for(int i=0; i<root->getNumChildren(); i++) {
				string nodeTypeC = root->getChild(i)->getNodeType();
				if(nodeTypeC.compare("STMTLST_NODE")==0)
					contains->insertStmtStmtLst(stmtNum,root->getChild(i)->getChild(0)->getStmtNum());
				if(nodeTypeC.compare("VAR_NODE")==0){
					int varIndex = varTable->getVarIndex(root->getChild(i)->getData());
					contains->insertStmtVar(stmtNum,varIndex);
				}
				if(nodeTypeC.compare("CONSTANT_NODE")==0){
					int constIndex = constTable->getConstIndex(atoi(root->getChild(i)->getData().c_str()));
					contains->insertStmtConst(stmtNum,constIndex);
				}
				if(root->getChild(i)->getData().compare("+")==0){
					plusCount ++;
					contains->insertStmtPlus(stmtNum,plusCount);
				}
				if(root->getChild(i)->getData().compare("-")==0){
					minusCount ++;
					contains->insertStmtMinus(stmtNum,minusCount);
				}
				if(root->getChild(i)->getData().compare("*")==0){
					timesCount ++;
					contains->insertStmtTimes(stmtNum,timesCount);
				}

				recursiveExtractContains(root->getChild(i));	
			}
			return;
		}
		if(root->getData().compare("+")==0) {
			for(int i=0; i<root->getNumChildren(); i++) {
				string nodeTypeC = root->getChild(i)->getNodeType();
				if(nodeTypeC.compare("VAR_NODE")==0){
					int varIndex = varTable->getVarIndex(root->getChild(i)->getData());
					contains->insertPlusVar(plusCount,varIndex);
				}
				if(nodeTypeC.compare("CONSTANT_NODE")==0){
					int constIndex = constTable->getConstIndex(atoi(root->getChild(i)->getData().c_str()));
					contains->insertPlusConst(plusCount,constIndex);
				}
				if(root->getChild(i)->getData().compare("+")==0){
					plusCount ++;
					contains->insertPlusPlus(plusCount-1,plusCount);
				}
				if(root->getChild(i)->getData().compare("-")==0){
					minusCount ++;
					contains->insertPlusMinus(plusCount,minusCount);
				}
				if(root->getChild(i)->getData().compare("*")==0){
					timesCount ++;
					contains->insertPlusTimes(plusCount,timesCount);
				}
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}
		if(root->getData().compare("-")==0) {
			for(int i=0; i<root->getNumChildren(); i++) {
				string nodeTypeC = root->getChild(i)->getNodeType();
				if(nodeTypeC.compare("VAR_NODE")==0){
					int varIndex = varTable->getVarIndex(root->getChild(i)->getData());
					contains->insertMinusVar(minusCount,varIndex);
				}
				if(nodeTypeC.compare("CONSTANT_NODE")==0){
					int constIndex = constTable->getConstIndex(atoi(root->getChild(i)->getData().c_str()));
					contains->insertMinusConst(minusCount,constIndex);
				}
				if(root->getChild(i)->getData().compare("+")==0){
					plusCount ++;
					contains->insertMinusPlus(minusCount,plusCount);
				}
				if(root->getChild(i)->getData().compare("-")==0){
					minusCount ++;
					contains->insertMinusMinus(minusCount-1,minusCount);
				}
				if(root->getChild(i)->getData().compare("*")==0){
					timesCount ++;
					contains->insertMinusTimes(minusCount,timesCount);
				}
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}

		if(root->getData().compare("-")==0) {
			for(int i=0; i<root->getNumChildren(); i++) {
				string nodeTypeC = root->getChild(i)->getNodeType();
				if(nodeTypeC.compare("VAR_NODE")==0){
					int varIndex = varTable->getVarIndex(root->getChild(i)->getData());
					contains->insertTimesVar(timesCount,varIndex);
				}
				if(nodeTypeC.compare("CONSTANT_NODE")==0){
					int constIndex = constTable->getConstIndex(atoi(root->getChild(i)->getData().c_str()));
					contains->insertTimesConst(timesCount,constIndex);
				}
				if(root->getChild(i)->getData().compare("+")==0){
					plusCount ++;
					contains->insertTimesPlus(timesCount,plusCount);
				}
				if(root->getChild(i)->getData().compare("-")==0){
					minusCount ++;
					contains->insertTimesMinus(timesCount,minusCount);
				}
				if(root->getChild(i)->getData().compare("*")==0){
					timesCount ++;
					contains->insertTimesTimes(timesCount-1,timesCount);
				}
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}

	}
	return;
}

