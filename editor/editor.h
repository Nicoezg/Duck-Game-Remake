#ifndef EDITOR_H
#define EDITOR_H

#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <vector>

#include "../common/configs/configurations.h"
#include "yamlhandler.h"
#define CONFIG Configurations::configurations()
namespace Ui {
class Editor;
}

class Editor : public QWidget {
  Q_OBJECT

public:
  explicit Editor(QWidget *parent = nullptr);
  ~Editor();

  // cppcheck-suppress unknownMacro
private slots:
  void on_ExitButton_clicked();
  void on_EraseButton_clicked();
  void on_SaveButton_clicked();
  void on_LoadButton_clicked();
  void on_EraiserButton_clicked();

protected:
  bool eventFilter(QObject *obj, QEvent *event) override;

private:
  Ui::Editor *ui;
  QPixmap *sprite_actual;
  int tileID;
  std::vector<QPixmap> tiles;
  YamlHandler yamlHandler;
  int filas;
  int columnas;
  QStringList obtenerArchivosImagen(const QString &directorio);
  void cargarTilesEnGrilla(const QString &nombre, const QString &rutaBase,
                           int &fila, int &columna);
  void cargarTodosLosTiles();
  void crearMapaVacio(int filas, int columnas);
  void cleanLayout(QGridLayout *layout);
  void cambiarFondo(int index);
};

#endif // EDITOR_H
