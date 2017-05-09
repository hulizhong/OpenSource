0.1_event := 0.1-event_test.c
0.7c_event := 0.7c-event_test.c
0.7c_signal := 0.7c-signal_test.c
0.7c_time := 0.7c-time_test.c
0.8_event := 0.8-event_test.c

goal := 0.1_event 0.7c_event 0.7c_signal 0.7c_time 0.8_event
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

clean:
	rm *.o $(goal) -f

