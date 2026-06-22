#include "mainwindow.h"
#include <QPixmap>

static const char* COLOR_FONDO        = "#1a0a2e";
static const char* COLOR_PANEL        = "#2d1b4e";
static const char* COLOR_ACENTO       = "#7c3aed";
static const char* COLOR_TEXTO        = "#e2d9f3";
static const char* COLOR_BURBUJA_ENV  = "#4c1d95";
static const char* COLOR_BURBUJA_REC  = "#2d1b4e";

MainWindow::MainWindow(int mi_rank, QWidget *parent)
    : QMainWindow(parent), m_mi_rank(mi_rank), m_usuario_actual(-1),
      m_visor_chat_actual(nullptr)
{
    for (int i = 0; i < N_USERS; i++) {
        m_usuarios.append(users[i]);
        m_avatares << ":/utils/user.png";
        m_rank_a_indice[users[i].rank] = i;
    }

    setWindowTitle("ChatMode");
    setFixedSize(400, 700);

    m_pila = new QStackedWidget(this);
    setCentralWidget(m_pila);

    construir_lista_chats();
    construir_vista_chat();
    construir_difusion();

    m_pila->addWidget(m_pagina_lista);
    m_pila->addWidget(m_pagina_chat);
    m_pila->addWidget(m_pagina_difusion);
    m_pila->setCurrentWidget(m_pagina_lista);

    configurar_estilos();

    m_receptor = new Receptor_MPI(this);
    connect(m_receptor, &Receptor_MPI::mensaje_recibido,
            this, &MainWindow::mostrar_mensaje_recibido);
    m_receptor->start();
}

MainWindow::~MainWindow() {
    m_receptor->detener();
    m_receptor->wait();
}

