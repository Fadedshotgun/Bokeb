#include "headers/definitions.h"
#include "headers/declarations.h"

int interpretAST(struct ASTnode *node) {
    int leftValue, rightValue;

    if (node->left) {
        leftValue = interpretAST(node->left);
    }
    if (node->right) {
        rightValue = interpretAST(node->right);
    }

    switch (node->operation) {
        case AST_ADD: return leftValue + rightValue;
        case AST_SUB: return leftValue - rightValue;
        case AST_MUL: return leftValue * rightValue;
        case AST_DIV: return leftValue / rightValue;
        case AST_INTLIT: return node->intvalue;
        default:
            printf("Unknown operation %d in interpretAST()\n", node->operation);
            exit(1);
    }
}