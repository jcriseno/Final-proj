//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include "Token.hpp"

Token::Token(): _stringS{""}, _name{""}, _eof{false}, _eol{false}, _symbol{'\0'}, _stringSymbol{""}, _isWholeNumber{false} {}

void Token::print() const {
    if( eol() ) std::cout << "EOL\n" ;
    else if( eof() )                    std::cout << "EOF" ;
    else if( isPoundSymbol() ) std::cout << "#";
    else if( isOpenParen() )  std::cout << "(" ;
    else if( isCloseParen() )  std::cout << ")" ;
    else if( isOpenBracket() ) std::cout << "{" ;
    else if( isClosedBracket() ) std::cout << "}" ;
    else if( isColon() ) std::cout << ":";
    else if( isNewLine() ) std::cout << '\n';
    else if( isEmptySpace() ) std::cout << ' ';
    else if( isDoubleQuotationMark() ) std::cout << '"';
    else if( isSingleQuotationMark() ) std::cout << '\'';
    else if( isComma() ) std::cout << ", ";
    else if( isAssignmentOperator() )  std::cout << " = " ;
    else if( isSemiColon() )  std::cout << ";" ;
    else if( isMultiplicationOperator() )  std::cout << " * " ;
    else if( isAdditionOperator() )  std::cout << " + " ;
    else if( isSubtractionOperator() )  std::cout << " - " ;
    else if( isModuloOperator() )  std::cout << " % " ;
    else if( isDivisionOperator() )  std::cout << " / " ;
    else if( isGreaterOperator() ) std::cout << " > ";
    else if( isLessOperator() ) std::cout << " < ";
    else if( isEqualToOperator() ) std::cout << " == ";
    else if( isGreatEqualOperator() ) std::cout << " >= ";
    else if( isLessEqualOperator() ) std::cout << " <= ";
    else if( isNotEqualOperator() ) std::cout << " != ";
    else if( isForLoop() ) std::cout << "for";
    else if( isPrintStmt() ) std::cout << "print";
    else if( isInStmt() ) std::cout << "in";
    else if( isRangeStmt() ) std::cout << "range";
    else if( isName() )  std::cout << getName();
    else if( isStringS() ) std::cout << getStringS();
    else if( isWholeNumber() ) std::cout << getWholeNumber();
    else std::cout << "Uninitialized token.\n";
}
