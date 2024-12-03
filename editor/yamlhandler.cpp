#include "yamlhandler.h"
#include <iostream>

void YamlHandler::ponerTile(YAML::Emitter &out, int columna_inicial,
                            int columna_final, int fila_inicial, int fila_final,
                            int tile) {
  out << YAML::BeginMap;
  out << YAML::Key << "start_x" << YAML::Value << columna_inicial;
  out << YAML::Key << "end_x" << YAML::Value << columna_final;
  out << YAML::Key << "start_y" << YAML::Value << fila_inicial;
  out << YAML::Key << "end_y" << YAML::Value << fila_final;
  out << YAML::Key << "tile" << YAML::Value << tile;
  out << YAML::EndMap;
}

QString YamlHandler::getSavefilename() {
  QString filename =
      QFileDialog::getSaveFileName(nullptr, QObject::tr("Save File"), "",
                                   QObject::tr("YAML Files (*.yaml)"));
  return filename;
}

QString YamlHandler::getLoadfilename() {
  QString filename =
      QFileDialog::getOpenFileName(nullptr, QObject::tr("Open File"), "",
                                   QObject::tr("YAML Files (*.yaml)"));
  return filename;
}
void YamlHandler::save(QString &filename, QGridLayout *mapLayout,
                       QComboBox *backgroundBox, int filas, int columnas) {
  YAML::Emitter out;
  out << YAML::BeginMap;

  // Propiedades generales del mapa
  out << YAML::Key << "fondo" << YAML::Value
      << backgroundBox->currentText().toStdString();
  out << YAML::Key << "alto" << YAML::Value << filas;
  out << YAML::Key << "ancho" << YAML::Value << columnas;

  // Iniciar la lista de tiles
  out << YAML::Key << "Structures" << YAML::Value << YAML::BeginSeq;
  QLabel *anterior = nullptr;
  int fila_inicial = -1;
  int columna_inicial = -1;
  int columna_final = -1;

  // procesar de forma horizontal
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      QLabel *label =
          qobject_cast<QLabel *>(mapLayout->itemAtPosition(i, j)->widget());

      // Si no hay label o es un tile no válido, saltamos
      if (!label || label->pixmap().isNull() ||
          label->property("tile_id").toInt() == EMPTY_TILE ||
          label->property("tile_id").toInt() >= SPAWN_TILE) {
        // Si había una estructura anterior, la guardamos antes de resetear
        if (anterior != nullptr) {
          // Solo guardar si el ancho es mayor a 1
          if (columna_final - columna_inicial > 0) {
            ponerTile(out, columna_inicial, columna_final, fila_inicial,
                      fila_inicial, anterior->property("tile_id").toInt());
          }
          anterior = nullptr;
          fila_inicial = -1;
          columna_inicial = -1;
          columna_final = -1;
        }
        continue;
      }

      // Primera estructura o nueva estructura
      if (anterior == nullptr || label->property("tile_id").toInt() !=
                                     anterior->property("tile_id").toInt()) {
        // Si había una estructura anterior, la guardamos
        if (anterior != nullptr) {
          // Solo guardar si el ancho es mayor a 1
          if (columna_final - columna_inicial > 0) {
            ponerTile(out, columna_inicial, columna_final, fila_inicial,
                      fila_inicial, anterior->property("tile_id").toInt());
          }
        }

        // Reiniciamos con la nueva estructura
        anterior = label;
        fila_inicial = i;
        columna_inicial = j;
        columna_final = j;
      }
      // Estructura continua
      else {
        columna_final = j;
      }
    }

    // Al final de cada fila, guardamos la última estructura si existe
    if (anterior != nullptr &&
        anterior->property("tile_id").toInt() < SPAWN_TILE) {
      // Solo guardar si el ancho es mayor a 1
      if (columna_final - columna_inicial > 0) {
        ponerTile(out, columna_inicial, columna_final, fila_inicial,
                  fila_inicial, anterior->property("tile_id").toInt());
      }
    }

    // Reseteamos para la siguiente fila
    anterior = nullptr;
    fila_inicial = -1;
    columna_inicial = -1;
    columna_final = -1;
  }
  // Estructuras verticales de largo > 1
  for (int j = 0; j < columnas; j++) {
    anterior = nullptr;
    fila_inicial = -1;
    columna_inicial = j;
    int fila_final = -1;

    for (int i = 0; i < filas; i++) {
      QLabel *label =
          qobject_cast<QLabel *>(mapLayout->itemAtPosition(i, j)->widget());

      if (!label || label->pixmap().isNull() ||
          label->property("tile_id").toInt() == EMPTY_TILE ||
          label->property("tile_id").toInt() >= SPAWN_TILE) {
        if (anterior != nullptr) {
          if (fila_final - fila_inicial > 0) {
            ponerTile(out, columna_inicial, columna_inicial, fila_inicial,
                      fila_final, anterior->property("tile_id").toInt());
          }
          anterior = nullptr;
          fila_inicial = -1;
          fila_final = -1;
        }
        continue;
      }

      if (anterior == nullptr || label->property("tile_id").toInt() !=
                                     anterior->property("tile_id").toInt()) {
        if (anterior != nullptr) {
          if (fila_final - fila_inicial > 0) {
            ponerTile(out, columna_inicial, columna_inicial, fila_inicial,
                      fila_final, anterior->property("tile_id").toInt());
          }
        }

        anterior = label;
        fila_inicial = i;
        fila_final = i;
      } else {
        fila_final = i;
      }
    }

    if (anterior != nullptr &&
        anterior->property("tile_id").toInt() < SPAWN_TILE) {
      if (fila_final - fila_inicial > 0) {
        ponerTile(out, columna_inicial, columna_inicial, fila_inicial,
                  fila_final, anterior->property("tile_id").toInt());
      }
    }
  }
  // Estructuras de largo 1
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      QLabel *label =
          qobject_cast<QLabel *>(mapLayout->itemAtPosition(i, j)->widget());
      if (!label || label->pixmap().isNull() ||
          label->property("tile_id").toInt() == EMPTY_TILE ||
          label->property("tile_id").toInt() >= SPAWN_TILE) {
        continue;
      }

      // Verificar si es de largo 1 (no tiene continuación horizontal)
      bool esIndividual = true;
      if (j > 0) {
        QLabel *labelIzq = qobject_cast<QLabel *>(
            mapLayout->itemAtPosition(i, j - 1)->widget());
        if (labelIzq && labelIzq->property("tile_id").toInt() ==
                            label->property("tile_id").toInt()) {
          esIndividual = false;
        }
      }

      if (j < columnas - 1) {
        QLabel *labelDer = qobject_cast<QLabel *>(
            mapLayout->itemAtPosition(i, j + 1)->widget());
        if (labelDer && labelDer->property("tile_id").toInt() ==
                            label->property("tile_id").toInt()) {
          esIndividual = false;
        }
      }

      if (i > 0) {
        QLabel *labelArriba = qobject_cast<QLabel *>(
            mapLayout->itemAtPosition(i - 1, j)->widget());
        if (labelArriba && labelArriba->property("tile_id").toInt() ==
                               label->property("tile_id").toInt()) {
          esIndividual = false;
        }
      }

      if (i < filas - 1) {
        QLabel *labelAbajo = qobject_cast<QLabel *>(
            mapLayout->itemAtPosition(i + 1, j)->widget());
        if (labelAbajo && labelAbajo->property("tile_id").toInt() ==
                              label->property("tile_id").toInt()) {
          esIndividual = false;
        }
      }

      if (esIndividual) {
        ponerTile(out, j, j, i, i, label->property("tile_id").toInt());
      }
    }
  }

  out << YAML::EndSeq;

  out << YAML::Key << "Spawns" << YAML::Value << YAML::BeginSeq;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      QLabel *label =
          qobject_cast<QLabel *>(mapLayout->itemAtPosition(i, j)->widget());
      if (label && !label->pixmap().isNull()) {
        if (label->property("tile_id").toInt() == SPAWN_TILE) {
          out << YAML::BeginMap;
          out << YAML::Key << "x" << YAML::Value << j;
          out << YAML::Key << "y" << YAML::Value << i;
          out << YAML::EndMap;
        }
      }
    }
  }

  out << YAML::EndSeq;

  out << YAML::Key << "Interactuables" << YAML::Value << YAML::BeginSeq;

  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      QLabel *label =
          qobject_cast<QLabel *>(mapLayout->itemAtPosition(i, j)->widget());
      if (label && !label->pixmap().isNull()) {
        if (label->property("tile_id").toInt() >= INTERACTUABLES_START &&
            label->property("tile_id").toInt() <= TOTAL_TILES) {
          out << YAML::BeginMap;
          out << YAML::Key << "x" << YAML::Value << j;
          out << YAML::Key << "y" << YAML::Value << i;
          out << "ID" << TOTAL_TILES - label->property("tile_id").toInt();
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

void YamlHandler::load(QString &filename, QGridLayout *mapLayout,
                       QComboBox *backgroundBox, std::vector<QPixmap> &tiles) {
  QFile file(filename);
  if (!file.open(QIODevice::ReadOnly)) {
    return;
  }

  QString yaml = file.readAll();
  YAML::Node doc = YAML::Load(yaml.toStdString());

  QString background = QString::fromStdString(doc["fondo"].as<std::string>());
  if (background == "Forest") {
    backgroundBox->setCurrentIndex(0);
  } else if (background == "Lava") {
    backgroundBox->setCurrentIndex(1);
  } else {
    backgroundBox->setCurrentIndex(2);
  }

  for (const auto &structure : doc["Structures"]) {
    int start_x = structure["start_x"].as<int>();
    int end_x = structure["end_x"].as<int>();
    int start_y = structure["start_y"].as<int>();
    int end_y = structure["end_y"].as<int>();
    int tile = structure["tile"].as<int>();
    for (int i = start_y; i <= end_y; i++) {
      for (int j = start_x; j <= end_x; j++) {
        QLabel *label =
            qobject_cast<QLabel *>(mapLayout->itemAtPosition(i, j)->widget());
        label->setPixmap(tiles[tile]);
        label->setProperty("tile_id", tile);
      }
    }
  }

  for (const auto &spawn : doc["Spawns"]) {
    int x = spawn["x"].as<int>();
    int y = spawn["y"].as<int>();
    QLabel *label =
        qobject_cast<QLabel *>(mapLayout->itemAtPosition(y, x)->widget());
    label->setPixmap(tiles[SPAWN_TILE]);
    label->setProperty("tile_id", SPAWN_TILE);
  }

  for (const auto &interactuable : doc["Interactuables"]) {
    int x = interactuable["x"].as<int>();
    int y = interactuable["y"].as<int>();
    int id = interactuable["ID"].as<int>();
    QLabel *label =
        qobject_cast<QLabel *>(mapLayout->itemAtPosition(y, x)->widget());
    label->setPixmap(tiles[TOTAL_TILES - id]);
    label->setProperty("tile_id", TOTAL_TILES - id);
  }
}
