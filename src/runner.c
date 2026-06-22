#include <stdio.h>
#include <string.h>

#include "../include/message.h"
#include "../include/coordinator.h"
#include "../include/client.h"
#include "../include/wrapped_mpi.h"
#include "../include/protocol.h"
#include "../include/utils.h"

void run_cli(int rank) {
    Messages sms;

    switch (rank) {
        case 1:
            // Broadcast
            sms.mode = BROADCAST;
            sms.sender = 1;
            sms.receiver_count = 3;
            sms.receivers[0] = 2;
            sms.receivers[1] = 3;
            sms.receivers[2] = 4;
            message_rand(sms.text, MAX_MESSAGE);
            send_message_CLI(&sms);
            break;

        case 2:
            // Mensaje directo de 2 a 3
            sms.mode = DIRECT;
            sms.sender = 2;
            sms.receiver = 3;
            message_rand(sms.text, MAX_MESSAGE);
            send_message_CLI(&sms);
            break;

        case 3:
            // Mensaje directo de 3 hacia 4
            sms.mode = DIRECT;
            sms.sender = 3;
            sms.receiver = 4;
            message_rand(sms.text, MAX_MESSAGE);
            send_message_CLI(&sms);
            break;

        case 4:
            // Mensaje directo de 4 hacia 1
            sms.mode = DIRECT;
            sms.sender = 4;
            sms.receiver = 1;
            message_rand(sms.text, MAX_MESSAGE);
            send_message_CLI(&sms);
            break;
    }
}

void menu(int rank){
    printf("Selecciona una opcion: \n1. Abrir UI\n2. Usar terminal automatico\n");
    int opcion;
    if (scanf("%d", &opcion) != 1) {
        printf("Error al leer entrada\n");
        return;
    }
    getchar();

    switch (opcion) {
        case 1:
            // Abrir UI
            break;
        case 2:
            // Usar terminal automático
            coordinator_run();
            {
                int n_users = N_USERS;
                broadcast_numbers_processors(&n_users, COORDINATOR);
            }
            run_cli(rank);
            break;
        default:
            printf("Opción no válida\n");
            break;
    }
}
