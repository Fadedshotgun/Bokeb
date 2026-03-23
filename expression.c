#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

int tokenToASToperation(int token) {
    switch (token) {
        case TOKEN_PLUS: return AST_ADD;
        case TOKEN_MINUS: return AST_SUB;
        case TOKEN_STAR: return AST_MUL;
        case TOKEN_SLASH: return AST_DIV;
        case TOKEN_INTLIT: return AST_INTLIT;
        default:
            printf("Unknown token %d in tokenToASToperation()\n", token);
            exit(1);
    }
}

static struct ASTnode *primary(void) {
    struct ASTnode *node;

    // make ast leaf node for integer literal token
    switch (Token.token)
    {
        case TOKEN_INTLIT:
            node = makeASTintegerNode(AST_INTLIT, Token.intvalue);
            scanNextToken(&Token);
            return node;
        default:
            printf("syntax error on line %d\n", Line);
            exit(1);
    }
}

static int precedenceArray[] = { 0, 10, 10, 20, 20,   0 };
//                              EOF  +   -   *   /  INTLIT

static int operatorPrecedence(int tokenType) {
    int precedence = precedenceArray[tokenType];
    if (precedence == 0) {
        printf("Syntax errorrr on line %d\n", Line);
        exit(1);
    }

    return precedence;
}

// pratt parsing, makes my head hurt tbh
// more info at: https://journal.stuffwithstuff.com/2011/03/19/pratt-parsers-expression-parsing-made-easy/
struct ASTnode *binaryExpression(int ptp) {
    struct ASTnode *left, *right;
    int tokenType;

    left = primary();

    tokenType = Token.token;
    if (tokenType == TOKEN_SEMICOLON || tokenType == TOKEN_RIGHTPAREM) {
        return left;
    }

    while (operatorPrecedence(tokenType) > ptp) {
        scanNextToken(&Token);

        right = binaryExpression(precedenceArray[tokenType]);
        left = makeASTnode(tokenToASToperation(tokenType), left, right, 0);

        tokenType = Token.token;
        if (tokenType == TOKEN_SEMICOLON || tokenType == TOKEN_RIGHTPAREM) {
            return left;
        }
    }

    return left;
}