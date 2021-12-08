CC=cc
CFLAGS=-std=c99
CFLAGS+=-W -Wall
CFLAGS+=-O3
CFLAGS+=-g -ggdb
CFLAGS+=-I ./deps/clibs/module
LDLIBS= -ldl -lm
LDFLAGS= 

SRCS=src/foo-test.c src/foo.c src/bar/bar.c
TARGETS=src/foo-test libfoo.a libbar.a

libbar.a: src/bar/bar.o
libfoo.a: src/foo.o
src/foo-test: src/foo-test.o libfoo.a libbar.a

TEST_SUITE=src/foo-test

.DEFAULT_GOAL=all
.PHONY: all
all: $(TARGETS)

SRC_DIR ?= $(patsubst %/,%, $(dir $(abspath $(firstword $(MAKEFILE_LIST)))))
CFLAGS+=-I$(SRC_DIR)/include

.PHONY: clean
clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)
	$(RM) $(DEPS)
ifneq ($(SRC_DIR), $(CURDIR))
	-@rmdir $(OBJDIRS)
endif

.PHONY: test
test: $(TEST_SUITE)
	$(CURDIR)/$(TEST_SUITE)

#SRCS=$(notdir $(wildcard $(SRC_DIR)src/*.c))
OBJS=$(SRCS:.c=.o)
DEPS=$(OBJS:.o=.d)

# Object file subdirectories
ifneq ($(SRC_DIR), $(CURDIR))
vpath %.c $(SRC_DIR)

OBJDIRS=$(filter-out $(CURDIR)/, $(sort $(dir $(abspath $(OBJS)))))
$(OBJDIRS): ; @mkdir $@
$(DEPS): | $(OBJDIRS)
$(OBJS): | $(OBJDIRS)
endif

-include $(DEPS)

# implicit rules for building archives not parallel safe (e.g. make -j 3)
%.a: ; ar rcs $@ $^

