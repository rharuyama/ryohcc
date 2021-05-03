.intel_syntax noprefix
.globl main
main:
   push 2

   push 5

   pop rdi
   pop rax
   imul rax, rdi
   push rax

   push 9

   pop rdi
   pop rax
   sub rax, rdi
   push rax

   pop rax
   ret
