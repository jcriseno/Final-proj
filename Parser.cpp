
/*  The majority of the work is done by the class 'convert'.
    This class builds an expression tree using the input infix
    expression.  A post-order traversal of the expression tree 'dumps'
    it into an array in postfix form.  The iterator copies the token
    from this array to user's arrays.

*/

#include<vector>
#include<iostream>
#include <stack>

#include "Token.hpp"
#include "Parser.hpp"
#include "Statements.hpp"
#include "Range.h"



// Parser functions
void Parser::die(std::string where, std::string message, Token &token) {
    std::cout << where << " " << message << std::endl;
    token.print();
    std::cout << std::endl;
    std::cout << "\nThe following is a list of tokens that have been identified up to this point.\n";
    tokenizer.printProcessedTokens();
    exit(1);
}

Statements *Parser::statements() {
    // This function is called when we KNOW that we are about to parse
    // a series of assignment statements.


    Statements *stmts = new Statements();
    Token tok = tokenizer.getToken();
    while (tok.isName()) {
        if(tok.isKeyword()){
            //For stmt and print stmt
            if(tok.isPrintStmt()){
                tokenizer.ungetToken();
                //std::cout << "Parsing a print statement\n";
                PrintStatement *printstmt = printStatement();
                stmts->addStatement(printstmt);
                tok = tokenizer.getToken();
            }
            if(tok.isForLoop()){
                // Do For Loops
                tokenizer.ungetToken();
                ForStatement *forstmt = forStatement();
                stmts->addStatement(forstmt);
                tok = tokenizer.getToken();
            }
        }
        else {
            tokenizer.ungetToken();
            AssignmentStatement *assignStmt = assignStatement();
            stmts->addStatement(assignStmt);
            tok = tokenizer.getToken();
        }
        // Add a get token here
        //tok = tokenizer.getToken();
    }


    tokenizer.ungetToken();
    return stmts;
}

ForStatement *Parser::forStatement() {
    //for i in range(x):
    //for i in range(x,y):
    //for i in range(x,y,z):

    // for
    Token forToken =  tokenizer.getToken();
    if(!forToken.isForLoop()){
        die("Parser:ForStatement", "Expected a for token, instead got", forToken);
    }

    //i
    Token varToken = tokenizer.getToken();
    if(!varToken.isName()){
        die("Parser:ForStatement", "Expected a var token, instead got", varToken);
    }

    // in
    Token inToken = tokenizer.getToken();
    if(!inToken.isInStmt()){
        die("Parser:ForStatement", "Expected a in token, instead got", inToken);
    }

    // range
    Token rangeToken = tokenizer.getToken();
    if(!rangeToken.isRangeStmt()){
        die("Parser:ForStatement", "Expected a range token, instead got", rangeToken);
    }

    // (
    Token openParenToken = tokenizer.getToken();
    if (!openParenToken.isOpenParen()){
        die("Parser:ForStatement", "Expected an Open Parentheses, instead got", openParenToken);
    }

    // x
    int x;
    int y;
    int z;
    int forLoopArgs = 1;
    Token xToken = tokenizer.getToken();
    if(xToken.isWholeNumber()){
        x = xToken.getWholeNumber();

        Token commaToken1 = tokenizer.getToken();
        if(commaToken1.isComma()){
            // y
            Token yToken = tokenizer.getToken();
            y = yToken.getWholeNumber();
            forLoopArgs++;


            Token commaToken2 = tokenizer.getToken();
            if(commaToken2.isComma()){
                // z
                Token zToken = tokenizer.getToken();
                z = zToken.getWholeNumber();
                forLoopArgs++;
            }
            else{
                tokenizer.ungetToken();
            }
        }
        else{
            tokenizer.ungetToken();
        }
    }

    if(forLoopArgs == 1){
        Range range = Range(x);
    }
    else if(forLoopArgs == 2){
        Range range = Range(x,y);

    }
    else if(forLoopArgs == 3){
        Range range = Range(x,y,z);

    }


    // )
    Token closedParenToken = tokenizer.getToken();
    if (!closedParenToken.isCloseParen()){
        die("Parser::ForStatement", "Expected an closed Parentheses, instead got", closedParenToken);
    }

    // :
    Token colonToken = tokenizer.getToken();
    if(!colonToken.isColon()){
        die("Parser::ForStatement", "Expected a colon, instead got", colonToken);
    }



    // for(i = 0; i < num; i = i + 1){ <statements> }

    // for
    /*

    Token forToken =  tokenizer.getToken();
    if(!forToken.isForLoop()){
        die("Parser:ForStatement", "Expected a for token, instead got", forToken);
    }
    // (
    Token openParenToken = tokenizer.getToken();
    if(!openParenToken.isOpenParen()){
        die("Parser::ForStatement", "Expected an Open Paren Token, instead got", openParenToken);
    }
    // i = 0;
    AssignmentStatement *astmt1 = assignStatement();
    Token firstSemi = tokenizer.getToken();
    if(!firstSemi.isSemiColon()){
        die("Parser::ForStatement", "Expected a Semi Colon Token 1, instead got", firstSemi);
    }
    // i < num;
    ExprNode *rel_node = rel_expr();
    Token secondSemi = tokenizer.getToken();
    if(!secondSemi.isSemiColon()){
        die("Parser::ForStatement", "Expected a Semi Colon Token 2, instead got", secondSemi);
    }
    Token firstEOL = tokenizer.getToken();
    if(!firstEOL.isNewLine())
        die("Parser::ForStatement", "Expected a First EOL 1, instead got", firstEOL);
    // i = i + 1
    AssignmentStatement *astmt3 = assignStatement();
    // )
    Token closedParenToken = tokenizer.getToken();
    if(!closedParenToken.isCloseParen()){
        die("Parser::ForStatement", "Expected a Closed Paren Token, instead got", closedParenToken);
    }
    Token secondEOL = tokenizer.getToken();
    if(!secondEOL.isNewLine())
        die("Parser::ForStatement", "Expected a Second EOL 2, instead got", secondEOL);
    // {

    Token openBracketToken = tokenizer.getToken();
    if(!openBracketToken.isOpenBracket()){
        die("Parser::ForStatement", "Expected an Open Bracket Token, instead got", openBracketToken);
    }

    // <statements>
    Statements *forstmts = statements();
    // }

    Token closeBracketToken = tokenizer.getToken();
    if(!closeBracketToken.isClosedBracket()){
        die("Parser::ForStatement", "Expected an Closed Bracket Token, instead got", closeBracketToken);
    }

    */

    //return new ForStatement(astmt1, rel_node, astmt3, forstmts);

    return new ForStatement()


}

