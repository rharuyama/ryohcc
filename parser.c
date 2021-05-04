typedef enum{
  ND_NUM,
  ND_MUL,
  ND_DIV,
  ND_ADD,
  ND_SUB,
  ND_REQ,
  ND_REL,
  ND_EQU,
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

Node* add();

Node* primary(){
  if(strcmp(top->data, "(") == 0){
    top = top->next;
    Node* node = add();
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
  Node* node = unary(); // unary()

  while(1){
    if(strcmp(top->data, "*") == 0){
      top = top->next;
      node = new_node(ND_MUL, node, unary()); // unary()
      
    }else if(strcmp(top->data, "/") == 0){
      top = top->next;
      node = new_node(ND_DIV, node, unary()); // unary()
      
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
      
    }else{
      return node;
    }
  }
}

Node* expr(){
  return equality();
}

