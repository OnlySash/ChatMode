#include <QApplication>
#include "mainwindow.h"

#include "../include/wrapped_mpi.h"
#include "../include/coordinator.h"
#include "../include/protocol.h"

extern "C" {
    void coordinator_run();
    void contact_online(int rank);
}

int main(int argc, char *argv[]) {

    int rank, size;
    init_parallelization_mpi(&argc, &argv, &rank, &size);

    printf("Rank %d iniciado\n", rank);
    fflush(stdout);

    if(rank == 0){
        printf("Rank 0: entrando a coordinator_run\n");
        fflush(stdout);

        coordinator_run();
    }
    //Usamos rank 1 ya que es el usuario que vamos a controlar
    else if (rank == 1) {
        printf("Rank 1: entrando a iniciar QT\n");
        fflush(stdout);
        contact_online(rank);
        sync_processors();

        QApplication app(argc, argv);
        MainWindow w(rank);
        w.show();

        int ret = app.exec();
        finalize_parallelization_mpi();
        return ret;
    } else {
        contact_online(rank);
        sync_processors();
        // los demás procesos solo hacen en CLI
        //client_run();
    }

    finalize_parallelization_mpi();
    return 0;
}