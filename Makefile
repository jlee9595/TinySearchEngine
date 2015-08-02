# crawler.makefile
CC = gcc
CFLAGS = -Wall -pedantic -std=c11
LDFLAGS = -lcurl

EXEC = crawler
OBJS = crawler.o hashtable.o web.o
SRCS = crawler.c common.h hashtable.c hashtable.h web.c web.h


$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) $(LDFLAGS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS) 
