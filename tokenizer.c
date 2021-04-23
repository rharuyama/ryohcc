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
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <fcntl.h>

Token* new_token(TokenKind kind, Token* next, int val, char* str){
  Token* pnew_tok = malloc(sizeof(Token));
  pnew_tok->kind = kind;
  pnew_tok->next = next;
  pnew_tok->val = val;
  pnew_tok->str = str;
  return pnew_tok;
}

Token* tokenizer(char* source_file){
  unsigned char buf[4096];

  int fd = open(source_file, O_RDONLY);
  int tmp_errno = errno;
  if(fd < 0){
    fprintf(stderr, "cannot open %s: %s\n", source_file, strerror(tmp_errno));
    exit(1);
  }
  int nread = read(fd, buf, sizeof(buf));

  char* p = (char*)buf;
  Token* ptop = NULL;
  Token* cur = ptop;
  for(int i = 1; i <= nread-1; i++){
    if(isspace(*p)){
      p++;
      continue;
    }

    if(isdigit(*p)){
      while(cur){
	cur = cur->next;
      }
      int val = strtol(p, &p, 10);
      cur = new_token(TK_NUM, NULL, val, NULL);
      printf("%d\n", cur->val);
      continue;
    }

    if(*p == '*'){
      while(cur){
	cur = cur->next;
      }
      cur = new_token(TK_RESERVED, NULL, 0, "*");
      printf("%s\n", cur->str);
      p++;
      continue;
    }

    if(*p == '/'){
      while(cur){
	cur = cur->next;
      }
      cur = new_token(TK_RESERVED, NULL, 0, "/");
      printf("%s\n", cur->str);
      p++;
      continue;
    }

    if(*p == EOF){
      break;
    }

    fprintf(stderr, "invalid token: %c\n", *p);
    exit(1);
  }

  close(fd);
  return ptop;
}

int main(){
  tokenizer("source");
}

