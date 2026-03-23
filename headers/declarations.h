struct token;

// scan
int scanNextToken(struct token *t);

// AST
struct ASTnode *makeASTnode(int operation, struct ASTnode *left, struct ASTnode *right, int intvalue);
struct ASTnode *makeASTintegerNode(int operation, int value);
struct ASTnode *makeASTunary(int operation, struct ASTnode *left, int value);

// expression
struct ASTnode *binaryExpression(int ptp);

// statement

void statements(void);

// generator / interpreter
int interpretAST(struct ASTnode *node);

int generateAssemblyFromAST(struct ASTnode *node);

void generateCode(struct ASTnode *node);

//code generator
void freeall_registers(void);
void cgpreamble();
void cgpostamble();
int cgload(int value);
int cgadd(int r1, int r2);
int cgsub(int r1, int r2);
int cgmul(int r1, int r2);
int cgdiv(int r1, int r2);
void cgprintint(int r);

// utils
void match(int t, char *what);
void semi(void);
void leftParem(void);
void rightParem(void);