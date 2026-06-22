/*envían sus mensajes al coordinador indicando el tipo (directo o difusión) 
mediante etiquetas (tags) de MPI, 
y reciben los mensajes dirigidos a ellos.
*/

#include "../include/wrapped_mpi.h"
#include "../include/message.h"
#include "../include/coordinator.h"
#include "../include/client.h"
#include "../include/utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
    printf("Escribe un mensaje (máximo %d caracteres): ", MAX_MESSAGE);
    char mensaje[MAX_MESSAGE];
    if (fgets(mensaje, MAX_MESSAGE, stdin) == NULL) {
        printf("Error al leer mensaje\n");
    }
}

void message_rand(char *buf, int max_len){
    int length = 3 + rand() % (max_len - 3);
    for (int i = 0; i < length; i++) {
        buf[i] = 'a' + (rand() % 26);
    }
    buf[length] = '\0';
}

void send_message_CLI(Messages *sms){
    message_rand(sms->text, MAX_MESSAGE);

    send_string(sms->text, COORDINATOR, MESSAGE_TAG);
}

void esperar_mensaje(Messages *sms){
    //Esperar a recibir un mensaje dirigido a este cliente
    receive_string(sms->text, sizeof(sms->text),sms->sender, MESSAGE_TAG);
    printf("Esperando mensaje, espera activa");
    //Mostrar el mensaje recibido al usuario
}

void process_messages(int rank){
    //Messag
}

void protocol_run(){

}

