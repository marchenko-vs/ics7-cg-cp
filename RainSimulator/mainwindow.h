#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QDoubleSpinBox>

#include <cstdlib>
#include <vector>

#include "object.h"

#define WIDTH 1000
#define HEIGHT 720
#define DEPTH 256

#define DEFAULT_FROM_X 2
#define DEFAULT_FROM_Y 2
#define DEFAULT_FROM_Z 7

#define DEFAULT_LIGHT_X 0
#define DEFAULT_LIGHT_Y -1
#define DEFAULT_LIGHT_Z -1

#define NUM_OF_DROPLETS 3375

#define MIN_DROPLETS_Y -0.3

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
    void on_spinBox_valueChanged(int arg1);
    void on_spinBox_4_valueChanged(int arg1);
    void animate();
    void render();
    void generateRain(const double density);
    void on_spinBox_2_valueChanged(int arg1);
    void on_spinBox_3_valueChanged(int arg1);
    void on_spinBox_5_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QImage *image;
    QTimer *animation_timer;
    QTimer *rendering_timer;

    QColor mode = QColor(12, 20, 69);

    RainDroplet **droplets;
    Ground *ground;

    int droplet_size_slider;
    int previous_time, previous_size;
    int previous_dx, previous_dz;
    int previous_density;
    int num_of_rows;
    int correction;
    double sum_dx_delta, sum_dz_delta;
    double density;
    std::size_t rain_time;

    double dx, dy, dz;
};
#endif // MAINWINDOW_H
