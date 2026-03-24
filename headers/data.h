#include <stdio.h>
#include <wchar.h>
#include "definitions.h"

extern int Line;
extern wint_t Putback;
extern FILE *InFile;
extern FILE	*Outfile;
extern struct token Token;
extern wchar_t Text[TEXTLEN + 1];
extern struct symbolTable globalSymbols[NUMBER_OF_SYMBOLS]; // Global Variables