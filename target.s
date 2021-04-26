.intel_syntax noprefix
.globl main
main:
   push 6

   push 5

   pop rdi
   pop rax
   imul rax, rdi
   push rax

   push 5

   pop rdi
   pop rax
   cqo
   idiv rax, rdi
   push rax

   push 3

   pop rdi
   pop rax
   cqo
   idiv rax, rdi
   push rax

   pop rax
   ret
