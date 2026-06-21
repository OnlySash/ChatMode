#ifndef MESSAGE_H
#define MESSAGE_H

//Tamaños predefinidos para nombres, mensajes y cantidad de usuarios
#define MAX_MESSAGE 50
#define N_USERS 4

//defina una estructura con remitente, 
//destinatario o lista de destino, 
//longitud y cuerpo del mensaje, 

typedef enum{
    DIRECT,
    BROADCAST
} type_send;

//Cambiar estructura
typedef struct {
    type_send mode;              //directo o difusion
    int send_rank;              //rank del que envia
    
    char sender;      //nombre del que envia
    char receiver;    //nombre del que recibe

    int receiver_count;         //cantidad de destinatarios en difusion
    char receivers; //nombres de los destinatarios en difusion
    
    char text[MAX_MESSAGE];
} Messages;

#endif //MESSAGE_H