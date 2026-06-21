/*registra a los clientes conectados, 
mantiene la tabla que asocia cada rank con un nombre de usuario, 
administra las listas de difusión y enruta cada mensaje hacia su destino. 
También puede registrar bitácoras y métricas globales.*/
#include <stdio.h>
#include <string.h>

#include "../include/coordinator.h"
#include "../include/wrapped_mpi.h"
#include "../include/message.h"
#include "../include/client.h"

void en_linea(){
    // Avisa inicialmente que estan en lìnea
    char username[32];
    for (int i = 1; i <= N_USERS; i++) {
        receive_string(username, sizeof(username), i, STATISTICS_TAG);
        printf("[%s] En linea.\n", username);
    }
    printf("[Coordinator] Sistema iniciado.");

}

//coordina envìo y recivir mensajes

void metricas(){

}

void coordinator_run(){
    en_linea();
}