	.intel_syntax noprefix
	.globl main
main:
	push 30

	push 43

	call plus

	ret

plus:
	pop rbp // save return address
	
	pop rdi

	pop rsi
	
	add rsi, rdi
	mov rax, rsi

	push rbp
	
	ret
