# Copyright (c) 2015 Adys Tech
# Author: Adarsha (mvadu)
CC = gcc
CFLAGS = -std=gnu99 -lrt -lm
DEPS = pi_2_mmio.h common_dht_read.h pi_2_dht_read.h
objects = pi_2_mmio.o common_dht_read.o pi_2_dht_read.o

#make predefined:
#$@ =

#tell make that each .o depends on .c and .h included in DEPS
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# The default rule - compiling our main program:
all:	dht_get pin_on pin_off
		echo all: make complete

dht_get: dht_get.o $(objects)
	$(CC) -o $@ $+ $(CFLAGS)

pin_on: pin_on.o $(objects)
	$(CC) -o $@ $+ $(CFLAGS)

pin_off: pin_off.o $(objects)
	$(CC) -o $@ $+ $(CFLAGS)

.PHONY: clean
clean:
	rm *.o
