CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99 -g -DDEBUG
CFLAGS_iteration = -O0
CFLAGS_binary  = -O0
CFLAGS_byte  = -O0
CFLAGS_recursive  = -Wall -std=gnu99 -g -DDEBUG -O0

EXEC = iteration binary byte recursive harley
all: $(EXEC)

SRCS_common = main.c

iteration: $(SRCS_common) iteration.c clz.h
	$(CC) $(CFLAGS_common) $(CFLAGS_iteration) \
		-o $@ -Diteration $(SRCS_common) $@.c

binary: $(SRCS_common) binary.c clz.h
	$(CC) $(CFLAGS_common) $(CFLAGS_binary) \
		-o $@ -Dbinary $(SRCS_common) $@.c

byte: $(SRCS_common) byte.c clz.h
	$(CC) $(CFLAGS_common) $(CFLAGS_byte) \
		-o $@ -Dbyte $(SRCS_common) $@.c

harley: $(SRCS_common) harley.c clz.h
	$(CC) $(CFLAGS_common) $(CFLAGS_byte) \
		-o $@ -Dharley $(SRCS_common) $@.c

recursive: $(SRCS_common) recursive.c clz.hpp
	gcc  $(CFLAGS_recursive) \
		-o $@ -Drecursive $(SRCS_common) $@.c

run:$(EXEC)
	./iteration
	./binary
	./byte
	./recursive

.PHONY: clean
clean:
	$(RM) $(EXEC) *.o
