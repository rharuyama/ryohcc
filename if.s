.intel_syntax noprefix
.globl main
main:
	push rbp
	mov rbp, rsp
	sub rsp, 208

	push 3

	push 3

	pop rdi
	pop rax
	cmp rax, rdi
	sete al
	movzx rax, al
	push rax

	// ^ code compiled from A
	// add from here; if (A) B
	pop rax

	cmp rax, 0
	je .Lend000

	push 88 // < code compiled from B

.Lend000:
	// add until here

	pop rax
	
	mov rsp, rbp
	pop rbp
	ret

