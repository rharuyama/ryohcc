.intel_syntax noprefix
.globl main
main:
   push 7

   push 5

   push 2

   pop rdi
   pop rax
   imul rax, rdi
   push rax

   pop rdi
   pop rax
   add rax, rdi
   push rax

   pop rax
   ret
