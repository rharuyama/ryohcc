#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>

typedef struct Node Node;
struct Node{
  char c;
  Node* lhs;
  Node* rhs;
};

Node* new_node(char c, Node* lhs, Node* rhs){
  Node* node = calloc(1, sizeof(Node));
  node->c = c;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

Node* primary(char* p){
  Node* node = new_node(*p, NULL, NULL);
  return node;
}

Node* mul(char* p){
  Node* lhs = primary(p);

  return lhs;
}

void print_tree(Node* node){
  if(node->lhs == NULL || node->rhs == NULL){
    printf("%c ", node->c);
    return;
  }
  printf("(");
  printf("%c ", node->c);
  print_tree(node->lhs);
  print_tree(node->rhs);
  printf(")");
}

int main(int argc, char** argv){
  char* p = argv[1];

  Node* node = mul(p);

  print_tree(node);
  printf("\n");
}
