#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "tokenizer.c"
#include "parser.c"

void codegen(Node* root){
  if(root->kind == ND_NUM){
    printf("   push %d\n\n", root->val);

  }else if(root->kind == ND_MUL){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   imul rax, rdi\n");
    printf("   push rax\n\n");
  }else{
    printf("// ERROR HERE in codegen");
  }
}

int main(int argc, char** argv){
  char* input = argv[1]; // "5 * 20"

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  tokenizer(input); // Token* top にトークンの列がセットされる
  show_tokens();
  
  // parser
  Node* root = parser(); 

  codegen(root);

  printf("   pop rax\n");
  printf("   ret\n");
}
