#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<ctype.h>

//qt
#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QPaintevent>
#include <QtMultimedia\QCamera>
#include <QtMultimedia\QCameraImageCapture>
#include <QtMultimediaWidgets\QCameraViewfinder>
#include <QLayout>
#include <QObject>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <QTextCodec>

//opencv
#include <opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<stack>
using namespace cv;
using namespace std;

extern int k ;  //滑动条对应的连通域个数



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QCamera *camera;
    QCameraViewfinder *viewfinder;
    QCameraImageCapture *imageCapture;

	

private slots:
    void displayImage(int, QImage);
    void captureImage();
    void saveImage();
	void tab(QPixmap);
	void open();
	Mat QImage2cvMat(QImage);
	void color(Mat &, Mat &);
	void erode_me(Mat &, Mat &);
	void ROI_me(Mat &, Mat &, Mat &);
	QImage cvMat2QImage(const Mat& mat);
};



#endif // MAINWINDOW_H
