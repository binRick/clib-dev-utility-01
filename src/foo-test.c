#include <stdio.h>
#include <bar/bar.h>
#include <foo.h>

int main(int argc, char *argv[]) { 
  (void)argc; 
  (void)argv; 
  fprintf(stdout, "%s\n", "OK");
  return foo(bar(0)); 
}
