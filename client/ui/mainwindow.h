// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:

  void on_Join_clicked();

  void on_Exit_clicked();

  void on_Create_clicked();

  void on_Volver_clicked();

  void on_BackButton_clicked();

  void on_EditorButton_clicked();

  void on_refreshButton_clicked();

  void on_Connect_clicked();

  void on_leaveLobbyButton_clicked();

  void on_connectCreat_clicked();

  void on_QuantityPlayers_activated(int index);

  void on_CreateLocalPlayers_activated(int index);

private:
  Ui::MainWindow *ui;
  QMediaPlayer *player;
  QAudioOutput *audio;
  void setupServerList();
  void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
  void RefreshServerList();
  void resizeEvent(QResizeEvent *event);
  void setupAudio();
  void setupEditor();
};

#endif // MAINWINDOW_H
