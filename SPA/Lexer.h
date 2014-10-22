#include <iostream>
#include <string>

using namespace std;

enum {DIGIT, LETTER, ERROR, SPACE, EOL, PLUS, TIMES, IDENT, INT_LIT};

class Lexer {

public:
	char nextChar;
	int charClass;
	string lexeme;

private:
	string input;

public:
	int lex();
	void setNewInput(string in);
	Lexer(string in="");
	virtual ~Lexer();

private:
	void addChar();
	void getChar();
};