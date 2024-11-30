#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), editor(nullptr), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupEditor();

}

void MainWindow::setupEditor() {
    editor = new Editor();
    if (!ui->centralwidget->layout()) {
        QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);
        ui->centralwidget->setLayout(layout);
    }

    ui->centralwidget->layout()->addWidget(editor);
}


MainWindow::~MainWindow() {
    delete editor;
    delete ui;
}
