#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>

#define MAX_PDU_SIZE 65535
#define DATA_MAX_SIZE (MAX_PDU_SIZE - sizeof(MessageHeader))

// Estructura de la cabecera del mensaje
typedef struct {
    unsigned char pattern[1]; // Patron de inicio
    unsigned int destination; // PAS + PID destino
    unsigned int source;      // PAS + PID origen
    unsigned short length;    // Longitud del mensaje
    unsigned char type[2];    // Tipo y control de fragmentacion
} MessageHeader;

// Estructura del mensaje completo
typedef struct {
    MessageHeader header;
    char data[DATA_MAX_SIZE]; // Datos del mensaje
} Message;

// Prototipos de funciones para las primitivas de servicio
void A_Conectar_peticion(int writeid, const char* cliente_id, const char* servidor_id, int modo_conexion, int tipo_transferencia);
void A_Conectar_indicacion(int readid, char* cliente_id, char* servidor_id, int* modo_conexion, int* tipo_transferencia);
void A_Conectar_respuesta(int writeid, int confirmacion);
void A_Conectar_confirmacion(int readid, int* confirmacion);
void A_Transferir_peticion(int writeid, const char* datos, size_t tamano_datos);
void A_Transferir_indicacion(int readid, char* datos, size_t* tamano_datos);
void A_Transferir_respuesta(int writeid, int confirmacion);
void A_Transferir_confirmacion(int readid, int* confirmacion);
void A_Desconectar_peticion(int writeid);
void A_Desconectar_indicacion(int readid);
void A_Desconectar_respuesta(int writeid, int confirmacion);
void A_Desconectar_confirmacion(int readid, int* confirmacion);

// La implementación de las primitivas se desarrollará proximamente. 
// En esta práctica se diseña la estructura y se realiza un esqueleto del código.

