#include "editor.h"
#include "ui_editor.h"
#include <QDir>
#include <QLabel>

Editor::Editor(QWidget *parent) : QWidget(parent), ui(new Ui::Editor) {
  ui->setupUi(this);
  cargarTodosLosTiles();
}

Editor::~Editor() { delete ui; }

QStringList Editor::obtenerArchivosImagen(const QString &directorio) {
  QDir dir(directorio);
  QStringList archivos = dir.entryList(QDir::Files);
  QStringList archivosImagen;
  for (const QString &archivo : archivos) {
    if (archivo.endsWith(".png")) {
      archivosImagen.append(archivo);
    }
  }
  return archivosImagen;
}

void Editor::cargarTilesEnGrilla(const QStringList &archivos,
                                 const QString &rutaBase, int &fila,
                                 int &columna) {
  const int columnasMax = 5;  // Ajusta según la cantidad de columnas deseadas
  const int tileSide = 16;    // Tamaño de cada tile
  const int displaySize = 64; // Tamaño de visualización en la UI

  for (const QString &archivo : archivos) {
    // Cargar el spritesheet completo
    QPixmap spritesheet(rutaBase + "/" + archivo);

    // Calcular cuántos tiles hay en cada dirección
    int tilesX = spritesheet.width() / tileSide;
    int tilesY = spritesheet.height() / tileSide;

    // Recorrer el spritesheet y extraer cada tile
    for (int y = 0; y < tilesY; y++) {
      for (int x = 0; x < tilesX; x++) {
        // Crear un label para este tile
        QLabel *label = new QLabel();

        // Extraer el tile de 16x16 del spritesheet
        QPixmap tile =
            spritesheet.copy(x * tileSide, y * tileSide, tileSide, tileSide);

        // Escalar el tile al tamaño de visualización (64x64)
        QPixmap scaledTile =
            tile.scaled(displaySize, displaySize, Qt::KeepAspectRatio,
                        Qt::FastTransformation);

        // Configurar el label
        label->setPixmap(scaledTile);
        label->setFixedSize(displaySize, displaySize);

        // Almacenar el tile original (16x16) como propiedad del label para uso
        // posterior
        label->setProperty("originalTile", tile);

        // Añadir el label al layout
        ui->tilesLayout->addWidget(label, fila, columna);

        // Mover a la siguiente celda
        columna++;
        if (columna >= columnasMax) {
          columna = 0;
          fila++;
        }
      }
    }
  }
}

void Editor::cargarTodosLosTiles() {

  ui->tilesLayout->setContentsMargins(0, 0, 0, 0);
  ui->tilesLayout->setHorizontalSpacing(0);
  ui->tilesLayout->setVerticalSpacing(0);

  int fila = 0;
  int columna = 0;

  QStringList archivos1 = obtenerArchivosImagen(":/images/sprites");
  cargarTilesEnGrilla(archivos1, ":/images/sprites", fila, columna);
}
