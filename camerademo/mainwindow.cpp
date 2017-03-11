#include "mainwindow.h"
#include "ui_mainwindow.h"

stack<pair<int, int>>area;
pair<int, int>place;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    camera = new QCamera(this);
    viewfinder = new QCameraViewfinder(this);
    imageCapture = new QCameraImageCapture(camera);
    ui->label->setScaledContents(true);    //自动调整为QLabel大小
	ui->imageLabel->setScaledContents(true);
    ui->horizontalLayout->addWidget(viewfinder);
    camera->setViewfinder(viewfinder);
    camera->start();
    QObject::connect(imageCapture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(displayImage(int, QImage)));
    QObject::connect(ui->capturePushButton, SIGNAL(clicked()), this, SLOT(captureImage()));
    QObject::connect(ui->savePushButton, SIGNAL(clicked()), this, SLOT(saveImage()));
    QObject::connect(ui->exitPushButton, SIGNAL(clicked()), qApp, SLOT(quit()));
	 
    QObject::connect(ui->openPushButton, SIGNAL(clicked()), this, SLOT(open()));
	//Failed
	QObject::connect(ui->tabPushButton, SIGNAL(clicked()), this, SLOT(tab(ui->label->pixmap()))); 

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::displayImage(int, QImage image){
    ui->label->setPixmap(QPixmap::fromImage(image));
	//调整QLabel大小
	/*ui->label->resize(ui->label->pixmap()->size()); */

    ui->statusBar->showMessage(tr("捕获成功"), 5000);
}

void MainWindow::captureImage(){
    ui->statusBar->showMessage(tr("正在捕获图片"), 1000);
    imageCapture->capture();

}

void MainWindow::saveImage(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save to"), QDir::homePath(), tr("jpeg格式文件(*.jpg)"));
    if (fileName.isEmpty()) {
        ui->statusBar->showMessage(tr("Error"), 5000);
        return;
    }
    const QPixmap* pixmap = ui->label->pixmap();
    if (pixmap) {
        pixmap->save(fileName);
        ui->statusBar->showMessage(tr("Saving succeed"), 5000);
    }

}



Mat MainWindow::QImage2cvMat(QImage image)
{
	Mat mat;
	switch (image.format()){
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
		cvtColor(mat, mat, CV_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
		break;
	}
	return mat;
}

QImage MainWindow::cvMat2QImage(const Mat& mat)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		QImage image(mat.cols, mat.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = mat.data;
		for (int row = 0; row < mat.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, mat.cols);
			pSrc += mat.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)mat.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		QMessageBox::information(this, "Error", "Mat could not be converted to QImage.");
		return QImage();
	}
}


