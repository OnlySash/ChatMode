#ifndef UTILS_H
#define UTILS_H

//Etiquetas de MPI
#define MESSAGE_TAG 1
#define PERMISSION_TAG 2
#define DELIVERED_TAG 3
#define STATISTICS_TAG 4

#define COORDINATOR 0

//Utiles para el manejo del coordinador
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

//Tamaños predefinidos para mensajes y cantidad de usuarios
#define MAX_MESSAGE 50
#define N_USERS 4


typedef enum{
    DIRECT,
    BROADCAST
} type_send;

//Estructura para mensajes
typedef struct {
    type_send mode;              //directo o difusion

    int sender;      //# del que envia
    int receiver;    //# del que recibe

    int receiver_count;         //cantidad de destinatarios en difusion
    int receivers[N_USERS]; //# de los destinatarios en difusion
    
    char text[MAX_MESSAGE];
} Messages;

#endif //UTILS_H