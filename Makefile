ryohcc:
	clang -o .ryohcc ryohcc.c -g

target: ryohcc
	clang -o .target target.s

test: ryohcc
	bash test.sh
