#ifndef UTILS_H
#define UTILS_H

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

typedef struct {
    int rank;
    char name[50];
} User;

//Tamaños predefinidos para nombres, mensajes y cantidad de usuarios
#define MAX_MESSAGE 50
#define N_USERS 4

typedef enum{
    DIRECT,
    BROADCAST
} type_send;

//Cambiar estructura
typedef struct {
    type_send mode;              //directo o difusion

    char sender;      //nombre del que envia
    char receiver;    //nombre del que recibe

    int receiver_count;         //cantidad de destinatarios en difusion
    char receivers[N_USERS]; //nombres de los destinatarios en difusion
    
    char text[MAX_MESSAGE];
} Messages;

#endif //UTILS_H