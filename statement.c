#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

// Print
void printStatement() {
    struct ASTnode *tree;
    int reg;

    match(TOKEN_PRINT, "друкаваць"); // друкаваць = print
    leftParem();

    tree = binaryExpression(0);
    reg = generateAssemblyFromAST(tree, -1);

    cgprintint(reg);
    freeall_registers();

    rightParem();
    semi();
}

// Variable assignment
void assignment() {
    struct ASTnode *left, *right, *tree;
    int id;

    identifier();
    if ((id = findGlobalSymbol(Text)) == -1) {
        printf("Undeclared variable %ls on line %d\n", Text, Line);
        exit(1);
    }
    right = makeASTleafNode(AST_LVIDENTIFIER, id);

    match(TOKEN_EQUALS, "=");

    left = binaryExpression(0);
    tree = makeASTnode(AST_ASSIGN, left, right, 0);

    generateAssemblyFromAST(tree, -1);
    freeall_registers();

    semi();
}

// Read all statements
void statements(void) {
    while (1) {
        switch (Token.token) {
            case TOKEN_PRINT:
                printStatement();
                break;
            case TOKEN_INT:
                intDeclaration();
                break;
            case TOKEN_IDENTIFIER:
                assignment();
                break;
            case TOKEN_EOF:
                return;
            default:
                printf("Syntax error on line %d, with token %d\n", Line, Token.token);
                exit(1);
        }
    }
}