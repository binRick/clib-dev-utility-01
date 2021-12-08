#include <stdio.h>
#include <bar/bar.h>
#include <foo.h>

#define LOG_LEVEL   DEBUG
#include "seethe.h"
#define DEBUG_COLOUR    ""
#define INFO_COLOUR     "\x1B[36m"
#define NOTICE_COLOUR   "\x1B[32;1m"
#define WARNING_COLOUR  "\x1B[33m"
#define ERROR_COLOUR    "\x1B[31m"
#define CRITICAL_COLOUR "\x1B[41;1m"

#define DISPLAY_COLOUR  1
#define DISPLAY_TIME    0
#define DISPLAY_LEVEL   0
#define DISPLAY_FUNC    0
#define DISPLAY_FILE    0
#define DISPLAY_LINE    0
#define DISPLAY_BORDER  1
#define DISPLAY_MESSAGE 1
#define DISPLAY_ENDING  1
#define DISPLAY_RESET   1


int main(int argc, char *argv[]) { 
  (void)argc; 
  (void)argv; 
  char *msg[100];
  sprintf(msg,"%s","Running Tests");
  info(msg);
  sprintf(msg,"%s","OK");
  info(msg);
  return foo(bar(0)); 
}
