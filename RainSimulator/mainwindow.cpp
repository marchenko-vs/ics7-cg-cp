#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vertex.h"
#include "face.h"

#include <iostream>
#include <cstdlib>

/* self-written functions to draw instead of any libs */
void drawPoint(int x, int y, QGraphicsScene *scene, QColor color)
{
    scene->addLine(x, -y, x + 1, -y - 1, color);
}

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
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    const int width = 1000;
    const int height = 700;

    const QColor white_color = QColor(255, 255, 255);

    ui->setupUi(this);
    this->setWindowTitle("Rain Simulator 3D");

    scene = new QGraphicsScene;
    ui->graphicsView->setScene(scene);
    scene->setBackgroundBrush(Qt::black);

    obj = new Object;
    obj->GetObject("../RainSimulator/obj/african_head.obj");
    obj->draw(width, height, scene, white_color);
}

MainWindow::~MainWindow()
{
    delete ui;
}
