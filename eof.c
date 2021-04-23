#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
  // printf("%d\n", atoi(argv[1]));
  char* p = argv[1];
  while(1){
    unsigned long len = strlen(p);
    printf("%lu\n", len);
    if(len == 0){
      break;
    }
    p++;
  }
  return 0;
}
