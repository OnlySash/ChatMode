#ifndef PROTOCOL_H
#define PROTOCOL_H

#ifdef __cplusplus
extern "C" {
    #endif

#include "../include/utils.h"

void contact_online(int rank);

void escribir_mensaje();

void send_message_CLI(Messages *sms);

void message_rand(char *buf, int max_len);

void esperar_mensaje(Messages *sms);

#ifdef __cplusplus
}
#endif

#endif //PROTOCOL_H