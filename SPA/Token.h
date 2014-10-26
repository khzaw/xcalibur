#pragma once

#include <string>

using namespace std;

class Token {
public:
	string text;
	Token();
	Token(string t);
	~Token();
};