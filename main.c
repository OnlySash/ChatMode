//Enviar mensajes a un destinatario específico 
//Enviar mensajes a una lista de difusiòn
//Permitir varias instancias en ejecuciòn simultànea, cada una enviando y reciviendo mensajes
//Incluir un proceso coordinador, correspondiente al rank 0, encargado de administrar y enrutar la mensajerìa

#include <stdio.h>
#include <stdlib.h>

#include "include/message.h"
#include "include/client.h"
#include "include/coordinator.h"
#include "include/wrapped_mpi.h"

void menu(){
    printf("Selecciona una opcion: \n1. Abrir UI\n2. Usar terminal automatico\n3. Uar terminal manual\n");
    int opcion;
    if (scanf("%d", &opcion) != 1) {
        printf("Error al leer entrada\n");
        return;
    }
    getchar();

    switch (opcion) {
        case 1:
            // Abrir UI
            break;
        case 2:
            // Usar terminal automático
            coordinator_run();
            break;
        case 3:
            // Usar terminal manual
            break;
        default:
            printf("Opción no válida\n");
            break;
    }
}


int main(int argc, char *argv[]) {
    int rank, size;
    // Inicializar MPI
    init_parallelization_mpi(&argc, &argv, &rank, &size);

    if (rank == 0) {
        menu();
    } else {
        contacto_en_linea(rank);
    }

    // Finalizar MPI
    finalize_parallelization_mpi();
    return 0;
}