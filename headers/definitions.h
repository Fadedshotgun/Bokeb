#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h> 

#define TEXTLEN	512

// Token Struct
struct token {
    int token;
    int intvalue;
};

// Token Types
enum {
    TOKEN_EOF,
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH,
    TOKEN_INTLIT, //INTLIT = Integer Literal
    TOKEN_SEMICOLON, 
    TOKEN_LEFTPAREM, TOKEN_RIGHTPAREM,
    //KEYWORDS
    TOKEN_PRINT
}; 

//Abstract Syntax Tree Struct
struct ASTnode {
    int operation; // Operation to be performed
    struct ASTnode *left; // Child trees
    struct ASTnode *right;
    int intvalue; // Integer literal value, if this is a INTLIT node
};

//AST types
enum {
    AST_ADD, AST_SUB, AST_MUL, AST_DIV, AST_INTLIT
};

#endif