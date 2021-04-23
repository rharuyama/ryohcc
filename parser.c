#include "max_token_length.h"

// 抽象構文木のノードの種類
typedef enum {
  /* ND_ADD, // + */
  /* ND_SUB, // - */
  ND_MUL, // *
  ND_DIV, // /
  ND_NUM, // 整数
} NodeKind;

typedef struct Node Node;

// 抽象構文木のノードの型
struct Node {
  NodeKind kind; // ノードの型
  Node *lhs;     // 左辺
  Node *rhs;     // 右辺
  int val;       // kindがND_NUMの場合のみ使う
};

#include <stdio.h>
#include <stdlib.h>

/* Node* new_node_num(int val){ */
/*   Node* node = calloc(1, sizeof(Node)); */
/*   node->kind = ND_NUM; */
/*   node->val = val; */
/*   return node; */
/* } */

Node* new_node(NodeKind kind, Node* lhs, Node* rhs, int val){
  Node* node = malloc(sizeof(Node));
  node->kind = kind;
  node->lhs = lhs;
  node->rhs = rhs;
  node->val = val;
  return node;
}

Node* primary(Token* tokens){
  Node* node = malloc(sizeof(Node));
  node->lhs = NULL;
  printf("%d\n", tokens->val);
  node->val = tokens->val;
  node->rhs = NULL;
  
  return node;
}

Node* mul(Token* tokens){
  if(tokens == NULL){
    return NULL;
  }
  if(tokens->next == NULL){
    return NULL;
  }
  
  Node* node = primary(tokens);
  
  tokens = tokens->next;
  
  while(1){
    if(strcmp(tokens->str, "*")){
      Node* rhs = mul(tokens->next);
      node = new_node(ND_MUL, node, rhs, 0);
      return node;
    }else if(strcmp(tokens->str, "/")){
      Node* rhs = mul(tokens->next);
      node = new_node(ND_DIV, node, rhs, 0);
      return node;
    }else{
      return node;
    }
  }
}

Node* parser(char* source_file){
  Token* tokens = tokenizer(source_file);
  Node* parse_tree_root = malloc(sizeof(Node));

  parse_tree_root = mul(tokens);
  
  return parse_tree_root;    
}

