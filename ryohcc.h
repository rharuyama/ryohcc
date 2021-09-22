#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

// tokenizer

typedef enum{
  TK_RESERVED,
  TK_NUM,
  TK_EOF,
  TK_IDENT,
  TK_RETURN,
}TokenKind;

typedef struct Token Token;
struct Token{
  int val;
  char* data;
  TokenKind kind;
  Token* next;
  int len;
};

extern Token* top;

bool at_eof(Token*);
void show_tokens();
Token* new_token(TokenKind, Token*, char*);
Token* tokenizer(char*);
bool is_alnum(char);

// parser

typedef enum{
  ND_NUM = 100, // for debugging
  ND_MUL,
  ND_DIV,
  ND_ADD,
  ND_SUB,
  ND_REQ,
  ND_REL,
  ND_EQU,
  ND_NEQ,
  ND_ASS,
  ND_LVAR,
  ND_RETURN,
  ND_IF,
}NodeKind;

typedef struct Node Node;
struct Node{
  NodeKind kind;
  Node* lhs;
  Node* rhs;
  int val;
  int offset;

  // "if" statement
  Node* cond;
  Node* then;
  Node* els;
};

typedef struct LVar LVar;
struct LVar{
  LVar* next;
  char* name;  
  int len;
  int offset;
};

extern Node* code[100][100];
extern int code_idx;
extern int block;

Node* new_node(NodeKind, Node*, Node*);
Node* new_node_num(NodeKind, int);
Node* new_node_lvar(int);
bool isin(Token*);
int set_val(Token*);
Node* add();
Node* primary();
Node* unary();
Node* mul();
Node* relational();
Node* equality();
Node* assign();
Node* expr();
Node* stmt();
void program();
LVar* locals;

// ryohcc.c (codegen)

void codegen(Node*);
