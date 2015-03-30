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
	/*
	for(size_t i = 1; i < subqueriesSet.size(); i++) {
		if((ans->getSynonymIndex(subqueriesSet[i]->leftSynonym) != -1) || (ans->getSynonymIndex(subqueriesSet[i]->rightSynonym) != -1)) {
			ans = subqueriesSet[i]->solve(ans);
		} else {
			ResultTuple* interim = subqueriesSet[i]->solve();
			ans = ans->cross(interim);
		}
	}
	*/
	subqueriesSet.erase(subqueriesSet.begin());
	while (subqueriesSet.size() > 0) {
		if((ans->getSynonymIndex(subqueriesSet[0]->leftSynonym) != -1) || (ans->getSynonymIndex(subqueriesSet[0]->rightSynonym) != -1)) {
			ans = subqueriesSet[0]->solve(ans);
			subqueriesSet.erase(subqueriesSet.begin());
		} else {
			// expected size of ans + cost to do cartesian product
			int cost1 = subqueriesSet.front()->getPriority() + subqueriesSet.front()->getPriority() * ans->getAllResults().size();
			
			// find next query with related synonyms
			int index = -1;
			for (size_t i = 1; i < subqueriesSet.size(); i++) {
				if ((ans->getSynonymIndex(subqueriesSet[i]->leftSynonym) != -1) || (ans->getSynonymIndex(subqueriesSet[i]->rightSynonym) != -1)) {
					if (subqueriesSet[i]->getPriority() <= cost1) {
						index = i;
						break;
					}
				}
			}

			if (index != -1) {
				ans = subqueriesSet[index]->solve(ans);
				subqueriesSet.erase(subqueriesSet.begin() + index);
			} else {
				ResultTuple* interim = subqueriesSet[0]->solve();
				ans = ans->cross(interim);
				subqueriesSet.erase(subqueriesSet.begin());
			}
		}
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
