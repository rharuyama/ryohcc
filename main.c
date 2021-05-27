#include "ryohcc.h"

int main(int argc, char** argv){
  char* input = argv[1];

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  top = tokenizer(input); // Token* top にトークンの列がセットされる
 // show_tokens();

  // parser
  program();
  Node* root = code[code_idx - 1];

 // dump_test(root);

  // prorogue
  printf("  push rbp\n");
  printf("  mov rbp, rsp\n");
  printf("  sub rsp, 208\n\n");
  
  for(int i = 0; code[i]; i++){
    codegen(code[i]);
    printf("  pop rax\n");
  }

  // epilogue
  printf("  mov rsp, rbp\n");
  printf("  pop rbp\n");
  printf("  ret\n");
}
