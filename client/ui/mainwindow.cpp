// mainwindow.cpp
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "common/actions/connection/join.h"
#include "common/actions/connection/refresh_games.h"
#include <QListWidgetItem>
#include <QMessageBox>
#include <QPixmap>

#define MENU_ID 0
#define CREATE_ID 1
#define SERVERS_ID 2
#define JOIN_ID 3
#define LOBBY_ID 4

MainWindow::MainWindow(Client *client, QWidget *parent)
    : QMainWindow(parent), client(client), ui(new Ui::MainWindow) {

  // Configurar la interfaz de usuario
  ui->setupUi(this);
  setWindowTitle("Duck Game");
  setupAudio();

  // Conectar la señal aboutToQuit a la ranura handleAboutToQuit
  connect(QApplication::instance(), &QApplication::aboutToQuit, this,
          &MainWindow::handleAboutToQuit);

  ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow() {
  player->stop();
  delete player;
  delete audio;
  delete ui;
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status) {
  if (status >= QMediaPlayer::EndOfMedia) {
    player->setPosition(0);
    player->play();
  }
}

void MainWindow::setupAudio() {
  player = new QMediaPlayer(this);
  audio = new QAudioOutput(this);
  player->setAudioOutput(audio);

  audio->setVolume(0.1);

  player->setSource(QUrl("qrc:/sound/menumusic.wav"));

  connect(player, &QMediaPlayer::mediaStatusChanged, this,
          &MainWindow::onMediaStatusChanged);

  // Reproducir
  player->play();
}

static std::vector<QColor> colors = {
    QColor(255, 255, 255), QColor(255, 0, 0),     QColor(238, 158, 213),
    QColor(231, 111, 15),  QColor(154, 154, 154), QColor(255, 255, 0)};

void MainWindow::update_players_list(const Event &event) {
  ui->playerList->clear(); // Limpia la lista

  QString ss = QString("Jugadores conectados: %1/%2")
                   .arg(event.get_actual_players())
                   .arg(event.get_max_players());
  ui->playerListLabel->setText(ss);

  for (const auto &player_data : event.get_players_data()) {
    // Crear el texto como QString
    QString player_string = QString("Name: %1 Id: %2")
                                .arg(player_data.get_name().c_str())
                                .arg(player_data.get_id());

    // Crear un QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(player_string);

    // Cambiar color según ID
    int id = player_data.get_id();
    if ((id - 1) < int(colors.size())) { // Verificar que el índice sea válido
      item->setForeground(colors[id - 1]);
    }

    // Agregar el ítem a la lista
    ui->playerList->addItem(item);
  }

  // Lógica adicional para mostrar/ocultar el botón
  if (client->get_player_id_1() != 1) {
    ui->startGameButton->hide();
  }
}

void MainWindow::RefreshServerList(Event &event) {
  ui->serverList->clear();

  ui->LobbyName->setText(QString("Sala %1").arg(event.get_games().size() + 1));

  std::list<GameRoom> game_rooms = event.get_games();
  for (auto &game : game_rooms) {
    // Crear el texto del servidor
    QString server_text = QString("Servidor %1 | %2 - Online (%3/%4 jugadores)")
                              .arg(game.get_game_code())
                              .arg(game.get_game_name().c_str())
                              .arg(game.get_actual_players())
                              .arg(game.get_max_players());

    // Crear el QListWidgetItem
    QListWidgetItem *item = new QListWidgetItem(server_text);

    // Agregar el ítem a la lista
    ui->serverList->addItem(item);

    // Conectar el evento al ítem
    connect(ui->serverList, &QListWidget::itemClicked, this,
            [this, item, &game]() {
              // Cambiar al widget deseado
              ui->Player2NameJoin->hide();
              ui->stackedWidget->setCurrentIndex(JOIN_ID);
              ui->Player1NameJoin->setText(
                  QString("Player %1").arg(game.get_actual_players() + 1));
              ui->Player2NameJoin->setText(
                  QString("Player %1").arg(game.get_actual_players() + 2));

              // Establecer el código del juego seleccionado en el cliente
              client->set_game_code(game.get_game_code());
              if (game.get_actual_players() + 1 >= game.get_max_players()) {
                ui->GameModeJoin->setEnabled(false);
              }
            });
  }
}

void MainWindow::setupServerList() {
  std::shared_ptr<Action> action = std::make_shared<RefreshGames>();
  client->send_action(action);
}

void MainWindow::show_connected_players(const Event &event) {
  if (!event.is_connected()) {
    ui->GameModeJoin->setCurrentIndex(0);
    ui->GameModeJoin->activated(0);
    on_Join_clicked();
    return;
  }

  GameRoom game_room = event.get_game_room();
  ui->lobbyTitle->setText(game_room.get_game_name().c_str());
  update_players_list(event);
}

void MainWindow::on_GameModeCreate_activated(int index) {
  if (index == 0) {
    ui->player2namecreate->hide();
  } else {
    ui->player2namecreate->show();
  }
}

void MainWindow::on_GameModeJoin_activated(int index) {
  if (index == 0) {
    ui->Player2NameJoin->hide();
  } else {
    ui->Player2NameJoin->show();
  }
}

void MainWindow::on_Volver_clicked() { ui->stackedWidget->setCurrentIndex(0); }

void MainWindow::on_BackButton_clicked() {
  ui->stackedWidget->setCurrentIndex(MENU_ID);
}

void MainWindow::on_leaveLobbyButton_clicked() {
  ui->stackedWidget->setCurrentIndex(MENU_ID);
}
void MainWindow::on_Exit_clicked() { exit(); }

void MainWindow::handleAboutToQuit() {
  if (client->is_closed()) {
    return;
  }
  if (client->is_connected()) {
    close();
    return;
  }
  exit();
}

void MainWindow::on_Create_clicked() {
  if (client->is_connected()) {
    ui->stackedWidget->setCurrentIndex(LOBBY_ID);
    return;
  }
  if (ui->GameModeCreate->currentIndex() == 0) {
    ui->player2namecreate->hide();
  } else {
    ui->player2namecreate->show();
  }

  ui->stackedWidget->setCurrentIndex(CREATE_ID);
}

void MainWindow::on_connectCreat_clicked() {
  std::shared_ptr<Action> action;
  std::string game_name = ui->LobbyName->text().toStdString();
  int max_players = ui->LimitPlayerQuantity->currentText().toInt();
  std::string player_name_1 = ui->player1namecreate->text().toStdString();
  std::string player_name_2;

  GameMode mode = UN_JUGADOR;
  if (ui->GameModeCreate->currentIndex() != 0) {
    mode = DOS_JUGADORES;
    player_name_2 = ui->player2namecreate->text().toStdString();
  }

  action = std::make_shared<Create>(mode, max_players, game_name, player_name_1,
                                    player_name_2);

  client->send_action(action);

  ui->stackedWidget->setCurrentIndex(LOBBY_ID);
}

void MainWindow::on_startGameButton_clicked() {
  std::shared_ptr<Action> action = std::make_shared<Action>(START);
  client->send_action(action);
}

void MainWindow::on_Join_clicked() {
  if (client->is_connected()) {
    ui->stackedWidget->setCurrentIndex(LOBBY_ID);
    return;
  }
  setupServerList();
  ui->stackedWidget->setCurrentIndex(SERVERS_ID);
}

void MainWindow::on_refreshButton_clicked() {
  std::shared_ptr<Action> action = std::make_shared<RefreshGames>();
  client->send_action(action);
}

void MainWindow::on_Connect_clicked() {
  std::string player_name_1 = ui->Player1NameJoin->text().toStdString();
  std::string player_name_2;

  GameMode mode = UN_JUGADOR;
  if (ui->GameModeJoin->currentIndex() != 0) {
    mode = DOS_JUGADORES;
    player_name_2 = ui->Player2NameJoin->text().toStdString();
  }

  int game_code = client->get_game_code();
  std::shared_ptr<Action> action =
      std::make_shared<Join>(game_code, mode, player_name_1, player_name_2);

  client->send_action(action);

  ui->stackedWidget->setCurrentIndex(LOBBY_ID);
}

void MainWindow::exit() {
  client->close();
  close();
}
