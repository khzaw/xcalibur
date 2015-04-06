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
			int plusCountOfRoot = plusCount;
			for(int i=0; i<root->getNumChildren(); i++) {
				string nodeTypeC = root->getChild(i)->getNodeType();
				if(nodeTypeC.compare("VAR_NODE")==0){
					int varIndex = varTable->getVarIndex(root->getChild(i)->getData());
					contains->insertPlusVar(plusCountOfRoot,varIndex);
				}
				if(nodeTypeC.compare("CONSTANT_NODE")==0){
					int constIndex = constTable->getConstIndex(atoi(root->getChild(i)->getData().c_str()));
					contains->insertPlusConst(plusCountOfRoot,constIndex);
				}
				if(root->getChild(i)->getData().compare("+")==0){
					plusCount ++;
					contains->insertPlusPlus(plusCountOfRoot,plusCount);
				}
				if(root->getChild(i)->getData().compare("-")==0){
					minusCount ++;
					contains->insertPlusMinus(plusCountOfRoot,minusCount);
				}
				if(root->getChild(i)->getData().compare("*")==0){
					timesCount ++;
					contains->insertPlusTimes(plusCountOfRoot,timesCount);
				}
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}
		if(root->getData().compare("-")==0) {
			int minusCountOfRoot;
			for(int i=0; i<root->getNumChildren(); i++) {
				string nodeTypeC = root->getChild(i)->getNodeType();
				if(nodeTypeC.compare("VAR_NODE")==0){
					int varIndex = varTable->getVarIndex(root->getChild(i)->getData());
					contains->insertMinusVar(minusCountOfRoot,varIndex);
				}
				if(nodeTypeC.compare("CONSTANT_NODE")==0){
					int constIndex = constTable->getConstIndex(atoi(root->getChild(i)->getData().c_str()));
					contains->insertMinusConst(minusCountOfRoot,constIndex);
				}
				if(root->getChild(i)->getData().compare("+")==0){
					plusCount ++;
					contains->insertMinusPlus(minusCountOfRoot,plusCount);
				}
				if(root->getChild(i)->getData().compare("-")==0){
					minusCount ++;
					contains->insertMinusMinus(minusCountOfRoot,minusCount);
				}
				if(root->getChild(i)->getData().compare("*")==0){
					timesCount ++;
					contains->insertMinusTimes(minusCountOfRoot,timesCount);
				}
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}

		if(root->getData().compare("*")==0) {
			int timesCountOfRoot = timesCount;
			for(int i=0; i<root->getNumChildren(); i++) {
				string nodeTypeC = root->getChild(i)->getNodeType();
				if(nodeTypeC.compare("VAR_NODE")==0){
					int varIndex = varTable->getVarIndex(root->getChild(i)->getData());
					contains->insertTimesVar(timesCountOfRoot,varIndex);
				}
				if(nodeTypeC.compare("CONSTANT_NODE")==0){
					int constIndex = constTable->getConstIndex(atoi(root->getChild(i)->getData().c_str()));
					contains->insertTimesConst(timesCountOfRoot,constIndex);
				}
				if(root->getChild(i)->getData().compare("+")==0){
					plusCount ++;
					contains->insertTimesPlus(timesCountOfRoot,plusCount);
				}
				if(root->getChild(i)->getData().compare("-")==0){
					minusCount ++;
					contains->insertTimesMinus(timesCountOfRoot,minusCount);
				}
				if(root->getChild(i)->getData().compare("*")==0){
					timesCount ++;
					contains->insertTimesTimes(timesCountOfRoot,timesCount);
				}
				recursiveExtractContains(root->getChild(i));
			}
			return;
		}

	}
	return;
}

