#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>

namespace Ui {
class Editor;
}

class Editor : public QWidget {
  Q_OBJECT

public:
  explicit Editor(QWidget *parent = nullptr);
  ~Editor();

  private slots:
  void on_Menu_clicked();

  private:
  Ui::Editor *ui;
  QStringList obtenerArchivosImagen(const QString &directorio);
  void cargarTilesEnGrilla(const QStringList &archivos, const QString &rutaBase,
                           int &fila, int &columna);
  void cargarTodosLosTiles();
  void crearMapaVacio(int filas, int columnas);
};

#endif // EDITOR_H
