#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

// like the interpreter but making assmebly instead
int generateAssemblyFromAST(struct ASTnode *node) {
    int leftValue, rightValue;

    if (node->left) {
        leftValue = generateAssemblyFromAST(node->left);
    }
    if (node->right) {
        rightValue = generateAssemblyFromAST(node->right);
    }

    switch (node->operation) {
        case AST_ADD: return (cgadd(leftValue, rightValue));
        case AST_SUB: return (cgsub(leftValue, rightValue));
        case AST_MUL: return (cgmul(leftValue, rightValue));
        case AST_DIV: return (cgdiv(leftValue, rightValue));
        case AST_INTLIT: return (cgload(node->intvalue));

        default:
            printf("Unknown AST operation %d in generateAssemblyFromAST()\n", node->operation);
            exit(1);
    }
}