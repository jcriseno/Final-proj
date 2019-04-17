//
// Created by Ali A. Kooshesh on 2/5/19.
//

#include "Statements.hpp"
#include "SymTab.hpp"

// Statement
Statement::Statement() {}

// Statements
Statements::Statements() {}
void Statements::addStatement(Statement *statement) { _statements.push_back(statement); }

void Statements::print() {
    for (auto s: _statements)
        s->print();
}

void Statements::evaluate(SymTab &symTab) {
    for (auto s: _statements)
        s->evaluate(symTab);
}

// For Statement
ForStatement::ForStatement() : _Expression1{nullptr},
                                _Expression3{nullptr},
                                _Rel_expr{nullptr},
                                _innerStatements{nullptr}{}

ForStatement::ForStatement(
        AssignmentStatement *expr1,
        ExprNode *relexpr,
        AssignmentStatement *expr3,
        Statements *innerstatements) :
        _Expression1{expr1}, _Rel_expr{relexpr},
        _Expression3{expr3}, _innerStatements{innerstatements} {}

AssignmentStatement *&ForStatement::getExpr1(){
    return _Expression1;
}

AssignmentStatement *&ForStatement::getExpr3(){
    return _Expression3;
}

ExprNode *&ForStatement::getRelexpr(){
    return _Rel_expr;
}

Statements *&ForStatement::getInnerStatements(){
    return _innerStatements;
}

void ForStatement::print() {
    std::cout << "for(";
    getExpr1()->print();
    std::cout << ";";
    getRelexpr()->print();
    std::cout << ";";
    getExpr3()->print();
    std::cout << "){";
    getInnerStatements()->print();
    std::cout << "}";
}

void ForStatement::evaluate(SymTab &symTab) {
    getExpr1()->evaluate(symTab);
    while(getRelexpr()->evaluate(symTab) != 0){
        getInnerStatements()->evaluate(symTab);
        getExpr3()->evaluate(symTab);
    }
}



// Print Statement
PrintStatement::PrintStatement() :  _rhsVariable{""}{}

PrintStatement::PrintStatement(std::string rhsVar):
        _rhsVariable{rhsVar} {}

PrintStatement::PrintStatement(ExprNode *rightHandSideExpression) :
        _rightHandSideExpr{rightHandSideExpression} {}

PrintStatement::PrintStatement(std::vector<ExprNode *> rhsVect) :
        _rhsVect{rhsVect} {}

