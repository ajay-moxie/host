CC=gcc
OBJECTS= host_communication.o main.o serial_windows.o slave.o wifi_windows.o
DEPS= host_communication.h serial_windows.h slave.h host_commands.h wifi_windows.h config.h
CFLAGS=-I -lws2_32
LIB=-lws2_32

all:	host.exe
host.exe:	$(OBJECTS)
	$(CC) -o host.exe $(OBJECTS) $(LIB)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

typedeftest:	types-test.c typedef.h
	$(CC) -o typedeftest.exe types-test.c

config_wifi:
	cp config/wifi.config config.h

config_serial:
	cp config/serial.config config.h

client: client.c
	$(CC) -o client.exe client.c -lws2_32

server: server.c
	$(CC) -o serv.exe server.c -lws2_32
clean:
	rm -f $(OBJECTS) *.exe config.h
