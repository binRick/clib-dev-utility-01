#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <bar/bar.h>
#include <foo.h>

#include "ms/ms.h"
#include "closure/closure.c"

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

#include "bench/bench.c"
#include <math.h>

#define CLOG_SHORT_MACROS 1
#include "clog/clog.h"
#include "clog/clog.c"
#include "cflag/cflag.h"
#include "timer/timer.h"
#include "timer/timer.c"

#include "termcolor-c/termcolor-c.h"
#define LOG_COLOR (1) // 0: off, 1: on, default: 1
#define LOG_LEVEL (7) // -1: off, 0~7: different log levels, default: 7

#include "lwlog/lwlog.h"



struct state {
  int count;
};

void * callback(void * ctx, void * arg){
  if (ctx == NULL) return NULL;
  struct state * state = (struct state *)ctx;
  state->count++; // increment invocation counter

  printf("callback has been called %d times, Message was '%s'\n", state->count, (char*) arg);
  return NULL;

}






void example_benchmark() {
    BENCHMARK(example_bench, 1)

    FILE *file;
    file = fopen("/etc/passwd", "r");
    fclose(file);

    END_BENCHMARK(example_bench)
    BENCHMARK_SUMMARY(example_bench);
}


void example_measure() {
    MEASURE(example_measure)

    FILE *file;
    file = fopen("/etc/passwd", "r");
    fclose(file);

    END_MEASURE(example_measure)
    MEASURE_SUMMARY(example_measure);


    clog_init(NULL);

    cmessage("Message :]");
    cinfo("Some info");
    cwarning("Some warning");
    puts("Normal output");
    cdebug("Some debugging");
    cerror("Some error");


}


int main(int argc, char *argv[]) { 
  (void)argc; 
  (void)argv; 


	timer_t timer;
	printf("Timer started\n");

	timer_start(&timer);
	usleep(1e6);
	timer_pause(&timer);

	printf("Delta (us): %ld\n", timer_delta_us(&timer));
	printf("Delta (ms): %ld\n", timer_delta_ms(&timer));
	printf("That should be around 1 second\n\n");

	timer_unpause(&timer);
	usleep(5e5);
	timer_pause(&timer);

	printf("Delta (us): %ld\n", timer_delta_us(&timer));
	printf("Delta (ms): %ld\n", timer_delta_ms(&timer));
	printf("And that should add to 1.5 seconds\n\n");


  char *msg[100];
  sprintf(msg,"%s","Running Tests");
  info(msg);
  sprintf(msg,"%s","OK");
  info(msg);
  example_benchmark();
 // example_measure();
  struct state state = {
    .count = 0,
  };

  closure_t cb = closure_new(callback, &state);

  closure_call(cb, "Hello World!!");
  closure_call(cb, "Lorem");
  closure_call(cb, "Ipsum ...");
  closure_call(cb, "You Get the picture.");

  printf("Our callback was called %d times\n", state.count);


    fputs("Hello, colorful world\n", text_green(stdout));
    fputs("Hello, colorful world\n", text_underline(stdout));
    fputs("Hello, colorful world\n", text_bold(stdout));
    fputs("Hello, colorful world\n", text_dark(stdout));
    reset_colors(stdout);
    fputs("Hello, colorful world\n", background_white(text_red(stdout)));
    reset_colors(stdout);



    lwlog_emerg("This a emerge log.");
    lwlog_alert("This a alert log.");
    lwlog_crit("This a crit log.");
    lwlog_err("This a err log.");
    lwlog_warning("This a warning log.");
    lwlog_notice("This a notice log.");
    lwlog_info("This a info log.");
    lwlog_debug("This a debug log.");

  return foo(bar(0)); 
}
