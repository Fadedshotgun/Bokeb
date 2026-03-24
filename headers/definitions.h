#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h> 

#define TEXTLEN	512
#define NUMBER_OF_SYMBOLS 1024

// Token Struct
struct token {
    int token;
    int intvalue;
};

// Token Types
enum {
    TOKEN_EOF,
    TOKEN_PLUS, TOKEN_MINUS, TOKEN_STAR, TOKEN_SLASH, TOKEN_EQUALS,
    TOKEN_INTLIT, //INTLIT = Integer Literal
    TOKEN_SEMICOLON, TOKEN_LEFTPAREM, TOKEN_RIGHTPAREM,
    TOKEN_IDENTIFIER, //IDENTIFIER = variable name
    //KEYWORDS
    TOKEN_PRINT, TOKEN_INT
}; 

// Abstract Syntax Tree Struct
struct ASTnode {
    int operation; // Operation to be performed
    struct ASTnode *left; // Child trees
    struct ASTnode *right;
    union {
        int intvalue; // Integer literal value, if this is a INTLIT node
        int id; // Symbol slot number if Identifier node
    } v;
};

// AST types
enum {
    AST_ADD, AST_SUB, AST_MUL, AST_DIV, AST_INTLIT, AST_ASSIGN, AST_IDENTIFIER, AST_LVIDENTIFIER
};

// Symbol Table
struct symbolTable {
    wchar_t *name;
};

#endif