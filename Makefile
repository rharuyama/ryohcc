ryohcc:
	clang -o .ryohcc ryohcc.c

target: ryohcc
	clang -o .target target.s

test: ryohcc
	bash test.sh
