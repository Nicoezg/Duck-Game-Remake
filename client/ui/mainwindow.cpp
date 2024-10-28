// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_editor.h"
#include "./ui_mainwindow.h"
#include "editor.h"
#include <QFile>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  // Establecer un tamaño fijo para la ventana
  this->setFixedSize(1366, 768);

  // Configurar la interfaz de usuario
  ui->setupUi(this);
  this->setWindowTitle("Duck Game");
  // setupAudio();
  setupEditor();
}

MainWindow::~MainWindow() {
  delete player;
  delete audio;
  delete ui;
}

void MainWindow::RefreshServerList() {
  ui->serverList->clear();

  QStringList servers = {"Servidor 1 - Online (25/50 jugadores)",
                         "Servidor 2 - Online (12/30 jugadores)",
                         "Servidor 3 - Online (0/50 jugadores)",
                         "Servidor 4 - Online (3/20 jugadores)"};

  // Agrega cada servidor al QListWidget
  ui->serverList->addItems(servers);

  connect(ui->serverList, &QListWidget::itemClicked, this,
          [this](QListWidgetItem *item) {
            ui->Player2NameJoin->hide();
            ui->stackedWidget->setCurrentIndex(3);
          });
}

void MainWindow::setupServerList() {
  ui->serverList->clear();
  // Agregar servidores de ejemplo al QListWidget

  QStringList servers = {"Servidor 1 - Online (25/50 jugadores)",
                         "Servidor 2 - Online (12/30 jugadores)",
                         "Servidor 3 - Online (48/100 jugadores)",
                         "Servidor 4 - Online (3/20 jugadores)"};

  ui->serverList->addItems(servers);

  // Conectar la señal de selección de servidor
  connect(ui->serverList, &QListWidget::itemClicked, this,
          [this](QListWidgetItem *item) {
            ui->Player2NameJoin->hide();
            ui->stackedWidget->setCurrentIndex(3);
          });
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
  if (status == QMediaPlayer::EndOfMedia) {
    player->setPosition(0);
    player->play();
  }
}

void MainWindow::setupAudio() {
  player = new QMediaPlayer(this);
  audio = new QAudioOutput(this);
  player->setAudioOutput(audio);

  audio->setVolume(0.6);

  player->setSource(QUrl("qrc:/sound/menumusic.wav"));

  connect(player, &QMediaPlayer::mediaStatusChanged, this,
          &MainWindow::onMediaStatusChanged);

  // Reproducir
  player->play();
}

void MainWindow::resizeEvent(QResizeEvent *event) {}

void MainWindow::setupEditor() {
  Editor *editor = new Editor(this);

  ui->stackedWidget->addWidget(editor);
}

void MainWindow::on_Join_clicked() {
  setupServerList();
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Exit_clicked() { close(); }

void MainWindow::on_Create_clicked() {
  if (ui->CreateLocalPlayers->currentIndex() == 0) {
    ui->player2namecreate->hide();
  } else {
    ui->player2namecreate->show();
  }
  ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_Volver_clicked() { ui->stackedWidget->setCurrentIndex(0); }

void MainWindow::on_BackButton_clicked() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_EditorButton_clicked() {
  ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_refreshButton_clicked() { RefreshServerList(); }

void MainWindow::on_Connect_clicked() { ui->stackedWidget->setCurrentIndex(4); }

void MainWindow::on_leaveLobbyButton_clicked() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_connectCreat_clicked() {
  ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_QuantityPlayers_activated(int index) {
  if (index == 0) {
    ui->Player2NameJoin->hide();
  } else {
    ui->Player2NameJoin->show();
  }
}

void MainWindow::on_CreateLocalPlayers_activated(int index) {
  if (index == 0) {
    ui->player2namecreate->hide();
  } else {
    ui->player2namecreate->show();
  }
}
