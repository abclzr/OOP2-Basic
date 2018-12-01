/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "parser.h"
#include "../StanfordCPPLib/error.h"


using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
   /* Empty */
}

Statement::~Statement() {
   /* Empty */
}

string Statement::get_source_str() {
	return source_str;
}

IF_statement::IF_statement(int num, string str) {
	linenum = num;
	source_str = str;
	int p1 = str.find("IF");
	int p2 = str.find("THEN");
	string str_exp = str.substr(p1 + 3, p2 - 1 - p1 - 3);

	int p3 = str_exp.find("<"); op = 0;
	if (p3 == string::npos) {
		p3 = str_exp.find(">"); op = 1;
	}
	if (p3 == string::npos) {
		p3 = str_exp.find("="); op = 2;
	}

	string s1 = str_exp.substr(0, p3);
	string s2 = str_exp.substr(p3 + 1, str_exp.size() - p3 - 1);

	TokenScanner token1(s1);
	token1.ignoreComments();
	token1.scanNumbers();
	token1.ignoreWhitespace();
	rt1 = parseExp(token1);

	TokenScanner token2(s2);
	token2.ignoreComments();
	token2.scanNumbers();
	token2.ignoreWhitespace();
	rt2 = parseExp(token2);

	string s3 = str.substr(p2 + 5, str.size() - p2 - 5);
	to_linenum = stringToInteger(s3);
}

IF_statement::~IF_statement() {
	delete rt1;
	delete rt2;
}

int IF_statement::execute(EvalState & state) {
	int n1 = rt1->eval(state);
	int n2 = rt2->eval(state);
	if (op == 0) {
		if (n1 < n2) return to_linenum;
		else return - 1;
	}
	else if (op == 1) {
		if (n1 > n2) return to_linenum;
		else return -1;
	}
	else {
		if (n1 == n2) return to_linenum;
		else return -1;
	}
}


REM_statement::REM_statement(int num, string str) {
	linenum = num;
	source_str = str;
	return;
}

REM_statement::~REM_statement() {
	return;
}

int REM_statement::execute(EvalState & state) {
	return -1;
}


LET_statement::LET_statement(int num, string str) {
	linenum = num;
	source_str = str;
	int p = str.find("LET");
	string st = str.substr(p + 4, str.size() - p - 4);
	
	TokenScanner token(st);
	token.ignoreComments();
	token.scanNumbers();
	token.ignoreWhitespace();
	rt = parseExp(token);

	return;
}

LET_statement::~LET_statement() {
	delete rt;
}

int LET_statement::execute(EvalState & state) {
	int e = rt->eval(state);
	return -1;
}


PRINT_statement::PRINT_statement(int num, string str) {
	linenum = num;
	source_str = str;
	int p = str.find("PRINT");
	string st = str.substr(p + 6, str.size() - p - 6);

	TokenScanner token(st);
	token.ignoreComments();
	token.scanNumbers();
	token.ignoreWhitespace();
	rt = parseExp(token);
}

PRINT_statement::~PRINT_statement() {
	return;
}

int PRINT_statement::execute(EvalState & state) {
	int e = rt->eval(state);
	cout << e << endl;
	return -1;
}


INPUT_statement::INPUT_statement(int num, string str) {
	linenum = num;
	source_str = str;
	int p = str.find("INPUT");
	string st = str.substr(p + 6, str.size() - p - 6);
	var = st;
}

INPUT_statement::~INPUT_statement() {
	return;
}

int INPUT_statement::execute(EvalState & state) {
	try {
		cout << " ? ";
		string str;
		char ch = getchar();
		while (ch != '\n') {
			str += ch;
			ch = getchar();
		}
		int num = stringToInteger(str);
		state.setValue(var, num);
	}
	catch (ErrorException & ex) {
		cout << ex.getMessage() << endl;
		execute(state);
	}
	return -1;
}


END_statement::END_statement(int num, string str) {
	linenum = num;
	source_str = str;
	return;
}

END_statement::~END_statement() {
	return;
}

int END_statement::execute(EvalState & state) {
	return -2;
}


GOTO_statement::GOTO_statement(int num, string str) {
	linenum = num;
	source_str = str;
	int p = str.find("GOTO");
	string s = str.substr(p + 5, str.size() - p - 5);
	to_linenum = stringToInteger(s);
	return;
}

GOTO_statement::~GOTO_statement() {
	return;
}

int GOTO_statement::execute(EvalState & state) {
	return to_linenum;
}

