#include "headers/data.h"
#include "headers/definitions.h"
#include "headers/declarations.h"

// Read next character from file
static int next(void) {
    wint_t character;

    if (Putback) {
        character = Putback;
        Putback = 0;
        return character;
    }

    character = fgetwc(InFile);
    if ('\n' == character) { Line++; }

    return character;
}

// Put back a character to be read
static void putback(wint_t character) {
    Putback = character; 
}

// Gets the next character that is actual wanted (not whitespace) :p
static wint_t skipToNextCharacter(void) {
    wint_t character;

    character = next();
    while (L' ' == character || L'\t' == character || L'\n' == character || L'\r' == character || L'\f' == character) {
        character = next();
    }
    return (character);
}

static int charPos(wchar_t *s, wint_t c) {
  wchar_t *p;

  p = wcschr(s, c);
  return (p ? p - s : -1);
}

static int scanInt(wint_t character) {
    int nextNumber, value = 0;

    nextNumber = charPos(L"0123456789", character);
    while (nextNumber >= 0) {
        value = value * 10 + nextNumber;
        character = next();

        nextNumber = charPos(L"0123456789", character);
    }

    // Put back non-integer we just hit
    putback(character);
    return value;
}

//reads alphanumeric characters and underscores until it hits a non-alphanumeric
static int scanIdentifier(wint_t character, wchar_t*buffer, int limit) {
    int i = 0;

    while (iswalpha(character) || iswdigit(character) || L'_' == character) {
        //printf("%c", character);
        if (limit - 1 == i) {
            fprintf(stderr, "Identifier too long on line %d\n", Line);
            exit(1);
        } else if (i < limit - 1) {
            buffer[i++] = character;
        }
        character = next();
    }

    putback(character);
    buffer[i] = '\0';
    return i;
}

static int findKeyword(wchar_t *string) {
    switch (*string) {
        case L'д':
            if (wcscmp(string, L"друкаваць") == 0) {
                return TOKEN_PRINT;
                printf("A");
            }
            break;
    }
    return 0;
}

int scanNextToken(struct token *t) {
    wint_t character;
    int tokenType;

    character = skipToNextCharacter();

    switch (character) {
        case WEOF:
            t->token = TOKEN_EOF;
            return 0; // NO MORE TOKENS :)
        case L'+':
            t->token = TOKEN_PLUS;
            break;
        case L'-':
            t->token = TOKEN_MINUS;
            break;
        case L'/':
            t->token = TOKEN_SLASH;
            break;
        case L'*':
            t->token = TOKEN_STAR;
            break;
        case L'(':
            t->token = TOKEN_LEFTPAREM;
            break;
        case L')':
            t->token = TOKEN_RIGHTPAREM;
            break;
        case L';':
            t->token = TOKEN_SEMICOLON;
            break;
        default:
            if (iswdigit(character)) {
                t->intvalue = scanInt(character);
                t->token = TOKEN_INTLIT;
                break;
            } else if (iswalpha(character) || L'_' == character) {
                wprintf(L"Scanning identifier starting with %lc on line %d\n", character, Line);
                scanIdentifier(character, Text, TEXTLEN);

                if (tokenType = findKeyword(Text)) {
                    t->token = tokenType;
                    break;
                } 
                    
                wprintf(L"Unknown identifierrrrr %ls on line %d\n", Text, Line);
                exit(1);

                break;
            }

            wprintf(L"Cannot recognize character %lc on line %d\n", character, Line);
            exit(1);
    }

    return (1); // FOUND TOKEN
}