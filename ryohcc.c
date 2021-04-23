#include <stdio.h>
#include <stdlib.h>

typedef struct Token Token;
struct Token{
  int val;
  char* data;
  Token* next;
};

int main(int argc, char** argv){
  char* input = argv[1]; // "42 * 7"

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  // tokenizer
  char* p = input;
  Token* newTok = malloc(sizeof(Token));
  newTok->val = strtol(p, &p, 10);

  printf("   mov rax, %d\n", newTok->val);

  printf("   ret\n");
}
