/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "parser.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:
	int linenum;
	string source_str;
/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual int execute(EvalState & state) = 0;

   string get_source_str();

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class IF_statement : Statement {
public:
	IF_statement(int, string);
	~IF_statement();
	int execute(EvalState &);
private:
	int to_linenum, op;
	Expression *rt1, *rt2;
};

class REM_statement : Statement {
public:
	REM_statement(int, string);
	~REM_statement();
	int execute(EvalState &);
};

class LET_statement : Statement {
public:
	LET_statement(int, string);
	~LET_statement();
	int execute(EvalState &);
private:
	Expression *rt;
};

class PRINT_statement : Statement {
public:
	PRINT_statement(int, string);
	~PRINT_statement();
	int execute(EvalState &);
private:
	Expression *rt;
};

class INPUT_statement : Statement {
public:
	INPUT_statement(int, string);
	~INPUT_statement();
	int execute(EvalState &);
private:
	string var;
};

class END_statement : Statement {
public:
	END_statement(int, string);
	~END_statement();
	int execute(EvalState &);
};

class GOTO_statement : Statement {
public:
	GOTO_statement(int, string);
	~GOTO_statement();
	int execute(EvalState &);
private:
	int to_linenum;
};

#endif
