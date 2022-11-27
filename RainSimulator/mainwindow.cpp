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
    droplets = new RainDroplet *[NUM_OF_DROPLETS];

    rain_time = 100;
    previous_time = 0;
    previous_size = 0;
    droplet_size_slider = 0;
    dy = -0.3;
    dx = dz = 0.0;
    previous_dx = previous_dz = 0;

    image = new QImage(QSize(WIDTH, HEIGHT), QImage::Format_RGB32);
    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);

    QShortcut *press_d = new QShortcut(QKeySequence(Qt::Key_D),
                                       this, SLOT(rotate_right()));
    QShortcut *press_a = new QShortcut(QKeySequence(Qt::Key_A),
                                       this, SLOT(rotate_left()));
    QShortcut *press_w = new QShortcut(QKeySequence(Qt::Key_W),
                                       this, SLOT(rotate_up()));
    QShortcut *press_s = new QShortcut(QKeySequence(Qt::Key_S),
                                       this, SLOT(rotate_down()));

    int cube = cbrt(NUM_OF_DROPLETS);

    OriginalRainDroplet *main_droplets =
            new OriginalRainDroplet("../RainSimulator/obj/rain.obj");

    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
    {
        droplets[i] = new RainDroplet(main_droplets);
    }

    double init_dx = -0.9;
    double init_dy = 1.0;
    double init_dz = 1.0;

    double delta_x = 1.5 / (cube - 2);
    double delta_y = 0.05;
    double delta_z = 0.1;
    int cube_2 = cube * cube;

    for (std::size_t i = 0; i < cube; i++) // i * N * L + j * L + k
    {
        for (std::size_t j = 0; j < cube; j++)
        {
            for (std::size_t k = 0; k < cube; k++)
            {
                droplets[i * cube_2 + j * cube + k]->translate(init_dx, init_dy, init_dz);
                init_dx += delta_x;
            }
            init_dx = -0.9;
            init_dz -= delta_z;
        }
        init_dx = -0.9;
        init_dz = 1.0;
        init_dy -= delta_y;
    }

    ground = new Ground("../RainSimulator/obj/ground.obj");

    ground->translate(0, -.6, 0);
    this->render();

    animation_timer = new QTimer();

    connect(animation_timer, SIGNAL(timeout()), this, SLOT(animate()));

    animation_timer->start(rain_time);
}

MainWindow::~MainWindow()
{
    delete animation_timer;
    delete[] z_buffer;
    delete[] droplets;

    delete ui;
}

void MainWindow::animate()
{
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
    {
        if (droplets[i]->get_dy() < -0.4)
        {
            //droplets[i]->set_dx(-droplets[i]->get_dx());
            droplets[i]->set_dy(1);
            //droplets[i]->set_dz(-droplets[i]->get_dz());
            continue;
        }

        droplets[i]->translate(dx, dy, dz);
    }
    this->render();
}

void MainWindow::render()
{
    for (std::size_t i = 0; i < WIDTH * HEIGHT; i++)
        z_buffer[i] = 0;
    image->fill(mode.rgb());
    ground->draw(WIDTH, HEIGHT, 0, 102, 0, image);
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
        droplets[i]->draw(WIDTH, HEIGHT, 51, 153, 255, image);
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

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (previous_time - arg1 < 0)
        dy -= 0.01;
    else if (previous_time - arg1 > 0)
        dy += 0.01;

    previous_time = arg1;
}

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    if (previous_dx - arg1 < 0)
        dx -= 0.01;
    else if (previous_dx - arg1 > 0)
        dx += 0.01;

    previous_dx = arg1;
}

void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    if (previous_dz - arg1 < 0)
        dz += 0.01;
    else if (previous_dz - arg1 > 0)
        dz -= 0.01;

    previous_dz = arg1;
}

void MainWindow::on_spinBox_4_valueChanged(int arg1)
{
    double d = 0;
    if (previous_size - arg1 < 0)
        d = 0.001;
    else if (previous_size - arg1 > 0)
        d = -0.001;

    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
        droplets[i]->scale(d, d, d);

    previous_size = arg1;
}

