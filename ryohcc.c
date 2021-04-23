#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Token Token;
struct Token{
  int val;
  char* data;
  Token* next;
};

int main(int argc, char** argv){
  char* input = argv[1]; // "5 * 20"

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  // tokenizer
  char* p = input;
  Token* newTok = malloc(sizeof(Token));
  Token* top = newTok;
  newTok->val = strtol(p, &p, 10);

  while(1){
    if(isspace(*p)){
      p++;
    }else{
      break;
    }
  }

  Token* newTok2 = malloc(sizeof(Token));
  newTok->next = newTok2;
  newTok2->data = "*";
  p++;

  while(1){
    if(isspace(*p)){
      p++;
    }else{
      break;
    }
  }

  Token* newTok3 = malloc(sizeof(Token));
  newTok2->next = newTok3;
  newTok3->val = strtol(p, &p, 10);
 
  // print Tokens for testing
  fprintf(stderr, "%d ", top->val);
  top = top->next;
  fprintf(stderr, "%s ", top->data);
  top = top->next;
  fprintf(stderr, "%d ", top->val);
  // top = top->next; // SIGBUS
  fprintf(stderr, "\n");

  printf("   mov rax, %d\n", newTok->val);

  printf("   ret\n");
}
