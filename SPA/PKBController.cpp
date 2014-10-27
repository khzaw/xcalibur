#pragma once
#include "PKBController.h"

using namespace std;

PKBController::PKBController() {
	this->ast = AST();
	this->procTable = ProcTable();
	this->varTable = VarTable();
}

PKBController::~PKBController() {
}