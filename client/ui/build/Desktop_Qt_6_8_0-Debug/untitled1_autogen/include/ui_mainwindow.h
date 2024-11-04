/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
public:
  QWidget *centralwidget;
  QVBoxLayout *verticalLayout;
  QStackedWidget *stackedWidget;
  QWidget *Main;
  QVBoxLayout *verticalLayout_2;
  QSpacerItem *verticalSpacer;
  QHBoxLayout *hLayout;
  QPushButton *Create;
  QPushButton *EditorButton;
  QPushButton *Join;
  QPushButton *Exit;
  QWidget *CreateMenu;
  QVBoxLayout *verticalLayout_3;
  QSpacerItem *verticalSpacer_5;
  QGridLayout *gridLayout;
  QLabel *label;
  QLineEdit *player1namecreate;
  QLabel *LimitLabel;
  QComboBox *LimitPlayerQuantity;
  QComboBox *CreateLocalPlayers;
  QLineEdit *player1namecreate_2;
  QLineEdit *LobbyName;
  QLabel *label_2;
  QPushButton *connectCreat;
  QPushButton *BackButton;
  QSpacerItem *verticalSpacer_4;
  QWidget *Servidores;
  QVBoxLayout *verticalLayout_4;
  QListWidget *serverList;
  QPushButton *refreshButton;
  QPushButton *Volver;
  QWidget *Connecting;
  QVBoxLayout *verticalLayout_5;
  QSpacerItem *verticalSpacer_2;
  QLabel *LabelConnect;
  QComboBox *QuantityPlayers;
  QLineEdit *Player1NameInput;
  QLineEdit *Player2NameInput;
  QPushButton *Connect;
  QSpacerItem *verticalSpacer_3;
  QVBoxLayout *verticalLayout_6;
  QWidget *Lobby;
  QVBoxLayout *lobbyLayout;
  QLabel *lobbyTitle;
  QLabel *playerListLabel;
  QListWidget *playerList;
  QPushButton *startGameButton;
  QPushButton *leaveLobbyButton;

  void setupUi(QMainWindow *MainWindow) {
    if (MainWindow->objectName().isEmpty())
      MainWindow->setObjectName("MainWindow");
    MainWindow->resize(1146, 659);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName("centralwidget");
    QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding,
                           QSizePolicy::Policy::MinimumExpanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(
        centralwidget->sizePolicy().hasHeightForWidth());
    centralwidget->setSizePolicy(sizePolicy);
    centralwidget->setStyleSheet(QString::fromUtf8(
        "#centralwidget {\n"
        "    border-image: url(:/images/fondo.jpg) 0 0 0 0 stretch stretch;\n"
        "}"));
    verticalLayout = new QVBoxLayout(centralwidget);
    verticalLayout->setObjectName("verticalLayout");
    stackedWidget = new QStackedWidget(centralwidget);
    stackedWidget->setObjectName("stackedWidget");
    stackedWidget->setStyleSheet(QString::fromUtf8(""));
    Main = new QWidget();
    Main->setObjectName("Main");
    verticalLayout_2 = new QVBoxLayout(Main);
    verticalLayout_2->setObjectName("verticalLayout_2");
    verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum,
                                     QSizePolicy::Policy::Expanding);

    verticalLayout_2->addItem(verticalSpacer);

    hLayout = new QHBoxLayout();
    hLayout->setSpacing(5);
    hLayout->setObjectName("hLayout");
    Create = new QPushButton(Main);
    Create->setObjectName("Create");
    Create->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); /* "
                          "Marr\303\263n con transparencia */\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); /* "
                          "Marr\303\263n con m\303\241s transparencia */\n"
                          "}\n"
                          ""));

    hLayout->addWidget(Create);

    EditorButton = new QPushButton(Main);
    EditorButton->setObjectName("EditorButton");
    EditorButton->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); /* "
                          "Marr\303\263n con transparencia */\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); /* "
                          "Marr\303\263n con m\303\241s transparencia */\n"
                          "}\n"
                          ""));

    hLayout->addWidget(EditorButton);

    Join = new QPushButton(Main);
    Join->setObjectName("Join");
    Join->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); /* "
                          "Marr\303\263n con transparencia */\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); /* "
                          "Marr\303\263n con m\303\241s transparencia */\n"
                          "}\n"
                          ""));

    hLayout->addWidget(Join);

    Exit = new QPushButton(Main);
    Exit->setObjectName("Exit");
    Exit->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); /* "
                          "Marr\303\263n con transparencia */\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); /* "
                          "Marr\303\263n con m\303\241s transparencia */\n"
                          "}\n"
                          ""));

    hLayout->addWidget(Exit);

    verticalLayout_2->addLayout(hLayout);

    stackedWidget->addWidget(Main);
    CreateMenu = new QWidget();
    CreateMenu->setObjectName("CreateMenu");
    verticalLayout_3 = new QVBoxLayout(CreateMenu);
    verticalLayout_3->setObjectName("verticalLayout_3");
    verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum,
                                       QSizePolicy::Policy::Expanding);

    verticalLayout_3->addItem(verticalSpacer_5);

    gridLayout = new QGridLayout();
    gridLayout->setObjectName("gridLayout");
    label = new QLabel(CreateMenu);
    label->setObjectName("label");
    label->setStyleSheet(QString::fromUtf8("QLabel {\n"
                                           "    border: 4px solid #df9f1f; \n"
                                           "    color: #df9f1f; \n"
                                           "    font-family: \"Arial Black\";\n"
                                           "    font-size: 35px;\n"
                                           "    font-weight: bold;\n"
                                           "    text-transform: uppercase;\n"
                                           "    padding: 15px 30px;\n"
                                           "    margin: 10px;\n"
                                           "}"));

    gridLayout->addWidget(label, 3, 0, 1, 1);

    player1namecreate = new QLineEdit(CreateMenu);
    player1namecreate->setObjectName("player1namecreate");
    player1namecreate->setStyleSheet(
        QString::fromUtf8("QLineEdit {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}"));

    gridLayout->addWidget(player1namecreate, 5, 0, 1, 1);

    LimitLabel = new QLabel(CreateMenu);
    LimitLabel->setObjectName("LimitLabel");
    QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred,
                            QSizePolicy::Policy::Maximum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(LimitLabel->sizePolicy().hasHeightForWidth());
    LimitLabel->setSizePolicy(sizePolicy1);
    LimitLabel->setStyleSheet(
        QString::fromUtf8("QLabel {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}"));

    gridLayout->addWidget(LimitLabel, 1, 0, 1, 1);

    LimitPlayerQuantity = new QComboBox(CreateMenu);
    LimitPlayerQuantity->addItem(QString());
    LimitPlayerQuantity->addItem(QString());
    LimitPlayerQuantity->addItem(QString());
    LimitPlayerQuantity->addItem(QString());
    LimitPlayerQuantity->addItem(QString());
    LimitPlayerQuantity->setObjectName("LimitPlayerQuantity");
    LimitPlayerQuantity->setStyleSheet(
        QString::fromUtf8("QComboBox {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          ""));

    gridLayout->addWidget(LimitPlayerQuantity, 1, 1, 1, 1);

    CreateLocalPlayers = new QComboBox(CreateMenu);
    CreateLocalPlayers->addItem(QString());
    CreateLocalPlayers->addItem(QString());
    CreateLocalPlayers->setObjectName("CreateLocalPlayers");
    CreateLocalPlayers->setStyleSheet(
        QString::fromUtf8("QComboBox {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          ""));

    gridLayout->addWidget(CreateLocalPlayers, 3, 1, 1, 1);

    player1namecreate_2 = new QLineEdit(CreateMenu);
    player1namecreate_2->setObjectName("player1namecreate_2");
    player1namecreate_2->setStyleSheet(
        QString::fromUtf8("QLineEdit {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}"));

    gridLayout->addWidget(player1namecreate_2, 5, 1, 1, 1);

    LobbyName = new QLineEdit(CreateMenu);
    LobbyName->setObjectName("LobbyName");
    LobbyName->setStyleSheet(
        QString::fromUtf8("QLineEdit {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}"));

    gridLayout->addWidget(LobbyName, 0, 1, 1, 1);

    label_2 = new QLabel(CreateMenu);
    label_2->setObjectName("label_2");
    label_2->setStyleSheet(
        QString::fromUtf8("QLabel {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}"));

    gridLayout->addWidget(label_2, 0, 0, 1, 1);

    verticalLayout_3->addLayout(gridLayout);

    connectCreat = new QPushButton(CreateMenu);
    connectCreat->setObjectName("connectCreat");
    connectCreat->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); \n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); \n"
                          "}"));

    verticalLayout_3->addWidget(connectCreat);

    BackButton = new QPushButton(CreateMenu);
    BackButton->setObjectName("BackButton");
    BackButton->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); \n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); \n"
                          "}\n"
                          ""));

    verticalLayout_3->addWidget(BackButton);

    verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum,
                                       QSizePolicy::Policy::Expanding);

    verticalLayout_3->addItem(verticalSpacer_4);

    stackedWidget->addWidget(CreateMenu);
    Servidores = new QWidget();
    Servidores->setObjectName("Servidores");
    verticalLayout_4 = new QVBoxLayout(Servidores);
    verticalLayout_4->setObjectName("verticalLayout_4");
    serverList = new QListWidget(Servidores);
    serverList->setObjectName("serverList");
    serverList->setStyleSheet(QString::fromUtf8(
        "QListView {\n"
        "    background-color: #2E2E2E;     /* Fondo gris */\n"
        "    color: #FFFFFF;                /* Texto blanco */\n"
        "    border: 1px solid #444444;     /* Borde */\n"
        "    selection-background-color: #4D4D4D; /* Fondo seleccionado */\n"
        "    selection-color: #FFFFFF;      /* Texto seleccionado */\n"
        "}\n"
        "\n"
        "QListView::item {\n"
        "    padding: 10px;                 /* Espaciado en los \303\255tems "
        "*/\n"
        "    border-bottom: 1px solid #444444; /* Borde entre \303\255tems */\n"
        "}\n"
        "\n"
        "QListView::item:selected {\n"
        "    background-color: #4D4D4D;     /* Fondo del \303\255tem "
        "seleccionado */\n"
        "}\n"
        ""));

    verticalLayout_4->addWidget(serverList);

    refreshButton = new QPushButton(Servidores);
    refreshButton->setObjectName("refreshButton");
    refreshButton->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); /* "
                          "Marr\303\263n con transparencia */\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); /* "
                          "Marr\303\263n con m\303\241s transparencia */\n"
                          "}\n"
                          ""));

    verticalLayout_4->addWidget(refreshButton);

    Volver = new QPushButton(Servidores);
    Volver->setObjectName("Volver");
    Volver->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); /* "
                          "Marr\303\263n con transparencia */\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); /* "
                          "Marr\303\263n con m\303\241s transparencia */\n"
                          "}\n"
                          ""));

    verticalLayout_4->addWidget(Volver);

    stackedWidget->addWidget(Servidores);
    Connecting = new QWidget();
    Connecting->setObjectName("Connecting");
    verticalLayout_5 = new QVBoxLayout(Connecting);
    verticalLayout_5->setObjectName("verticalLayout_5");
    verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum,
                                       QSizePolicy::Policy::Expanding);

    verticalLayout_5->addItem(verticalSpacer_2);

    LabelConnect = new QLabel(Connecting);
    LabelConnect->setObjectName("LabelConnect");
    LabelConnect->setStyleSheet(
        QString::fromUtf8("QLabel {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}"));

    verticalLayout_5->addWidget(LabelConnect);

    QuantityPlayers = new QComboBox(Connecting);
    QuantityPlayers->addItem(QString());
    QuantityPlayers->addItem(QString());
    QuantityPlayers->setObjectName("QuantityPlayers");
    QuantityPlayers->setStyleSheet(
        QString::fromUtf8("QComboBox {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QComboBox::drop-down {\n"
                          "    border: none; \n"
                          "}\n"
                          "\n"
                          "QComboBox::item {\n"
                          "    color: #df9f1f; \n"
                          "}\n"
                          "\n"
                          ""));

    verticalLayout_5->addWidget(QuantityPlayers);

    Player1NameInput = new QLineEdit(Connecting);
    Player1NameInput->setObjectName("Player1NameInput");
    Player1NameInput->setStyleSheet(
        QString::fromUtf8("QLineEdit {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "\n"
                          ""));

    verticalLayout_5->addWidget(Player1NameInput);

    Player2NameInput = new QLineEdit(Connecting);
    Player2NameInput->setObjectName("Player2NameInput");
    Player2NameInput->setStyleSheet(
        QString::fromUtf8("QLineEdit {\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          ""));

    verticalLayout_5->addWidget(Player2NameInput);

    Connect = new QPushButton(Connecting);
    Connect->setObjectName("Connect");
    Connect->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 35px;\n"
                          "    font-weight: bold;\n"
                          "    text-transform: uppercase;\n"
                          "    padding: 15px 30px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1); /* "
                          "Marr\303\263n con transparencia */\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2); /* "
                          "Marr\303\263n con m\303\241s transparencia */\n"
                          "}\n"
                          ""));

    verticalLayout_5->addWidget(Connect);

    verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum,
                                       QSizePolicy::Policy::Expanding);

    verticalLayout_5->addItem(verticalSpacer_3);

    verticalLayout_6 = new QVBoxLayout();
    verticalLayout_6->setObjectName("verticalLayout_6");

    verticalLayout_5->addLayout(verticalLayout_6);

    stackedWidget->addWidget(Connecting);
    Lobby = new QWidget();
    Lobby->setObjectName("Lobby");
    lobbyLayout = new QVBoxLayout(Lobby);
    lobbyLayout->setObjectName("lobbyLayout");
    lobbyTitle = new QLabel(Lobby);
    lobbyTitle->setObjectName("lobbyTitle");
    lobbyTitle->setStyleSheet(QString::fromUtf8("QLabel {\n"
                                                "    font-size: 24px;\n"
                                                "    font-weight: bold;\n"
                                                "    color: #df9f1f;\n"
                                                "}"));

    lobbyLayout->addWidget(lobbyTitle);

    playerListLabel = new QLabel(Lobby);
    playerListLabel->setObjectName("playerListLabel");
    playerListLabel->setStyleSheet(QString::fromUtf8("QLabel {\n"
                                                     "    font-size: 18px;\n"
                                                     "    color: #ffffff;\n"
                                                     "}"));

    lobbyLayout->addWidget(playerListLabel);

    playerList = new QListWidget(Lobby);
    playerList->setObjectName("playerList");
    playerList->setStyleSheet(
        QString::fromUtf8("QListView {\n"
                          "    background-color: #2E2E2E;\n"
                          "    color: #FFFFFF;\n"
                          "    border: 1px solid #444444;\n"
                          "}"));

    lobbyLayout->addWidget(playerList);

    startGameButton = new QPushButton(Lobby);
    startGameButton->setObjectName("startGameButton");
    startGameButton->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 20px;\n"
                          "    font-weight: bold;\n"
                          "    padding: 10px 20px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1);\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2);\n"
                          "}"));

    lobbyLayout->addWidget(startGameButton);

    leaveLobbyButton = new QPushButton(Lobby);
    leaveLobbyButton->setObjectName("leaveLobbyButton");
    leaveLobbyButton->setStyleSheet(
        QString::fromUtf8("QPushButton {\n"
                          "    background-color: transparent;\n"
                          "    border: 4px solid #df9f1f; \n"
                          "    color: #df9f1f; \n"
                          "    font-family: \"Arial Black\";\n"
                          "    font-size: 20px;\n"
                          "    font-weight: bold;\n"
                          "    padding: 10px 20px;\n"
                          "    margin: 10px;\n"
                          "}\n"
                          "\n"
                          "QPushButton:hover {\n"
                          "    background-color: rgba(139, 69, 19, 0.1);\n"
                          "}\n"
                          "\n"
                          "QPushButton:pressed {\n"
                          "    background-color: rgba(139, 69, 19, 0.2);\n"
                          "}"));

    lobbyLayout->addWidget(leaveLobbyButton);

    stackedWidget->addWidget(Lobby);

    verticalLayout->addWidget(stackedWidget);

    MainWindow->setCentralWidget(centralwidget);

    retranslateUi(MainWindow);

    stackedWidget->setCurrentIndex(1);

    QMetaObject::connectSlotsByName(MainWindow);
  } // setupUi

  void retranslateUi(QMainWindow *MainWindow) {
    MainWindow->setWindowTitle(QCoreApplication::translate(
        "MainWindow", "Selector de Servidores", nullptr));
    Create->setText(
        QCoreApplication::translate("MainWindow", "Create", nullptr));
    EditorButton->setText(
        QCoreApplication::translate("MainWindow", "Editor", nullptr));
    Join->setText(QCoreApplication::translate("MainWindow", "Join", nullptr));
    Exit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
    label->setText(
        QCoreApplication::translate("MainWindow", "Local Players", nullptr));
    player1namecreate->setText(
        QCoreApplication::translate("MainWindow", "Player 1", nullptr));
    LimitLabel->setText(
        QCoreApplication::translate("MainWindow", "Player Limits", nullptr));
    LimitPlayerQuantity->setItemText(
        0, QCoreApplication::translate("MainWindow", "2", nullptr));
    LimitPlayerQuantity->setItemText(
        1, QCoreApplication::translate("MainWindow", "3", nullptr));
    LimitPlayerQuantity->setItemText(
        2, QCoreApplication::translate("MainWindow", "4", nullptr));
    LimitPlayerQuantity->setItemText(
        3, QCoreApplication::translate("MainWindow", "5", nullptr));
    LimitPlayerQuantity->setItemText(
        4, QCoreApplication::translate("MainWindow", "6", nullptr));

    CreateLocalPlayers->setItemText(
        0, QCoreApplication::translate("MainWindow", "1", nullptr));
    CreateLocalPlayers->setItemText(
        1, QCoreApplication::translate("MainWindow", "2", nullptr));

    player1namecreate_2->setText(
        QCoreApplication::translate("MainWindow", "Player 2 ", nullptr));
    LobbyName->setText(QString());
    label_2->setText(
        QCoreApplication::translate("MainWindow", "Lobby Name", nullptr));
    connectCreat->setText(
        QCoreApplication::translate("MainWindow", "Connect", nullptr));
    BackButton->setText(
        QCoreApplication::translate("MainWindow", "Volver", nullptr));
    refreshButton->setText(
        QCoreApplication::translate("MainWindow", "Refresh", nullptr));
    Volver->setText(
        QCoreApplication::translate("MainWindow", "Volver", nullptr));
    LabelConnect->setText(
        QCoreApplication::translate("MainWindow", "Players", nullptr));
    QuantityPlayers->setItemText(
        0, QCoreApplication::translate("MainWindow", "1", nullptr));
    QuantityPlayers->setItemText(
        1, QCoreApplication::translate("MainWindow", "2", nullptr));

    Player1NameInput->setText(
        QCoreApplication::translate("MainWindow", "Player 1 ", nullptr));
    Player2NameInput->setText(
        QCoreApplication::translate("MainWindow", "Player 2", nullptr));
    Connect->setText(
        QCoreApplication::translate("MainWindow", "Connect", nullptr));
    lobbyTitle->setText(
        QCoreApplication::translate("MainWindow", "Lobby", nullptr));
    playerListLabel->setText(QCoreApplication::translate(
        "MainWindow", "Jugadores Conectados:", nullptr));
    startGameButton->setText(
        QCoreApplication::translate("MainWindow", "Iniciar Juego", nullptr));
    leaveLobbyButton->setText(
        QCoreApplication::translate("MainWindow", "Salir del Lobby", nullptr));
  } // retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
