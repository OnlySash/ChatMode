#ifndef MESSAGE_H
#define MESSAGE_H

//Tamaños predefinidos para nombres, mensajes y cantidad de usuarios
#define MAX_MESSAGE 512

typedef enum{
    DIRECT,
    BROADCAST
} type_send;

//Cambiar estructura
typedef struct {
    type_send mode;              //directo o difusion
    int send_rank;              //rank del que envia
    
    char sender[MAX_NAME];      //nombre del que envia
    char receiver[MAX_NAME];    //nombre del que recibe

    int receiver_count;         //cantidad de destinatarios en difusion
    char receivers[MAX_USERS][MAX_NAME]; //nombres de los destinatarios en difusion
    
    char text[MAX_MESSAGE];
} Messages;

#endif //MESSAGE_H