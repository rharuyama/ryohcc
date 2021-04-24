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
  Node* newNode3 = new_node_num(ND_NUM, val);
  return newNode3;
}

Node* parser(){
  Token* cur = top;

  Node* newNode = primary(cur); // 6

  // if(cur->next->kind == TK_RESERVED && cur->next->data == '*')

  cur = cur->next; // *

  Node* tmp_root = new_node(ND_MUL, newNode, primary(cur = cur->next)); // 5

  cur = cur->next; // * 

  Node* tmp_root2 = new_node(ND_MUL, tmp_root, primary(cur->next));  // 4

  return tmp_root2;
}


