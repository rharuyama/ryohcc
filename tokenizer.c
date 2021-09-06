#include "ryohcc.h"

Token* top;

bool at_eof(Token* cur){
  if(cur->kind == TK_EOF){
    return 1;
  }else{
    return 0;
  }
}

Token* new_token(TokenKind kind, Token* cur, char* data){
  Token* newTok = calloc(1, sizeof(Token));
  newTok->kind = kind;
  newTok->data = data;
  cur->next = newTok;
  return newTok;
}

bool is_alnum(char c){
  return  ('a' <= c && c <= 'z')
      ||  ('A' <= c && c <= 'Z')  
      ||  ('0' <= c && c <= '9')
      ||  (c == '_');
}

Token* tokenizer(char* p){
  Token head;
  head.next = NULL;
  Token* cur = &head;

  while(*p){
    if(isspace(*p)){
      p++;
      continue;
    }

    if(*p == '*'){
      cur = new_token(TK_RESERVED, cur, "*");
      p++;
      continue;
    }

    if(*p == '/'){
      cur = new_token(TK_RESERVED, cur, "/");
      p++;
      continue;
    }

    if(*p == '+'){
      cur = new_token(TK_RESERVED, cur, "+");
      p++;
      continue;
    }

    if(*p == '-'){
      cur = new_token(TK_RESERVED, cur, "-");
      p++;
      continue;
    }

    if(*p == '('){
      cur = new_token(TK_RESERVED, cur, "(");
      p++;
      continue;
    }

    if(*p == ')'){
      cur = new_token(TK_RESERVED, cur, ")");
      p++;
      continue;
    }

    if(*p == '<' && *(p+1) == '='){
      cur = new_token(TK_RESERVED, cur, "<=");
      p = p + 2;
      continue;
    }

    if(*p == '>' && *(p+1) == '='){
      cur = new_token(TK_RESERVED, cur, ">=");
      p = p + 2;
      continue;
    }

    if(*p == '<'){
      cur = new_token(TK_RESERVED, cur, "<");
      p++;
      continue;
    }

    if(*p == '>'){
      cur = new_token(TK_RESERVED, cur, ">");
      p++;
      continue;
    }

    if(*p == '=' && *(p + 1) == '='){
      cur = new_token(TK_RESERVED, cur, "==");
      p = p + 2;
      continue;
    }

    if(*p == '!' && *(p + 1) == '='){
      cur = new_token(TK_RESERVED, cur, "!=");
      p = p + 2;
      continue;
    }

    if(*p == '='){
      cur = new_token(TK_RESERVED, cur, "=");
      p++;
      continue;
    }

    if(strncmp(p, "return", 6) == 0 ){
      cur = new_token(TK_RETURN, cur, "return");
      p = p + 6;
      continue;
    }

    if(strncmp(p, "if", 2) == 0){
      cur = new_token(TK_RESERVED, cur, "if");
      p += 2;
      continue;
    }

    if( ('a' <= *p && *p <= 'z' ) || ('A' <= *p && 'Z' <= *p) ){
      int cnt = 1;
      while( ('a' <= *(p + cnt) && *(p + cnt) <= 'z' ) 
          || ('A' <= *(p + cnt) && *(p + cnt) <= 'Z' )
          || ('0' <= *(p + cnt) && *(p + cnt) <= '9' ) ){
        cnt++;
      }

      cur = new_token(TK_IDENT, cur, p);
      cur->len = cnt;
      p += cnt;
      continue;
    }

    if(isdigit(*p)){
      cur = new_token(TK_NUM, cur, p);
      cur->val = strtol(p, &p, 10);
      continue;
    }

    if(*p == ';'){
      cur = new_token(TK_RESERVED, cur, ";");
      p++;
      continue;
    }

    fprintf(stderr, "cannot tokenize\n");
    exit(1);
  }

  new_token(TK_EOF, cur, "\0");
  return head.next;
}
