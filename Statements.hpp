//
// Created by Ali A. Kooshesh on 2/5/19.
//

#ifndef EXPRINTER_STATEMENTS_HPP
#define EXPRINTER_STATEMENTS_HPP

#include <iostream>
#include <vector>

#include "ArithExpr.hpp"
#include "SymTab.hpp"

// The Statement (abstract) class serves as a super class for all statements that
// are defined in the language. Ultimately, statements have to be evaluated.
// Therefore, this class defines evaluate, a pure-virtual function to make
// sure that all subclasses of Statement provide an implementation for this
// function.

class Statement {
public:
    Statement();

    virtual void print() = 0;
    virtual void evaluate(SymTab &symTab) = 0;

};


// PrintStatement class
class PrintStatement : public Statement {
public:
    PrintStatement();
    PrintStatement(std::string rhsVar);
    PrintStatement(ExprNode* rightHandSideExpr);
    PrintStatement(std::vector<ExprNode*> rhsVect);

    std::string &rhsVariable();
    ExprNode *rightHandSideExpr() const;
    const std::vector<ExprNode *> &rhsVect() const;

    virtual void print();
    virtual void evaluate(SymTab &symTab);



private:
    std::vector<ExprNode*> _rhsVect;
    std::string _rhsVariable;
    ExprNode *_rightHandSideExpr;


};


// Statements is a collection of Statement. For example, all statements in a function
// can be represented by an instance of Statements.

class Statements {
public:
    Statements();

    void addStatement(Statement *statement);
    void evaluate(SymTab &symTab);

    void print();

private:
    std::vector<Statement *> _statements;
};

// AssignmentStatement represents the notion of an lValue having been assigned an rValue.
// The rValue is an expression.

class AssignmentStatement : public Statement {
public:
    AssignmentStatement();
    AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr);

    std::string &lhsVariable();
    ExprNode *&rhsExpression();

    virtual void evaluate(SymTab &symTab);
    virtual void print();

private:
    std::string _lhsVariable;
    ExprNode *_rhsExpression;
    std::string _rhsStr;
};

// For statement class
class ForStatement : public Statement {
public:
    ForStatement();
    ForStatement(AssignmentStatement *expr1, ExprNode *relexpr, AssignmentStatement *expr3, Statements *innerStatements);


    AssignmentStatement *&getExpr1();
    AssignmentStatement *&getExpr3();
    ExprNode *&getRelexpr();
    Statements *&getInnerStatements();


    virtual void print();
    virtual void evaluate(SymTab &symTab);

private:
    AssignmentStatement *_Expression1;
    AssignmentStatement *_Expression3;
    ExprNode *_Rel_expr;
    Statements *_innerStatements;
};

#endif //EXPRINTER_STATEMENTS_HPP
