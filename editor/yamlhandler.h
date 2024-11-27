#ifndef YAMLHANDLER_H
#define YAMLHANDLER_H

#include <yaml-cpp/yaml.h>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QDir>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>




#define TOTAL_TILES 100
#define SPAWN_TILE 96
#define INTERACTUABLES_START 97
#define EMPTY_TILE -1

class YamlHandler{
    public:
        static void load( QGridLayout *layout, QComboBox *backgroundBox, std::vector<QPixmap> &tiles);
        static void save( QGridLayout *layout, QComboBox *backgroundBox);
        YamlHandler(){} ;
        ~YamlHandler(){};
};

#endif // YAMLHANDLER_H
