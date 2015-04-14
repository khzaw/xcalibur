#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"
#include "CacheTable.h"

using namespace std;
// TODO: 77, 119, 236?
class AffectsSubquery : public Subquery {
public:
	bool isConcurrent;
	AffectsSubquery(map<string, string>* m, PKBController* p) : Subquery(m, p){
	
	}

	ResultTuple* solve(){
		ResultTuple* ans;
		switch (isSyn) {
			case 1: case 4:
				ans = solveRightSyn();
				break;
			case 2: case 5:
				ans = solveLeftSyn();
				break;
			case 3:
				ans = solveBothSyn();
				break;
			default:
				ans = solveOther();
		}
		return ans;
	}
	
	bool validate() {
		//right synonym
		if(isSyn == 1 || isSyn == 4 || isSyn == 3) {
			string s = synonymTable->at(rightSynonym);
			if (!(s == "assign" || s == "stmt" || s == "prog_line")) {
				return false;
			}
		}
		//left synonym
		if (isSyn == 2 || isSyn == 5 || isSyn == 3) {
			string s = synonymTable->at(leftSynonym);
			if (!(s == "assign" || s == "stmt" || s == "prog_line")) {
				return false;
			}
		}
		type = 2;
		return true;
	}

	void setPriority() {
		int magnitude = 20;	//calculated during profiling
		bool isLeftSynStmtOrProgLine = true;
		bool isRightSynStmtOrProgLine = true;
		switch (isSyn) {
			case 1: // (int, syn)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 2: // (syn, int)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 3: // (syn, syn)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size() * (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 4: // (_, syn)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			case 5:	// (syn, _)
				priority = (pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE")).size();
				break;
			default: 
				priority = 0;
				break;
		}

		priority *= magnitude;
	}

	ResultTuple* solve(ResultTuple* tuple) {
		ResultTuple* ans;
		switch (isSyn) {
			case 1: case 4:
				ans = solveRightSyn(tuple);
				break;
			case 2: case 5:
				ans = solveLeftSyn(tuple);
				break;
			case 3:
				ans = solveBothSyn(tuple);
				break;
			default: break;
		}
		return ans;
	}

	ResultTuple* solveLeftSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		vector<int> previous = vector<int>();
		vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");

		set<int> tempAffected = set<int>();
		vector<int> Affected;

		if (isSyn == 2) {	// Affects(syn, stmt)
			if (isConcurrent) {
				try {
					Affected = CacheTable::instance()->affectedCache.at(rightIndex);
				} catch (exception& e) {
					for (size_t i = 0; i < assStmt.size(); i++) {
						if (pkb->affectsExtractor->isAffects(assStmt[i], rightIndex)) {
							tempAffected.insert(assStmt[i]);
						} 
					}
					Affected.assign(tempAffected.begin(), tempAffected.end());
				}
			} else {
				for (size_t i = 0; i < assStmt.size(); i++) {
					if (pkb->affectsExtractor->isAffects(assStmt[i], rightIndex)) {
						tempAffected.insert(assStmt[i]);
					} 
				}
				Affected.assign(tempAffected.begin(), tempAffected.end());
			}
		} else {	// Affects(syn, _): Get all Affected stmt
			if (isConcurrent) {
				for (size_t i = 0; i < assStmt.size(); i++) {
					for (size_t j = 0; j < assStmt.size(); j++) {
						try {
							if (CacheTable::instance()->isAffectsCache.at(make_pair(assStmt[i], assStmt[j]))) {
								tempAffected.insert(assStmt[i]);
								break;
							}
						} catch (exception& e) {
							if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
								tempAffected.insert(assStmt[i]);
								break;
							}
						}
					}
				}
			} else {
				for (size_t i = 0; i < assStmt.size(); i++) {
					for (size_t j = 0; j < assStmt.size(); j++) {
						if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
							tempAffected.insert(assStmt[i]);
							break;
						}
					}
				}
			}
			Affected.assign(tempAffected.begin(), tempAffected.end());
		}

		pair<int, int> p = pair<int, int>();
		p.second = rightIndex;
		for(size_t i = 0; i < Affected.size(); i++) {
			if (isConcurrent && isSyn == 1) {
				p.second = Affected[i];
				CacheTable::instance()->isAffectsCache[p] = true;
			}

			vector<int> temp = vector<int>();	
			temp.push_back(Affected.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	ResultTuple* solveLeftSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());
		pair<int, int> p = pair<int, int>();
		p.second = rightIndex;

		int index = tuple->getSynonymIndex(leftSynonym);
		for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
			vector<int> temp = tuple->getAllResults().at(i);
			if (isSyn == 2) {	// Affects(syn, stmt)
				p.first = temp.at(index);

				if (isConcurrent) {
					try {
						if (CacheTable::instance()->isAffectsCache.at(p)) {
							result->addResultRow(temp);
						}
					} catch (exception& e) {
						if (pkb->affectsExtractor->isAffects(temp.at(index), rightIndex)) {
							result->addResultRow(temp);
							CacheTable::instance()->isAffectsCache[p] = true;
						} else {
							CacheTable::instance()->isAffectsCache[p] = false;	
						}
					}
				} else {
					if (pkb->affectsExtractor->isAffects(temp.at(index), rightIndex)) {
						result->addResultRow(temp);
					}
				}
			} else {	// Affects(syn, _)
				if (!pkb->affectsExtractor->getAffects(temp.at(index)).empty()) {
					result->addResultRow(temp);
				}
			}
		}
		return result;
	}

	ResultTuple* solveRightSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(rightSynonym);
		tuple->addSynonymToMap(rightSynonym, index);
		set<int> tempAffects;
		vector<int> Affects;

		if (isSyn == 1) {	// Affects(stmt, syn): Get Affects of stmt
			if (isConcurrent) {
				try {
					Affects = CacheTable::instance()->affectsCache.at(rightIndex);
				} catch (exception& e) {
					tempAffects = pkb->affectsExtractor->getAffects(leftIndex);
					Affects.assign(tempAffects.begin(), tempAffects.end());
					CacheTable::instance()->affectsStarCache.insert(make_pair(rightIndex, Affects));
				}
			} else {
				tempAffects = pkb->affectsExtractor->getAffects(leftIndex);
				Affects.assign(tempAffects.begin(), tempAffects.end());
				CacheTable::instance()->affectsStarCache.insert(make_pair(rightIndex, Affects));
			}
		} else {	// Affects(_, syn): Get all Affected stmt
			vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			if (isConcurrent) {
				for (size_t i = 0; i < assStmt.size(); i++) {
					for (size_t j = 0; j < assStmt.size(); j++) {
						try {
							if (CacheTable::instance()->isAffectsCache.at(make_pair(assStmt[j], assStmt[i]))) {
								tempAffects.insert(assStmt[i]);
								break;
							}
						} catch (exception& e) {
							if (pkb->affectsExtractor->isAffects(assStmt[j], assStmt[i])) {
								tempAffects.insert(assStmt[i]);
								break;
							}
						}
					}
				}
			} else {
				for (size_t i = 0; i < assStmt.size(); i++) {
					for (size_t j = 0; j < assStmt.size(); j++) {
						if (pkb->affectsExtractor->isAffects(assStmt[j], assStmt[i])) {
							tempAffects.insert(assStmt[i]);
							break;
						}
					}
				}
			}
			Affects.assign(tempAffects.begin(), tempAffects.end());
		}

		pair<int, int> p = pair<int, int>();
		p.first = leftIndex;
		for(size_t i = 0; i < Affects.size(); i++) {
			if (isConcurrent && isSyn == 1) {
				p.second = Affects[i];
				CacheTable::instance()->isAffectsCache[p] = true;
			}
			
			vector<int> temp = vector<int>();
			temp.push_back(Affects.at(i));
			tuple->addResultRow(temp);
		}
		return tuple;
	}

	ResultTuple* solveRightSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());
		int size = tuple->getAllResults().size();
		vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
		int index = tuple->getSynonymIndex(rightSynonym);
		pair<int, int> p = pair<int, int>();

		if (isSyn == 1) {	// Affects(stmt, syn)
			p.first = leftIndex;
			for (size_t i = 0; i < size; i++) {
				vector<int> temp = tuple->getAllResults().at(i);
				p.second = temp.at(index);
				if (isConcurrent) {
					try {
						if (CacheTable::instance()->isAffectsCache.at(make_pair(leftIndex, temp[index]))) {
							result->addResultRow(temp);
						}
					} catch (exception& e) {
						if (pkb->affectsExtractor->isAffects(leftIndex, temp[index])) {
							result->addResultRow(temp);
							CacheTable::instance()->isAffectsCache[p] = true;
						} else {
							CacheTable::instance()->isAffectsCache[p] = false;
						}
					}
				} else {
					if (pkb->affectsExtractor->isAffects(leftIndex, temp[index])) {
						result->addResultRow(temp);
					}
				}
			}
		} else {	// Affects(_, syn)
			for (size_t i = 0; i < size; i++) {
				vector<int> temp = tuple->getAllResults().at(i);
				p.second = temp[index];
				for (size_t j = 0; j < assStmt.size(); j++) {
					p.first = assStmt[j];
					if (isConcurrent) {
						try {
							if (CacheTable::instance()->isAffectsCache.at(make_pair(assStmt[j], temp[index]))) {
								result->addResultRow(temp);
								break;
							}
						} catch (exception& e) {
							if (pkb->affectsExtractor->isAffects(assStmt[j], temp[index])) {
								result->addResultRow(temp);
								CacheTable::instance()->isAffectsCache[p] = true;
								break;
							} else {
								CacheTable::instance()->isAffectsCache[p] = false;
							}
						}
					} else {
						if (pkb->affectsExtractor->isAffects(assStmt[j], temp[index])) {
							result->addResultRow(temp);
							break;
						}
					}
				}
			}
		}
		return result;
	}

	ResultTuple* solveBothSyn() {
		ResultTuple* tuple = new ResultTuple();
		int index = tuple->addSynonym(leftSynonym);
		tuple->addSynonymToMap(leftSynonym, index);
		index = tuple->addSynonym(rightSynonym);
		tuple->addSynonymToMap(rightSynonym, index);
		pair<int, int> p = pair<int, int>();

		vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
		for (size_t i = 0; i < assStmt.size(); i++) {
			p.first = assStmt[i];
			for (size_t j = 0; j < assStmt.size(); j++) {
				p.second = assStmt[j];
				if (isConcurrent) {
					try {
						if (CacheTable::instance()->isAffectsCache.at(p)) {
							vector<int> row = vector<int>();
							row.push_back(assStmt.at(i));
							row.push_back(assStmt.at(j));
							tuple->addResultRow(row);
						}
					} catch (exception& e) {
						if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
							vector<int> row = vector<int>();
							row.push_back(assStmt.at(i));
							row.push_back(assStmt.at(j));
							tuple->addResultRow(row);
							CacheTable::instance()->isAffectsCache[p] = true;
						} else {
							CacheTable::instance()->isAffectsCache[p] = false;
						}
					}
				} else {				
					if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
						vector<int> row = vector<int>();
						row.push_back(assStmt.at(i));
						row.push_back(assStmt.at(j));
						tuple->addResultRow(row);
					}
				}
			}
		}
		return tuple;
	}

	ResultTuple* solveBothSyn(ResultTuple* tuple) {
		ResultTuple* result = new ResultTuple();
		result->setSynonym(tuple->getSynonyms());
		result->setSynonymMap(tuple->getSynonymMap());
		pair<int, int> p = pair<int, int>();
		int lIndex = tuple->getSynonymIndex(leftSynonym);
		int rIndex = tuple->getSynonymIndex(rightSynonym);
		if (lIndex != -1 && rIndex != -1){ //case 1: both are inside
			for (size_t i = 0; i < tuple->getAllResults().size(); i++){
				if (isConcurrent) {
					p.first = tuple->getResultAt(i, lIndex);
					p.second = tuple->getResultAt(i, rIndex);
					try {
						if (CacheTable::instance()->isAffectsCache.at(p)) {
							result->addResultRow(tuple->getResultRow(i));
						}
					} catch (exception& e) {
						if (pkb->affectsExtractor->isAffects(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
							result->addResultRow(tuple->getResultRow(i));
							CacheTable::instance()->isAffectsCache[p] = true;
						} else {
							CacheTable::instance()->isAffectsCache[p] = false;
						}
					}
				} else {
					if (pkb->affectsExtractor->isAffects(tuple->getResultAt(i, lIndex), tuple->getResultAt(i, rIndex))){
						result->addResultRow(tuple->getResultRow(i));
					}
				}
			}
		} else if (rIndex == -1) { //case 2: only left is inside
			int index = result->addSynonym(rightSynonym);
			result->addSynonymToMap(rightSynonym, index);
			map<int, vector<int>> prevSolution = map<int, vector<int>>();
			
			for (size_t i = 0; i < tuple->getAllResults().size(); i++) {
				vector<int> Affects;
				set<int> tempAffects;
				int leftValue = tuple->getResultAt(i, lIndex);

				if (isConcurrent) {
					try {
						Affects = CacheTable::instance()->affectsCache.at(leftValue);
					} catch (exception& e) {
						tempAffects = pkb->affectsExtractor->getAffects(leftValue);
						Affects.assign(tempAffects.begin(), tempAffects.end());
						CacheTable::instance()->affectsCache.insert(make_pair(leftValue, Affects));
					}
				} else {
					try {
						Affects = prevSolution.at(leftValue);
					} catch (exception& e) {
						tempAffects = pkb->affectsExtractor->getAffects(leftValue);
						Affects.assign(tempAffects.begin(), tempAffects.end());
						prevSolution.insert(make_pair(leftValue, Affects));
					}
				}
				
				p.first = leftValue;
				for (size_t j = 0; j < Affects.size(); j++){
					if (isConcurrent) {
						p.second = Affects[j];
						CacheTable::instance()->isAffectsCache[p] = true;
					}
					
					vector<int> newRow(tuple->getResultRow(i));
					newRow.push_back(Affects[j]);
					result->addResultRow(newRow);
				}
			}
		} else if (lIndex == -1) { //case 3: only right is inside
			int index = result->addSynonym(leftSynonym);
			int size = tuple->getAllResults().size();
			result->addSynonymToMap(leftSynonym, index);
			map<int, vector<int>> prevSolution = map<int, vector<int>>();
			vector<int> pre = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
						
			for (size_t i = 0; i < size; i++) {
				int rightValue = tuple->getResultAt(i, rIndex);
				set<int> tempAffected;
				vector<int> Affected;

				if (isConcurrent) {
					try {
						Affected = CacheTable::instance()->affectedCache.at(rightValue);
					} catch (exception& e) {
						for (size_t x = 0; x < pre.size(); x++) {
							if (pkb->affectsExtractor->isAffects(pre[x], rightValue)) {
								Affected.push_back(pre[x]);
							}
						}
						CacheTable::instance()->affectedCache.insert(make_pair(rightValue, Affected));
					}
				} else {
					try {
						Affected = prevSolution.at(rightValue);
					} catch (exception& e) {
						for (size_t x = 0; x < pre.size(); x++) {
							if (pkb->affectsExtractor->isAffects(pre[x], rightValue)) {
								Affected.push_back(pre[x]);
							}
						}
						prevSolution.insert(make_pair(rightValue, Affected));
					}
				}

				p.second = rightValue;
				for (size_t j = 0; j < Affected.size(); j++){
					if (isConcurrent) {
						p.first = Affected[j];
						CacheTable::instance()->isAffectsCache[p] = true;
					}

					vector<int> newRow(tuple->getResultRow(i));
					newRow.push_back(Affected[j]);
					result->addResultRow(newRow);
				}
			}
		}
		return result;
	}

	// BOOLEAN Result
	ResultTuple* solveOther() {
		ResultTuple* tuple = new ResultTuple();
		tuple->setBool(true);
		if(isSyn == 0) {	//(digit, digit)
			tuple->setEmpty(!pkb->affectsExtractor->isAffects(leftIndex, rightIndex));
		} else if (isSyn == 7) {	//(_, digit)
			tuple->setEmpty(pkb->affectsExtractor->getAffectsBy(rightIndex).empty());
		} else if (isSyn == 8) {	//(digit, _)
			tuple->setEmpty(pkb->affectsExtractor->getAffects(leftIndex).empty());
		} else {	//(_, _)
			vector<int> assStmt = pkb->statementTable->getStmtNumUsingNodeType("ASSIGN_NODE");
			for (size_t i = 0; i < assStmt.size(); i++) {
				for (size_t j = 0; j < assStmt.size(); j++) {
					if (pkb->affectsExtractor->isAffects(assStmt[i], assStmt[j])) {
						tuple->setEmpty(false);
						return tuple;
					}
				}
			}
			tuple->setEmpty(true);
		}
		return tuple;
	}
};