CFLAGS:=-march=native -O2 -pipe -ggdb -std=gnu99
cc = gcc

objs=quicksort.o randomcreate.o

quicksort:$(objs)
	$(cc) $(CFLAGS) -o quicksort $(objs)

quicksort.o:quicksort.c
randomcreate.o:randomcreate.h randomcreate.c

clean:
	rm quicksort *.o
