#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>

#include <cstdlib>
#include <vector>

#include "object.h"

#define WIDTH 700
#define HEIGHT 630

#define NUM_OF_DROPLETS 20

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void rotate_left();
    void rotate_right();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QImage *image;

    RainDroplet **droplets;
    Ground *ground;

    QTimer *timer;

    QColor mode = QColor(102, 178, 255);
};
#endif // MAINWINDOW_H
