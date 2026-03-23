#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

int Line;
wint_t Putback;
FILE *InFile;
FILE *Outfile;
struct token Token;
wchar_t Text[TEXTLEN + 1];

wchar_t *tokenStrings[] = { L"+", L"-", L"*", L"/", L"Integer Literal" };

void main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please provide an input file\n");
        exit(1);
    }

    Line = 1;
    Putback = '\n';

    // gotta convert to wide string cuz wide strings r stupid
    size_t len = strlen(argv[1]) + 1;
    wchar_t *wfilename = malloc(len * sizeof(wchar_t));
    mbstowcs(wfilename, argv[1], len);

    InFile = _wfopen(wfilename, L"r, ccs=UTF-8");
    free(wfilename);
    if (InFile == NULL) {
        printf("Could not open file %s\n", argv[1]);
        exit(1);
    }

    if ((Outfile = fopen("out.s", "w")) == NULL) {
        printf("Unable to create out.s");
        exit(1);
    }

    scanNextToken(&Token);
    
    cgpreamble();
    statements();
    cgpostamble();

    fclose(InFile);
    exit(0);
}