#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vertex.h"
#include "face.h"
#include "object.h"

#include <iostream>
#include <cstdlib>
#include <thread>

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QColor(0, 0, 110));

    obj = new Object("../RainSimulator/obj/cube.obj");
    obj->draw(WIDTH, HEIGHT, scene, QColor(255, 255, 255));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    scene->clear();

    obj->draw(WIDTH, HEIGHT, scene, QColor(255, 255, 255));
}


void MainWindow::on_pushButton_2_clicked()
{
    scene->setBackgroundBrush(QColor(102, 178, 255));
}


void MainWindow::on_pushButton_3_clicked()
{
    scene->setBackgroundBrush(QColor(0, 0, 110));
}

