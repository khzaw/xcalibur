#pragma once
#include <iostream>
#include "..\Frontend\TNode.h"
#include "Siblings.h"
#include "VarTable.h"
#include "ConstantTable.h"
#include "ProcTable.h"
#include "SiblingsExtractor.h"
#include <set>

using namespace std;

SiblingsExtractor::SiblingsExtractor() {

}

SiblingsExtractor::SiblingsExtractor(Sibling* sibling, VarTable* varTable, ConstantTable* constTable, ProcTable* procTable){
	this->sibling = sibling;
	this->varTable = varTable;
	this->constTable = constTable;
	this->procTable = procTable;
	plusCount=0;
	minusCount=0;
	timesCount=0;
}

void SiblingsExtractor::extractSibling(){
	vector<int> procsVec;
	vector<TNode*> rootTable = procTable->getProcRootTable();
	for(int i=0; i<rootTable.size();i++){
		procsVec.push_back(procTable->getProcIndex(rootTable.at(i)->getData()));
	}
	for(int i=0; i<procsVec.size(); i++){
		for(int j=i+1; j<procsVec.size(); j++){
			sibling->insertProcProc(procsVec.at(i), procsVec.at(j));
		}
	}
	for(int i=0; i<procTable->getProcRootTable().size(); i++){
		recursiveExtractSibling(procTable->getProcRootTable()[i]);
	}
	return;	
}

