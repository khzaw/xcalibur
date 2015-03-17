#pragma once
#include <vector>
#include "Subquery.h"
#include "ResultTuple.h"

class OptimizedSubquerySolver{
public:
	OptimizedSubquerySolver();
	ResultTuple* solveSet(vector<Subquery*> subqueriesSet);
	vector<ResultTuple* > multithreadSolve(vector<vector<Subquery*> > disjointSubqueries);
};