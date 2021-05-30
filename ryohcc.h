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

// parser

typedef enum{
  ND_NUM,
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
}NodeKind;

typedef struct Node Node;
struct Node{
  NodeKind kind;
  Node* lhs;
  Node* rhs;
  int val;
  int offset;
};

extern Node* code[100];
extern int code_idx;

Node* new_node(NodeKind, Node*, Node*);
Node* new_node_num(NodeKind, int);
Node* new_node_lvar(int);
Node* add();
Node* primary();
Node* unary();
Node* mul();
Node* relational();
Node* equality();
Node* assign();
Node* expr();
void stmt();
void program();

// ryohcc.c (codegen)

void codegen(Node*);
