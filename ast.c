#include "headers/definitions.h"

struct ASTnode *makeASTnode(int operation, struct ASTnode *left, struct ASTnode *right, int intvalue) {
    struct ASTnode *newNode = malloc(sizeof(struct ASTnode));

    newNode->operation = operation;
    newNode->left = left;
    newNode->right = right;
    newNode->intvalue = intvalue;

    return newNode;
}

struct ASTnode *makeASTintegerNode(int operation, int value) {
    return makeASTnode(operation, NULL, NULL, value); // a simple integer leaf
}  

struct ASTnode *makeASTunary(int operation, struct ASTnode *left, int value) {
    return makeASTnode(operation, left, NULL, value); //only one child
}