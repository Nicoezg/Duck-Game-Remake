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

  void RefreshServerList(Event &event);

  void exit();

  void show_connected_players(const Event &event);

  void update_players_list(const Event &event);

  ~MainWindow();

private slots:

  void on_Create_clicked();

  void on_GameModeCreate_activated(int index);

  void on_connectCreat_clicked();

  void on_startGameButton_clicked();

  void on_Join_clicked();

  void on_refreshButton_clicked();

  void on_Connect_clicked();

  void on_GameModeJoin_activated(int index);

  void on_Volver_clicked();

  void on_BackButton_clicked();

  void on_Exit_clicked();

  void on_leaveLobbyButton_clicked();

  void handleAboutToQuit();

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
