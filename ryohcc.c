#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "tokenizer.c"
#include "parser.c"

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

int main(int argc, char** argv){
  char* input = argv[1]; // "5 * 20"

  printf(".intel_syntax noprefix\n");
  printf(".globl main\n");
  printf("main:\n");

  tokenizer(input); // Token* top にトークンの列がセットされる
  show_tokens();

  // parser
  Node* root = parser();

  dump_test(root);
  
  codegen(root);

  printf("   pop rax\n");
  printf("   ret\n");
}
