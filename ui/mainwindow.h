#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMap>

#include "receptor_mpi.h"   // ← solo esto, sin redefinir la clase

extern "C" {
#include "../include/wrapped_mpi.h"
#include "../include/coordinator.h"
#include "../include/protocol.h"
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(int mi_rank, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void abrir_chat(int indice_usuario);
    void enviar_directo();
    void enviar_difusion();
    void retroceder();
    void ver_mensaje_recibido(int remitente, QString texto);

private:
    void config_estilos();
    void lista_chats();
    void vista_chat();
    void config_difusion();
    void agregar_recibido(const QString &remitente, const QString &texto);

    int m_mi_rank;
    QStackedWidget *m_pila;

    QWidget     *m_pagina_lista;
    QListWidget *m_lista_chats;

    QWidget    *m_pagina_chat;
    QLabel     *m_encabezado_chat;
    QMap<int, QTextEdit*> m_visores_chat;
    QTextEdit  *m_visor_chat_actual;
    QLineEdit  *m_entrada_chat;
    int         m_usuario_actual;
    QWidget     *m_area_chat;
    QWidget     *m_pagina_difusion;
    QTextEdit   *m_visor_difusion;
    QLineEdit   *m_entrada_difusion;
    QListWidget *m_lista_destinatarios;

    QList<User> m_usuarios;
    QStringList m_avatares;
    QMap<int, int> m_rank_a_indice;

    Receptor_MPI *m_receptor;
};

#endif