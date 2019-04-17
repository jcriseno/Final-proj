//
// Created by Ali A. Kooshesh on 2/5/19.
//

#ifndef EXPRINTER_SYMTAB_HPP
#define EXPRINTER_SYMTAB_HPP

#include <string>
#include <map>
#include "Token.hpp"

// This is a flat and integer-based symbol table. It allows for variables to be
// initialized, determines if a give variable has been defined or not, and if
// a variable has been defined, it returns its value.

class TypeDescriptor{
public:
    enum types {INTEGER, STRING, BOOL};

    explicit TypeDescriptor(types type): _type{type} {}

    virtual ~TypeDescriptor();

    types &type() { return _type; }


private:
    types _type;
};

class NumberTypeDescriptor: public TypeDescriptor{
public:
    union {
        int intValue;
        short boolValue;
    } value;

    explicit NumberTypeDescriptor(types descType):  TypeDescriptor(descType) {}
    /*
    NumberTypeDescriptor();
    NumberTypeDescriptor(std::string variableName, int value);
    NumberTypeDescriptor(std::string variableName);
     */

private:
    std::string _variableName;
    int _intValue;
};

class StringTypeDescriptor: public TypeDescriptor{
public:
    std::string stringValue;

    explicit StringTypeDescriptor(types descType): TypeDescriptor(descType){}
    /*
    StringTypeDescriptor(std::string variableName, std::string stringValue);
    StringTypeDescriptor(std::string variableName);
    std::string name();
    std::string stringValue;
     */

private:
    std::string _variableName;
    std::string _stringValue;
};

class SymTab {
public:
    void setValueFor(std::string vName, int value);
    void setValueFor(std::string vName, std::string value);
    bool isDefined(std::string vName);
    TypeDescriptor* getValueFor(std::string vName);

private:
    std::map<std::string, TypeDescriptor*> symTab;
};





#endif //EXPRINTER_SYMTAB_HPP
