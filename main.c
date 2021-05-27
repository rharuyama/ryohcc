#include "ryohcc.h"

int main(int argc, char** argv){
  char* input = argv[1];

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  top = tokenizer(input); // Token* top にトークンの列がセットされる
  show_tokens();

  // parser
  program();

  // prorogue
  printf("\tpush rbp\n");
  printf("\tmov rbp, rsp\n");
  printf("\tsub rsp, 208\n\n");
  
  for(int i = 0; code[i]; i++){
    codegen(code[i]);
    printf("\tpop rax\n\n");
  }

  // epilogue
  printf("\tmov rsp, rbp\n");
  printf("\tpop rbp\n");
  printf("\tret\n\n");
}
