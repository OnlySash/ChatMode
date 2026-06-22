#include "../include/wrapped_mpi.h"
#include "../include/coordinator.h"

#include <mpi.h>
#include <stdio.h>
#include <string.h>

void init_parallelization_mpi(int* argc, char*** argv, int* rank, int* size)
{
    MPI_Init_thread(argc, argv);
    MPI_Comm_rank(MPI_COMM_WORLD, rank);
    MPI_Comm_size(MPI_COMM_WORLD, size);
}

void finalize_parallelization_mpi(void)
{
    MPI_Finalize();
}

void broadcast_numbers_processors(int* value, int source)
{
    MPI_Bcast(value, 1, MPI_INT, source, MPI_COMM_WORLD);
}

void broadcast_general(Messages *sms, int source)
{
    MPI_Bcast(sms, sizeof(Messages), MPI_BYTE, source, MPI_COMM_WORLD);
}

void sync_processors(void)
{
    MPI_Barrier(MPI_COMM_WORLD);
}

void send_int(int value, int destination, int tag)
{
    MPI_Send(&value, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
}

void receive_int(int* value, int source, int tag, MPI_Status* status)
{
    MPI_Recv(value, 1, MPI_INT, source, tag, MPI_COMM_WORLD, status);
}

void send_string(char *text, int destination, int tag)
{
    MPI_Send(text, strlen(text) + 1, MPI_CHAR, destination, tag, MPI_COMM_WORLD);
}

void receive_string(char *text, int length, int source, int tag)
{
    MPI_Recv(text, length, MPI_CHAR, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
}

/*cada cliente debe separar el hilo de la interfaz del hilo de
comunicación (por ejemplo, con pthreads y MPI_Init_thread), 
de manera que la GUI no se congele mientras se espera un mensaje.
*/