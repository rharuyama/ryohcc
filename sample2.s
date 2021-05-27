.intel_syntax noprefix
.globl main
main:
	push rbp
	mov rbp, rsp
	sub rsp, 208
	
	// a = 3 + 4;
	push 3
	push 4

	pop rax
	pop rdi
	add rax, rdi
	push rax

	mov QWORD PTR [rbp-8], rax

	// b = 5
	mov QWORD PTR [rbp-16], 5

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
