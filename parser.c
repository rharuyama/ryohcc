#include <stdio.h>
#include <stdlib.h>

typedef enum{
  ND_MUL,
  ND_NUM,
}NodeKind;

typedef struct Node Node;
struct Node{
  NodeKind kind;
  Node* lhs;
  Node* rhs;
  int val;
};

Node* ntop;

void parser(){
  fprintf(stderr, "WORKS FINE %d\n", top->val);
}
