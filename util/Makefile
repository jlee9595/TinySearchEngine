CC = gcc
CFLAGS = -Wall -pedantic -std=c11


EXEC = libtseutil.a
OBJS = file.o web.o
#SRCS = invertedIndex.c list.c hashtable.c  invertedIndex.h list.h hashtable.h common.h
SRCS = file.c web.c file.h web.h 
$(EXEC): $(OBJS)
	ar -cvq libtseutil.a *.o

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)


debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)

clean:
	 rm *.o
