ryohcc:
	clang -o ryohcc main.c ryohcc.c parser.c tokenizer.c -g

target: ryohcc
	clang -o target target.s

test: clean ryohcc
	bash test.sh

clean:
	rm -rf ryohcc target *.s *.out
