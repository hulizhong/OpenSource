0.1_event := 0.1-event_test.c
0.7c_event := 0.7c-event_test.c
0.7c_signal := 0.7c-signal_test.c
0.7c_time := 0.7c-time_test.c
0.8_event := 0.8-event_test.c
215_event_fifo := 215-event_fifo.c
215_signal := 215-signal.c
215_time := 215-time.c

goal := 0.1_event 0.7c_event 0.7c_signal 0.7c_time 0.8_event 215_event_fifo 215_signal 215_time
all : $(goal)

0.1_event : $(0.1_event)
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent -L ./libevent -levent


0.7c_event : $(0.7c_event)
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent -L ./libevent -levent
0.7c_signal : $(0.7c_signal)
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent -L ./libevent -levent
0.7c_time : $(0.7c_time)
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent -L ./libevent -levent


0.8_event : $(0.8_event)
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent -L ./libevent -levent


215_event_fifo : $(215_event_fifo)
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent/include -L ./libevent/.libs -levent -Wl,-rpath=/home/OSPL/event/libevent/.libs/
	###Dont use -Wl,rpath. 
	###/a/b/c/libxx.so, lib path was /a/b/c/ not /a/b /a ..
215_signal : $(215_signal) 
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent/include -L ./libevent/.libs -levent -Wl,-rpath=/home/OSPL/event/libevent/.libs/
215_time : $(215_time)
	gcc -ggdb3 -O0 $? -o $@ -I ./libevent/include -L ./libevent/.libs -levent -Wl,-rpath=/home/OSPL/event/libevent/.libs/

clean:
	rm *.o $(goal) -f

