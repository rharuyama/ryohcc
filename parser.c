typedef enum{
  ND_MUL,
  ND_DIV,
  ND_ADD,
  ND_SUB,
  ND_NUM,
}NodeKind;

typedef struct Node Node;
struct Node{
  NodeKind kind;
  Node* lhs;
  Node* rhs;
  int val;
};

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

Node* primary(Token* cur){
  int val = cur->val;
  Node* newNode = new_node_num(ND_NUM, val);
  return newNode;
}

Node* mul(Token* cur){
  Node* node = primary(cur);

  while(1){
    if(cur->next->kind == TK_EOF){
      return node;
      
    }else if(cur->next->kind == TK_RESERVED &&
	     strcmp(cur->next->data, "*") == 0){
      cur = cur->next;
      Node* rhs = primary(cur->next);
      node = new_node(ND_MUL, node, rhs);
      cur = cur->next;
      
    }else if(cur->next->kind == TK_RESERVED &&
	     strcmp(cur->next->data, "/") == 0){
      cur = cur->next;
      Node* rhs = primary(cur->next);
      node = new_node(ND_DIV, node, rhs);
      cur = cur->next;
      
    }else{
      return node; // This function will not omit error
    }
  }
}

Node* expr(Token* cur){
  Node* node = mul(cur);

  while(1){
    if(cur->next->kind == TK_EOF){
      return node;
      
    }else if(cur->next->kind == TK_RESERVED &&
	     strcmp(cur->next->data, "+") == 0){
      cur = cur->next;
      Node* rhs = mul(cur->next);
      node = new_node(ND_ADD, node, rhs);
      cur = cur->next;
      
    }else{
      return node; // This function will not omit error
    }
  }
}

Node* parser(){
  Token* cur = top;

  Node* root = expr(cur); // 6

  return root;
}


