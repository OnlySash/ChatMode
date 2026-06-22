#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "../include/utils.h"

void contact_online(int rank);

void tipo_mensaje();

void escribir_mensaje();

void send_message_CLI(Messages *sms);

void message_rand(char *buf, int max_len);

void esperar_mensaje(Messages *sms);

//void process_messages(int rank);

void protocol_run();

#endif //PROTOCOL_H