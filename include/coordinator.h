#ifndef COORDINATOR_H
#define COORDINATOR_H

#define MESSAGE_TAG 1
#define PERMISSION_TAG 2
#define DELIVERED_TAG 3
#define STATISTICS_TAG 4

#define COORDINATOR 0

typedef struct {
    int active_contacts;
    int server_open;
    int pending_queue[100];
    int front;
    int rear;
} Coordinator;


void en_linea();

void metricas();

void coordinator_run();

#endif //COORDINATOR_H