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

Node* expr();

Node* primary(){
  if(strcmp(top->data, "(") == 0){
    top = top->next;
    Node* node = expr();
    if(strcmp(top->data, ")") == 0){
      top = top->next;
      return node;
    }
    fprintf(stderr, "no close parenthesis");
    exit(1);
  }
  
  Node* node = new_node_num(ND_NUM, top->val);
  top = top->next;
  return node;
}

Node* mul(){
  Node* node = primary();

  while(1){
    if(strcmp(top->data, "*") == 0){
      top = top->next;
      node = new_node(ND_MUL, node, primary());
      
    }else if(strcmp(top->data, "/") == 0){
      top = top->next;
      node = new_node(ND_DIV, node, primary());
      
    }else{
      return node;
    }
  }
}

Node* expr(){
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


