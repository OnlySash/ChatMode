//Enviar mensajes a un destinatario específico 
//Enviar mensajes a una lista de difusiòn
//Permitir varias instancias en ejecuciòn simultànea, cada una enviando y reciviendo mensajes
//Incluir un proceso coordinador, correspondiente al rank 0, encargado de administrar y enrutar la mensajerìa

#include <stdio.h>
#include <stdlib.h>
#include "include/wrapped_mpi.h"
#include "include/message.h"
#include "include/coordinator.h"
#include "include/client.h"
#include "include/protocol.h"

int main(int argc, char *argv[]) {
    int rank, size;
    // Inicializar MPI
    init_parallelization_mpi(&argc, &argv, &rank, &size);

    if(rank == COORDINATOR){
        coordinator_run();
    }else{
        contacto_en_linea(rank);
        run_cli(rank);
    }

    // Finalizar MPI
    finalize_parallelization_mpi();
    return 0;
}