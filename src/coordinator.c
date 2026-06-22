/*registra a los clientes conectados, 
mantiene la tabla que asocia cada rank con un nombre de usuario, 
administra las listas de difusión y enruta cada mensaje hacia su destino. 
También puede registrar bitácoras y métricas globales.*/
#include <stdio.h>
#include <string.h>
#include <mpi.h>

#include "../include/coordinator.h"
#include "../include/wrapped_mpi.h"
#include "../include/message.h"
#include "../include/utils.h"

//Tabla de usernames
User users[] = {
    {1, "Sasha"},
    {2, "Karina"},
    {3, "Amber"},
    {4, "Wendy"}
};


void en_linea(){
    // Avisa inicialmente que estan en lìnea
    char username[32];
    for (int i = 1; i <= N_USERS; i++) {
        receive_string(username, sizeof(username), i, STATISTICS_TAG);
        printf("[%s] En linea.\n", username);
    }
    printf("[Coordinator] Sistema iniciado.");

}

//coordina envío y recibir mensajes
void process_request(Messages* sms, Coordinator* state){
    if (sms->mode == DIRECT) {
        // Enviar mensaje directo al destinatario
        send_messages(sms, sms->receiver, MESSAGE_TAG);
    } else if (sms->mode == BROADCAST) {
        // Enviar mensaje de difusión a todos
        broadcast_general(sms, COORDINATOR);
    } else {
        // Encolar si no hay capacidad
        if (state->rear < 100) {
            state->pending_queue[state->rear++] = sms->sender;
        }
    }
}

void metricas(){
}
void coordinator_run(){
    en_linea();
    // Procesar mensajes entrantes de los clientes
    Coordinator state = {0};
    for (int i = 0; i < N_USERS; i++) {
        Messages sms;
        MPI_Status status;
        receive_messages(&sms, MPI_ANY_SOURCE, MESSAGE_TAG, &status);
        process_request(&sms, &state);
    }
    sync_processors();
}
