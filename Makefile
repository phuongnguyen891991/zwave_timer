
TIMER_LIB = ./lib
LIB_SRC = lib/currTime.c lib/initial_timer.c lib/vnode.c lib/utils.c lib/linked_list.c

CC = gcc
CFLAGS= -I. -Wall -s -lrt
LOCAL_SRCS = timer_stack_final.c

all: timer_stack_final
timer_stack_final: 
	$(CC) -o $@ $(LOCAL_SRCS) $(LIB_SRC) $(CFLAGS) -lpthread

clean:
	rm -f *.o timer_stack_final
