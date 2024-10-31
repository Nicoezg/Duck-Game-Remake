#include "editor.h"
#include "ui_editor.h"
#include <QDir>
#include <QLabel>
#include <iostream>
#include <QGridLayout>
#include <QStackedWidget>


Editor::Editor(QWidget *parent) : QWidget(parent), ui(new Ui::Editor) {
  ui->setupUi(this);
  cargarTodosLosTiles();
  crearMapaVacio(10, 10);
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
  const int columnasMax = 8;  // Ajusta según la cantidad de columnas deseadas
  const int tileSide = 16;    // Tamaño de cada tile
  const int displaySize = 64; // Tamaño de visualización en la UI

  // Obtener el widget que contiene el layout (scrollAreaWidgetContents)
  QWidget* containerWidget = ui->scrollArea->widget();
  if (!containerWidget) {
      containerWidget = new QWidget(ui->scrollArea_2);
      ui->scrollArea_2->setWidget(containerWidget);
  }


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
  containerWidget->setFixedSize(columnasMax * displaySize, fila * displaySize);
}

void Editor::cargarTodosLosTiles() {

  int fila = 0;
  int columna = 0;

  QStringList archivos1 = obtenerArchivosImagen(":/images/sprites");
  cargarTilesEnGrilla(archivos1, ":/images/sprites", fila, columna);
}

void Editor::crearMapaVacio(int filas, int columnas) {
    QGridLayout *mapaLayout = ui->mapLayout;
    mapaLayout->setSpacing(0);
    mapaLayout->setContentsMargins(0, 0, 0, 0);

    const int tileSide = 64;

    // Limpiar el layout existente si es necesario
    while (QLayoutItem* item = mapaLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    QWidget* containerWidget = ui->scrollArea_2->widget();
    if (!containerWidget) {
        containerWidget = new QWidget(ui->scrollArea_2);
        ui->scrollArea_2->setWidget(containerWidget);
    } 

    // Establecer la imagen de fondo solo para el contenedor
    containerWidget->setStyleSheet("QWidget#mapWidget { border-image: url(:/images/forest.png) 0 0 0 0 stretch stretch; }");

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            QLabel *label = new QLabel(containerWidget);
            label->setFixedSize(tileSide, tileSide);

            // Configurar el QLabel con un fondo transparente
            label->setStyleSheet("background-color: transparent; border: 1px solid #FFA500;");
            
            mapaLayout->addWidget(label, i, j);
        }
    }

    containerWidget->setFixedSize(columnas * tileSide, filas * tileSide);
    ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}


void Editor::on_Menu_clicked()
{
  QStackedWidget *stackedWidget = qobject_cast<QStackedWidget*>(this->parentWidget());
  if (stackedWidget) {
      stackedWidget->setCurrentIndex(0);
  }
      
}
