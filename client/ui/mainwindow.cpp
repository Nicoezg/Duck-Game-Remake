// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_editor.h"
#include "./ui_mainwindow.h"
#include "editor.h"
#include "common/actions/connection/refresh_games.h"
#include "common/actions/connection/join.h"
#include <QFile>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPalette>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), client("localhost", "4040"), ui(new Ui::MainWindow) {
    // Establecer un tamaño fijo para la ventana

    // Configurar la interfaz de usuario
    ui->setupUi(this);
    this->setWindowTitle("Duck Game");
    // setupAudio();
    setupEditor();
    client.run();
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
    client.close();

    delete player;
    delete audio;
    delete editor;
    delete ui;

}

void MainWindow::RefreshServerList() {
    ui->serverList->clear();

    std::shared_ptr<Action> action = std::make_shared<RefreshGames>();
    std::shared_ptr<Event> event = client.run_command(action);


    QStringList servers;

    for (auto &game: event->get_games()) {
        std::string ss = "Servidor " + std::to_string(game.get_game_code()) + " - Online (" +
                         std::to_string(game.get_actual_players()) + "/" +
                         std::to_string(game.get_max_players()) + " jugadores)";
        servers.append(ss.c_str());
    }

    // Agrega cada servidor al QListWidget
    ui->serverList->addItems(servers);

    connect(ui->serverList, &QListWidget::itemClicked, this,
            [this](QListWidgetItem *item) {
                ui->Player2NameJoin->hide();
                ui->stackedWidget->setCurrentIndex(3);
                client.set_game_code(item->text().split(" ")[1].toInt());
            });
}

void MainWindow::setupServerList() {
    RefreshServerList();
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

void MainWindow::resizeEvent(QResizeEvent *) {}

void MainWindow::setupEditor() {
    Editor *editor2 = new Editor(this);

    ui->stackedWidget->addWidget(editor2);
}

void MainWindow::on_Join_clicked() {
    setupServerList();
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_Exit_clicked() { close(); }

void MainWindow::on_Create_clicked() {
    if (ui->GameModeCreate->currentIndex() == 0) {
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

void MainWindow::on_Connect_clicked() {
    GameMode mode = UN_JUGADOR;

    client.set_player_1_name(ui->player1namecreate->text().toStdString());
    if (ui->GameModeJoin->currentIndex() == 1) {
        mode = DOS_JUGADORES;
        client.set_player_2_name(ui->player2namecreate->text().toStdString());
    }

    int game_code = client.get_game_code();
    std::shared_ptr<Action> action = std::make_shared<Join>(game_code, mode);

    auto event = client.run_command(action);

    std::string ss = "Servidor " + std::to_string(game_code) +
                     " | Jugadores conectados: " +
                     std::to_string(event->get_actual_players()) + "/" +
                     std::to_string(event->get_max_players());

    ui->playerListLabel->setText(ss.c_str());
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_leaveLobbyButton_clicked() {
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_connectCreat_clicked() {
    std::shared_ptr<Action> action;
    int max_players = ui->LimitPlayerQuantity->currentText().toInt();
    if (ui->GameModeCreate->currentIndex() == 0) {
        action = std::make_shared<Create>(UN_JUGADOR, max_players);
    } else {
        action = std::make_shared<Create>(DOS_JUGADORES, max_players);
        client.set_player_2_name(ui->player2namecreate->text().toStdString());
    }

    client.set_player_1_name(ui->player1namecreate->text().toStdString());
    auto event = client.run_command(action);

    std::string ss = "Servidor " + std::to_string(event->get_game_code()) +
                     " | Jugadores conectados: " +
                     std::to_string(event->get_actual_players()) + "/" +
                     std::to_string(event->get_max_players());

    ui->playerListLabel->setText(ss.c_str());
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_GameModeJoin_activated(int index) {
    if (index == 0) {
        ui->Player2NameJoin->hide();
    } else {
        ui->Player2NameJoin->show();
    }
}

void MainWindow::on_GameModeCreate_activated(int index) {
    if (index == 0) {
        ui->player2namecreate->hide();
    } else {
        ui->player2namecreate->show();
    }
}

