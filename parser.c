#include "max_token_length.h"

typedef struct _node Node;
struct _node{
  Node* lhs;
  char val[MAX_TOKEN_LENGTH];
  Node* rhs;
};

#include <stdio.h>
#include <stdlib.h>

Token* parser(char* src){
  return tokenizer(src);    
}
