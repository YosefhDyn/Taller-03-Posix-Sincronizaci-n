CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -pthread
TARGETS = producer consumer posixSincro
SOURCES = producer.c consumer.c posixSincro.c
HEADERS = shared.h

all: $(TARGETS)

producer: producer.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $< -lrt

consumer: consumer.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $< -lrt

posixSincro: posixSincro.c
	$(CC) $(CFLAGS) -o $@ $< -lrt

clean:
	rm -f $(TARGETS) *.o

clean-sem:
	rm -f /dev/shm/sem.vacio /dev/shm/sem.lleno
	rm -f /dev/shm/memoria_compartida

run-producer: producer
	./producer

run-consumer: consumer
	./consumer

run-both: producer consumer
	./producer & ./consumer &

.PHONY: all clean clean-sem run-producer run-consumer run-both