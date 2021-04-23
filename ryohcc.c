#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  int val = atoi(argv[1]);
  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");
  printf("   mov rax, %d\n", val);
  printf("   ret\n");
}
