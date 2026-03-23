#include "headers/definitions.h"
#include "headers/data.h"
#include "headers/declarations.h"

void statements(void) {
    struct ASTnode *tree;
    int reg;

    while (1) {
        match(TOKEN_PRINT, "print");
        leftParem();

        printf("Parsing expression...\n");
        tree = binaryExpression(0);
        reg = generateAssemblyFromAST(tree);

        cgprintint(reg);
        freeall_registers();

        printf("Matching right parenthesis...\n");
        rightParem();

        semi();
        printf("Parsed statement\n");
        if (Token.token == TOKEN_EOF) {
            break;
        }
    }
}