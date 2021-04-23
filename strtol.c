#include <stdlib.h>
#include <stdio.h>
#include <errno.h>    /* ERANGEを使用するために必要 */
#include <limits.h>   /* LONG_MAXとLONG_MINを使用するために必要 */

int main(void)
{
	char s[128], *e;
	long n;
	int base;
	
	printf("何進数で変換しますか。");
	scanf("%d", &base);
	printf("変換する数値を入力してください。");
	scanf("%s", s);
	
	n = strtol(s, &e, base);
	
	if (errno != ERANGE) {
		printf("変換数値＝%ld\n", n);
		if (*e != '\0') {
			printf("変換不可能部分＝%s\n", e);
			printf("%d文字目の\'%c\'が変換不可\n", e-s+1, *e);
		}
	}
	else if (n == LONG_MAX)
		printf("long値で表現できる値を上回りました。\n");
	else if (n == LONG_MIN)
		printf("long値で表現できる値を下回りました。\n");
	
	return 0;
}
