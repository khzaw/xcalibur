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
	OPERATOR_OPENPAREN,
	OPERATOR_CLOSEPAREN,
};

// NULL; 0
// ADDITION, SUB; 1
// MULTI, DIVI; 2
// OPEN, CLOSE: 3

static string OPERATORS_NODE_NAMES[] = {
	"NULL_NODE",
	"PLUS_NODE",
	"MINUS_NODE",
	"MULTIPLY_NODE",
	"DIVIDE_NODE"
};

class Operator {
public:
	int op;
	string value;			// we can get away with it because we won't be evaluating the expression
	Operator(int op, string value);
	~Operator();
	bool isNull();
};