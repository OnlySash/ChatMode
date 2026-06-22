#ifndef RECEPTOR_MPI_H
#define RECEPTOR_MPI_H

#include <QThread>
#include <QString>
#include <mpi.h>

extern "C" {
#include "../include/wrapped_mpi.h"
#include "../include/utils.h"
}

class Receptor_MPI : public QThread {
    Q_OBJECT
public:
    explicit Receptor_MPI(QObject *parent = nullptr) : QThread(parent) {}
    void detener() { m_activo = false; }

signals:
    void mensaje_recibido(int remitente, QString texto);

protected:
    void run() override {
        m_activo = true;
        while (m_activo) {
            Messages sms;
            receive_messages(&sms, MPI_ANY_SOURCE, MESSAGE_TAG, nullptr);
            emit mensaje_recibido(sms.sender, QString::fromUtf8(sms.text));
        }
    }

private:
    bool m_activo = true;
};

#endif