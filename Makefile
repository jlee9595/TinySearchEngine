# crawler.makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11
LDFLAGS = -lcurl

EXEC = crawler
OBJS = crawler.o hashtable.o web.o list.o
SRCS = crawler.c hashtable.c web.c list.c hashtable.h web.h list.h common.h 


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(EXEC) $(OBJS) $(LDFLAGS) 
