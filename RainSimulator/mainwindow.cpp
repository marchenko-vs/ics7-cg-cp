#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vertex.h"
#include "face.h"
#include "object.h"

#include <iostream>
#include <cstdlib>

#include <QPushButton>

/* self-written functions to draw instead of any libs
void drawLine(int x_0, int y_0, int x_1, int y_1,
              QGraphicsScene *scene, QColor color)
{
    bool steep = false;

    if (std::abs(x_0 - x_1) < std::abs(y_0 - y_1))
    {
        std::swap(x_0, y_0);
        std::swap(x_1, y_1);

        steep = true;
    }

    if (x_0 > x_1)
    {
        std::swap(x_0, x_1);
        std::swap(y_0, y_1);
    }

    int dx = x_1 - x_0;
    int dy = y_1 - y_0;

    int derror_2 = std::abs(dy) * 2;
    int error_2 = 0;

    int y = y_0;

    for (int x = x_0; x <= x_1; ++x)
    {
        if (steep)
        {
            drawPoint(y, x, scene, color);
        }
        else
        {
            drawPoint(x, y, scene, color);
        }

        error_2 += derror_2;

        if (error_2 > dx)
        {
            if (y_1 > y_0)
            {
                y++;
            }
            else
            {
                y--;
            }

            error_2 -= dx * 2;
        }
    }
} */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    const int width = 660;
    const int height = 540;

    const QColor white_color = QColor(255, 255, 255);

    ui->setupUi(this);
    this->setWindowTitle("Rain Simulator 3D");

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(QColor(0, 0, 110));

    obj = new Object("../RainSimulator/obj/cube.obj");
    obj->draw(650, 540, scene, QColor(255, 255, 255));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    scene->clear();
    obj->rotate_z(30);
    obj->draw(650, 540, scene, QColor(255, 255, 255));
}


void MainWindow::on_pushButton_2_clicked()
{
    scene->setBackgroundBrush(QColor(102, 178, 255));
}


void MainWindow::on_pushButton_3_clicked()
{
    scene->setBackgroundBrush(QColor(0, 0, 110));
}

