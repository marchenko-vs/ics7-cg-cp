#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDoubleSpinBox>

#include <cstdlib>
#include <vector>

#include "object.h"

#define WIDTH 1005
#define HEIGHT 635
#define DEPTH 255

#define DEFAULT_FROM_X 0
#define DEFAULT_FROM_Y 0

#define DEFAULT_LIGHT_X 0
#define DEFAULT_LIGHT_Y 0

#define NUM_OF_DROPLETS 2

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void render();

private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void rotate_left();
    void rotate_right();
    void rotate_up();
    void rotate_down();

    void on_pushButton_4_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_5_clicked();

    void on_pushButton_12_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_11_clicked();

    void animate();

    void on_horizontalSlider_2_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QImage *image;
    QTimer *timer;
    QColor mode = QColor(102, 178, 255);

    RainDroplet **droplets;
    Ground *ground;

    int droplet_size_slider;
    std::size_t rain_time;
};
#endif // MAINWINDOW_H
