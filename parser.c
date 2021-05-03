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

Node* primary(){
  Node* node = new_node_num(ND_NUM, top->val);
  top++;
  return node;
}

Node* mul(){
  Node* node = primary();
  return node;
}

Node* expr(){
  Node* node = mul();
  return node;
}

Node* parser(){
  Node* root = expr(); // 6

  return root;
}


