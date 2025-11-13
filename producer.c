#include "shared.h"

int main() {
    // Crear semáforos
    sem_t *vacio = sem_open("/vacio", O_CREAT, 0644, BUFFER_SIZE);
    sem_t *lleno = sem_open("/lleno", O_CREAT, 0644, 0);
    
    if (vacio == SEM_FAILED || lleno == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // Crear memoria compartida
    int shm_fd = shm_open("/memoria_compartida", O_CREAT | O_RDWR, 0644);
    if (shm_fd < 0) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }
    
    // Configurar tamaño de la memoria compartida
    if (ftruncate(shm_fd, sizeof(compartir_datos)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    // Mapear memoria compartida
    compartir_datos *compartir = mmap(NULL, sizeof(compartir_datos), 
                                     PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (compartir == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Inicializar estructura
    compartir->entrada = 0;
    compartir->salida = 0;

    printf("Productor: Iniciando producción...\n");

    // Producir 10 items
    for (int i = 1; i <= 10; i++) {
        sem_wait(vacio);  // Esperar si el buffer está lleno
        
        compartir->bus[compartir->entrada] = i;
        printf("Productor: Produce %d en posición %d\n", i, compartir->entrada);
        compartir->entrada = (compartir->entrada + 1) % BUFFER_SIZE;
        
        sem_post(lleno);  // Señalar que hay un nuevo item
        sleep(1);  // Simular tiempo de producción
    }

    printf("Productor: Finalizada la producción\n");

    // Limpieza
    munmap(compartir, sizeof(compartir_datos));
    close(shm_fd);
    sem_close(vacio);
    sem_close(lleno);
    
    return 0;
}
