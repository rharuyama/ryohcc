#include "tokenizer.c"
#include "parser.c" 
#include "codegen.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){
  codegen(argv[1]);
  return 0;
}
