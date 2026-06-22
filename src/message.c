/*serializada como un búfer de caracteres.
Documente este protocolo en el README y en los diagramas.
*/

#include "../include/wrapped_mpi.h"
#include "../include/message.h"
#include "../include/protocol.h"
#include "../include/coordinator.h"

#include <string.h>
#include <stdio.h>

//Caso de prueba generalizada y funcional
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
            break;

        case 2:
            // Mensaje directo de 2 a 3
            sms.mode = DIRECT;
            sms.sender = 2;
            sms.receiver = 3;
            message_rand(sms.text, MAX_MESSAGE);
            break;

        case 3:
            // Mensaje directo de 3 hacia 4
            sms.mode = DIRECT;
            sms.sender = 3;
            sms.receiver = 4;
            message_rand(sms.text, MAX_MESSAGE);
            break;

        case 4:
            // Mensaje directo de 4 hacia 1
            sms.mode = DIRECT;
            sms.sender = 4;
            sms.receiver = 1;
            message_rand(sms.text, MAX_MESSAGE);
            break;
    }
    printf("Rank %s enviando mensaje\n", get_username(rank));
    //Adenlanta la salida/ print
    fflush(stdout);
    send_message_CLI(&sms);
    broadcast_general(&sms, COORDINATOR);

    if (sms.mode == BROADCAST) {
        for (int i = 0; i < sms.receiver_count; i++) {
            if (sms.receivers[i] == rank) {
                printf("Rank %s recibió broadcast: %s\n",get_username(rank), sms.text);
                break;
            }
        }
    }

    if (rank == 3 || rank == 4 || rank == 1) {
        esperar_mensaje(&sms);
    }
}


