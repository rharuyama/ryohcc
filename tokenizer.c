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

bool at_eof(Token* cur){
  if(cur->kind == TK_EOF){
    return 1;
  }else{
    return 0;
  }
}

void show_tokens(){
  Token* cur = top;
  fprintf(stderr, "--> %d\n", cur->val);
  cur = cur->next;

  while(1){
    if(cur->kind == TK_RESERVED){
      fprintf(stderr, "--> %s\n", cur->data);
      cur = cur->next;
      continue;
    }

    if(cur->kind == TK_NUM){
      fprintf(stderr, "--> %d\n", cur->val);
      cur = cur->next;
      continue;
    }

    if(cur->kind == TK_EOF){
      fprintf(stderr, "--> EOF\n");
      break;
    }
  }
}

Token* new_token(TokenKind kind, Token* cur, char* data){
  Token* newTok = calloc(1, sizeof(Token));
  newTok->kind = kind;
  newTok->data = data;
  cur->next = newTok;
  return newTok;
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

    if(isdigit(*p)){
      cur = new_token(TK_NUM, cur, p);
      cur->val = strtol(p, &p, 10);
      continue;
    }

    fprintf(stderr, "cannot tokenize\n");
    exit(1);
  }

  new_token(TK_EOF, cur, "\0");
  return head.next;
}
