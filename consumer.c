#include "shared.h"

int main() {
    // Abrir semáforos existentes
    sem_t *vacio = sem_open("/vacio", 0);
    sem_t *lleno = sem_open("/lleno", 0);
    
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Abrir memoria compartida existente
    int fd_compartido = shm_open("/memoria_compartida", O_RDWR, 0644);
    if (fd_compartido < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    // Mapear memoria compartida
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos), 
                                     PROT_READ | PROT_WRITE, MAP_SHARED, fd_compartido, 0);
    if (compartir == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    compartir->salida = 0;
    printf("Consumidor: Iniciando consumo...\n");

    // Consumir 10 items
    for (int i = 1; i <= 10; i++) {
        sem_wait(lleno);  // Esperar si el buffer está vacío
        
        int item = compartir->bus[compartir->salida];
        printf("Consumidor: Consume %d de posición %d\n", item, compartir->salida);
        compartir->salida = (compartir->salida + 1) % BUFFER_SIZE;
        
        sem_post(vacio);  // Señalar que hay un espacio vacío
        sleep(2);  // Simular tiempo de consumo
    }

    printf("Consumidor: Finalizado el consumo\n");

    // Limpieza
    munmap(compartir, sizeof(compartir_datos));
    close(fd_compartido);
    sem_close(lleno);
    sem_close(vacio);
    
    return 0;
}
