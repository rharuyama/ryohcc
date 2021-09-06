#include "ryohcc.h"

void codegen(Node* root){
  if(root->kind == ND_NUM){
    printf("\tpush %d\n\n", root->val);

  }else if(root->kind == ND_MUL){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\timul rax, rdi\n");
    printf("\tpush rax\n\n");
    
  }else if(root->kind == ND_DIV){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tcqo\n");
    printf("\tidiv rax, rdi\n");
    printf("\tpush rax\n\n");
    
  }else if(root->kind == ND_ADD){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tadd rax, rdi\n");
    printf("\tpush rax\n\n");
    
  }else if(root->kind == ND_SUB){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tsub rax, rdi\n");
    printf("\tpush rax\n\n");
    
  }else if(root->kind == ND_REQ){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tcmp rax, rdi\n");
    printf("\tsetle al\n");
    printf("\tmovzx rax, al\n");
    printf("\tpush rax\n\n");

  }else if(root->kind == ND_REL){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tcmp rax, rdi\n");
    printf("\tsetl al\n");
    printf("\tmovzx rax, al\n");
    printf("\tpush rax\n\n");

  }else if(root->kind == ND_EQU){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tcmp rax, rdi\n");
    printf("\tsete al\n");
    printf("\tmovzx rax, al\n");
    printf("\tpush rax\n\n");

  }else if(root->kind == ND_NEQ){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("\tpop rdi\n");
    printf("\tpop rax\n");
    printf("\tcmp rax, rdi\n");
    printf("\tsetne al\n");
    printf("\tmovzx rax, al\n");
    printf("\tpush rax\n\n");

  }else if(root->kind == ND_ASS){
    codegen(root->rhs);
    if(root->lhs->kind != ND_LVAR){
      fprintf(stderr, "left hand side in assignment is not variable: ");
      fprintf(stderr, "%d where\n", root->lhs->kind);
      fprintf(stderr, "ND_NUM = %d\n", ND_NUM);
      fprintf(stderr, "ND_MUL = %d\n", ND_MUL);
      fprintf(stderr, "ND_DIV = %d\n", ND_DIV);
      fprintf(stderr, "ND_ADD = %d\n", ND_ADD);
      fprintf(stderr, "ND_SUB = %d\n", ND_SUB);      
    }
    printf("\tpop rax\n");
    printf("\tmov QWORD PTR [rbp-%d], rax\n\n", root->lhs->offset);

  }else if(root->kind == ND_LVAR){
    printf("\tpush [rbp-%d]\n\n", root->offset);

  }else if(root->kind == ND_RETURN){
    codegen(root->lhs);
    printf("\tpop rax\n");
    printf("\tmov rsp, rbp\n");
    printf("\tpop rbp\n");
    printf("\tret\n\n");

  }else if(root->kind == ND_IF){
    if(root->els == NULL){
      codegen(root->cond);
      printf("\tpop rax\n");
      printf("\tcmp rax, 0\n");
      printf("\tje .Lend000\n");
      codegen(root->then);
      printf(".Lend000:\n\n");
    }else{
      codegen(root->cond);
      printf("\tpop rax\n");
      printf("\tcmp rax, 0\n");      
      printf("\tje .Lelse000\n");
      codegen(root->then);
      printf("\tjmp .Lend000\n");
      printf(".Lelse000:\n");
      codegen(root->els);
      printf(".Lend000:\n\n");      
    }
    
  }else{
    printf("// ERROR HERE in codegen");
  }
}
