#include <mpi.h>
#ifndef WRAPPER_MPI_H
#define WRAPPER_MPI_H

//Tags para tipo de mensaje y registro de usuarios
#define TAG_DIRECT 1
#define TAG_BROADCAST 2
#define TAG_REGISTER 3

void init_parallelization_mpi(int* argc, char*** argv, int* rank, int* size);
void finalize_parallelization_mpi(void);

// void check_numbers_processors(int size, int required);
void broadcast_numbers_processors(int* value, int source);
void sync_processors(void);

void send_int(int value, int destination, int tag);
void receive_int(int* value, int source, int tag, MPI_Status* status);
void send_string(char* text, int destination, int tag);
void receive_string(char* text, int length, int source, int tag);


#endif //WRAPPER_MPI_H