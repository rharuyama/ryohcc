ryohcc:
	clang -o .ryohcc ryohcc.c -g

target: ryohcc
	clang -o .target target.s

test: ryohcc clean
	bash test.sh

clean:
	rm -rf .ryohcc .target *.s
