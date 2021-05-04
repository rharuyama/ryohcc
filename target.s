.intel_syntax noprefix
.globl main
main:
   push 83

   push 83

   pop rdi
   pop rax
   cmp rax, rdi
   sete al
   movzx rax, al
   push rax

   pop rax
   ret
