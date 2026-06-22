/*envían sus mensajes al coordinador indicando el tipo (directo o difusión) 
mediante etiquetas (tags) de MPI, 
y reciben los mensajes dirigidos a ellos.
*/

#include "../include/wrapped_mpi.h"
#include "../include/message.h"
#include "../include/coordinator.h"
#include "../include/utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Envia señañ en linea
void contact_online(int rank){
    if (rank < 1 || rank > N_USERS) {
        printf("Rank %d no es un cliente válido\n", rank);
        return;
    }
    send_int(rank, COORDINATOR,STATISTICS_TAG);
    //send_string((char*) usernames[rank - 1], COORDINATOR, STATISTICS_TAG);
}

void escribir_mensaje(){
    //Que el usuario escriba un mensaje
    //Limitar la longitud del mensaje a MAX_MESSAGE 50
    printf("Escribe un mensaje (máximo %d caracteres): ", MAX_MESSAGE);
    char mensaje[MAX_MESSAGE];

    char *eltexto = fgets(mensaje, MAX_MESSAGE, stdin);

    if (eltexto == NULL) {
        printf("Error al leer mensaje\n");
    }
}

//Para pruebas crea un mensaje random
void message_rand(char *buf, int max_len){
    int length = 3 + rand() % (max_len - 3);
    for (int i = 0; i < length; i++) {
        buf[i] = 'a' + (rand() % 26);
    }
    buf[length] = '\0';
}

void send_message_CLI(Messages *sms){
    send_messages(sms, COORDINATOR, MESSAGE_TAG);
}

void esperar_mensaje(Messages *sms){
    //Esperar a recibir un mensaje dirigido a este cliente
    receive_messages(sms, COORDINATOR, MESSAGE_TAG, NULL);
    printf("Rank %s recibió de %s: %s\n",get_username(sms->receiver), get_username(sms->sender), sms->text);
    //Mostrar el mensaje recibido al usuario
}


