// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "client/communication/client.h"
#include <QAudioOutput>
#include <QMainWindow>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(Client *client, QWidget *parent = nullptr);

  void RefreshServerList(const std::shared_ptr<Event> &event);

  void exit();

  void show_connected_players(const std::shared_ptr<Event> &event,
                              const int game_code);

  ~MainWindow();

private slots:

  void on_startGameButton_clicked();

  void on_Join_clicked();

  void on_Exit_clicked();

  void on_Create_clicked();

  void on_Volver_clicked();

  void on_BackButton_clicked();

  void on_refreshButton_clicked();

  void on_Connect_clicked();

  void on_leaveLobbyButton_clicked();

  void on_connectCreat_clicked();

  void on_GameModeJoin_activated(int index);

  void on_GameModeCreate_activated(int index);

private:
  Client *client;
  Ui::MainWindow *ui;
  QMediaPlayer *player;
  QAudioOutput *audio;

  void setupServerList();

  void onMediaStatusChanged(QMediaPlayer::MediaStatus status);


  void setupAudio();

};

#endif // MAINWINDOW_H
