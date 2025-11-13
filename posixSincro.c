#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

#define MAX_BUFFERS 5

// Declaraciones globales (las mismas del código original)
char buf[MAX_BUFFERS][100];
int buffer_index;
int buffer_print_index;

pthread_mutex_t buf_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buf_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t spool_cond = PTHREAD_COND_INITIALIZER;
int buffers_available = MAX_BUFFERS;
int lines_to_print = 0;

// Prototipos de funciones
void *producer(void *arg);
void *spooler(void *arg);

int main(int argc, char **argv) {
    // El resto del código main permanece igual...
}
