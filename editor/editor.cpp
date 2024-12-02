#include "editor.h"
#include "ui_editor.h"
#include <QDir>
#include <QFile>
#include <QGridLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QFileDialog>
#include <iostream>
#include <yaml-cpp/yaml.h>
#define TOTAL_TILES 52
#define SPAWN_TILE 48
#define INTERACTUABLES_START 49
#define FILAS 30
#define COLUMNAS 40
#define EMPTY_TILE -1
#define MAP_GRID_ID 1
#define TILES_GRID_ID 0

Editor::Editor(QWidget *parent)
    : QWidget(parent), ui(new Ui::Editor), sprite_actual(nullptr), tileID(EMPTY_TILE){
  ui->setupUi(this);
  

  cargarTodosLosTiles();
  
  filas=FILAS;
  columnas=COLUMNAS;


  crearMapaVacio(filas, columnas);
  connect(ui->backgroundBox, &QComboBox::currentIndexChanged, this,
          &Editor::cambiarFondo);
}

Editor::~Editor() {
  cleanLayout(ui->tilesLayout);
  cleanLayout(ui->mapLayout);
  if (sprite_actual) {
    delete sprite_actual;
  }
  delete ui;
}

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

void Editor::cargarTilesEnGrilla(const QString &nombre, const QString &rutaBase,
                                 int &fila, int &columna) {
  const int columnasMax = 4;  // Ajusta según la cantidad de columnas deseadas
  const int tileSide = 16;    // Tamaño de cada tile
  const int displaySize = 128; // Tamaño de visualización en la UI

  QWidget *containerWidget = ui->scrollArea->widget();
  // Cargar el spritesheet completo
  QPixmap spritesheet(rutaBase + "/" + nombre);

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

      label->setPixmap(scaledTile);
      label->setFixedSize(displaySize, displaySize);

      label->setProperty("grilla_id", TILES_GRID_ID);
      label->setProperty("tile_id", fila * columnasMax + columna);
      label->installEventFilter(this);
      tiles.push_back(scaledTile.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation));
      

      ui->tilesLayout->addWidget(label, fila, columna);

      columna++;
      if (columna >= columnasMax) {
        columna = 0;
        fila++;
      }
    }
  }
  containerWidget->setFixedSize(columnasMax * displaySize, fila * displaySize);
}

void Editor::cargarTodosLosTiles() {

  int fila = 0;
  int columna = 0;

  QStringList archivos1 = obtenerArchivosImagen(":/images/sprites");
  cargarTilesEnGrilla(archivos1[1], ":/images/sprites", fila, columna);
  cargarTilesEnGrilla(archivos1[0], ":/images/sprites", fila, columna);
}

void Editor::crearMapaVacio(int filas, int columnas) {
  QGridLayout *mapaLayout = ui->mapLayout;
  mapaLayout->setSpacing(0);
  mapaLayout->setContentsMargins(0, 0, 0, 0);

  const int tileSide = 32;

  // Limpiar el layout existente si es necesario
  while (QLayoutItem *item = mapaLayout->takeAt(0)) {
    delete item->widget();
    delete item;
  }

  cambiarFondo(ui->backgroundBox->currentIndex());

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      QLabel *label = new QLabel();
      label->setFixedSize(tileSide, tileSide);
      label->setProperty("grilla_id", MAP_GRID_ID);
      label->setProperty("tile_id", EMPTY_TILE);
      label->installEventFilter(this);
            // Configurar el QLabel con un fondo transparente
      label->setStyleSheet(
          "background-color: transparent; border: 1px solid #FFA500;");
      mapaLayout->addWidget(label, i, j);
    }
  }

}

bool Editor::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QLabel *label = qobject_cast<QLabel *>(obj);
    if (label) {
      int grilla_id = label->property("grilla_id").toInt() ;

      if (grilla_id == TILES_GRID_ID) {
        // El label es un tile de la grilla
        const QPixmap currentPixmap = label->pixmap().scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);


        if (sprite_actual) {
          delete sprite_actual;
        }
        sprite_actual = new QPixmap(currentPixmap);
        tileID = label->property("tile_id").toInt();

      } else if (grilla_id == MAP_GRID_ID) {
        // El label es una celda del mapa
        if (sprite_actual) {
          label->clear();
          label->setPixmap(*sprite_actual);
          label->setProperty("tile_id", tileID);
        } else {
          label->clear();
          label->setProperty("tile_id", EMPTY_TILE);
        }
      }
      return true;
    }
  }
  return QWidget::eventFilter(obj, event);
}

void Editor::cleanLayout(QGridLayout *layout) {
  for (int i = 0; i < layout->count(); ++i) {
    QLayoutItem *item = layout->itemAt(i);
    if (QLabel *label = qobject_cast<QLabel *>(item->widget())) {
      label->clear();
    }
  }
}

void Editor::on_ExitButton_clicked() { QApplication::quit(); }

void Editor::on_EraseButton_clicked() { cleanLayout(ui->mapLayout); }


void Editor::on_SaveButton_clicked() {
  QString filename = yamlHandler.getSavefilename();
  if (filename.isEmpty() || !filename.endsWith(".yaml")) {
    return;
  }

  yamlHandler.save(filename,ui->mapLayout, ui->backgroundBox,filas, columnas);
}

void Editor::on_EraiserButton_clicked() {
  if (sprite_actual) {
    delete sprite_actual;
  }
  sprite_actual = nullptr;
}

void Editor::on_LoadButton_clicked() {
  QString filename=yamlHandler.getLoadfilename();

  if (filename.isEmpty() || !filename.endsWith(".yaml")) {
    return;
  }

  cleanLayout(ui->mapLayout);


  crearMapaVacio(filas, columnas);
  
  yamlHandler.load(filename,ui->mapLayout, ui->backgroundBox,tiles);
}

void Editor::cambiarFondo(int index) {
  QWidget *containerWidget = ui->scrollArea_2->widget();
  if (index == 0) { // Índice 0 corresponde a "Forest"
    containerWidget->setStyleSheet(
        "QWidget#mapWidget { border-image: url(:/images/forest.png) 0 0 0 0 "
        "stretch stretch; }");
  } else if (index == 1) { // Índice 1 corresponde a "Lava"
    containerWidget->setStyleSheet(
        "QWidget#mapWidget { border-image: url(:/images/lava.png) 0 0 0 0 "
        "stretch stretch; }");
  } else {
    containerWidget->setStyleSheet("QWidget#mapWidget { border-image: url(:/images/nieve.png) 0 0 0 0 "
        "stretch stretch; }");
  }
}