.intel_syntax noprefix
.globl main
main:
   push 6

   push 5

   pop rdi
   pop rax
   add rax, rdi
   push rax

   push 4

   push 3

   pop rdi
   pop rax
   add rax, rdi
   push rax

   pop rdi
   pop rax
   imul rax, rdi
   push rax

   pop rax
   ret
