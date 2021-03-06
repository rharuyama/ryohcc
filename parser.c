#include "ryohcc.h"
bool at_eof(Token*);

int new_offset = 0;

Node* new_node(NodeKind kind, Node* lhs, Node* rhs){
  Node* newNode = calloc(1, sizeof(Node));
  newNode->kind = kind;
  newNode->lhs = lhs;
  newNode->rhs = rhs;
  return newNode;
}

Node* new_node_num(NodeKind kind, int val){
  Node* newNode = calloc(1, sizeof(Node));
  newNode->kind = kind;
  newNode->val = val;
  return newNode;
}

Node* new_node_lvar(int offset){
  Node* newNode = calloc(1, sizeof(Node));
  newNode->kind = ND_LVAR;
  newNode->offset = offset;
  return newNode;
}

LVar* new_lvar(char* name, int len, int offset){
  LVar* newLvar = calloc(1, sizeof(LVar));
  newLvar->next = locals;
  newLvar->name = name;
  newLvar->len = len;
  newLvar->offset = offset;
  return newLvar;
}

void reg(Token* tok){    
  locals = new_lvar(tok->data, tok->len, new_offset + 8);  
  new_offset += 8;
}

bool isin(Token* tok){
  LVar* pl = locals;
  if(pl == NULL){
    return false;
  }else{
    while(pl){
      if((strcmp(tok->data, pl->name)) == 0){
        return true;
      }else{
        pl = pl->next;
      }
    }
    return false;
  }    
}

int offset_value(Token* tok){
  int offset = locals->offset;
  LVar* pl = locals;

  while(pl){
    if((strcmp(tok->data, pl->name)) == 0){
      offset = pl->offset;
    }else{
      pl = pl->next;
    }
  }

  return offset;
}

void push_prog(Prog** ptop, Node* node, bool separator){
  Prog* newProg = calloc(1, sizeof(Prog));
  newProg->node = node;
  newProg->next = *ptop;
  newProg->separator = separator;
  *ptop = newProg;
}

void skip(char* s, int n, Node* node, bool push){
  if(strncmp(top->data, s, n) == 0){
    top = top->next;
    if(push){
      push_prog(&prog, node, false);
    }
  }
}

Node* add();

Node* primary(){
  if(strcmp(top->data, "(") == 0){
    top = top->next;
    Node* node = add();
    if(strcmp(top->data, ")") == 0){
      top = top->next;
      return node;
    }
    fprintf(stderr, "There is no close parenthesis😭 -- primary()\n");
    exit(1);
  }

  if(isalpha(top->data[0])){ // 変数名の頭しかチェックしていない
    int offset;    
    if(isin(top)){
      offset = offset_value(top);
      Node* node = new_node_lvar(offset);
      top = top->next;
      return node;
    }
    reg(top);
    offset = (top->data[0] - '`') * 8; // ofsett of 'a' = 8, of 'b' = 16 ...
    Node* node = new_node_lvar(offset);
    top = top->next;  
    return node;
  }else if(isdigit(top->data[0])){  
    if(top->kind != TK_NUM){
      fprintf(stderr, "Not a number😭\n");
    }
    Node* node = new_node_num(ND_NUM, top->val);
    top = top->next;
    return node;
  }else{
    fprintf(stderr, "Error in primary() in parser.c: [%s]😭\n", top->data);    
    Node* node = new_node_lvar(8);
    top = top->next;
    return node;
  }
}

Node* unary(){
  if(strcmp(top->data, "+") == 0){
    top = top->next;
    Node* zero = new_node_num(ND_NUM, 0);
    Node* node = new_node(ND_ADD, zero, primary());
    return node;

  }else if(strcmp(top->data, "-") == 0){
    top = top->next;
    Node* zero = new_node_num(ND_NUM, 0);
    Node* node = new_node(ND_SUB, zero, primary());
    return node;
  }else{
    Node* node = primary();
    return node;
  }
}

Node* mul(){
  Node* node = unary();

  while(1){
    if(strcmp(top->data, "*") == 0){
      top = top->next;
      node = new_node(ND_MUL, node, unary());
      
    }else if(strcmp(top->data, "/") == 0){
      top = top->next;
      node = new_node(ND_DIV, node, unary());
      
    }else{
      return node;
    }
  }
}

Node* add(){
  Node* node = mul();

  while(1){
    if(strcmp(top->data, "+") == 0){
      top = top->next;
      node = new_node(ND_ADD, node, mul());
      
    }else if(strcmp(top->data, "-") == 0){
      top = top->next;
      node = new_node(ND_SUB, node, mul());
      
    }else{
      return node;
    }
  }
}

Node* relational(){
  Node* node = add();

  while(1){
    if(strcmp(top->data, "<=") == 0){
      top = top->next;
      node = new_node(ND_REQ, node, add());

    }else if(strcmp(top->data, ">=") == 0){
      top = top->next;
      node = new_node(ND_REQ, add(), node);

    }else if(strcmp(top->data, "<") == 0){
      top = top->next;
      node = new_node(ND_REL, node, add());

    }else if(strcmp(top->data, ">") == 0){
      top = top->next;
      node = new_node(ND_REL, add(), node);
      
    }else{
      return node;
    }
  }
}

Node* equality(){
  Node* node = relational();

  while(1){
    if(strcmp(top->data, "==") == 0){
      top = top->next;
      node = new_node(ND_EQU, node, relational());

    }else if(strcmp(top->data, "!=") == 0){
      top = top->next;
      node = new_node(ND_NEQ, node, relational());
      
    }else{
      return node;
    }
  }
}

Node* assign(){
  Node* node = equality();

  while(1){
    if(strcmp(top->data, "=") == 0){
      top = top->next;
      node = new_node(ND_ASS, node, assign());

    }else{
      return node;
    }
  }
}

Node* expr(){
  return assign();
}

bool in_if = true;

Node* stmt(){
  Node* node;

  if(strncmp(top->data, "return", 6) == 0){    
    top = top->next;
    node = new_node(ND_RETURN, expr(), NULL);
    skip(";", 1, node, in_if); // push? == false

  }else if(strncmp(top->data, "if", 2) == 0){
    in_if = false;
    top = top->next;
    if(strncmp(top->data, "(", 1) > 0){
      fprintf(stderr, "No open parenthesis on if statement\n");
      exit(1);
    }
    top = top->next;
    node = new_node(ND_IF, NULL, NULL);
    node->cond = expr();
    if(strncmp(top->data, ")", 1) > 0){
      fprintf(stderr, "No close parenthesis on if statement\n");
      exit(1);
    }
    top = top->next;
    node->then = stmt();
    if(strncmp(top->data, "else", 4) == 0){
      top = top->next;
      node->els = stmt();
    }
    push_prog(&prog, node, false);
    
  }else{
    node = expr();
    skip(";", 1, node, in_if);
  }
  
  return node;
}

void program(){
  while(!at_eof(top)){
    stmt();
  }
}
