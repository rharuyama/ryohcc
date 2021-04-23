#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum{
  TK_RESERVED,
  TK_NUM,
  TK_EOF,
}TokenKind;

typedef struct Token Token;
struct Token{
  int val;
  char* data;
  TokenKind kind;
  Token* next;
};

Token* top;

void tokenizer(char* input){
  // tokenizer
  char* p = input;
  Token* newTok = malloc(sizeof(Token));
  top = newTok;
  newTok->val = strtol(p, &p, 10);
  newTok->kind = TK_NUM;

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
  newTok2->kind = TK_RESERVED;
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
  newTok3->kind = TK_RESERVED;
}

int main(int argc, char** argv){
  char* input = argv[1]; // "5 * 20"

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  tokenizer(input);

  
  printf("   mov rax, %d\n", top->val);
  printf("   ret\n");
  
  // print Tokens for testing
  fprintf(stderr, "%d ", top->val);
  top = top->next;
  fprintf(stderr, "%s ", top->data);
  top = top->next;
  fprintf(stderr, "%d ", top->val);
  // top = top->next; // SIGBUS
  fprintf(stderr, "\n");
}