void PrintStatement::evaluate(SymTab &symTab) {
    std::vector<ExprNode*> rightVect = rhsVect();
    for(size_t i = 0; i < rightVect.size(); i++){
        if(rightVect[i]->token().getStringS() != ""){
            std::cout << rightVect[i]->token().getStringS() << " ";
        }
        else if(rightVect[i]->token().isArithmeticOperator()){
            std::cout << rightVect[i]->evaluate(symTab) << " ";
        }
        else{
            NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>
                    (symTab.getValueFor(rightVect[i]->token().getName()));
            if (nDesc == nullptr){
                StringTypeDescriptor *sDesc = dynamic_cast<StringTypeDescriptor*>
                        (symTab.getValueFor(rightVect[i]->token().getName()));
                std::cout << sDesc->stringValue << " ";
            }
            else{
                std::cout << nDesc->value.intValue;
            }
        }
    }
    /*
    NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor *>(symTab.getValueFor(rhsVariable()));
    if (nDesc == nullptr){
        StringTypeDescriptor *nDesc = dynamic_cast<StringTypeDescriptor *>(symTab.getValueFor(rhsVariable()));
        std::cout << nDesc->stringValue << std::endl;
        return;
    }

    if(nDesc->type() == TypeDescriptor::INTEGER) {
        std::cout << nDesc->value.intValue << std::endl;
    }
    else if(nDesc->type() == TypeDescriptor::BOOL) {
        std::cout << nDesc->value.boolValue << std::endl;
    }
    else
        std::cout << "Misconfigured union type." << std::endl;
     */

    /*
     *
     * YOU WANT THIS STUFF

    std::cout << "BEGINNING TO EVALUATE PRINT " << std::endl;
    std::cout << "Going in with: ";
    rightHandSideExpr()->token().print();
    std::cout << std::endl;

    if(rightHandSideExpr()->token().isName()){
        TypeDescriptor *desc = symTab.getValueFor(rightHandSideExpr()->token().getName());
        //NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>(desc);
        //if(nDesc == nullptr){
        if(desc->type() == TypeDescriptor::STRING){
            std::cout << "PrintStatement::evaluate GOT A " << std::endl;
            //StringTypeDescriptor *sDesc = dynamic_cast<StringTypeDescriptor*>(desc);
            std::string value = rightHandSideExpr()->stringEvaluate(symTab);
            std::cout << value << std::endl;

        }
        else if(desc->type() == TypeDescriptor::INTEGER)
        {
            std::cout << "PrintStatement::evaluate GOT A TypeDescriptor::INTEGER" << std::endl;
            int value = rightHandSideExpr()->evaluate(symTab);
            std::cout << value << std::endl;
        }
    }
    else if(rightHandSideExpr()->token().isWholeNumber()){
        std::cout << "Here! " << std::endl;
        int value = rightHandSideExpr()->evaluate(symTab);
        std::cout << value << std::endl;
    }
    else if(rightHandSideExpr()->token().isStringS()){
        std::cout << "Here! NUMBER 2 " << std::endl;
        std::string value = rightHandSideExpr()->stringEvaluate(symTab);
        std::cout << value << std::endl;
    }
    else if(rightHandSideExpr()->token().isArithmeticOperator()){
        std::cout << "FOUND THIS" << std::endl;
        int value = rightHandSideExpr()->evaluate(symTab);
        std::cout << value << std::endl;

    }
    else{
        InfixExprNode *node = dynamic_cast<InfixExprNode*>(rightHandSideExpr());
        ExprNode *left = node->left();
        if(left->token().isName()){
            TypeDescriptor *desc = symTab.getValueFor(rightHandSideExpr()->token().getName());
            //NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>(desc);
            //if(nDesc == nullptr){
            if(desc->type() == TypeDescriptor::STRING){
                //StringTypeDescriptor *sDesc = dynamic_cast<StringTypeDescriptor*>(desc);
                std::cout << "How in the world did we get here" << std::endl;
                std::string value = rightHandSideExpr()->stringEvaluate(symTab);
                std::cout << value << std::endl;
            }
            else if(desc->type() == TypeDescriptor::INTEGER)
            {
                std::cout << "We are here!" << std::endl;
                int value = rightHandSideExpr()->evaluate(symTab);
                std::cout << value << std::endl;

            }
        }
        else if(left->token().isStringS()){
            std::string value = rightHandSideExpr()->stringEvaluate(symTab);
            std::cout << value << std::endl;

        }
        else if(left->token().isWholeNumber()){
            int value = rightHandSideExpr()->evaluate(symTab);
            std::cout << value << std::endl;

        }
        else if(left->token().isArithmeticOperator()){
            int value = rightHandSideExpr()->evaluate(symTab);
            std::cout << value << std::endl;

        }
    }
     */

    /*
    else if(rightHandSideExpr()->token().isName()){
        TypeDescriptor *desc = symTab.getValueFor(rightHandSideExpr()->token().getName());
        if(desc->type() == TypeDescriptor::INTEGER){
            std::string value = rightHandSideExpr()->stringEvaluate(symTab);
            std::cout << value << std::endl;
        }
        else if(desc->type() == TypeDescriptor::STRING){
            int value = rightHandSideExpr()->evaluate(symTab);
            std::cout << value << std::endl;
        }
    }
     */




}

void PrintStatement::print() {
    std::cout << "print ";
    std::cout <<_rhsVariable;
    std::cout << std::endl;
}

std::string &PrintStatement::rhsVariable() {
    return _rhsVariable;
}

ExprNode *PrintStatement::rightHandSideExpr() const {
    return _rightHandSideExpr;
}

const std::vector<ExprNode *> &PrintStatement::rhsVect() const {
    return _rhsVect;
}


// AssignmentStatement
AssignmentStatement::AssignmentStatement() : _lhsVariable{""}, _rhsExpression{nullptr} {}

AssignmentStatement::AssignmentStatement(std::string lhsVar, ExprNode *rhsExpr):
        _lhsVariable{lhsVar}, _rhsExpression{rhsExpr} {}

