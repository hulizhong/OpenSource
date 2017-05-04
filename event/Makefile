all : 0.1test

0.1test : 0.1-event-test.c
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent -L ./libevent -levent

clean:
	rm *.o  0.1test -f

