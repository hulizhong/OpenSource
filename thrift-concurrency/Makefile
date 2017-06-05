posixthread := Thread.h PosixThreadFactory.cpp Mutex.cpp Monitor.cpp

goal := posixthread
all : $(goal)

posixthread : $(posixthread)
	gcc -shared $? -o libposixthread.so


clean:
	rm *.o $(goal) -f

