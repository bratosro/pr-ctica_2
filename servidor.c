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

void server_function() {
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

    // Servidor en bucle infinito para procesar mensajes
    while (1) {
        // Esperar a que haya un mensaje nuevo
        while (shm_ptr->active != 1) {
            sleep(1);
        }

        // Procesar el mensaje
        printf("Mensaje recibido: %s", shm_ptr->message);
        // Aqu� se puede agregar l�gica adicional para procesar el mensaje

        // Enviar eco al cliente
        shm_ptr->active = 0; // Indicar que el mensaje ha sido procesado

        // Opcional: detener el servidor despu�s de procesar un mensaje
        // break;
    }

    // Desconectar del segmento de memoria compartida
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(1);
    }
}

int main() {
    server_function();
    return 0;
}