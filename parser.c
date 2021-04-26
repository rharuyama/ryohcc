typedef enum{
  ND_MUL,
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
    }
  }
}

Node* parser(){
  Token* cur = top;

  Node* newNode = mul(cur); // 6

  return newNode;
}


