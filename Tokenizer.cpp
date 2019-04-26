//
// Created by Ali A. Kooshesh on 1/30/19.
//

#include <iostream>
#include <string>
#include <stack>
#include "Tokenizer.hpp"

std::stack<int> indents;

std::string Tokenizer::readName() {
    // This function is called when it is known that
    // the first character in input is an alphabetic character.
    // The function reads and returns all characters of the name.

    std::string name;
    char c;
    while( inStream.get(c) && isalnum(c) ) {
        name += c;
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return name;
}

std::string Tokenizer::readString() {
    std::string str;
    char c;
    while( inStream.get(c) && c != '"'){
        str += c;
    }

    if(c != '"'){
        std::cout << "Tokenizer::readString() Expected a double quote instead got " << c << std::endl;
    }

    return str;
}

char Tokenizer::readChar() {
    char c;
    inStream.get(c);
    if (inStream.good())
        inStream.putback(c);
    return c;
}

int Tokenizer::readInteger() {
    // This function is called when it is known that
    // the first character in input is a digit.
    // The function reads and returns all remaining digits.

    int intValue = 0;
    char c;
    while( inStream.get(c) && isdigit(c) ) {
        intValue = intValue * 10 + c - '0';
    }
    if(inStream.good())  // In the loop, we have read one char too many.
        inStream.putback(c);
    return intValue;
}

Tokenizer::Tokenizer(std::ifstream &stream): ungottenToken{false}, inStream{stream}, lastToken{} {}

Token Tokenizer::getToken() {

    if (ungottenToken) {
        ungottenToken = false;
        return lastToken;
    }

    char c;
    char a;
    std::string s;
    Token token;
    bool parsingNewLine = true;
    int indentCounter = 0;

/*

    while (inStream.get(c)) {
        inStream.putback(c);

        while (inStream.get(c) && isspace(c) && c != '\n')  // Skip spaces but not new-line chars.
        {
            // if we know we are parsing a new line
            if(parsingNewLine == true){
                indentCounter++;
            }
        }
        // If our indent stack is empty
        if(indents.empty()){
            indents.push(indentCounter);
        }
        // We found a bigger number of indents
        else if(indentCounter > indents.top()){
            indents.push(indentCounter);
        }
        // We found a smaller number of indents
        else if(indentCounter < indents.top()){
            indents.pop();
            while(indentCounter < indents.top()){
                indents.pop();
            }
        }
        // We did not find a matching level of scope
        if (indentCounter != indents.top() && !indents.empty()){
            std::cout << "Tokenizer::getToken() Indentation error" << std::endl;
            exit(1);
        }

        // if the 'c' you just got is a comment sign
        if (c == '#') {
            std::cout << "we found a comment\n";
            while (inStream.get(c) && c != '\n')
                ;
            //inStream.get(c);
        }
        else {
            break;
        }
    }
    */

    /*
    while( inStream.get(c) && isspace(c) )  // Skip spaces including the new-line chars.
        ;

    */
    /*
    while (inStream.get(c) && isspace(c) && c != '\n')  // Skip spaces but not new-line chars.
        ;

     */
    if(inStream.bad()) {
        std::cout << "Error while reading the input stream in Tokenizer.\n";
        exit(1);
    }

    //while( inStream.get(a) )  // Skip spaces including the new-line chars.
    //    ;




    if( inStream.eof()) {
        token.eof() = true;
    }
    else if( isdigit(c) ) { // a integer?
        // put the digit back into the input stream so
        // we read the entire number in a function
        inStream.putback(c);
       // inStream.putback(a);
        token.setWholeNumber( readInteger() );

    }
    // This will take care of Rel Ops and the single '='
    else if( c == '=' ) {
        inStream.get(a);
        //a = inStream.peek();
        if(a == '='){
            s = "==";
            token.stringSymbol(s);
        } else{
            inStream.putback(a);
            token.symbol(c);
        }
    }
    else if( c == '!'){
        inStream.get(a);
        //a = inStream.peek();
        if(a == '='){
            s = "!=";
            token.stringSymbol(s);
        } else
        inStream.putback(a);
    }
    else if( c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
        //inStream.putback(a);
        token.symbol(c);
    }
    else if(c == '>') {
        inStream.get(a);
        //a = inStream.peek();
        if (a == '='){
            s = ">=";
            token.stringSymbol(s);
        } else {
            inStream.putback(a);
            token.symbol(c);
        }
    }
    else if( c == '<'){
        inStream.get(a);
        if (a == '='){
            s = "<=";
            token.stringSymbol(s);
        } else {
            inStream.putback(a);
            token.symbol(c);
        }
    }

    else if( c == ';' ) {
        //inStream.putback(a);
        token.symbol(c);
    }
    else if( c == '(' || c == ')') {
        //inStream.putback(a);
        token.symbol(c);
    }
    else if( c == '{' || c == '}'){
        token.symbol(c);
    }
    else if(c == '"'){
        //token.symbol(c);
        //inStream.putback(c);
        //token.setStringS( readString() );
        token.setStringS(readString());
    }
    else if(c == ','){
        token.symbol(c);
    }
    /*
    else if(c == '#'){
        while (inStream.get(c)){
            if (c == '\n'){
                inStream.putback(c);
                break;
            }
        }
    }
     */
    else if(c == '\n'){
        //token.symbol(c);
        token.eol() = true;
        parsingNewLine = true;

        while(inStream.get(c)){
            if (c != '\n'){
                inStream.putback(c);
                break;
            }

        }
    }
    else if( c == ' '){
        if (parsingNewLine){
            indentCounter++;
            inStream.get(c);
            while(isspace(c)){
                indentCounter++;
                inStream.get(c);
            }
            inStream.putback(c);

            // If our indent stack is empty
            if(indents.empty()){
                indents.push(indentCounter);
            }
                // We found a bigger number of indents
            else if(indentCounter > indents.top()){
                indents.push(indentCounter);
            }
                // We found a smaller number of indents
            else if(indentCounter < indents.top()){
                indents.pop();
                while(indentCounter < indents.top()){
                    indents.pop();
                }
            }
        }
    }
    else if(isalpha(c)) {  // an identifier?
        // put c back into the stream so we can read the entire name in a function.
        inStream.putback(c);
        //inStream.putback(a);
        token.setName( readName() );
    } else {
        std::cout << "Unknown character in input. ->" << c << "<-" << std::endl;
        exit(1);
    }
    _tokens.push_back(token);
    return lastToken = token;
}

void Tokenizer::ungetToken() {
    ungottenToken = true;
}

void Tokenizer::printProcessedTokens() {
    for(auto iter = _tokens.begin(); iter != _tokens.end(); ++iter) {
        iter->print();
        std::cout << std::endl;
    }
}
