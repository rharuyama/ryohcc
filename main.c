#include "ryohcc.h"

int main(int argc, char** argv){
  char* input = argv[1];

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  top = tokenizer(input); // Token* top にトークンの列がセットされる
  //  show_tokens();

  // parser
  program();
  Node* root = code[code_idx - 1];

  //  dump_test(root);
  
  codegen(root);

  printf("   pop rax\n");
  printf("   ret\n");
}
