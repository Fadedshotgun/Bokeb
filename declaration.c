#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

// Declare an integer variable
void intDeclaration(void) {
    match(TOKEN_INT, "цэлы"); // цэлы = int
    identifier();
    addGlobalSymbol(Text);
    cgglobalsymbol(Text);
    semi();
}