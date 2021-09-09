#include "ryohcc.h"

Node* code[100];
int code_idx = 0;
Prog* prog = NULL;

int main(int argc, char** argv){
  char* input = argv[1];
  locals = NULL;

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  top = tokenizer(input); // Token* top にトークンの列がセットされる
  
  // parser
  program();

  // prorogue
  printf("\tpush rbp\n");
  printf("\tmov rbp, rsp\n");
  printf("\tsub rsp, 208\n\n");

  // reverse prog
  Prog* prog_in_order = NULL;
  while(prog){
    push_prog(&prog_in_order, prog->node, false);
    prog = prog->next;
  }

  while(prog_in_order){
    codegen(prog_in_order->node);
    printf("\tpop rax\n\n");
    prog_in_order = prog_in_order->next;
  }

  // epilogue
  printf("\tmov rsp, rbp\n");
  printf("\tpop rbp\n");
  printf("\tret\n\n");
}
