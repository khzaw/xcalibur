#pragma once
#include <Windows.h>
#include <process.h>
#include <ppl.h>
#include <concurrent_vector.h>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Subquery.h"
#include "ResultTuple.h"
#include "OptimizedSubquerySolver.h"

OptimizedSubquerySolver::OptimizedSubquerySolver(){
}

ResultTuple* OptimizedSubquerySolver::solveSet(vector<Subquery*> subqueriesSet){
	ResultTuple* ans = subqueriesSet.at(0)->solve();
	for (size_t i = 1; i < subqueriesSet.size(); i++){
		ans = subqueriesSet.at(i)->solve(ans);
	}
	return ans;
}
	
vector<ResultTuple* > OptimizedSubquerySolver::multithreadSolve(vector<vector<Subquery*> > disjointSubqueries){
	Concurrency::concurrent_vector<ResultTuple* > concAns;
	Concurrency::concurrent_vector<vector<Subquery* > > concDisjointSubqueries;
	for (size_t i = 0; i < disjointSubqueries.size(); i++){
		concDisjointSubqueries.push_back(disjointSubqueries[i]);
	}
	vector<ResultTuple* > ans;
	Concurrency::parallel_for_each (begin(concDisjointSubqueries), end(concDisjointSubqueries), [&](vector<Subquery* > n) {
		concAns.push_back(solveSet(n));
	});
	for(size_t i = 0; i < concAns.size(); i++){
		ans.push_back(concAns[i]);
	}
	return ans;
}
