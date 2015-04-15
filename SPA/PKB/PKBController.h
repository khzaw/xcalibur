#pragma once

#include <map>
#include <stack>
#include <iostream>

#include "..\PKB\AST.h"
#include "..\PKB\VarTable.h"
#include "..\PKB\ProcTable.h"
#include "..\PKB\ConstantTable.h"
#include "..\PKB\Parent.h"
#include "..\PKB\Follows.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Uses.h"
#include "..\PKB\StatementTable.h"
#include "..\PKB\Modifies.h"
#include "..\PKB\Contains.h"
#include "..\PKB\Siblings.h"

//Design Extractor
#include "..\PKB\CallsExtractor.h"
#include "..\PKB\ParentExtractor.h"
#include "..\PKB\FollowsExtractor.h"
#include "..\PKB\ModifiesExtractor.h"
#include "..\PKB\UsesExtractor.h"
#include "..\PKB\NextExtractor.h"
#include "..\PKB\AffectsExtractor.h"
#include "..\PKB\extractContainsFromAst.h"
#include "..\PKB\SiblingsExtractor.h"

#include "..\PKB\OptimizedCFG.h"

using namespace std;

class PKBController {
public:
	VarTable* varTable;
	ProcTable* procTable;
	AST* ast;
	ConstantTable* constantTable;
	Parent* parentTable;
	Follows* followsTable;
	Modifies* modifiesTable;
	Uses* usesTable;
	StatementTable* statementTable;
	Calls* callsTable;
	Contains* containsTable;
	Sibling* siblingTable;
  OptimizedCFG* optimizedCFG;

	//Design Extractor
	CallsExtractor* callsExtractor;
	FollowsExtractor* followsExtractor;
	ParentExtractor* parentExtractor;
	ModifiesExtractor* modifiesExtractor;
	UsesExtractor* usesExtractor;
	NextExtractor* nextExtractor;
	AffectsExtractor* affectsExtractor;
	ExtractContainsFromAST* containsExtractor;
	SiblingsExtractor* siblingsExtractor;

	map<int, stack<int>> procAndContainers;

	PKBController();
	~PKBController();

	//DE
	void constructParent();
	void constructFollows();
	void constructCalls();
	void constructModifies();
	void constructUses();
	void constructNext();
  void constructOptimizedCFG();
	void constructContains();
	void constructSiblings();
};