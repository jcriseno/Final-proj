//
// Created by Ali A. Kooshesh on 1/30/19.
//

#ifndef EXPRINTER_TOKEN_HPP
#define EXPRINTER_TOKEN_HPP
#include<string>


class Token {

public:
    Token();

    bool &eof()  { return _eof; }
    bool &eol()  { return _eol; }

    bool eof() const { return _eof; }
    bool eol() const  { return _eol; }

    bool isPoundSymbol() const { return _symbol == '#'; }

    bool isOpenParen() const  { return _symbol == '('; }
    bool isCloseParen() const { return _symbol == ')'; }

    bool isOpenBracket() const { return _symbol == '{'; }
    bool isClosedBracket() const { return _symbol == '}'; }
    bool isNewLine() const { return _symbol == '\n'; }
    bool isEmptySpace() const { return _symbol == ' '; }
    bool isDoubleQuotationMark() const { return _symbol == '"'; }
    bool isSingleQuotationMark() const { return _symbol == '\''; }
    bool isComma() const { return _symbol == ','; }

    void symbol(char c) { _symbol = c; }
    void stringSymbol(std::string s) { _stringSymbol = s; }
    char symbol() { return _symbol; }


    bool isSemiColon() const { return _symbol == ';'; }
    bool isAssignmentOperator() const              { return _symbol == '='; }
    bool isMultiplicationOperator() const { return _symbol == '*'; }
    bool isAdditionOperator() const       { return _symbol == '+'; }
    bool isSubtractionOperator() const    { return _symbol == '-'; }
    bool isModuloOperator() const         { return _symbol == '%'; }
    bool isDivisionOperator() const       { return _symbol == '/'; }
    bool isArithmeticOperator() const {
        return isMultiplicationOperator() ||
               isAdditionOperator() ||
               isSubtractionOperator() ||
               isModuloOperator() ||
               isDivisionOperator();
    }
    bool isGreaterOperator() const {return _symbol == '>'; }
    bool isLessOperator() const {return _symbol == '<'; }
    bool isEqualToOperator() const {return _stringSymbol == "=="; }
    bool isGreatEqualOperator() const { return _stringSymbol == ">="; }
    bool isLessEqualOperator() const { return  _stringSymbol == "<="; }
    bool isNotEqualOperator() const { return  _stringSymbol == "!="; }
    bool isRelationalOperator() const {
        return isGreaterOperator() ||
               isLessOperator() ||
               isEqualToOperator() ||
               isGreatEqualOperator() ||
               isLessEqualOperator() ||
               isNotEqualOperator();
    }
    bool isForLoop() const { return _name == "for"; }
    bool isPrintStmt() const { return _name == "print"; }
    bool isKeyword() const {
        return isForLoop() ||
                isPrintStmt();
    }
    bool isName() const                   { return _name.length() > 0; }
    std::string getName() const                  { return _name; }
    void setName(std::string n) { _name = n; }

    bool &isStringS() { return _isStringS; }
    bool isStringS() const { return _isStringS; }
    std::string getStringS() const { return _stringS; }
    void setStringS(std::string n) {
        _stringS = n;
        isStringS() = true;
    }

    bool &isWholeNumber() { return _isWholeNumber; }
    bool isWholeNumber() const { return _isWholeNumber; }
    int getWholeNumber() const { return _wholeNumber; }
    void setWholeNumber(int n) {
        _wholeNumber = n;
        isWholeNumber() = true;
    }

    void print() const;

private:
    std::string _stringS;
    std::string _name;
    bool _eof, _eol;
    bool _isStringS;
    bool _isWholeNumber;
    char _symbol;
    std::string _stringSymbol;
    int _wholeNumber;
};

#endif //EXPRINTER_TOKEN_HPP