void SiblingsExtractor::recursiveExtractSibling(TNode* root){
	if(root==NULL || root->getNodeType().compare("VAR_NODE")==0 || root->getNodeType().compare("CONSTANT_NODE")==0 || (root->getNodeType().compare("CALL_NODE")==0) )
		return;
	else {
		string nodeType = root->getNodeType();
		
		if(nodeType.compare("PROC_NODE")==0){
			recursiveExtractSibling(root->getChild(0));
		}

		if(nodeType.compare("STMTLST_NODE")==0 || nodeType.compare("ELSE_NODE")==0 || nodeType.compare("THEN_NODE")==0){
			int stmtLstNum;
			if(nodeType.compare("STMTLST_NODE")==0){
				stmtLstNum = root->getChild(0)->getStmtNum();
			}
			else{
				stmtLstNum = root->getChild(0)->getChild(0)->getStmtNum();
				root = root->getChild(0);
			}
			vector<TNode*> children = root->getChildren(); 
			for(int i=0; i<root->getNumChildren(); i++) {
				for(int j=i+1; j<root->getNumChildren(); j++){
					sibling->insertStmtStmt(children.at(i)->getStmtNum(), children.at(j)->getStmtNum());
				}
			}
			for(int i=0; i<root->getNumChildren(); i++)
				recursiveExtractSibling(root->getChild(i));
			return;
		}

		if(nodeType.compare("ASSIGN_NODE")==0){
			int var = varTable->getVarIndex(root->getChild(0)->getData());
			string cNodeType = root->getChild(1)->getNodeType();
			if(cNodeType.compare("VAR_NODE")==0){
				int var1 = varTable->getVarIndex(root->getChild(1)->getData());
				sibling->insertVarVar(var,var1);
			}
			if(cNodeType.compare("CONSTANT_NODE")==0){
				int constant = constTable->getConstIndex(atoi(root->getChild(1)->getData().c_str()));
				sibling->insertVarConst(var,constant);
			}
			if(root->getChild(1)->getNodeType().compare("+")==0){
				plusCount ++;
				sibling->insertVarPlus(var,plusCount);
			}
			if(root->getChild(1)->getNodeType().compare("MINUS_NODE")==0){
				minusCount ++;
				sibling->insertVarMinus(var,minusCount);
			}
			if(root->getChild(1)->getNodeType().compare("TIMES_NODE")==0){
				timesCount ++;
				sibling->insertVarTimes(var,timesCount);
			}
			recursiveExtractSibling(root->getChild(1));
			return;
		}

		if(nodeType.compare("IF_NODE")==0) {
			int var = varTable->getVarIndex(root->getData());
			string c1NodeType = root->getChild(0)->getNodeType();
			string c2NodeType = root->getChild(1)->getNodeType();
			int thenStmtNum = root->getChild(0)->getChild(0)->getChild(0)->getStmtNum();
			int elseStmtNum = root->getChild(1)->getChild(0)->getChild(0)->getStmtNum();
			sibling->inserVarStmtLst(var,thenStmtNum);
			sibling->inserVarStmtLst(var,elseStmtNum);
			sibling->insertStmtLstStmtLst(thenStmtNum,elseStmtNum);
			recursiveExtractSibling(root->getChild(0));
			recursiveExtractSibling(root->getChild(1));
			return;
		}

		if(nodeType.compare("WHILE_NODE")==0){
			int var = varTable->getVarIndex(root->getData());
			string c1NodeType = root->getChild(0)->getNodeType();
			int stmtLstNum = root->getChild(0)->getChild(0)->getStmtNum();
			sibling->inserVarStmtLst(var,stmtLstNum);
			recursiveExtractSibling(root->getChild(0));
			return;
		}

		if(root->getNodeType().compare("PLUS_NODE")==0 || root->getNodeType().compare("MINUS_NODE")==0 || root->getNodeType().compare("TIMES_NODE")==0){
			TNode* child0 = root->getChild(0);
			TNode* child1 = root->getChild(1);

			if(child0->getNodeType().compare("VAR_NODE")==0){
				if(child1->getNodeType().compare("VAR_NODE")==0)
					sibling->insertVarVar(varTable->getVarIndex(child0->getData()), varTable->getVarIndex(child1->getData()));
				if(child1->getNodeType().compare("CONSTANT_NODE")==0)
					sibling->insertVarConst(varTable->getVarIndex(child0->getData()), constTable->getConstIndex(atoi(child1->getData().c_str())));
				
				if(child1->getNodeType().compare("PLUS_NODE")==0){
					plusCount++;
					sibling->insertVarPlus(varTable->getVarIndex(child0->getData()),plusCount);
				}
				if(child1->getNodeType().compare("MINUS_NODE")==0){
					minusCount++;
					sibling->insertVarMinus(varTable->getVarIndex(child0->getData()),minusCount);
				}
				if(child1->getNodeType().compare("TIMES_NODE")==0){
					timesCount++;
					sibling->insertVarTimes(varTable->getVarIndex(child0->getData()),timesCount);
				}
				recursiveExtractSibling(child0);
				recursiveExtractSibling(child1);
			}

			if(child0->getNodeType().compare("CONSTANT_NODE")==0){
				if(child1->getNodeType().compare("VAR_NODE")==0)
					sibling->insertVarConst(varTable->getVarIndex(child1->getData()), constTable->getConstIndex(atoi(child0->getData().c_str())));
				if(child1->getNodeType().compare("CONSTANT_NODE")==0)
					sibling->insertConstConst(constTable->getConstIndex(atoi(child0->getData().c_str())), constTable->getConstIndex(atoi(child1->getData().c_str())));
				
				if(child1->getNodeType().compare("PLUS_NODE")==0){
					plusCount++;
					sibling->insertConstPlus(constTable->getConstIndex(atoi(child0->getData().c_str())),plusCount);
				}
				if(child1->getNodeType().compare("MINUS_NODE")==0){
					minusCount++;
					sibling->insertConstMinus(constTable->getConstIndex(atoi(child0->getData().c_str())),minusCount);
				}
				if(child1->getNodeType().compare("TIMES_NODE")==0){
					timesCount++;
					sibling->insertConstTimes(constTable->getConstIndex(atoi(child0->getData().c_str())),timesCount);
				}
				recursiveExtractSibling(child0);
				recursiveExtractSibling(child1);
			}

			if(child0->getNodeType().compare("PLUS_NODE")==0){
				plusCount++;
				int rootCount = plusCount;
				if(child1->getNodeType().compare("VAR_NODE")==0){
					sibling->insertVarPlus(varTable->getVarIndex(child1->getData()),rootCount);
					recursiveExtractSibling(child0);
				}
				if(child1->getNodeType().compare("CONSTANT_NODE")==0){
					sibling->insertConstPlus(constTable->getConstIndex(atoi(child1->getData().c_str())), rootCount);
					recursiveExtractSibling(child0);
				}
				
				if(child1->getNodeType().compare("PLUS_NODE")==0){
					recursiveExtractSibling(child0);
					plusCount++;
					sibling->insertPlusPlus(rootCount,plusCount);
					recursiveExtractSibling(child1);
				}
				if(child1->getNodeType().compare("MINUS_NODE")==0){
					recursiveExtractSibling(child0);
					minusCount++;
					sibling->insertPlusMinus(rootCount,minusCount);
					recursiveExtractSibling(child1);
				}
				if(child1->getNodeType().compare("TIMES_NODE")==0){
					recursiveExtractSibling(child0);
					timesCount++;
					sibling->insertPlusTimes(rootCount,timesCount);
					recursiveExtractSibling(child1);
				}
			}

			if(child0->getNodeType().compare("MINUS_NODE")==0){
				minusCount++;
				int rootCount = minusCount;
				if(child1->getNodeType().compare("VAR_NODE")==0){
					sibling->insertVarMinus(varTable->getVarIndex(child1->getData()),rootCount);
					recursiveExtractSibling(child0);
				}

				if(child1->getNodeType().compare("CONSTANT_NODE")==0){
					sibling->insertConstMinus(constTable->getConstIndex(atoi(child1->getData().c_str())), rootCount);
					recursiveExtractSibling(child1);
				}
				if(child1->getNodeType().compare("PLUS_NODE")==0){
					recursiveExtractSibling(child0);
					plusCount++;
					sibling->insertPlusMinus(plusCount,rootCount);
					recursiveExtractSibling(child1);
				}
				if(child1->getNodeType().compare("MINUS_NODE")==0){
					recursiveExtractSibling(child0);
					minusCount++;
					sibling->insertMinusMinus(rootCount,minusCount);
					recursiveExtractSibling(child1);
				}
				if(child1->getNodeType().compare("TIMES_NODE")==0){
					recursiveExtractSibling(child0);
					timesCount++;
					sibling->insertMinusTimes(rootCount,timesCount);
					recursiveExtractSibling(child1);
				}
			}
			if(child0->getNodeType().compare("TIMES_NODE")==0){
				timesCount++;
				int rootCount = timesCount;
				if(child1->getNodeType().compare("VAR_NODE")==0){
					sibling->insertVarTimes(varTable->getVarIndex(child1->getData()),rootCount);
					recursiveExtractSibling(child0);
				}
				if(child1->getNodeType().compare("CONSTANT_NODE")==0){
					sibling->insertConstTimes(constTable->getConstIndex(atoi(child1->getData().c_str())), rootCount);
					recursiveExtractSibling(child0);
				}
				
				if(child1->getNodeType().compare("PLUS_NODE")==0){
					recursiveExtractSibling(child0);
					plusCount++;
					sibling->insertPlusTimes(plusCount,rootCount);
					recursiveExtractSibling(child1);
				}
				if(child1->getNodeType().compare("MINUS_NODE")==0){
					recursiveExtractSibling(child0);
					minusCount++;
					sibling->insertMinusTimes(minusCount, rootCount);
					recursiveExtractSibling(child1);
				}
				if(child1->getNodeType().compare("TIMES_NODE")==0){
					recursiveExtractSibling(child0);
					timesCount++;
					sibling->insertTimesTimes(rootCount,timesCount);
					recursiveExtractSibling(child1);
				}
			}
			return;
		}
	}
		
}

