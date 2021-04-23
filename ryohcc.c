#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "tokenizer.c"
#include "parser.c"

int main(int argc, char** argv){
  char* input = argv[1]; // "5 * 20"

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  tokenizer(input); // Token* top にトークンの列がセットされる
  show_tokens();
  
  // parser
  Node* root = parser(); 

  printf("   mov rax, %d\n", root->lhs->val);
  printf("   ret\n");
}
