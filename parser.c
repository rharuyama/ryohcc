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

Node* fun(Token* cur){
  int val = cur->val;
  Node* newNode3 = new_node_num(ND_NUM, val);
  return newNode3;
}

Node* parser(){
  Token* cur = top;

  Node* newNode = malloc(sizeof(Node));
  newNode->kind = ND_NUM;
  int val = cur->val; // これがないとセグフォになる（なぜ？）
  newNode->val = val;

  cur = cur->next;

  Node* newNode2 = new_node(ND_MUL, newNode, fun(cur->next));

  return newNode2;
}


