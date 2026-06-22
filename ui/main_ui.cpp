#include <QApplication>

#include "../include/wrapped_mpi.h"
#include "../include/coordinator.h"
//#include "mainwindow.h"

extern "C" {
    void coordinator_run();
}

int main(int argc, char *argv[]) {

    int rank, size;
    init_parallelization_mpi(&argc, &argv, &rank, &size);

    if(rank == 0){
        coordinator_run();
    }
    //Usamos rank 1 ya que es el usuario que vamos a controlar
    else if (rank == 1) {
        QApplication app(argc, argv);
        /*MainWindow w;
        w.show();*/

        int ret = app.exec();
        finalize_parallelization_mpi();
        return 0;
    } else {
        // los demás procesos solo hacen en CLI
        //client_run();
    }

    finalize_parallelization_mpi();
    return 0;
}