void MainWindow::configurar_estilos() {
    setStyleSheet(QString(R"(
        QMainWindow, QWidget {
            background-color: %1;
            color: %2;
            font-family: 'Courier New', monospace;
            font-size: 13px;
        }
        QListWidget {
            background-color: %1;
            border: none;
        }
        QListWidget::item {
            background-color: %3;
            border-radius: 8px;
            padding: 10px;
            margin: 4px 8px;
        }
        QListWidget::item:hover {
            background-color: %4;
        }
        QListWidget::item:selected {
            background-color: %4;
            border: 2px solid %4;
        }
        QTextEdit {
            background-color: %3;
            border: 1px solid %4;
            border-radius: 8px;
            padding: 8px;
            color: %2;
        }
        QLineEdit {
            background-color: %3;
            border: 2px solid %4;
            border-radius: 8px;
            padding: 8px;
            color: %2;
        }
        QPushButton {
            background-color: transparent;
            border: none;
        }
    )").arg(COLOR_FONDO, COLOR_TEXTO, COLOR_PANEL, COLOR_ACENTO));
}

void MainWindow::construir_lista_chats() {
    m_pagina_lista = new QWidget;
    auto *disposicion = new QVBoxLayout(m_pagina_lista);
    disposicion->setContentsMargins(0, 0, 0, 0);
    disposicion->setSpacing(0);

    auto *encabezado = new QLabel("  ChatMode");
    encabezado->setFixedHeight(56);
    encabezado->setStyleSheet(QString("background-color: %1; color: %2;"
                                      "font-size: 18px; font-weight: bold;")
                              .arg(COLOR_PANEL, COLOR_TEXTO));
    disposicion->addWidget(encabezado);

    m_lista_chats = new QListWidget;

    for (int i = 0; i < m_usuarios.size(); i++) {
        if (m_usuarios[i].rank == m_mi_rank) continue;

        auto *elemento = new QListWidgetItem;
        elemento->setSizeHint(QSize(0, 64));
        elemento->setData(Qt::UserRole, i);

        auto *fila = new QWidget;
        auto *fila_disp = new QHBoxLayout(fila);
        fila_disp->setContentsMargins(8, 4, 8, 4);

        auto *avatar = new QLabel;
        QPixmap pix(":/utils/user.png");
        avatar->setPixmap(pix.scaled(40, 40, Qt::KeepAspectRatio,
                                     Qt::SmoothTransformation));
        fila_disp->addWidget(avatar);

        auto *nombre = new QLabel(QString::fromUtf8(m_usuarios[i].name));
        nombre->setStyleSheet(QString("color: %1; font-size: 15px;").arg(COLOR_TEXTO));
        fila_disp->addWidget(nombre);
        fila_disp->addStretch();

        m_lista_chats->addItem(elemento);
        m_lista_chats->setItemWidget(elemento, fila);
    }

    connect(m_lista_chats, &QListWidget::itemClicked, this,
            [this](QListWidgetItem *elemento) {
        int indice_real = elemento->data(Qt::UserRole).toInt();
        abrir_chat(indice_real);
    });

    disposicion->addWidget(m_lista_chats);

    auto *barra_botones = new QWidget;
    barra_botones->setFixedHeight(60);
    barra_botones->setStyleSheet(QString("background-color: %1;").arg(COLOR_PANEL));
    auto *disp_botones = new QHBoxLayout(barra_botones);

    auto *btn_difusion = new QPushButton;
    btn_difusion->setIcon(QPixmap(":/utils/difusion.png"));
    btn_difusion->setIconSize(QSize(32, 32));
    btn_difusion->setToolTip("Difusión");
    connect(btn_difusion, &QPushButton::clicked, this, [this]() {
        m_pila->setCurrentWidget(m_pagina_difusion);
    });

    disp_botones->addStretch();
    disp_botones->addWidget(btn_difusion);
    disp_botones->addStretch();
    disposicion->addWidget(barra_botones);
}

void MainWindow::construir_vista_chat() {
    m_pagina_chat = new QWidget;
    auto *disposicion = new QVBoxLayout(m_pagina_chat);
    disposicion->setContentsMargins(0, 0, 0, 0);
    disposicion->setSpacing(0);

    // Encabezado con botón atrás visible
    auto *encabezado = new QWidget;
    encabezado->setFixedHeight(56);
    encabezado->setStyleSheet(QString("background-color: %1;").arg(COLOR_PANEL));
    auto *disp_encabezado = new QHBoxLayout(encabezado);

    auto *btn_retroceder = new QPushButton;
    btn_retroceder->setIcon(QPixmap(":/utils/mini_back.png"));
    btn_retroceder->setIconSize(QSize(32, 32));
    btn_retroceder->setFixedSize(44, 44);
    btn_retroceder->setStyleSheet(
        QString("QPushButton { background-color: %1; border-radius: 8px; }"
                "QPushButton:hover { background-color: %2; }")
        .arg(COLOR_ACENTO, COLOR_PANEL));
    connect(btn_retroceder, &QPushButton::clicked, this, &MainWindow::retroceder);

    m_encabezado_chat = new QLabel("Chat");
    m_encabezado_chat->setStyleSheet(QString("color: %1; font-size: 16px;"
                                             "font-weight: bold;").arg(COLOR_TEXTO));
    disp_encabezado->addWidget(btn_retroceder);
    disp_encabezado->addSpacing(8);
    disp_encabezado->addWidget(m_encabezado_chat);
    disp_encabezado->addStretch();
    disposicion->addWidget(encabezado);

    // Área de mensajes — guarda referencia como miembro
    m_area_chat = new QWidget;
    m_area_chat->setStyleSheet("background-image: url(:/utils/background.png);"
                               "background-repeat: repeat;");
    auto *disp_area = new QVBoxLayout(m_area_chat);
    disp_area->setContentsMargins(4, 4, 4, 4);
    disposicion->addWidget(m_area_chat, 1);

    // Barra de entrada
    auto *barra_entrada = new QWidget;
    barra_entrada->setFixedHeight(60);
    barra_entrada->setStyleSheet(QString("background-color: %1;").arg(COLOR_PANEL));
    auto *disp_entrada = new QHBoxLayout(barra_entrada);

    m_entrada_chat = new QLineEdit;
    m_entrada_chat->setPlaceholderText("Escribe un mensaje...");

    auto *btn_enviar = new QPushButton;
    btn_enviar->setIcon(QPixmap(":/utils/mini_send.png"));
    btn_enviar->setIconSize(QSize(28, 28));
    connect(btn_enviar, &QPushButton::clicked, this, &MainWindow::enviar_directo);
    connect(m_entrada_chat, &QLineEdit::returnPressed,
            this, &MainWindow::enviar_directo);

    disp_entrada->addWidget(m_entrada_chat);
    disp_entrada->addWidget(btn_enviar);
    disposicion->addWidget(barra_entrada);
}

void MainWindow::construir_difusion() {
    m_pagina_difusion = new QWidget;
    auto *disposicion = new QVBoxLayout(m_pagina_difusion);
    disposicion->setContentsMargins(0, 0, 0, 0);
    disposicion->setSpacing(0);

    auto *encabezado = new QWidget;
    encabezado->setFixedHeight(56);
    encabezado->setStyleSheet(QString("background-color: %1;").arg(COLOR_PANEL));
    auto *disp_encabezado = new QHBoxLayout(encabezado);

    auto *btn_retroceder = new QPushButton;
    btn_retroceder->setIcon(QPixmap(":/utils/mini_back.png"));
    btn_retroceder->setIconSize(QSize(32, 32));
    btn_retroceder->setFixedSize(44, 44);
    btn_retroceder->setStyleSheet(
        QString("QPushButton { background-color: %1; border-radius: 8px; }"
                "QPushButton:hover { background-color: %2; }")
        .arg(COLOR_ACENTO, COLOR_PANEL));
    connect(btn_retroceder, &QPushButton::clicked, this, &MainWindow::retroceder);

    auto *icono_difusion = new QLabel;
    icono_difusion->setPixmap(QPixmap(":/utils/mini_difusion.png")
                              .scaled(24, 24, Qt::KeepAspectRatio));

    auto *titulo = new QLabel("Difusión");
    titulo->setStyleSheet(QString("color: %1; font-size: 16px;"
                                  "font-weight: bold;").arg(COLOR_TEXTO));

    disp_encabezado->addWidget(btn_retroceder);
    disp_encabezado->addSpacing(8);
    disp_encabezado->addWidget(icono_difusion);
    disp_encabezado->addWidget(titulo);
    disp_encabezado->addStretch();
    disposicion->addWidget(encabezado);

    auto *etiqueta = new QLabel("  Seleccionar destinatarios:");
    etiqueta->setStyleSheet(QString("color: %1; padding: 4px;").arg(COLOR_TEXTO));
    disposicion->addWidget(etiqueta);

    m_lista_destinatarios = new QListWidget;
    m_lista_destinatarios->setSelectionMode(QAbstractItemView::MultiSelection);
    m_lista_destinatarios->setFixedHeight(160);

    for (int i = 0; i < m_usuarios.size(); i++) {
        if (m_usuarios[i].rank == m_mi_rank) continue;
        auto *elemento = new QListWidgetItem(
            QString::fromUtf8(m_usuarios[i].name),
            m_lista_destinatarios
        );
        elemento->setData(Qt::UserRole, m_usuarios[i].rank);
    }

    disposicion->addWidget(m_lista_destinatarios);

    m_visor_difusion = new QTextEdit;
    m_visor_difusion->setReadOnly(true);
    disposicion->addWidget(m_visor_difusion, 1);

    auto *barra_entrada = new QWidget;
    barra_entrada->setFixedHeight(60);
    barra_entrada->setStyleSheet(QString("background-color: %1;").arg(COLOR_PANEL));
    auto *disp_entrada = new QHBoxLayout(barra_entrada);

    m_entrada_difusion = new QLineEdit;
    m_entrada_difusion->setPlaceholderText("Mensaje para los seleccionados...");

    auto *btn_enviar = new QPushButton;
    btn_enviar->setIcon(QPixmap(":/utils/mini_send.png"));
    btn_enviar->setIconSize(QSize(28, 28));
    connect(btn_enviar, &QPushButton::clicked, this, &MainWindow::enviar_difusion);
    connect(m_entrada_difusion, &QLineEdit::returnPressed,
            this, &MainWindow::enviar_difusion);

    disp_entrada->addWidget(m_entrada_difusion);
    disp_entrada->addWidget(btn_enviar);
    disposicion->addWidget(barra_entrada);
}

// ── Slots ─────────────────────────────────────────────────────────
void MainWindow::abrir_chat(int indice) {
    m_usuario_actual = indice;
    int rank = m_usuarios[indice].rank;
    m_encabezado_chat->setText(QString::fromUtf8(m_usuarios[indice].name));

    // Crear visor si no existe para este contacto
    if (!m_visores_chat.contains(rank)) {
        auto *visor = new QTextEdit;
        visor->setReadOnly(true);
        visor->setStyleSheet("background-color: transparent; border: none;");
        visor->hide();
        m_visores_chat[rank] = visor;
        m_area_chat->layout()->addWidget(visor);
    }

    // Ocultar todos, mostrar solo el del contacto actual
    for (auto *v : m_visores_chat)
        v->hide();
    m_visores_chat[rank]->show();
    m_visor_chat_actual = m_visores_chat[rank];

    m_pila->setCurrentWidget(m_pagina_chat);
}

void MainWindow::enviar_directo() {
    if (m_usuario_actual < 0 || !m_visor_chat_actual) return;
    QString texto = m_entrada_chat->text().trimmed();
    if (texto.isEmpty()) return;

    m_visor_chat_actual->append(QString(
        "<div style='text-align:right;'>"
        "<span style='background-color:%1; color:%2; padding:6px 12px;"
        "border-radius:12px; display:inline-block;'>%3</span></div>"
    ).arg(COLOR_BURBUJA_ENV, COLOR_TEXTO, texto));

    Messages sms;
    sms.sender   = m_mi_rank;
    sms.receiver = m_usuarios[m_usuario_actual].rank;
    sms.mode     = DIRECT;
    strncpy(sms.text, texto.toUtf8().constData(), sizeof(sms.text) - 1);
    send_messages(&sms, COORDINATOR, MESSAGE_TAG);

    m_entrada_chat->clear();
}

void MainWindow::enviar_difusion() {
    QString texto = m_entrada_difusion->text().trimmed();
    if (texto.isEmpty()) return;

    QList<QListWidgetItem*> seleccionados = m_lista_destinatarios->selectedItems();
    if (seleccionados.isEmpty()) {
        m_visor_difusion->append("<i style='color:#ff6b6b;'>"
                                 "Selecciona al menos un destinatario.</i>");
        return;
    }

    QStringList nombres;
    for (auto *elem : seleccionados)
        nombres << elem->text();

    m_visor_difusion->append(QString(
        "<div style='text-align:right;'>"
        "<span style='background-color:%1; color:%2; padding:6px 12px;"
        "border-radius:12px; display:inline-block;'>%3</span>"
        "<br><small style='color:%2;'>→ %4</small></div>"
    ).arg(COLOR_BURBUJA_ENV, COLOR_TEXTO, texto, nombres.join(", ")));

    Messages sms;
    sms.sender         = m_mi_rank;
    sms.mode           = BROADCAST;
    sms.receiver_count = seleccionados.size();
    for (int i = 0; i < seleccionados.size(); i++)
        sms.receivers[i] = seleccionados[i]->data(Qt::UserRole).toInt();
    strncpy(sms.text, texto.toUtf8().constData(), sizeof(sms.text) - 1);
    send_messages(&sms, COORDINATOR, MESSAGE_TAG);

    m_entrada_difusion->clear();
}

void MainWindow::retroceder() {
    m_pila->setCurrentWidget(m_pagina_lista);
}

void MainWindow::mostrar_mensaje_recibido(int remitente, QString texto) {
    QString nombre = "Desconocido";
    if (m_rank_a_indice.contains(remitente))
        nombre = QString::fromUtf8(m_usuarios[m_rank_a_indice[remitente]].name);

    // Crear visor si no existe para este remitente
    if (!m_visores_chat.contains(remitente)) {
        auto *visor = new QTextEdit;
        visor->setReadOnly(true);
        visor->setStyleSheet("background-color: transparent; border: none;");
        visor->hide();
        m_visores_chat[remitente] = visor;
        m_area_chat->layout()->addWidget(visor);
    }

    m_visores_chat[remitente]->append(QString(
        "<div style='text-align:left;'>"
        "<small style='color:%1;'>%2</small><br>"
        "<span style='background-color:%3; color:%1; padding:6px 12px;"
        "border-radius:12px; display:inline-block;'>%4</span></div>"
    ).arg(COLOR_TEXTO, nombre, COLOR_BURBUJA_REC, texto));
}