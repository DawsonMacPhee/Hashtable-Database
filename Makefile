CFLAGS = -std=c99 -Wall -pedantic
CC = gcc

all: buildidx key2val val2key actors bacon1

debug: buildidx.c util.o hashfn.o
	$(CC) $(CFLAGS) buildidx.c util.o hashfn.o -o buildidx -DDEBUG

util.o: util.c
	$(CC) $(CFLAGS) -c util.c -o util.o

hashfn.o: hashfn.c
	$(CC) $(CFLAGS) -c hashfn.c -o hashfn.o

buildidx.o: buildidx.c
	$(CC) $(CFLAGS) -c buildidx.c -o buildidx.o

buildidx: buildidx.o util.o hashfn.o
	$(CC) $(CFLAGS) buildidx.o util.o hashfn.o -o buildidx

key2val.o: key2val.c
	$(CC) $(CFLAGS) -c key2val.c -o key2val.o

key2val: key2val.o util.o hashfn.o
	$(CC) $(CFLAGS) key2val.o util.o hashfn.o -o key2val

val2key.o: val2key.c
	$(CC) $(CFLAGS) -c val2key.c -o val2key.o

val2key: val2key.o util.o hashfn.o
	$(CC) $(CFLAGS) val2key.o util.o hashfn.o -o val2key

actors.o: actors.c
	$(CC) $(CFLAGS) -c actors.c -o actors.o

actors: actors.o util.o hashfn.o
	$(CC) $(CFLAGS) actors.o util.o hashfn.o -o actors

bacon1.o: bacon1.c
	$(CC) $(CFLAGS) -c bacon1.c -o bacon1.o

bacon1: bacon1.o util.o hashfn.o
	$(CC) $(CFLAGS) bacon1.o util.o hashfn.o -o bacon1

clean:
	rm util.o hashfn.o buildidx.o buildidx key2val.o key2val val2key.o val2key actors.o actors bacon1.o bacon1

removeKV:
	rm *.khs *.vhs