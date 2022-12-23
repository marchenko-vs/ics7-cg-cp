/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGraphicsView *graphicsView;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *spinBox;
    QLabel *label_4;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpinBox *spinBox_4;
    QSpinBox *spinBox_5;
    QLabel *label_5;
    QGroupBox *groupBox_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QGroupBox *groupBox_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QGroupBox *groupBox_4;
    QPushButton *pushButton_12;
    QPushButton *pushButton_10;
    QPushButton *pushButton_8;
    QPushButton *pushButton_11;
    QPushButton *pushButton_9;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1320, 820);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1320, 820));
        MainWindow->setMaximumSize(QSize(1320, 820));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 10, 1010, 730));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(1029, 10, 281, 281));
        QFont font;
        font.setPointSize(10);
        groupBox->setFont(font);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 40, 201, 31));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(70, 85, 201, 31));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(70, 190, 201, 20));
        label_3->setAlignment(Qt::AlignCenter);
        spinBox = new QSpinBox(groupBox);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setGeometry(QRect(10, 30, 51, 41));
        spinBox->setMaximum(10);
        spinBox->setSingleStep(1);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(70, 140, 201, 20));
        label_4->setAlignment(Qt::AlignCenter);
        spinBox_2 = new QSpinBox(groupBox);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setGeometry(QRect(10, 130, 51, 41));
        spinBox_2->setMinimum(-10);
        spinBox_2->setMaximum(10);
        spinBox_2->setSingleStep(1);
        spinBox_3 = new QSpinBox(groupBox);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setGeometry(QRect(10, 180, 51, 41));
        spinBox_3->setMinimum(-10);
        spinBox_3->setMaximum(10);
        spinBox_3->setSingleStep(1);
        spinBox_4 = new QSpinBox(groupBox);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        spinBox_4->setGeometry(QRect(10, 80, 51, 41));
        spinBox_4->setMinimum(0);
        spinBox_4->setMaximum(10);
        spinBox_4->setSingleStep(1);
        spinBox_5 = new QSpinBox(groupBox);
        spinBox_5->setObjectName(QString::fromUtf8("spinBox_5"));
        spinBox_5->setGeometry(QRect(10, 230, 51, 41));
        spinBox_5->setMinimum(0);
        spinBox_5->setMaximum(10);
        spinBox_5->setSingleStep(1);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(70, 240, 201, 20));
        label_5->setAlignment(Qt::AlignCenter);
        spinBox_2->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        spinBox->raise();
        label_4->raise();
        spinBox_3->raise();
        spinBox_4->raise();
        spinBox_5->raise();
        label_5->raise();
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(1030, 300, 281, 81));
        groupBox_2->setFont(font);
        pushButton_3 = new QPushButton(groupBox_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 30, 121, 41));
        pushButton_3->setFont(font);
        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(150, 30, 121, 41));
        pushButton_2->setFont(font);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(1030, 390, 281, 171));
        groupBox_3->setFont(font);
        pushButton_4 = new QPushButton(groupBox_3);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 130, 261, 31));
        pushButton_4->setFont(font);
        pushButton = new QPushButton(groupBox_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(120, 30, 41, 41));
        pushButton_5 = new QPushButton(groupBox_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(170, 80, 41, 41));
        pushButton_6 = new QPushButton(groupBox_3);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(70, 80, 41, 41));
        pushButton_7 = new QPushButton(groupBox_3);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(120, 80, 41, 41));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(1030, 570, 281, 171));
        groupBox_4->setFont(font);
        pushButton_12 = new QPushButton(groupBox_4);
        pushButton_12->setObjectName(QString::fromUtf8("pushButton_12"));
        pushButton_12->setGeometry(QRect(10, 130, 261, 31));
        pushButton_12->setFont(font);
        pushButton_10 = new QPushButton(groupBox_4);
        pushButton_10->setObjectName(QString::fromUtf8("pushButton_10"));
        pushButton_10->setGeometry(QRect(120, 80, 41, 41));
        pushButton_8 = new QPushButton(groupBox_4);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setGeometry(QRect(70, 80, 41, 41));
        pushButton_11 = new QPushButton(groupBox_4);
        pushButton_11->setObjectName(QString::fromUtf8("pushButton_11"));
        pushButton_11->setGeometry(QRect(170, 80, 41, 41));
        pushButton_9 = new QPushButton(groupBox_4);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setGeometry(QRect(120, 30, 41, 41));
        MainWindow->setCentralWidget(centralwidget);
        groupBox_3->raise();
        graphicsView->raise();
        groupBox->raise();
        groupBox_2->raise();
        groupBox_4->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1320, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Rain Simulator 3D", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\264\320\276\320\266\320\264\321\217", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214 \320\277\320\260\320\264\320\265\320\275\320\270\321\217 \320\272\320\260\320\277\320\265\320\273\321\214", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\272\320\260\320\277\320\265\320\273\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\260\320\264\320\265\320\275\320\270\321\217 \320\264\320\276\320\266\320\264\321\217 (Z)", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\320\260\320\264\320\265\320\275\320\270\321\217 \320\264\320\276\320\266\320\264\321\217 (X)", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\273\320\276\321\202\320\275\320\276\321\201\321\202\321\214 \320\264\320\276\320\266\320\264\321\217", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\222\321\200\320\265\320\274\321\217 \321\201\321\203\321\202\320\276\320\272", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\320\235\320\276\321\207\321\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\320\224\320\265\320\275\321\214", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\232\320\260\320\274\320\265\321\200\320\260", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\272\320\260\320\274\320\265\321\200\321\213", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\230\321\201\321\202\320\276\321\207\320\275\320\270\320\272 \321\201\320\262\320\265\321\202\320\260", nullptr));
        pushButton_12->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265 \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \320\270\321\201\321\202\320\276\321\207\320\275\320\270\320\272\320\260", nullptr));
        pushButton_10->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        pushButton_11->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
