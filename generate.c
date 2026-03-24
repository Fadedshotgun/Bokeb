#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

// Generate assembly code from an AST
int generateAssemblyFromAST(struct ASTnode *node, int reg) {
    int leftValue, rightValue;

    if (node->left) {
        leftValue = generateAssemblyFromAST(node->left, -1);
    }
    if (node->right) {
        rightValue = generateAssemblyFromAST(node->right, leftValue);
    }

    switch (node->operation) {
        case AST_ADD: return (cgadd(leftValue, rightValue));
        case AST_SUB: return (cgsub(leftValue, rightValue));
        case AST_MUL: return (cgmul(leftValue, rightValue));
        case AST_DIV: return (cgdiv(leftValue, rightValue));
        case AST_IDENTIFIER: return (cgloadglobal(globalSymbols[node->v.id].name));
        case AST_LVIDENTIFIER: return (cgstoreglobal(reg, globalSymbols[node->v.id].name));
        case AST_INTLIT: return (cgloadint(node->v.intvalue));
        case AST_ASSIGN: return (rightValue);

        default:
            printf("Unknown AST operation %d in generateAssemblyFromAST()\n", node->operation);
            exit(1);
    }
}