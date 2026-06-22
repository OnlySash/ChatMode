#include <stddef.h>

#include "message.h"
#include "utils.h"

#ifndef WRAPPED_MPI_H
#define WRAPPED_MPI_H

#ifdef __cplusplus
extern "C" {
#endif

void init_parallelization_mpi(int* argc, char*** argv, int* rank, int* size);
void finalize_parallelization_mpi();

void broadcast_numbers_processors(int* value, int source);
void broadcast_general(Messages *sms, int source);
void sync_processors(void);

void send_int(int value, int destination, int tag);
void receive_int(int* value, int source, int tag, void* status);
void send_string(char *text, int destination, int tag);
void receive_string(char *text, int length, int source, int tag);

// Send/receive full Messages structures
void send_messages(Messages *sms, int destination, int tag);
void receive_messages(Messages *sms, int source, int tag, void* status);

#ifdef __cplusplus
}
#endif

#endif //WRAPPED_MPI_H