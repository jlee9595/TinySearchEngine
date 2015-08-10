# crawler.makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11


EXEC = indexer
OBJS = indexer.o hashtable.o web.o file.o
SRCS = indexer.c hashtable.c web.c file.c hashtable.h web.h file.h


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) 

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(EXEC) $(OBJS)

clean: 
	rm -f *.o
	rm -f *.dat

