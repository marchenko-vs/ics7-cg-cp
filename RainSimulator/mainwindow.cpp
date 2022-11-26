#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>

#include <QImage>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include <QShortcut>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vertex.h"
#include "face.h"
#include "object.h"
#include "object.h"
#include "matrix.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    image = new QImage(QSize(WIDTH, HEIGHT), QImage::Format_RGB32);
    image->fill(mode.rgb());

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    QShortcut *press_a = new QShortcut(QKeySequence(Qt::Key_A),this,SLOT(rotate_left()));
    QShortcut *press_d = new QShortcut(QKeySequence(Qt::Key_D),this,SLOT(rotate_right()));

    droplets = new RainDroplet*[1];

    droplets[0] = new RainDroplet("../RainSimulator/obj/african_head.obj");
    droplets[0]->draw(WIDTH, HEIGHT, 51, 153, 255, image);

//    for (std::size_t i = 1; i < NUM_OF_DROPLETS; i++)
//    {
//        droplets[i] = new RainDroplet(*droplets[0]);
//        droplets[i]->translate(i, i, 0);
//    }

//    ground = new Ground("../RainSimulator/obj/droplet.obj");
//    ground->draw(WIDTH, HEIGHT, 0, 102, 0, image);
    image->mirror(false, true);
    scene->addPixmap(QPixmap::fromImage(*image));

    //timer = new QTimer();

//    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_clicked()));
//    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete[] droplets;
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    image->fill(mode.rgb());
//    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
//        droplets[i]->draw(WIDTH, HEIGHT, 51, 153, 255, image);
    //ground->draw(WIDTH, HEIGHT, 0, 102, 0, image);
    //droplets[0]->rotate(10, 10, 10);
    droplets[0]->draw(WIDTH, HEIGHT, 51, 153, 255, image);
    image->mirror(false, true);
    scene->addPixmap(QPixmap::fromImage(*image));
}

void MainWindow::rotate_left()
{
    image->fill(mode.rgb());
    droplets[0]->rotate(0, -10, 0);
    droplets[0]->draw(WIDTH, HEIGHT, 51, 153, 255, image);
    image->mirror(false, true);
    scene->addPixmap(QPixmap::fromImage(*image));
}

void MainWindow::rotate_right()
{
    image->fill(mode.rgb());
    droplets[0]->rotate(0, 10, 0);
    droplets[0]->draw(WIDTH, HEIGHT, 51, 153, 255, image);
    image->mirror(false, true);
    scene->addPixmap(QPixmap::fromImage(*image));
}

void MainWindow::on_pushButton_2_clicked()
{
    mode = QColor(102, 178, 255);
}

void MainWindow::on_pushButton_3_clicked()
{
    mode = QColor(0, 0, 110);
}
