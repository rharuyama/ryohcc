#include "ryohcc.h"

void codegen(Node* root){
  if(root->kind == ND_NUM){
    printf("   push %d\n\n", root->val);

  }else if(root->kind == ND_MUL){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   imul rax, rdi\n");
    printf("   push rax\n\n");
    
  }else if(root->kind == ND_DIV){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   cqo\n");
    printf("   idiv rax, rdi\n");
    printf("   push rax\n\n");
    
  }else if(root->kind == ND_ADD){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   add rax, rdi\n");
    printf("   push rax\n\n");
    
  }else if(root->kind == ND_SUB){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   sub rax, rdi\n");
    printf("   push rax\n\n");
    
  }else if(root->kind == ND_REQ){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   cmp rax, rdi\n");
    printf("   setle al\n");
    printf("   movzx rax, al\n");
    printf("   push rax\n\n");

  }else if(root->kind == ND_REL){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   cmp rax, rdi\n");
    printf("   setl al\n");
    printf("   movzx rax, al\n");
    printf("   push rax\n\n");

  }else if(root->kind == ND_EQU){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   cmp rax, rdi\n");
    printf("   sete al\n");
    printf("   movzx rax, al\n");
    printf("   push rax\n\n");

  }else if(root->kind == ND_NEQ){
    codegen(root->lhs);
    codegen(root->rhs);
    printf("   pop rdi\n");
    printf("   pop rax\n");
    printf("   cmp rax, rdi\n");
    printf("   setne al\n");
    printf("   movzx rax, al\n");
    printf("   push rax\n\n");

  }else if(root->kind == ND_ASS){
    codegen(root->rhs);
    if(root->lhs->kind != ND_LVAR){
      fprintf(stderr, "left hand side in assignment is not variable");
    }
    printf("   pop rax\n");
    printf("   mov QWORD PTR [rbp-8], rax\n\n");

  }else if(root->kind == ND_LVAR){
    printf("   push [rbp-8]\n\n");
    
  }else{
    printf("// ERROR HERE in codegen");
  }
}

void dump_as_Sexp(Node* root){
  if(root->kind == ND_NUM){
    fprintf(stderr, "%d ", root->val);
    
  }else if(root->kind == ND_MUL){
    fprintf(stderr, "(");
    fprintf(stderr, "* ");
    dump_as_Sexp(root->lhs);
    dump_as_Sexp(root->rhs);
    fprintf(stderr, ") ");
    
  }else if(root->kind == ND_DIV){
    fprintf(stderr, "(");
    fprintf(stderr, "/ ");
    dump_as_Sexp(root->lhs);
    dump_as_Sexp(root->rhs);
    fprintf(stderr, ") ");
    
  }else if(root->kind == ND_ADD){
    fprintf(stderr, "(");
    fprintf(stderr, "+ ");
    dump_as_Sexp(root->lhs);
    dump_as_Sexp(root->rhs);
    fprintf(stderr, ") ");

  }else if(root->kind == ND_SUB){
    fprintf(stderr, "(");
    fprintf(stderr, "- ");
    dump_as_Sexp(root->lhs);
    dump_as_Sexp(root->rhs);
    fprintf(stderr, ") ");
    
  }else{
    fprintf(stderr, "ERROR in dump_as_Sexp");    
  }
}

void dump_test(Node* root){
  dump_as_Sexp(root);
  fprintf(stderr, "\n");
}


