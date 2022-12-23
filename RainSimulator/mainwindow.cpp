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
    previous_density = 0;
    correction = 14;
    previous_time = 0;
    previous_size = 0;
    droplet_size_slider = 0;
    dy = -0.1;
    dx = dz = 0.0;
    density = 0.2;
    previous_dx = previous_dz = 0;
    sum_dx_delta = 0.0, sum_dz_delta = 0.0;
    num_of_rows = cbrt(NUM_OF_DROPLETS);
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
    OriginalRainDroplet *main_droplet =
            new OriginalRainDroplet("obj/droplet.obj");
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
        droplets[i] = new RainDroplet(main_droplet);
    ground = new Ground("obj/ground.obj");
    ground->scale(0.2, 0, 0.2);
    ground->translate(0, -.7, 0);
    this->generateRain(density);
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

void MainWindow::generateRain(const double density)
{
    const double left_x = -1.4;
    const double up_y = 1.1;
    bool even = 0;
    int cube = cbrt(NUM_OF_DROPLETS);
    double init_dx = left_x, init_dy = up_y, init_dz = 1.6;
    double delta_x = density;
    double delta_y = density;
    double delta_z = density;
    int cube_2 = cube * cube;
    double offset = density / 2.0;
    for (std::size_t i = 0; i < cube; i++)
    {
        for (std::size_t j = 0; j < cube; j++)
        {
            for (std::size_t k = 0; k < cube; k++)
            {
                droplets[i * cube_2 + j * cube + k]->translate(init_dx, init_dy, init_dz);
                init_dx += delta_x;
            }
            if (even)
                init_dx = left_x + offset;
            else
                init_dx = left_x;
            init_dz -= delta_z;
        }
        init_dy -= delta_y;
        if (even)
        {
            even = 0;
            init_dx = left_x;
            init_dz = 1.6;
        }
        else
        {
            even = 1;
            init_dx = left_x + offset;
            init_dz = 1.55;
        }
    }
}

void MainWindow::animate()
{
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
    {
        if (droplets[i]->get_dy() < MIN_DROPLETS_Y)
        {
            droplets[i]->set_dx(droplets[i]->get_dx() - this->sum_dx_delta * this->correction);
            droplets[i]->set_dy(1);
            droplets[i]->set_dz(droplets[i]->get_dz() - this->sum_dz_delta * this->correction);
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
    ground->draw(WIDTH, HEIGHT, 0, 154, 23, image);
    for (std::size_t i = 0; i < NUM_OF_DROPLETS; i++)
        droplets[i]->draw(WIDTH, HEIGHT, 51, 153, 255, image);
    scene->addPixmap(QPixmap::fromImage(*image));
}

void MainWindow::rotate_right()
{
    from.rotate(0.0, 0.1, 0.0);
    this->render();
}

void MainWindow::rotate_left()
{
    from.rotate(0.0, -0.1, 0.0);
    this->render();
}

void MainWindow::rotate_up()
{
    from.rotate(-0.1, 0.0, 0.0);
    this->render();
}

void MainWindow::rotate_down()
{
    from.rotate(0.1, 0.0, 0.0);
    this->render();
}

void MainWindow::on_pushButton_2_clicked()
{
    mode = QColor(69, 179, 224);
    this->render();
}

void MainWindow::on_pushButton_3_clicked()
{
    mode = QColor(12, 20, 69);
    this->render();
}

void MainWindow::on_pushButton_4_clicked()
{
    from.set_x(DEFAULT_FROM_X);
    from.set_y(DEFAULT_FROM_Y);
    from.set_z(DEFAULT_FROM_Z);
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
    light_dir.set_x(DEFAULT_LIGHT_X);
    light_dir.set_y(DEFAULT_LIGHT_Y);
    light_dir.set_z(DEFAULT_LIGHT_Z);
    this->render();
}

void MainWindow::on_pushButton_9_clicked()
{
    if (light_dir.get_y() > -8)
        light_dir.change_y(-0.1);
    this->render();
}

void MainWindow::on_pushButton_10_clicked()
{
    if (light_dir.get_y() < 8)
        light_dir.change_y(0.1);
    this->render();
}

void MainWindow::on_pushButton_8_clicked()
{
    if (light_dir.get_x() < 8)
        light_dir.change_x(0.1);
    this->render();
}

void MainWindow::on_pushButton_11_clicked()
{
    if (light_dir.get_x() > -8)
        light_dir.change_x(-0.1);
    this->render();
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if (previous_time - arg1 < 0)
        rain_time += 50;
    else if (previous_time - arg1 > 0)
        rain_time -= 50;
    previous_time = arg1;
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

void MainWindow::on_spinBox_2_valueChanged(int arg1)
{
    if (previous_dx - arg1 < 0)
    {
        dx += 0.01;
        sum_dx_delta += 0.01;
    }
    else if (previous_dx - arg1 > 0)
    {
        dx -= 0.01;
        sum_dx_delta -= 0.01;
    }
    previous_dx = arg1;
}


void MainWindow::on_spinBox_3_valueChanged(int arg1)
{
    if (previous_dz - arg1 < 0)
    {
        dz += 0.01;
        sum_dz_delta += 0.01;
    }
    else if (previous_dz - arg1 > 0)
    {
        dz -= 0.01;
        sum_dz_delta -= 0.01;
    }
    previous_dz = arg1;
}

void MainWindow::on_spinBox_5_valueChanged(int arg1)
{
    this->animation_timer->stop();
    if (this->previous_density - arg1 < 0)
        this->density += 0.05;
    else if (this->previous_density - arg1 > 0)
        this->density -= 0.05;
    this->previous_density = arg1;
    this->generateRain(this->density);
    this->animation_timer->start(this->rain_time);
}

