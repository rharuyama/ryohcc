#include "ryohcc.h"

int main(int argc, char** argv){
  char* input = argv[1];
  locals = NULL;

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  top = tokenizer(input); // Token* top にトークンの列がセットされる

  // parser
  compound_stmt();

  // prorogue
  printf("\tpush rbp\n");
  printf("\tmov rbp, rsp\n");
  printf("\tsub rsp, 208\n\n");

  while(){
    codegen(compound_stmt());
    printf("\tpop rax\n\n");          
  }
  
  /* int b = 0; */
  /* int c = 0; */
  /* for(b = 0; code[b][c]; b++){ */
  /*   for(c = 0; code[b][c]; c++){ */
  /*     codegen(code[b][c]); */
  /*     printf("\tpop rax\n\n");       */
  /*   } */
  /* } */

  // epilogue
  printf("\tmov rsp, rbp\n");
  printf("\tpop rbp\n");
  printf("\tret\n\n");
}
