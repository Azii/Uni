BIN = scheduler

#missing AllTests.cpp
SRC = \
	benchmark.c \
	Queue.c \
	main.c \
	task.c \
	LCFS.c \
	RR.c \
	SJN.c \
	MLF.c

CC	     = cc
CFLAGS   = -g -Wall -Wextra -Werror -O2
LFLAGS   = -lm

GDB    = gdb
RM     = rm -f

OBJS = $(SRC:%.c=%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

# pull in dependencies for .o files
-include $(OBJS:.o=.d)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
	$(CC) -MM $(CFLAGS) $*.c > $*.d

debug: $(BIN)
	$(GDB) ./$(BIN)

run: $(BIN)
	./$(BIN)

clean:
	$(RM) $(BIN) $(OBJS) *.d

.PHONY: clean debug run
