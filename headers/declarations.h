struct token;

// scan.c
int scanNextToken(struct token *t);

// ast.c
struct ASTnode *makeASTnode(int operation, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *makeASTleafNode(int operation, int value);
struct ASTnode *makeASTunary(int operation, struct ASTnode *left, int value);

// expression.c
struct ASTnode *binaryExpression(int ptp);

// statement.c
void statements(void);

// generator.c / interpreter.c
int generateAssemblyFromAST(struct ASTnode *node, int reg);
void generateCode(struct ASTnode *node);

// codegenerator.c
void freeall_registers(void);
void cgpreamble();
void cgmain();
void cgpostamble();
int cgloadint(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);
int cgloadglobal(wchar_t *name);
int cgstoreglobal(int r, wchar_t *name);
void cgglobalsymbol(wchar_t *name);

//symbol.c
int findGlobalSymbol(wchar_t *name);
int addGlobalSymbol(wchar_t *name);

// utils.c
void match(int t, char *what);
void semi(void);
void leftParem(void);
void rightParem(void);
void identifier(void);

// declarations.c
void intDeclaration(void);