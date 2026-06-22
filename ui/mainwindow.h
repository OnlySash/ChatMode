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

extern "C" {
    #include "../include/wrapped_mpi.h"
    #include "../include/coordinator.h"
}

struct User {
    int rank;
    QString name;
    QString avatar;  // ruta al PNG
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(int myRank, QWidget *parent = nullptr);

private slots:
    void openChat(int userIndex);
    void sendDirect();
    void sendBroadcast();
    void goBack();

private:
    void setupStyles();
    void buildChatList();    // pantalla principal — lista de chats
    void buildChatView();    // pantalla de conversación
    void buildBroadcast();   // pantalla de difusión

    int m_myRank;
    QStackedWidget *m_stack;

    // Pantalla principal
    QWidget     *m_pageList;
    QListWidget *m_chatList;

    // Pantalla de chat
    QWidget    *m_pageChat;
    QLabel     *m_chatHeader;
    QTextEdit  *m_chatDisplay;
    QLineEdit  *m_chatInput;
    int         m_currentUser;

    // Pantalla de difusión
    QWidget   *m_pageBroadcast;
    QTextEdit *m_broadcastDisplay;
    QLineEdit *m_broadcastInput;

    // Usuarios preestablecidos
    QList<User> m_users;
};

#endif