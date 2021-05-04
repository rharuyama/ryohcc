.intel_syntax noprefix
.globl main
main:
   push 0

   push 3

   pop rdi
   pop rax
   sub rax, rdi
   push rax

   push 0

   push 5

   pop rdi
   pop rax
   add rax, rdi
   push rax

   pop rdi
   pop rax
   imul rax, rdi
   push rax

   push 0

   push 1

   pop rdi
   pop rax
   sub rax, rdi
   push rax

   pop rdi
   pop rax
   imul rax, rdi
   push rax

   pop rax
   ret
