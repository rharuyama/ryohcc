.intel_syntax noprefix
.globl main
main:
   push 13

   push 17

   pop rdi
   pop rax
   cmp rax, rdi
   setl al
   movzx rax, al
   push rax

   pop rax
   ret
