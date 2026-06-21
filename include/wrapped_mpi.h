#include <stddef.h>
#include <mpi.h>
#ifndef WRAPPED_MPI_H
#define WRAPPED_MPI_H


#define MESSAGE_TAG 1
#define PERMISSION_TAG 2
#define DELIVERED_TAG 3
#define STATISTICS_TAG 4
#define COORDINATOR 0

void init_parallelization_mpi(int* argc, char*** argv, int* rank, int* size);
void finalize_parallelization_mpi();

// void check_numbers_processors(int size, int required);
void broadcast_numbers_processors(int* value, int source);
void sync_processors(void);

void send_int(int value, int destination, int tag);
void receive_int(int* value, int source, int tag, MPI_Status* status);
void send_string(char* text, int destination, int tag);
void receive_string(char* text, int length, int source, int tag);


#endif //WRAPPED_MPI_H