#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

#include "biblioteca_primitivas.h" // archivo de la biblioteca

#define SHM_KEY 0x1234
#define MAX_MESSAGE_SIZE 65535

// Estructura para la memoria compartida
typedef struct {
    int active;
    char message[MAX_MESSAGE_SIZE];
} SharedMemorySegment;

void client_function() {
    int shm_id;
    SharedMemorySegment* shm_ptr;

    // Obtener el ID del segmento de memoria compartida
    shm_id = shmget(SHM_KEY, sizeof(SharedMemorySegment), 0644 | IPC_CREAT);
    if (shm_id == -1) {
        perror("shmget");
        exit(1);
    }

    // Adjuntar el segmento de memoria compartida
    shm_ptr = (SharedMemorySegment*)shmat(shm_id, NULL, 0);
    if (shm_ptr == (void*)-1) {
        perror("shmat");
        exit(1);
    }

    // Esperar a que el segmento est� disponible
    while (shm_ptr->active != 0) {
        sleep(1);
    }

    // Escribir el mensaje en la memoria compartida
    printf("Ingrese el mensaje para el eco: ");
    fgets(shm_ptr->message, MAX_MESSAGE_SIZE, stdin);
    shm_ptr->active = 1; // Indicar que hay un mensaje nuevo

    // Esperar la respuesta del servidor
    while (shm_ptr->active != 0) {
        sleep(1);
    }

    // Mostrar el eco recibido
    printf("Eco recibido: %s", shm_ptr->message);

    // Desconectar del segmento de memoria compartida
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Eliminar el segmento de memoria compartida
    if (shmctl(shm_id, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
}
