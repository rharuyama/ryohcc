.intel_syntax noprefix
.globl main
main:	
	push rbp
	mov rbp, rsp
	sub rsp,208
	
	mov QWORD PTR [rbp-8], 3 // a = 3;
	mov QWORD PTR [rbp-16], 4 // b = 4;

	// a + b;
	push [rbp-8]
	push [rbp-16]

	pop rax
	pop rdi
	add rax, rdi
	push rax

	pop rax

	mov rsp, rbp
	pop rbp
	ret
