#ifndef COORDINATOR_H
#define COORDINATOR_H

#ifdef __cplusplus
extern "C" {
    #endif

#include "utils.h"

void online();

void metricas();

void process_request(Messages* sms, Coordinator* state);

void coordinator_run();

#ifdef __cplusplus
}
#endif

#endif //COORDINATOR_H