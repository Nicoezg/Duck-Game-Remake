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



#define TOTAL_TILES 52
#define SPAWN_TILE 48
#define INTERACTUABLES_START 49
#define EMPTY_TILE -1

class YamlHandler{
    public:
        static void load( QString &filename,QGridLayout *layout, QComboBox *backgroundBox, std::vector<QPixmap> &tiles);
        static void save( QString &filename,QGridLayout *layout, QComboBox *backgroundBox,int filas, int columnas);
        QString getSavefilename();
        QString getLoadfilename();
        YamlHandler(){} ;
        ~YamlHandler(){};
    private:
        static void ponerTile(YAML::Emitter &out, int columna_inicial, int columna_final,
                int fila_inicial,int fila_final, int tile);
};

#endif // YAMLHANDLER_H
