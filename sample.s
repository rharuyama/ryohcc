	.intel_syntax noprefix
	.globl main
main:
	push 7

	call nop // push continuation, jump into nop

	pop rax
	
	ret

nop:
	push rbp //
	mov rbp, rsp // open

	// instruction here

	mov rsp, rbp // close
	pop rbp //

	ret // pop the continuation, jump into there
