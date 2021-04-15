#include <stdio.h>
#include <stdlib.h>

void codegen(char* src){
  FILE* assem = fopen("assem.s", "w");

  fputs(".intel_syntax noprefix\n", assem);
  fputs(".globl main\n", assem);
  fputs("main:\n", assem);
  
  fputs("    mov rax, " , assem);
  fputs(parser(src), assem);
  fputs("\n", assem);

  fputs("    ret\n", assem);

  fclose(assem);
}

