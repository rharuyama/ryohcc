#include <stdio.h>
#include <stdlib.h>

void gen_body(Node* node, FILE* assem){
  if(node->kind == ND_NUM){
    fprintf(assem, "    push %d\n", node->val);
    return;
  }
  
  gen_body(node->lhs, assem);
  gen_body(node->rhs, assem);

  fprintf(assem, "    pop rdi\n");
  fprintf(assem, "    pop rax\n");

  switch(node->kind){
  /* case ND_ADD: */
  /*   fputs("    add rax, rdi\n"); */
  /*   break; */
  /* case ND_SUB: */
  /*   fputs("    sub rax, rdi\n"); */
  /*   break; */
  case ND_MUL:
    fprintf(assem, "    imul rax, rdi\n");
    break;
  case ND_DIV:
    fprintf(assem, "    cqo\n");
    fprintf(assem, "    idiv rdi\n");
    break;
  }
  fprintf(assem, "    push rax\n");
}

void codegen(char* source_file){
  FILE* assem = fopen("assem.s", "w");

  fputs(".intel_syntax noprefix\n", assem);
  fputs(".globl main\n", assem);
  fputs("main:\n", assem);
  
  fputs("    mov rax, " , assem);
  //Token* tok = parser(source_file);
  //fputs(tok->val, assem);
  Node* parse_tree_root = parser(source_file);
  gen_body(parse_tree_root, assem);

  fputs("    ret\n", assem);

  fclose(assem);
}

