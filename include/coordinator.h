#ifndef COORDINATOR_H
#define COORDINATOR_H

#include "utils.h"

void en_linea();

void metricas();

void process_request(Messages* sms, Coordinator* state);

void coordinator_run();

#endif //COORDINATOR_H