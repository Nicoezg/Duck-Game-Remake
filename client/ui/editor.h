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

private:
  Ui::Editor *ui;
  QStringList obtenerArchivosImagen(const QString &directorio);
  void cargarTilesEnGrilla(const QStringList &archivos, const QString &rutaBase,
                           int &fila, int &columna);
  void cargarTodosLosTiles();
};

#endif // EDITOR_H
