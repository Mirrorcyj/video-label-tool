#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "opencv2/opencv.hpp"
#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QLabel>
#include <QPaintEvent>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <QPoint>
#include <mylabel.h>
#include <QKeyEvent>

using namespace std;
using namespace cv;

namespace Ui {
class MainWindow;
class myLabel;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int isempty(myLabel *);

protected:
    void keyPressEvent(QKeyEvent *e);

private slots:
    void on_o_v_Button_clicked();
    void on_n_f_Button_clicked();
    void on_c_f_Button_clicked();

private:
    Ui::MainWindow *ui;

    VideoCapture video;
    Mat img_original, img_drawing;
    QImage defaultImage;

    int frame_counter = 0;
    int Top_y = 0;

    QPixmap pix;
    QPoint startPoint;
    QPoint endPoint;
    QString path;
    QString videoName;
    QString filePath;
    QFile *f;

    myLabel *imageLabel;

};

#endif // MAINWINDOW_H
