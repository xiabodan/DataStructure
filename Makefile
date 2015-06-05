all: example 

CXXFLAGS=	-c -g -O0 -fPIC
CC=gcc

OBJS_SERVER=	example.o xiabodan_list.o xiabodan_stack.o xiabodan_queue.o  xiabodan_recursion.o xiabodan_sorting.o
LIBS_SERVER=    -lpthread


.c.o:
	$(CC) $(CXXFLAGS) $<

example: $(OBJS_SERVER)
	$(CC) -o $@ $^ $(LIBS_SERVER)


clean:
	rm -f *.o
	rm -f example


	