void MainWindow::color(Mat & M_erode1, Mat &M_end)
{
	
	uchar temp = 0;
	for (int i = 0; i < M_erode1.rows; i++){
		for (int j = 0; j < M_erode1.cols; j++){
			temp = M_erode1.at<uchar>(i, j);
			if (temp <= 51)
			{
				M_end.at<Vec3b>(i, j)[0] = 255;
				M_end.at<Vec3b>(i, j)[1] = temp * 5;
				M_end.at<Vec3b>(i, j)[2] = 0;
			}
			else if (temp <= 102)
			{
				temp -= 51;

				M_end.at<Vec3b>(i, j)[0] = 255 - temp * 5;
				M_end.at<Vec3b>(i, j)[1] = 255;
				M_end.at<Vec3b>(i, j)[2] = 0;
			}
			else if (temp <= 153)
			{
				temp -= 102;

				M_end.at<Vec3b>(i, j)[0] = 0;
				M_end.at<Vec3b>(i, j)[1] = 255;
				M_end.at<Vec3b>(i, j)[2] = temp * 5;
			}
			else if (temp <= 204)
			{
				temp -= 153;

				M_end.at<Vec3b>(i, j)[0] = 0;
				M_end.at<Vec3b>(i, j)[1] = 255 - uchar(128.0*temp / 51.0 + 0.5);
				M_end.at<Vec3b>(i, j)[2] = 255;
			}
			else if (temp < 255)
			{
				temp -= 204;

				M_end.at<Vec3b>(i, j)[0] = 0;
				M_end.at<Vec3b>(i, j)[1] = 127 - uchar(127.0*temp / 51.0 + 0.5);
				M_end.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				M_end.at<Vec3b>(i, j)[0] = 255;
				M_end.at<Vec3b>(i, j)[1] = 255;
				M_end.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
}

//自己写的腐蚀+二值化
void MainWindow::erode_me(Mat &M, Mat &M_erode1){
	for (int i = 1; i < M.rows - 1; i++){
		for (int j = 1; j < M.cols - 1; j++){
			if (M.at<uchar>(i, j)>0 && M.at<uchar>(i, j + 1)>0 && M.at<uchar>(i, j - 1) > 0
				&& M.at<uchar>(i - 1, j) > 0 && M.at<uchar>(i + 1, j) > 0){
				M_erode1.at<uchar>(i, j) = 255;

			}
			else
			{
				M_erode1.at<uchar>(i, j) = 0;
			}
		}
	}
}

//ROI
void MainWindow::ROI_me(Mat &M, Mat &M_erode1, Mat &M_erode){
	int maxx = 0, maxy = 0, minx = 100000, miny = 100000;
	for (int i = 1; i < M.rows - 1; i++){
		for (int j = 1; j < M.cols - 1; j++){
			if (M.at<uchar>(i, j) == 0 && i >= maxx){
				maxx = i;
			}
			if (M.at<uchar>(i, j) == 0 && j >= maxy){
				maxy = j;
			}
			if (M.at<uchar>(i, j) == 0 && i <= minx){
				minx = i;
			}
			if (M.at<uchar>(i, j) == 0 && j <= miny){
				miny = j;
			}
		}
	}

	//防止溢出
	if (miny - 3 >= 0 && minx - 3 >= 0 && maxx + 3 <= M.rows&&maxy + 3 <= M.cols){
		M_erode = M_erode1(Rect(miny - 3, minx - 3, (maxy - miny + 7), (maxx - minx + 7)));
	}
	else
		M_erode = M_erode1;
}


//直接处理相机照片
void MainWindow::tab(QPixmap image){
	if (image.isNull()){
		QMessageBox::information(this, "Error!", "Pls Capture Ahead of Time");
	}
	else{
		Mat M = QImage2cvMat(image.toImage());
		Mat M_erode1 = Mat::zeros(M.rows, M.cols, CV_8UC1);


		threshold(M, M_erode1, 10, 255, CV_THRESH_BINARY);

	    //针对白色背景的ROI
	    Mat M_erode;
	    ROI_me(M, M_erode1, M_erode);
		//连通域标记（8通路）
		int flag = 1;
		int label = 0;

		if (label <= k){
			for (int i = 1; i < M_erode.rows - 1; i++){
				for (int j = 1; j < M_erode.cols - 1; j++){
					if (M_erode.at<uchar>(i, j) == 0){
						label++;
						area.push(pair<int, int>(i, j));
					}
					while (!area.empty()){
						place = area.top();
						int tempx = place.first;
						int tempy = place.second;
						M_erode.at<uchar>(tempx, tempy) = 255 / k*label;
						area.pop();
						if (tempx - 1 >= 0){
							if (M_erode.at<uchar>(tempx - 1, tempy) == 0) {
								area.push(pair<int, int>(tempx - 1, tempy));
							}
						}
						if (tempx + 1 <= M_erode.rows - 1){
							if (M_erode.at<uchar>(tempx + 1, tempy) == 0) {
								area.push(pair<int, int>(tempx + 1, tempy));
							}
						}
						if (tempy - 1 >= 0){
							if (M_erode.at<uchar>(tempx, tempy - 1) == 0) {
								area.push(pair<int, int>(tempx, tempy - 1));
							}
						}
						if (tempy + 1 <= M_erode.cols - 1){
							if (M_erode.at<uchar>(tempx, tempy + 1) == 0) {
								area.push(pair<int, int>(tempx, tempy - 1));
							}
						}
						if (tempx + 1 <= M_erode.rows - 1 && tempy + 1 <= M_erode.cols - 1){
							if (M_erode.at<uchar>(tempx + 1, tempy + 1) == 0) {
								area.push(pair<int, int>(tempx + 1, tempy + 1));
							}
						}
						if (tempx - 1 >= 0 && tempy + 1 <= M_erode.cols - 1){
							if (M_erode.at<uchar>(tempx - 1, tempy + 1) == 0) {
								area.push(pair<int, int>(tempx - 1, tempy + 1));
							}
						}
						if (tempx - 1 >= 0 && tempy - 1 >= 0){
							if (M_erode.at<uchar>(tempx - 1, tempy - 1) == 0) {
								area.push(pair<int, int>(tempx - 1, tempy - 1));
							}
						}
						if (tempx + 1 <= M_erode.rows - 1 && tempy - 1 >= 0){
							if (M_erode.at<uchar>(tempx + 1, tempy - 1) == 0) {
								area.push(pair<int, int>(tempx + 1, tempy - 1));
							}
						}
					}
				}
			}
		}

		Mat M_end(M_erode1.rows, M_erode1.cols, CV_8UC3);
		color(M_erode1, M_end);

		QImage M_end1=cvMat2QImage(M_end);
		ui->imageLabel->setPixmap(QPixmap::fromImage(M_end1));
	}
}


//打开一张图片进行处理
void MainWindow::open(){
	QImage img;
	Mat image;
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image File(*.bmp *.jpg *.jpeg *.png)"));
	QTextCodec *code = QTextCodec::codecForName("gb18030");
	string name = code->fromUnicode(filename).data();
	image = imread(name);
	if (!image.data){
		QMessageBox::information(this, "Error", "Pls Choose a Image");
	}
	else
	{
		cv::cvtColor(image, image, CV_BGR2RGB);
		img = cvMat2QImage(image);
		ui->label->clear();
		ui->label->setPixmap(QPixmap::fromImage(img));
		tab(QPixmap::fromImage(img));
	}
}
