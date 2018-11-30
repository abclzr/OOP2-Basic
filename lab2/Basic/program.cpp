/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
	state = new EvalState();
}

Program::~Program() {
   // Replace this stub with your own code
	pg.clear();
	if (state != nullptr) delete state;
}

void Program::clear() {
   // Replace this stub with your own code
	pg.clear(); 
	if (state != nullptr) delete state;
	state = new EvalState();
}

void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
	string ope;
	if (lineNumber != 0) {
		int l1 = line.find(" ");
		int l2 = line.find(" ", l1 + 1);
		if (l2 == string::npos) l2 = line.size();
		ope = line.substr(l1 + 1, l2 - l1 - 1);
	}
	else {
		int l2 = line.find(" ");
		ope = line.substr(0, l2);
	}
	if (ope == "IF") {
		IF_statement *p = new IF_statement(lineNumber, line);
		pg.insert(pair<int, Statement*>(lineNumber, (Statement*) p));
	}
	else if (ope == "REM") {
		REM_statement *p = new REM_statement(lineNumber, line);
		pg.insert(pair<int, Statement*>(lineNumber, (Statement*)p));
	}
	else if (ope == "LET") {
		LET_statement *p = new LET_statement(lineNumber, line);
		pg.insert(pair<int, Statement*>(lineNumber, (Statement*)p));
	}
	else if (ope == "PRINT") {
		PRINT_statement *p = new PRINT_statement(lineNumber, line);
		pg.insert(pair<int, Statement*>(lineNumber, (Statement*)p));
	}
	else if (ope == "INPUT") {
		INPUT_statement *p = new INPUT_statement(lineNumber, line);
		pg.insert(pair<int, Statement*>(lineNumber, (Statement*)p));
	}
	else if (ope == "END") {
		END_statement *p = new END_statement(lineNumber, line);
		pg.insert(pair<int, Statement*>(lineNumber, (Statement*)p));
	}
	else if (ope == "GOTO") {
		GOTO_statement *p = new GOTO_statement(lineNumber, line);
		pg.insert(pair<int, Statement*>(lineNumber, (Statement*)p));
	}
}

void Program::removeSourceLine(int lineNumber) {
	map<int, Statement*>::iterator it = pg.find(lineNumber);
	if (it == pg.end()) error("SYNTAX ERROR");
	pg.erase(it);
   // Replace this stub with your own code
}

string Program::getSourceLine(int lineNumber) {
	map<int, Statement*>::iterator it = pg.find(lineNumber);
	if (it == pg.end()) error("SYNTAX ERROR");
	string str = it->second->get_source_str();
	return str;    // Replace this stub with your own code
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
   // Replace this stub with your own code
}

Statement *Program::getParsedStatement(int lineNumber) {
   return NULL;  // Replace this stub with your own code
}

int Program::getFirstLineNumber() {
	map<int, Statement*>::iterator it = pg.begin();
	if (it == pg.end()) error("SYNTAX ERROR");
   return it->first;     // Replace this stub with your own code
}

int Program::getNextLineNumber(int lineNumber) {
	map<int, Statement*>::iterator it = pg.find(lineNumber);
	if (it == pg.end()) error("SYNTAX ERROR");
	++it; if (it == pg.end()) return -1;
	return it->first;     // Replace this stub with your own code
}

void Program::execute_oneline(int lineNumber) {
	map<int, Statement*>::iterator it = pg.find(lineNumber);
	if (it == pg.end()) error("SYNTAX ERROR");
	it->second->execute(*state);
	return;
}

void Program::run_it() {
	map<int, Statement*>::iterator it = pg.begin();
	while (it != pg.end()) {
		int result = it->second->execute(*state);
		if (result == -1) ++it;
		else {
			it = pg.find(result);
			if (it == pg.end())
				error("LINE NUMBER ERROR");
		}
	}
	return;
}

void Program::list_it() {
	map<int, Statement*>::iterator it = pg.begin();
	for (; it != pg.end(); ++it)
		cout << it->second->get_source_str();
	return;
}