.intel_syntax noprefix
.globl main
main:	
	push rbp
	mov rbp, rsp
	
	mov QWORD PTR [rbp-8], 42
	mov rax, QWORD PTR [rbp-8]

	pop rbp

	ret
