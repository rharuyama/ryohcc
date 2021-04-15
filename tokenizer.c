#define MAX_TOKEN_LENGTH 128

typedef struct _token Token;
struct _token{
  char val[MAX_TOKEN_LENGTH];
  Token* next;
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token* tokenizer(char* src){
  FILE* source = fopen(src, "r");

  char target[MAX_TOKEN_LENGTH];

  memset(target, 0, MAX_TOKEN_LENGTH);
  
  fread(target,
	sizeof(char),
	sizeof(target) / sizeof(target[0]),
	source);
  
  Token* ptok = malloc(sizeof(Token));
  strcpy(ptok->val, target);
  ptok->next = NULL;
  return ptok;
}
