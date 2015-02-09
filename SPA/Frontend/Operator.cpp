#pragma once
#include <iostream>
#include "SPA/Frontend/Operator.h"

using namespace std;

Operator::Operator(int op, string value) {
	this->op = op;
	this->value = value;
}

Operator::~Operator() {
}

bool Operator::isNull() {
	return op == OPERATOR_NULL;
}