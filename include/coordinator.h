#ifndef COORDINATOR_H
#define COORDINATOR_H

typedef struct {
    int active_contacts;
    int server_busy;
    int pending_queue[100];
    int front;
    int rear;
} Coordinator;

typedef struct {
    int rank;
    char name[50];
} User;

void en_linea();

void metricas();

void coordinator_run();

#endif //COORDINATOR_H