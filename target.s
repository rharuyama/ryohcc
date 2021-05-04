.intel_syntax noprefix
.globl main
main:
   push 1

   push 38

   push 0

   pop rdi
   pop rax
   imul rax, rdi
   push rax

   pop rdi
   pop rax
   cmp rax, rdi
   setle al
   movzx rax, al
   push rax

   pop rax
   ret
