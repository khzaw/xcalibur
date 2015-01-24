#pragma once
#include <string>
#include <vector>
#include <map>
#include "Subquery.h"
#include "Subquery.cpp"

using namespace std;

class ParentSubquery : public Subquery{
public:
	map<string, vector<int> >* solve(){
		// not implemented
		map<string, vector<int> > temp;
		return &temp;
	}

	map<string, vector<int> >* solve(map<string, vector<int> >*){
		// not implemented
		map<string, vector<int> > temp;
		return &temp;
	}
}