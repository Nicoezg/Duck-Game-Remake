#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "editor.h"
#include <QMainWindow>
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

private:
  Editor *editor;
  Ui::MainWindow *ui;
  void setupEditor();
};
#endif // MAINWINDOW_H
