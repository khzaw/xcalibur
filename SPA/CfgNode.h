#pragma once
#include <iostream>

using namespace std;

class CfgNode {

private:
	int prog_line_num;
	pair<CfgNode*,CfgNode*> fwdPtrs;
	pair<CfgNode*, CfgNode*> bkwdPtrs;

public:
	CfgNode();
	CfgNode(int);
	int getData();
	pair<CfgNode*,CfgNode*> getFwdPtrs();
	pair<CfgNode*, CfgNode*> getBkwdPtrs();
	void setFwdPtrs(CfgNode*, CfgNode*);
	void setBkwdPtrs(CfgNode*, CfgNode*);
	void setData(int);
}