PrintStatement *Parser::printStatement() {
    // <print-statement> -> print <id>

    Token printToken = tokenizer.getToken();
    if(!printToken.isPrintStmt()){
        die("Parser::printStatement", "Expected a print token, instead got", printToken);
    }
    // Getting a token and making sure it is a variable
    /*
    Token varName = tokenizer.getToken();
    if(!varName.isName()){
        die("Parser::printStatement", "Expected a var token, instead got", varName);
    }
     */
    //std::cout << "ABOUT TO CALL TEST LIST" << std::endl;
    //ExprNode *rightHandSideExpr = testlist();
    std::vector<ExprNode*> rightHandSideExpr = testlist();
    //std::cout << "FINISHED THE CALL TO  TEST LIST" << std::endl;

    //ExprNode *rightHandSideExpr = rel_expr();

    // Getting a token and making sure it a new line char



    Token tok = tokenizer.getToken();
    if (tok.isSemiColon())
        Token tok = tokenizer.getToken();
    if (tok.isPoundSymbol()){
        while(!tok.eol()) {
            Token tok = tokenizer.getToken();
        }
    }
    if (!tok.eol())
        die("Parser::printStatement", "Expected a New Line, instead got", tok);



   // return new PrintStatement(varName.getName());
   //std::cout << "Returning the finished print stmt!" << std::endl;
   return new PrintStatement(rightHandSideExpr);
}

AssignmentStatement *Parser::assignStatement() {
    // <assigment-statement> -> <var> = <value>

    Token varName = tokenizer.getToken();
    /*
    if(varName.isNewLine()){
        Token varName = tokenizer.getToken();
    }
     */
    // <var>
    if (!varName.isName())
        die("Parser::assignStatement", "Expected a name token, instead got", varName);

    // =
    Token assignOp = tokenizer.getToken();
    if (!assignOp.isAssignmentOperator())
        die("Parser::assignStatement", "Expected an equal sign, instead got", assignOp);


    //ExprNode *rightHandSideExpr = rel_expr();
    ExprNode *rightHandSideExpr = test();

    Token endTok = tokenizer.getToken();
    if(!endTok.eol())
        die("Parser::assignment ", "Expected a new line, instead got ", endTok );

    return new AssignmentStatement(varName.getName(), rightHandSideExpr);

}


