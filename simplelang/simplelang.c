#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node Node;
struct Node{
  char c;
  Node* lhs;
  Node* rhs;
};

char* tok;

Node* newNode(char c, Node* lhs, Node* rhs){
  Node* node = calloc(1, sizeof(Node));
  node->c = c;
  node->lhs = lhs;
  node->rhs = rhs;
  return node;
}

void show(Node* root){
  if(root->lhs == NULL || root->rhs == NULL){
      printf("%c ", root->c);
  }else{
    printf("(");
    printf("%c ", root->c);
    show(root->lhs);
    show(root->rhs);
    printf(") ");
  }
}

Node* expr();

Node* primary(){
  if(*tok == '('){
    tok++;
    Node* node = expr();
    if(*tok == ')'){
      tok++;
      return node;
    }
    fprintf(stderr, "no close parenthesis");
    exit(1);
  }
  
  Node* node = newNode(*tok, NULL, NULL);
  tok++; 
  return node;
}

Node* mul(){
  Node* node = primary();

  while(1){
    if(*tok == '*'){
      tok++;
      node = newNode('*', node, primary());

    }else{
      return node;
    }
  }
}

Node* expr(){
  Node* node = mul();

  while(1){
    if(*tok == '+'){
      tok++;
      node = newNode('+', node, mul());

    }else{
      return node;
    }
  }
}

int main(int argc, char** argv){
  tok = argv[1];

  Node* root = expr();
  
  show(root);
  printf("\n");
}
