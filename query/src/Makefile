CC = gcc
CFLAGS = -Wall -pedantic -std=c11


EXEC = query
OBJS = query.o hashtable.o invertedIndex.o list.o  
SRCS = query.c hashtable.c invertedIndex.c list.c hashtable.h invertedIndex.h list.h

UTILDIR=../../util/
UTILFLAG=-ltseutil
UTILLIB=$(UTILDIR)libtseutil.a
UTILC=$(UTILDIR)file.c $(UTILDIR)web.c
UTILH=$(UTILDIR)file.h $(UTILDIR)web.h

#$(EXEC): $(OBJS) $(UTILLIB)
#	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

$(EXEC): $(OBJS) $(UTILLIB)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS) -L$(UTILDIR) $(UTILFLAG)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) -c $(SRCS)

debug: $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -c $(SRCS)
	$(CC) $(CFLAGS) -g -ggdb -o $(EXEC) $(OBJS) -L$(UTILDIR) $(UTILFLAG)

$(UTILLIB): $(UTILC) $(UTILH)
	cd $(UTILDIR); make

test: $(SRCS)
	$(CC) $(CFLAGS) -ggdb -c $(UTILDIR)file.c $(UTILDIR)web.c hashtable.c invertedIndex.c list.c $(UTILDIR)file.h $(UTILDIR)web.h hashtable.h invertedIndex.h list.h
	$(CC) $(CFLAGS) -ggdb -o queryengine_test queryengine_test.c $(UTILDIR)file.o $(UTILDIR)web.o hashtable.o invertedIndex.o list.o

clean:
	rm -f *.o
	rm -f *.log
