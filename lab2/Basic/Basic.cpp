/*
 * File: Basic.cpp
 * ---------------
 * Name: [TODO:lizirui]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"

#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

enum ProcessType {RUN, LIST, CLEAR, QUIT, HELP, OTHER};

/* Function prototypes */

ProcessType processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   //cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
		  string line = getLine();
         ProcessType pt = processLine(line, program, state);
		 switch (pt) {
			case RUN:
				program.run_it();
			break;
			case LIST:
				program.list_it();
			break;
			case CLEAR:
				program.clear();
			break;
			case QUIT:
				return 0;
			break;
			case HELP:
				cout << "maozhuxishuoguo:zijidongshoufengyizushi" << endl;
			break;
			case OTHER:
			break;
		 }
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

ProcessType processLine(string line, Program & program, EvalState & state) {
	if (line == "RUN") return RUN;
	if (line == "LIST") return LIST;
	if (line == "CLEAR") return CLEAR;
	if (line == "QUIT") return QUIT;
	if (line == "HELP") return HELP;

	int pos = line.find(" ");
	if (line[0] >= '0' && line[0] <= '9') {
		int linenum = stringToInteger(line.substr(0, pos));
		if (pos == string::npos) program.removeSourceLine(linenum);
		else program.addSourceLine(linenum, line);
	}
	else {
		program.addSourceLine(0, line);
		program.execute_oneline(0);
		program.removeSourceLine(0);
	}
	/*
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line);
   Expression *exp = parseExp(scanner);
   int value = exp->eval(state);
   cout << value << endl;
   delete exp;
   */
   return OTHER;
}
