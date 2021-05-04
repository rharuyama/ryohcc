.intel_syntax noprefix
.globl main
main:
   push 5

   push 7

   pop rdi
   pop rax
   cmp rax, rdi
   setle al
   movzx rax, al
   push rax

   pop rax
   ret
