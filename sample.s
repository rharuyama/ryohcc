.intel_syntax noprefix
.globl main
main:	
	mov rbp, rsp
	
	mov QWORD PTR [rbp-8], 42
	mov rax, QWORD PTR [rbp-8]

	ret
