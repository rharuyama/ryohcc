#include "max_token_length.h"

// トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
};

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Token* new_token(TokenKind kind, Token* next, int val, char* str){
  Token* pnew_tok = malloc(sizeof(Token));
  pnew_tok->kind = kind;
  pnew_tok->next = next;
  pnew_tok->val = val;
  pnew_tok->str = str;
  return pnew_tok;
}

Token* tokenizer(char* source_file){
  FILE* source = fopen(source_file, "r");

  char target[MAX_TOKEN_LENGTH];

  memset(target, 0, MAX_TOKEN_LENGTH);
  
  fread(target,
	sizeof(char),
	sizeof(target) / sizeof(target[0]),
	source);

  // tokenizing here
  char* p = target;
  Token* ptop = NULL;
  Token* cur = ptop;
  while(p){
    if(isspace(*p)){
      p++;
      
    }else if(isdigit(*p)){
      while(cur){
	cur = cur->next;
      }
      int val = strtol(p, &p, 10);      
      cur = new_token(TK_NUM, NULL, val, NULL);
      printf("%d\n", cur->val);
      //p++;
      
    }else if(*p == '*'){
      while(cur){
	cur = cur->next;
      }
      cur = new_token(TK_RESERVED, NULL, 0, "*");
      printf("%s\n", cur->str);
      p++;
      
    }else if(*p == '/'){
      while(cur){
	cur = cur->next;
      }
      cur = new_token(TK_RESERVED, NULL, 0, "/");
      printf("%s\n", cur->str);
      p++;
     
    }else if(p == NULL){
      break;
      
    }else{
      fprintf(stderr, "invalid token: %c\n", *p);
      exit(1);
    }
  }

  //return 0; //　後で return ptopに直し，Parserの帰り型をToken＊にする
}

int main(){
  tokenizer("source");
}
