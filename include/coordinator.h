#ifndef COORDINATOR_H
#define COORDINATOR_H

#ifdef __cplusplus
extern "C" {
    #endif

#include "utils.h"

extern User users[N_USERS];

const char *get_username(int rank);

void online();

void metricas();

void process_request(Messages* sms, Coordinator* state);

void coordinator_run();

#ifdef __cplusplus
}
#endif

#endif //COORDINATOR_H