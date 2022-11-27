#include <iostream>
#include <cstdlib>
#include <thread>
#include <vector>
#include <memory>

#include <QImage>
#include <QPushButton>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QPixmap>
#include <QTimer>
#include <QShortcut>
#include <QDoubleSpinBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vertex.h"
#include "face.h"
#include "object.h"
#include "object.h"
#include "matrix.h"

int *z_buffer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    z_buffer = new int[WIDTH * HEIGHT];
    rain_time = 50;
    droplet_size_slider = 0;

    image = new QImage(QSize(WIDTH, HEIGHT), QImage::Format_RGB32);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    QShortcut *press_d = new QShortcut(QKeySequence(Qt::Key_D), this, SLOT(rotate_right()));
    QShortcut *press_a = new QShortcut(QKeySequence(Qt::Key_A), this, SLOT(rotate_left()));
    QShortcut *press_w = new QShortcut(QKeySequence(Qt::Key_W), this, SLOT(rotate_up()));
    QShortcut *press_s = new QShortcut(QKeySequence(Qt::Key_S), this, SLOT(rotate_down()));

    droplets = new RainDroplet *[NUM_OF_DROPLETS];

    droplets[0] = new RainDroplet("../RainSimulator/obj/droplet.obj");
    droplets[1] = new RainDroplet("../RainSimulator/obj/droplet.obj");
    ground = new Ground("../RainSimulator/obj/ground.obj");

    ground->translate(0, -.6, 0);
    droplets[0]->translate(-.5, 1, 0);
    droplets[1]->translate(.5, 1, 0);
    this->render();

    timer = new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
    timer->start(rain_time);
}

MainWindow::~MainWindow()
{
    delete[] z_buffer;
    delete[] droplets;
    delete ui;
}

void MainWindow::animate()
{
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
        droplets[i]->translate(0, -0.01, 0);
    this->render();
}

void MainWindow::render()
{
    for (std::size_t i = 0; i < WIDTH * HEIGHT; i++)
        z_buffer[i] = 0;
    image->fill(mode.rgb());
    ground->draw(WIDTH, HEIGHT, 0, 102, 0, image);
    droplets[0]->draw(WIDTH, HEIGHT, 51, 153, 255, image);
    droplets[1]->draw(WIDTH, HEIGHT, 100, 53, 155, image);
    scene->addPixmap(QPixmap::fromImage(*image));
}

void MainWindow::rotate_right()
{
    if (from.x < 8)
        from.x += 0.1;
    this->render();
}

void MainWindow::rotate_left()
{
    if (from.x > -8)
        from.x -= 0.1;
    this->render();
}

void MainWindow::rotate_up()
{
    if (from.y < 8)
        from.y += 0.1;
    this->render();
}

void MainWindow::rotate_down()
{
    if (from.y > -8)
        from.y -= 0.1;
    this->render();
}

void MainWindow::on_pushButton_2_clicked()
{
    mode = QColor(102, 178, 255);
    this->render();
}

void MainWindow::on_pushButton_3_clicked()
{
    mode = QColor(0, 0, 110);
    this->render();
}

void MainWindow::on_pushButton_4_clicked()
{
    from.x = DEFAULT_FROM_X;
    from.y = DEFAULT_FROM_Y;
    this->render();
}

void MainWindow::on_pushButton_6_clicked()
{
    this->rotate_left();
}

void MainWindow::on_pushButton_clicked()
{
    this->rotate_up();
}

void MainWindow::on_pushButton_7_clicked()
{
    this->rotate_down();
}

void MainWindow::on_pushButton_5_clicked()
{
    this->rotate_right();
}

void MainWindow::on_pushButton_12_clicked()
{
    light_dir.x = DEFAULT_LIGHT_X;
    light_dir.y = DEFAULT_LIGHT_Y;
    this->render();
}

void MainWindow::on_pushButton_9_clicked()
{
    if (light_dir.y > -8)
        light_dir.y -= 0.1;
    this->render();
}

void MainWindow::on_pushButton_10_clicked()
{
    if (light_dir.y < 8)
        light_dir.y += 0.1;
    this->render();
}

void MainWindow::on_pushButton_8_clicked()
{
    if (light_dir.x < 8)
        light_dir.x += 0.1;
    this->render();
}

void MainWindow::on_pushButton_11_clicked()
{
    if (light_dir.x > -8)
        light_dir.x -= 0.1;
    this->render();
}

void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    double new_scale = (position - droplet_size_slider) / 500.0;
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
        droplets[i]->scale(new_scale, new_scale, new_scale);
    droplet_size_slider = position;
    this->render();
}

