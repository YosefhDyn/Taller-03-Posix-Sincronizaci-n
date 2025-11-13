#ifndef SHARED_H
#define SHARED_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

typedef struct {
    int bus[BUFFER_SIZE];
    int entrada;
    int salida;
} compartir_datos;

#endif
