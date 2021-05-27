#include <stdio.h>

int main(){
    char s[10];
    char a = 'a';
    sprintf(s, "%c", a);
    printf("%s\n", s);
}