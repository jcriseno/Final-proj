//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include <iostream>
#include "SymTab.hpp"


TypeDescriptor::~TypeDescriptor(){}

/*
NumberTypeDescriptor::NumberTypeDescriptor(TypeDescriptor::types type): _type{type}

NumberTypeDescriptor::NumberTypeDescriptor() {}

NumberTypeDescriptor::NumberTypeDescriptor(std::string variableName, int value):
            _variableName{variableName}, _intValue {value} {}

NumberTypeDescriptor::NumberTypeDescriptor(std::string variableName): _variableName{variable}

std::string &NumberTypeDescriptor::name() { return variableName; }
*/

//SymTab for INTS
void SymTab::setValueFor(std::string vName, int value) {
    // Define a variable by setting its initial value.
    std::cout << vName << " <- " << value << std::endl;
    NumberTypeDescriptor *desc = new NumberTypeDescriptor(TypeDescriptor::INTEGER);
    desc->value.intValue =  value;
    symTab[vName] = desc;
}

void SymTab::setValueFor(std::string vName, std::string value) {
    // Define a variable by setting its initial value.
    std::cout << vName << " <- " << value << std::endl;
    StringTypeDescriptor *desc = new StringTypeDescriptor(TypeDescriptor::STRING);
    desc->stringValue = value;
    symTab[vName] = desc;
}

bool SymTab::isDefined(std::string vName) {
    return symTab.find(vName) != symTab.end();
}

TypeDescriptor* SymTab::getValueFor(std::string vName) {
    if( ! isDefined(vName)) {
        std::cout << "SymTab::getValueFor: " << vName << " has not been defined.\n";
        exit(1);
    }
    NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>(symTab.find(vName)->second);
    if(nDesc == nullptr){
        StringTypeDescriptor *nDesc = dynamic_cast<StringTypeDescriptor*>(symTab.find(vName)->second);
        std::cout << "SymTab::getValueFor: " << vName << " contains " << nDesc->stringValue << std::endl;
        return symTab.find(vName)->second;
    }
    if(nDesc->type() == TypeDescriptor::INTEGER) {
        std::cout << "SymTab::getValueFor: " << vName << " contains " << nDesc->value.intValue << std::endl;
    }
    else if(nDesc->type() == TypeDescriptor::BOOL){
        std::cout << "SymTab::getValueFor " << vName << " contains " << nDesc->value.boolValue << std::endl;
    }

    return symTab.find(vName)->second;
}

