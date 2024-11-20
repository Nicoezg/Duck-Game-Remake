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

Editor::Editor(QWidget *parent)
    : QWidget(parent), ui(new Ui::Editor), sprite_actual(nullptr), tileID(-1){
  ui->setupUi(this);
  

  cargarTodosLosTiles();
  crearMapaVacio(30, 40);
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
  const int columnasMax = 8;  // Ajusta según la cantidad de columnas deseadas
  const int tileSide = 16;    // Tamaño de cada tile
  const int displaySize = 64; // Tamaño de visualización en la UI

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

      label->setProperty("grilla_id", 0);
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

  QWidget *containerWidget = ui->scrollArea_2->widget();

  cambiarFondo(ui->backgroundBox->currentIndex());

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      QLabel *label = new QLabel(containerWidget);
      label->setFixedSize(tileSide, tileSide);

      // Configurar el QLabel con un fondo transparente
      label->setStyleSheet(
          "background-color: transparent; border: 1px solid #FFA500;");
      label->installEventFilter(this);
      label->setProperty("grilla_id", 1);

      mapaLayout->addWidget(label, i, j);
    }
  }

  containerWidget->setFixedSize(columnas * tileSide, filas * tileSide);
  ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  ui->scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

bool Editor::eventFilter(QObject *obj, QEvent *event) {
  if (event->type() == QEvent::MouseButtonPress) {
    QLabel *label = qobject_cast<QLabel *>(obj);
    if (label) {
      QString grilla_id = label->property("grilla_id").toString();

      if (grilla_id == "0") {
        // El label es un tile de la grilla
        const QPixmap currentPixmap = label->pixmap().scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);


        if (sprite_actual) {
          delete sprite_actual;
        }
        sprite_actual = new QPixmap(currentPixmap);
        tileID = label->property("tile_id").toInt();

      } else if (grilla_id == "1") {
        // El label es una celda del mapa
        if (sprite_actual) {
          label->clear();
          label->setPixmap(*sprite_actual);
          label->setProperty("tile_id", tileID);
        } else {
          label->clear();
          label->setProperty("tile_id", -1);
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

void ponerTile(YAML::Emitter &out, int columna_inicial, int columna_final,
               int fila, int tile) {
  out << YAML::BeginMap;
  out << YAML::Key << "start_x" << YAML::Value << columna_inicial;
  out << YAML::Key << "end_x" << YAML::Value << columna_final;
  out << YAML::Key << "y" << YAML::Value << fila;
  out << YAML::Key << "tile" << YAML::Value << tile;
  out << YAML::EndMap;
}

void Editor::on_SaveButton_clicked() {


  QString filename= QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("YAML Files (*.yaml)"));

  YAML::Emitter out;
  out << YAML::BeginMap;

  // Propiedades generales del mapa
  out << YAML::Key << "fondo" << YAML::Value
      << ui->backgroundBox->currentText().toStdString();
  out << YAML::Key << "alto" << YAML::Value << ui->mapLayout->rowCount();
  out << YAML::Key << "ancho" << YAML::Value <<ui->mapLayout->columnCount();
  // Iniciar la lista de tiles
  out << YAML::Key << "Structures" << YAML::Value << YAML::BeginSeq;
  QLabel *anterior = nullptr;
  int fila_inicial = -1;
  int columna_inicial = -1;
  int columna_final = -1;
  for (int i = 0; i < ui->mapLayout->rowCount(); i++) {
    for (int j = 0; j < ui->mapLayout->columnCount(); j++) {
      QLabel *label =
          qobject_cast<QLabel *>(ui->mapLayout->itemAtPosition(i, j)->widget());
      if (label && !label->pixmap().isNull()) {
        if (label->property("tile_id").toInt() == -1 ||
            label->property("tile_id").toInt() >= 96) {
          continue;
        }
        if (anterior == nullptr || label->property("tile_id").toInt() !=
                                       anterior->property("tile_id").toInt()) {
          if (anterior != nullptr) {
            ponerTile(out, columna_inicial, columna_final, fila_inicial,
                      anterior->property("tile_id").toInt());
          }
          anterior = label;
          fila_inicial = i;
          columna_inicial = j;
          columna_final = j;
        } else {
          columna_final = j;
        }
      }
    }
    if (anterior != nullptr && anterior->property("tile_id").toInt() <= 95) {
      ponerTile(out, columna_inicial, columna_final, fila_inicial,
                anterior->property("tile_id").toInt());
    }
    anterior = nullptr;
    fila_inicial = -1;
    columna_inicial = -1;
    columna_final = -1;
  }
  out << YAML::EndSeq; // Termina la lista de tiles

  out << YAML::Key << "Spawns" << YAML::Value << YAML::BeginSeq;

  for (int i = 0; i < ui->mapLayout->rowCount(); i++) {
    for (int j = 0; j < ui->mapLayout->columnCount(); j++) {
      QLabel *label =
          qobject_cast<QLabel *>(ui->mapLayout->itemAtPosition(i, j)->widget());
      if (label && !label->pixmap().isNull()) {
        if (label->property("tile_id").toInt() == 96) {
          out << YAML::BeginMap;
          out << YAML::Key << "x" << YAML::Value << j;
          out << YAML::Key << "y" << YAML::Value << i;
          out << YAML::EndMap;
        }
      }
    }
  }

  out << YAML::EndSeq; // Termina la lista de spawns

  out << YAML::Key << "Interactuables" << YAML::Value << YAML::BeginSeq;

  for (int i = 0; i < ui->mapLayout->rowCount(); i++) {
    for (int j = 0; j < ui->mapLayout->columnCount(); j++) {
      QLabel *label =
          qobject_cast<QLabel *>(ui->mapLayout->itemAtPosition(i, j)->widget());
      if (label && !label->pixmap().isNull()) {
        if (label->property("tile_id").toInt() >= 97 &&
            label->property("tile_id").toInt() <= 99) {
          out << YAML::BeginMap;
          out << YAML::Key << "x" << YAML::Value << j;
          out << YAML::Key << "y" << YAML::Value << i;
          out << "ID" << 99 - label->property("tile_id").toInt();
          out << YAML::EndMap;
        }
      }
    }
  }

  out << YAML::EndSeq; // Termina la lista de interactuables

  out << YAML::EndMap; // Termina el mapa raíz

  QFile file(filename);
  if (file.open(QIODevice::WriteOnly)) {
    QTextStream stream(&file);
    stream << QString::fromStdString(out.c_str());
    file.close();
  }
}

void Editor::on_EraiserButton_clicked() {
  if (sprite_actual) {
    delete sprite_actual;
  }
  sprite_actual = nullptr;
}

void Editor::on_LoadButton_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, tr("Open File"), "", tr("YAML Files (*.yaml)"));
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    return;
  }

  QString yaml = file.readAll();
  YAML::Node doc = YAML::Load(yaml.toStdString());

  QString background = QString::fromStdString(doc["fondo"].as<std::string>());
  if (background == "Forest") {
    ui->backgroundBox->setCurrentIndex(0);
  } else if (background == "Lava") {
    ui->backgroundBox->setCurrentIndex(1);
  }

  int filas = doc["alto"].as<int>();
  int columnas = doc["ancho"].as<int>();

  cleanLayout(ui->mapLayout);
  crearMapaVacio(filas, columnas);

  for (const auto &tile : doc["Structures"]) {
    int start_x = tile["start_x"].as<int>();
    int end_x = tile["end_x"].as<int>();
    int y = tile["y"].as<int>();
    int tile_id = tile["tile"].as<int>();

    for (int i = start_x; i <= end_x; i++) {
      QLabel *label =
          qobject_cast<QLabel *>(ui->mapLayout->itemAtPosition(y, i)->widget());
      label->setPixmap(tiles[tile_id]);
      label->setProperty("tile_id", tile_id);
    }
  }

  for (const auto &spawn : doc["Spawns"]) {
    int x = spawn["x"].as<int>();
    int y = spawn["y"].as<int>();
    QLabel *label =
        qobject_cast<QLabel *>(ui->mapLayout->itemAtPosition(y, x)->widget());
    label->setPixmap(tiles[96]);
    label->setProperty("tile_id", 96);
  }

  for (const auto &interactuable : doc["Interactuables"]) {
    int x = interactuable["x"].as<int>();
    int y = interactuable["y"].as<int>();
    int id = interactuable["ID"].as<int>();
    QLabel *label =
        qobject_cast<QLabel *>(ui->mapLayout->itemAtPosition(y, x)->widget());
    label->setPixmap(tiles[99 - id]);
    label->setProperty("tile_id", 99 - id);
  }
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
    // Manejar otros casos
  }
}