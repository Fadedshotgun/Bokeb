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

// Put back a character to be read next
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

// Finds what position a character is in a string
static int charPos(wchar_t *s, wint_t c) {
  wchar_t *p;

  p = wcschr(s, c);
  return (p ? p - s : -1);
}

// Scans an integer literal until we hit a non-integer character
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

// Reads alphanumeric characters and underscores until it hits a non-alphanumeric
static int scanIdentifier(wint_t character, wchar_t*buffer, int limit) {
    int i = 0;

    while (iswalpha(character) || iswdigit(character) || L'_' == character) {
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

// Finding keywords, based off first character 
static int findKeyword(wchar_t *string) {
    switch (*string) {
        case L'д':
            if (wcscmp(string, L"друкаваць") == 0) {
                return TOKEN_PRINT;
            }
            break;
        case L'ц':
            if (wcscmp(string, L"цэлы") == 0) {
                return TOKEN_INT;
            }
            break;
    }
    return 0;
}

int scanNextToken(struct token *t) {
    wint_t character;
    int tokenType;

    character = skipToNextCharacter();

    // Tokens 
    switch (character) {
        case WEOF:
            t->token = TOKEN_EOF;
            return 0; 
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
        case L'=':
            t->token = TOKEN_EQUALS;
            break;
        default:
            if (iswdigit(character)) {
                t->intvalue = scanInt(character);
                t->token = TOKEN_INTLIT;
                break;
            } else if (iswalpha(character) || L'_' == character) {
                scanIdentifier(character, Text, TEXTLEN);

                if (tokenType = findKeyword(Text)) {
                    t->token = tokenType;
                    break;
                } 
                    
                // If not a keyword, its an identifier
                t->token = TOKEN_IDENTIFIER;
                break;
            }

            wprintf(L"Cannot recognize character %lc on line %d\n", character, Line);
            exit(1);
    }

    return (1); // FOUND TOKEN
}