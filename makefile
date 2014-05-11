CC=gcc
OBJECTS= host_communication.o main.o serial_windows.o slave.o
DEPS= host_communication.h serial_windows.h slave.h host_commands.h
CFLAGE=-I

all:	host.exe
host.exe:	$(OBJECTS)
	$(CC) -o host.exe $(OBJECTS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

typedeftest:	types-test.c typedef.h
	$(CC) -o typedeftest.exe types-test.c
clean:
	rm -f $(OBJECTS) *.exe