std::vector<ExprNode *>Parser::testlist() {
    // <testlist> -> {',' <test>}*

    /*
    ExprNode *left = test();
    Token tok = tokenizer.getToken();
    while(tok.isComma()){
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = test();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
     */

    ExprNode *first = test();
    std::vector<ExprNode*> testVect;
    //ExprNode *first = test();
    //testVect.push_back(first);
    Token tok = tokenizer.getToken();
    while(tok.isComma()){
        testVect.push_back(first);
        first = test();
        tok = tokenizer.getToken();
    }
    testVect.push_back(first);

    tokenizer.ungetToken();
    return testVect;





}


ExprNode *Parser::test() {
    return rel_expr();
}


ExprNode *Parser::rel_expr() {
    // This will do the following grammar rules

    // <rel-expr> -> <expr> {(==, != , >, <, >=, <=) <expr>}


    ExprNode *left = expr();
    Token tok = tokenizer.getToken();
    while (tok.isEqualToOperator() || tok.isNotEqualOperator() || tok.isGreaterOperator() || tok.isLessOperator() || tok.isGreatEqualOperator() || tok.isLessEqualOperator()){
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = expr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

/*
ExprNode *Parser::rel_term() {
    // This will do the following grammar rules

    // <rel-expr> -> <rel-term> {(>, <, >=, <=) <rel-term>}

    ExprNode *left = expr();
    Token tok = tokenizer.getToken();
    while (tok.isGreaterOperator() || tok.isLessOperator() || tok.isGreatEqualOperator() || tok.isLessEqualOperator()){
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = expr();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}
*/

ExprNode *Parser::expr() {
    // This function parses the grammar rules:

    // <expr> -> <term> { <add_op> <term> }
    // <add_op> -> + | -

    // However, it makes the <add_op> left associative.

    ExprNode *left = term();
    Token tok = tokenizer.getToken();
    while (tok.isAdditionOperator() || tok.isSubtractionOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = term();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}


ExprNode *Parser::term() {
    // This function parses the grammar rules:

    // <term> -> <primary> { <mult_op> <primary> }
    // <mult_op> -> * | / | %

    // However, the implementation makes the <mult-op> left associate.
    ExprNode *left = primary();
    Token tok = tokenizer.getToken();

    while (tok.isMultiplicationOperator() || tok.isDivisionOperator() || tok.isModuloOperator()) {
        InfixExprNode *p = new InfixExprNode(tok);
        p->left() = left;
        p->right() = primary();
        left = p;
        tok = tokenizer.getToken();
    }
    tokenizer.ungetToken();
    return left;
}

ExprNode *Parser::primary() {
    // This function parses the grammar rules:

    // <primary> -> [0-9]+
    // <primary> -> [_a-zA-Z]+
    // <primary> -> (<expr>)

    Token tok = tokenizer.getToken();

    //std::cout << "This is a number" << tok.isWholeNumber() << std::endl;


    tok.print();
    std::cout << std::endl;
    if (tok.isWholeNumber() ) {
        //std::cout << "tok::WholeNumber Giving back token: ";
        //tok.print();
        return new WholeNumber(tok);
    }
    else if( tok.isStringS() ) {
        //std::cout << "tok::StringS Giving back token: ";
        //tok.print();
        return new String(tok);
    }
    else if( tok.isName() ) {
        //std::cout << "tok::Name Giving back token: ";
        //tok.print();
        return new Variable(tok);
    }
    /*
    else if (tok.isDoubleQuotationMark()){
        ExprNode *p = rel_expr();
        Token token = tokenizer.getToken();
        if (!token.isDoubleQuotationMark())
            die("Parser::primary", "Expected ending quotation mark, instead got", token);
        return p;
    }
     */

    else if (tok.isOpenParen()) {
        ExprNode *p = rel_expr();
        Token token = tokenizer.getToken();
        if (!token.isCloseParen())
            die("Parser::primary", "Expected close-parenthesis, instead got", token);
        return p;
    }
    die("Parser::primary", "Unexpected token", tok);

    return nullptr;  // Will not reach this statement!
}
