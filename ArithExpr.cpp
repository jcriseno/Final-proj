//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include<iostream>
#include "ArithExpr.hpp"
#include "SymTab.hpp"

// ExprNode
ExprNode::ExprNode(Token token): _token{token} {}

Token ExprNode::token() { return _token; }

// InfixExprNode functions
InfixExprNode::InfixExprNode(Token tk) : ExprNode{tk}, _left(nullptr), _right(nullptr) {}

ExprNode *&InfixExprNode::left() { return _left; }

ExprNode *&InfixExprNode::right() { return _right; }


int InfixExprNode::evaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    int lValue = left()->evaluate(symTab);
    int rValue = right()->evaluate(symTab);
    std::cout << "InfixExprNode::evaluate: " << lValue << " " << token().symbol() << " " << rValue << std::endl;
    if( token().isAdditionOperator() )
        return lValue + rValue;
    else if(token().isSubtractionOperator())
        return lValue - rValue;
    else if(token().isMultiplicationOperator())
        return lValue * rValue;
    else if(token().isDivisionOperator())
        return lValue / rValue; // division by zero?
    else if( token().isModuloOperator() )
        return lValue % rValue;
    else if( token().isEqualToOperator())
        return lValue == rValue;
    else if( token().isNotEqualOperator())
        return lValue != rValue;
    else if( token().isGreaterOperator() )
        return lValue > rValue;
    else if( token().isLessOperator() )
        return lValue < rValue;
    else if( token().isGreatEqualOperator() )
        return lValue >= rValue;
    else if( token().isLessEqualOperator() )
        return lValue <= rValue;
    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
}


std::string InfixExprNode::stringEvaluate(SymTab &symTab) {
    // Evaluates an infix expression using a post-order traversal of the expression tree.
    std::string lValue = left()->stringEvaluate(symTab);
    std::string rValue = right()->stringEvaluate(symTab);
    std::cout << "InfixExprNode::stringEvaluate: " << lValue << " " << token().symbol() << " " << rValue << std::endl;
    if( token().isAdditionOperator() )
        return lValue + rValue;
    else {
        std::cout << "InfixExprNode::evaluate: don't know how to evaluate this operator\n";
        token().print();
        std::cout << std::endl;
        exit(2);
    }
}

void InfixExprNode::print() {
    _left->print();
    token().print();
    _right->print();
}

// WHoleNumber
WholeNumber::WholeNumber(Token token): ExprNode{token} {}

void WholeNumber::print() {
    token().print();
}


int WholeNumber::evaluate(SymTab &symTab) {
    std::cout << "WholeNumber::evaluate: returning " << token().getWholeNumber() << std::endl;
    return token().getWholeNumber();
}

std::string WholeNumber::stringEvaluate(SymTab &symTab) {
    std::cout << "WholeNumber::stringEvaluate was called!" << std::endl;
    exit(1);
}



//String
String::String(Token token) : ExprNode{token} {}

void String::print() {
    token().print();
}

int String::evaluate(SymTab &symTab){
    std::cout << "String::evaluate FOR INT called! " << std::endl;
    exit(2);
}

std::string String::stringEvaluate(SymTab &symTab) {
    std::cout << "String::evaluate: returning " << token().getStringS() << std::endl;
    return token().getStringS();
}


// Variable
Variable::Variable(Token token): ExprNode{token} {}

void Variable::print() {
    token().print();
}


int Variable::evaluate(SymTab &symTab) {
    if( ! symTab.isDefined(token().getName())) {
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    TypeDescriptor *desc = symTab.getValueFor(token().getName());
    NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor *>(desc);
    if ( nDesc == nullptr ) {
        std::cout << "Variable::evaluate, nDesc is NULL\n";
        exit(1);
    }
    std::cout << "Variable::evaluate: returning " << symTab.getValueFor(token().getName()) << std::endl;
    return nDesc->value.intValue;
}


std::string Variable::stringEvaluate(SymTab &symTab) {
    if( !symTab.isDefined(token().getName())){
        std::cout << "Use of undefined variable, " << token().getName() << std::endl;
        exit(1);
    }
    TypeDescriptor *desc = symTab.getValueFor(token().getName());
    StringTypeDescriptor *nDesc = dynamic_cast<StringTypeDescriptor *>(desc);
    if( nDesc == nullptr ){
        std::cout << "Variable::stringEvaluate, nDesc is NULL\n";
        exit(1);
    }
    std::cout << "Variable::evaluate: returning " << symTab.getValueFor(token().getName()) << std::endl;
    return nDesc->stringValue;
}


