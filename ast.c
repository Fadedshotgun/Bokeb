#include "headers/definitions.h"

struct ASTnode *makeASTnode(int operation, struct ASTnode *left, struct ASTnode *right, int intvalue) {
    struct ASTnode *newNode = malloc(sizeof(struct ASTnode));

    newNode->operation = operation;
    newNode->left = left;
    newNode->right = right;
    newNode->v.intvalue = intvalue;

    return newNode;
}

struct ASTnode *makeASTleafNode(int operation, int value) {
    return makeASTnode(operation, NULL, NULL, value); // A simple leaf node, no children
}  

struct ASTnode *makeASTunary(int operation, struct ASTnode *left, int value) {
    return makeASTnode(operation, left, NULL, value); // Only 1 child node
}