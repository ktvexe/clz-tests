CC ?= gcc
CFLAGS_common ?= -Wall -std=gnu99 -g -DDEBUG
CFLAGS_iteration = -O0
CFLAGS_binary  = -O0
CFLAGS_byte  = -O0
CFLAGS_harlay  = -O0
CFLAGS_recursive  = -O0
ifeq ($(strip $(PROFILE)),1)
CFLAGS_common += -Dcorrect
endif
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
	$(CC) $(CFLAGS_common) $(CFLAGS_harley) \
		-o $@ -Dharley $(SRCS_common) $@.c

recursive: $(SRCS_common) recursive2.c clz.hpp
	gcc  $(CFLAGS_common) $(CFLAGS_recursive) \
		-o $@ -Drecursive $(SRCS_common) $@2.c

run:$(EXEC)
	taskset -c 1 ./iteration 100000000 100016384
	taskset -c 1 ./binary 100000000 100016384
	taskset -c 1 ./byte 100000000 100016384
	taskset -c 1 ./recursive 100000000 100016384
	taskset -c 1 ./harley 100000000 100016384

plot:iteration.txt iteration.txt binary.txt byte.txt harley.txt
	gnuplot scripts/runtime.gp


.PHONY: clean
clean:
	$(RM) $(EXEC) *.o *.txt *.png
