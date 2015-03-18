#pragma once
#include <Windows.h>
#include <process.h>
#include <ppl.h>
#include <concurrent_vector.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ctime>

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
	Concurrency::parallel_for_each (begin(disjointSubqueries), end(disjointSubqueries), [&](vector<Subquery* > n) {
		concAns.push_back(solveSet(n));
	});
	vector<ResultTuple* > ans(concAns.begin(), concAns.end());
	return ans;
}

vector<ResultTuple* > OptimizedSubquerySolver::singlethreadSolve(vector<vector<Subquery*> > disjointSubqueries){
	vector<ResultTuple* > ans;
	for_each(begin(disjointSubqueries), end(disjointSubqueries), [&](vector<Subquery* > n) {
		ans.push_back(solveSet(n));
	});
	return ans;
}
