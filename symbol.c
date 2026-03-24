#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

static int nextFreeGlobalSymbolSlot = 0;

// Find a global symbols id given its name
int findGlobalSymbol(wchar_t *name) {
    for (int i = 0; i < nextFreeGlobalSymbolSlot; i++) {
        if (wcscmp(globalSymbols[i].name, name) == 0 && *name == *globalSymbols[i].name) {
            return i;
        }
    }
    return -1;
}

// Returns a new global symbol id
static int newGlobalSymbol(void) {
    int p;
    if ((p = nextFreeGlobalSymbolSlot++) >= NUMBER_OF_SYMBOLS) {
        printf("Too many global symbols defined\n");
        exit(1);
    }
    return p;
}

// Creates a new global symbol
int addGlobalSymbol(wchar_t *name) {
    int y;

    if ((y = findGlobalSymbol(name)) != -1) {
        return y;
    }

    y = newGlobalSymbol();
    globalSymbols[y].name = wcsdup(name);
    return y;
}