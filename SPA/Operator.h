#pragma once
#include <iostream>
using namespace std;

// so far every operator that we might encounter is left associative
enum OPERATORS {
	OPERATOR_NULL,			// the sentinel value
	OPERATOR_ADDITION,
	OPERATOR_SUBTRACTION,
	OPERATOR_MULTIPLICATION,
	OPERATOR_DIVISON,
};

class Operator {
public:
	int op;
	string value;			// we can get away with it because we won't be evaluating the expression
	Operator(int op, string value);
	~Operator();
	bool isNull();
};