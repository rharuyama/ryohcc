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

Node* ntop;

Node* fun(Token* cur){
  Node* newNode3 = malloc(sizeof(Node));
  newNode3->kind = ND_NUM;
  newNode3->val = cur->next->val;
  return newNode3;
}

void parser(){
  fprintf(stderr, "I CAN SEE GLOBAL VAR top! WORKS FINE! %d\n", top->val);

  Token* cur = top;
  Node* newNode = malloc(sizeof(Node));
  newNode->kind = ND_NUM;
  int val = cur->val; // これがないとセグフォになる（なぜ？）
  newNode->val = val;

  return; // 以降でコンパイルは通るがCodegenがうまくいかない（次，なぜか調べる）
  Token* next = cur->next;
  cur = next;

  Node* newNode2 = malloc(sizeof(Node));
  newNode2->kind = ND_MUL;
  newNode2->lhs = newNode;
  newNode2->rhs = fun(cur);
}