void AssignmentStatement::evaluate(SymTab &symTab) {
    if (rhsExpression()->token().isName()){
        NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>
                (symTab.getValueFor(rhsExpression()->token().getName()));
        if(nDesc == nullptr){
            StringTypeDescriptor *sDesc = dynamic_cast<StringTypeDescriptor*>
                    (symTab.getValueFor(rhsExpression()->token().getName()));
            std::string stringValue = sDesc->stringValue;
            symTab.setValueFor(lhsVariable(), stringValue);
        }
        else{
            int value = nDesc->value.intValue;
            symTab.setValueFor(lhsVariable(), value);
        }
    }
    else if(rhsExpression()->token().isWholeNumber()){
        int rhs = rhsExpression()->evaluate(symTab);
        symTab.setValueFor(lhsVariable(), rhs);
    }
    else if (rhsExpression()->token().isStringS()){
        std::string stringRhs = rhsExpression()->stringEvaluate(symTab);
        symTab.setValueFor(lhsVariable(), stringRhs);
    }
    /*
     *
     * YOU WANT THIS STUFF
    if(rhsExpression()->token().isName()){
        TypeDescriptor *desc = symTab.getValueFor(rhsExpression()->token().getName());
        //NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>(desc);
        //if(nDesc == nullptr){
        if(desc->type() == TypeDescriptor::STRING){
            std::cout << "AssignmentStatement::evaluate GOT A " << std::endl;
            //StringTypeDescriptor *sDesc = dynamic_cast<StringTypeDescriptor*>(desc);
            std::string rhs = rhsExpression()->stringEvaluate(symTab);
            symTab.setValueFor(lhsVariable(), rhs);
        }
        else if(desc->type() == TypeDescriptor::INTEGER)
        {
            std::cout << "AssignmentStatement::evaluate GOT A TypeDescriptor::INTEGER" << std::endl;
            int rhs = rhsExpression()->evaluate(symTab);
            symTab.setValueFor(lhsVariable(), rhs);
        }
    }
    else if(rhsExpression()->token().isStringS()){
        std::cout << "AssignmentStatement::evaluate GOT A stringS" << std::endl;
        std::string rhs = rhsExpression()->stringEvaluate(symTab);
        symTab.setValueFor(lhsVariable(), rhs);
    }
    else if(rhsExpression()->token().isWholeNumber()){
        std::cout << "AssignmentStatement::evaluate GOT A AWholeNumber" << std::endl;
        int rhs = rhsExpression()->evaluate(symTab);
        symTab.setValueFor(lhsVariable(), rhs);
    }
    else if(rhsExpression()->token().isArithmeticOperator()){
        int rhs = rhsExpression()->evaluate(symTab);
        symTab.setValueFor(lhsVariable(), rhs);
    }
    else{
        InfixExprNode *node = dynamic_cast<InfixExprNode*>(rhsExpression());
        ExprNode *left = node->left();
        if(left->token().isName()){
            TypeDescriptor *desc = symTab.getValueFor(rhsExpression()->token().getName());
            //NumberTypeDescriptor *nDesc = dynamic_cast<NumberTypeDescriptor*>(desc);
            //if(nDesc == nullptr){
            if(desc->type() == TypeDescriptor::STRING){
                //StringTypeDescriptor *sDesc = dynamic_cast<StringTypeDescriptor*>(desc);
                std::cout << "How in the world did we get here" << std::endl;
                std::string rhs = rhsExpression()->stringEvaluate(symTab);
                symTab.setValueFor(lhsVariable(), rhs);
            }
            else if(desc->type() == TypeDescriptor::INTEGER)
            {
                std::cout << "We are here!" << std::endl;
                int rhs = rhsExpression()->evaluate(symTab);
                symTab.setValueFor(lhsVariable(), rhs);
            }
        }
        else if(left->token().isStringS()){
            std::string rhs = rhsExpression()->stringEvaluate(symTab);
            symTab.setValueFor(lhsVariable(), rhs);
        }
        else if(left->token().isWholeNumber()){
            int rhs = rhsExpression()->evaluate(symTab);
            symTab.setValueFor(lhsVariable(), rhs);
        }
        else if(left->token().isArithmeticOperator()){
            int rhs = rhsExpression()->evaluate(symTab);
            symTab.setValueFor(lhsVariable(), rhs);
        }
    }
     */
    int rhs = rhsExpression()->evaluate(symTab);
    symTab.setValueFor(lhsVariable(), rhs);
}

std::string &AssignmentStatement::lhsVariable() {
    return _lhsVariable;
}

ExprNode *&AssignmentStatement::rhsExpression() {
    return _rhsExpression;
}

void AssignmentStatement::print() {
    std::cout << _lhsVariable << " = ";
    _rhsExpression->print();
    std::cout << std::endl;
}
