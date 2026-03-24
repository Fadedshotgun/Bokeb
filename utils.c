#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

// Makes sure next token is what we expect
void match(int t, char *what) {
  if (Token.token == t) {
    scanNextToken(&Token);
  } else {
    printf("'%s' expected on line %d\n", what, Line);
    exit(1);
  }
}

// Just shorthand functions for matching tokens
void semi(void) {
  match(TOKEN_SEMICOLON, ";");
}

void leftParem(void) {
  match(TOKEN_LEFTPAREM, "(");
}

void rightParem(void) {
  match(TOKEN_RIGHTPAREM, ")");
}

void identifier(void) {
  match(TOKEN_IDENTIFIER, "identifier");
}