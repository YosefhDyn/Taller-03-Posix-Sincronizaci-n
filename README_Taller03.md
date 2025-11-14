# 🧵 Taller 03 – Sincronización POSIX  
### Semáforos POSIX • Memoria Compartida • Pthreads • Buffer Circular

Este repositorio contiene la implementación completa del **Taller 03 de Sincronización POSIX**, cuyo objetivo es aplicar distintos mecanismos de concurrencia y comunicación en sistemas UNIX/Linux.

## 📁 Estructura del repositorio
```
├── producer.c
├── consumer.c
├── shared.h
├── posixSincro.c
├── Makefile
└── README.md
```

## 🧩 Actividad 1 – Semáforos POSIX + Memoria Compartida
Implementación del problema productor–consumidor utilizando:
- semáforos POSIX (`sem_open`, `sem_wait`, `sem_post`)
- memoria compartida (`shm_open`, `mmap`)
- buffer circular

## 🔄 Actividad 2 – Pthreads + Mutex + Condiciones
Implementación multihilo utilizando:
- creación de hilos (`pthread_create`)
- exclusión mutua (`pthread_mutex_t`)
- sincronización con condiciones (`pthread_cond_t`)
- buffer circular de cadenas

## 🛠 Compilación
```
make
```

## ▶️ Ejecución
```
make run-both
./posixSincro
```

## 🧹 Limpieza
```
make clean
make clean-sem
```

## 📄 Informe
Incluye informe en Word sobre el taller.
