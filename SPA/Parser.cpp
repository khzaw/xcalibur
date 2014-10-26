#pragma once

#include <fstream>

#include "Parser.h"
#include "Token.h"


using namespace std;

Parser::Parser() {
	this->nextToken = Token ("");
	this->procedureName = "";

}

void Parser::parse(string filename) {
	if(!(Parser::checkFileExists)) {
		cout << filename << " does not exist!";
		return;
	}

	string currentLine, programString;
	ifstream inputFile;
	inputFile.open(filename);
	while(!inputFile.eof()) {
		getline(inputFile, currentLine);
		programString += " " + currentLine;
	}
	inputFile.close();
	this->lexer = Lexer(programString);
	// program();

	
}

void Parser::program() {
	nextToken = getToken();
	procedure();
}


Token Parser::getToken() {
	
}