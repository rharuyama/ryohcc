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

void show_tokens();
Token* tokenizer(char*);

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

extern Node* code[100];
extern int code_idx;

typedef struct Prog Prog;
struct Prog{ 
  Node* node;
  Prog* next;
  bool separator;
};
extern Prog* prog;

void program();
LVar* locals;
void push_prog(Prog**, Node*, bool);

// ryohcc.c (codegen)

void codegen(Node*);
