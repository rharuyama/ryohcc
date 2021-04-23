#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

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

void tokenizer(char* p){
  Token* newTok = malloc(sizeof(Token));
  Token* cur = newTok;
  top = newTok;
  newTok->val = strtol(p, &p, 10);
  fprintf(stderr, "%d\n", newTok->val);
  newTok->kind = TK_NUM;

  while(1){
    if(isspace(*p)){
      p++;
      continue;     
    }else if(*p == '*'){
      Token* newTok2 = malloc(sizeof(Token));
      newTok2->data = "*";
      fprintf(stderr, "%s\n", newTok2->data);
      newTok2->kind = TK_RESERVED;
      cur->next = newTok2;
      cur = cur->next;
      p++;
    }else if(isdigit(*p)){
      Token* newTok3 = malloc(sizeof(Token));
      newTok3->val = strtol(p, &p, 10);
      fprintf(stderr, "%d\n", newTok3->val);
      newTok3->kind = TK_NUM;
      cur->next = newTok3;
      cur = cur->next;
    }else{
      // ひとまず上記以外のパターンは無視するが，これで良いのだろうか？
      break;
    }
  }
}
