/*envían sus mensajes al coordinador indicando el tipo (directo o difusión) 
mediante etiquetas (tags) de MPI, 
y reciben los mensajes dirigidos a ellos.
*/

#include "../include/wrapped_mpi.h"
#include "../include/message.h"
#include "../include/coordinator.h"
#include "../include/client.h"

#include <stdio.h>
#include <string.h>

//Tabla de usernames
static const char* usernames[] = {
    "Sasha", "Karina", "Amber", "Wendy"
};

void contacto_en_linea(int rank){
    if (rank < 1 || rank > N_USERS) {
        printf("Rank %d no es un cliente válido\n", rank);
        return;
    }
    send_string((char*) usernames[rank - 1], COORDINATOR, STATISTICS_TAG);
}


void tipo_mensaje(){
    //Que el usuario elija el tipo de mensaje (directo o difusión)
}

void escribir_mensaje(){
    //Que el usuario escriba un mensaje
    //Limitar la longitud del mensaje a MAX_MESSAGE 50
    printf("Escribe tu mensaje (máximo %d caracteres): ", MAX_MESSAGE);
    char mensaje[MAX_MESSAGE];
    if (fgets(mensaje, MAX_MESSAGE, stdin) == NULL) {
        printf("Error al leer mensaje\n");
    }
}

void mensaje_rand(){
    
}

void esperar_mensaje(char* text, int length, int source, int tag){
    //Esperar a recibir un mensaje dirigido a este cliente
    receive_string(text, length, source, tag);
    printf("Esperando mensaje, espera activa");
    //Mostrar el mensaje recibido al usuario
}

void protocol_run(){

}

