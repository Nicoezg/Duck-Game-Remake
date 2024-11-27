#include "yamlhandler.h"
#include <iostream>

void ponerTile(YAML::Emitter &out, int columna_inicial, int columna_final,
               int fila, int tile) {
  out << YAML::BeginMap;
  out << YAML::Key << "start_x" << YAML::Value << columna_inicial;
  out << YAML::Key << "end_x" << YAML::Value << columna_final;
  out << YAML::Key << "y" << YAML::Value << fila;
  out << YAML::Key << "tile" << YAML::Value << tile;
  out << YAML::EndMap;
}

void YamlHandler::save( QGridLayout *mapLayout,
                             QComboBox *backgroundBox) {
QString filename= QFileDialog::getSaveFileName(nullptr, QObject::tr("Save File"), "", QObject::tr("YAML Files (*.yaml)"));

  YAML::Emitter out;
  out << YAML::BeginMap;

  // Propiedades generales del mapa
  out << YAML::Key << "fondo" << YAML::Value
      << backgroundBox->currentText().toStdString();
  out << YAML::Key << "alto" << YAML::Value << mapLayout->rowCount();
  out << YAML::Key << "ancho" << YAML::Value <<mapLayout->columnCount();
  // Iniciar la lista de tiles
out << YAML::Key << "Structures" << YAML::Value << YAML::BeginSeq;
QLabel *anterior = nullptr;
int fila_inicial = -1;
int columna_inicial = -1;
int columna_final = -1;

for (int i = 0; i < mapLayout->rowCount(); i++) {
    for (int j = 0; j < mapLayout->columnCount(); j++) {
        QLabel *label = qobject_cast<QLabel *>(mapLayout->itemAtPosition(i, j)->widget());
        
        // Si no hay label o es un tile no válido, saltamos
        if (!label || label->pixmap().isNull() || 
            label->property("tile_id").toInt() == EMPTY_TILE || 
            label->property("tile_id").toInt() >= SPAWN_TILE) {
            // Si había una estructura anterior, la guardamos antes de resetear
            if (anterior != nullptr) {
                ponerTile(out, columna_inicial, columna_final, fila_inicial,
                          anterior->property("tile_id").toInt());
                anterior = nullptr;
                fila_inicial = -1;
                columna_inicial = -1;
                columna_final = -1;
            }
            continue;
        }

        // Primera estructura o nueva estructura
        if (anterior == nullptr || 
            label->property("tile_id").toInt() != anterior->property("tile_id").toInt()) {
            // Si había una estructura anterior, la guardamos
            if (anterior != nullptr) {
                ponerTile(out, columna_inicial, columna_final, fila_inicial,
                          anterior->property("tile_id").toInt());
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
    if (anterior != nullptr && anterior->property("tile_id").toInt() < SPAWN_TILE) {
        ponerTile(out, columna_inicial, columna_final, fila_inicial,
                  anterior->property("tile_id").toInt());
    }

    // Reseteamos para la siguiente fila
    anterior = nullptr;
    fila_inicial = -1;
    columna_inicial = -1;
    columna_final = -1;
}
  out << YAML::EndSeq; // Termina la lista de tiles

  out << YAML::Key << "Spawns" << YAML::Value << YAML::BeginSeq;

  for (int i = 0; i < mapLayout->rowCount(); i++) {
    for (int j = 0; j < mapLayout->columnCount(); j++) {
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

  out << YAML::EndSeq; // Termina la lista de spawns

  out << YAML::Key << "Interactuables" << YAML::Value << YAML::BeginSeq;

  for (int i = 0; i < mapLayout->rowCount(); i++) {
    for (int j = 0; j < mapLayout->columnCount(); j++) {
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

void YamlHandler::load( QGridLayout *mapLayout, QComboBox *backgroundBox,
                            std::vector<QPixmap> &tiles) {
      QString filename = QFileDialog::getOpenFileName(
      nullptr, QObject::tr("Open File"), "", QObject::tr("YAML Files (*.yaml)"));
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
  }



  for (const auto &tile : doc["Structures"]) {
    int start_x = tile["start_x"].as<int>();
    int end_x = tile["end_x"].as<int>();
    int y = tile["y"].as<int>();
    int tile_id = tile["tile"].as<int>();

    for (int i = start_x; i <= end_x; i++) {
      QLabel *label =
          qobject_cast<QLabel *>(mapLayout->itemAtPosition(y, i)->widget());
      label->setPixmap(tiles[tile_id]);
      label->setProperty("tile_id", tile_id);
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
