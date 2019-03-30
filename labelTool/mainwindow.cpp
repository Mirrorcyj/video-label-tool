#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QFile>
#include <QTextStream>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    imageLabel = new myLabel(this);
    ui->scrollArea->setWidget(imageLabel);
    ui->frameTotalNumLine->setText("0");
    ui->currentFrameNumLine->setText("0");
    ui->fpsLine->setText("0");
    ui->frameWidthLine->setText("0");
    ui->frameHeightLine->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

/******************** open_video button ********************/
void MainWindow::on_o_v_Button_clicked()
{

    path = QFileDialog::getOpenFileName(this, tr("Open video"), ".", tr("video Files(*.avi *.mp4)"));   //get file path
    string videoPath = path.toStdString();
    videoName = path.section('/',-1);
    ui->videoName->setText(videoName);
    if(path.length() == 0) {
            QMessageBox::information(this, tr("Path"), tr("You didn't select any files."));
    } else {
            ui->textEdit->append(tr("You selected ") + path);
            if(video.isOpened()){
                video.release();
                imageLabel->clear();
                frame_counter = 0;
            };
            if(video.open(videoPath))
                {

                    video = VideoCapture(videoPath);
                    ui->n_f_Button->setEnabled(true);
                }
            else {
               ui->textEdit->append("open video failed!");
            };

            //get video parameters
            double frameH = video.get(CV_CAP_PROP_FRAME_HEIGHT);
            double frameW = video.get(CV_CAP_PROP_FRAME_WIDTH);
            double fps = video.get(CV_CAP_PROP_FPS);
            double numFrames = video.get(CV_CAP_PROP_FRAME_COUNT);

            //set video parameters
            ui->frameTotalNumLine->setText(QString::number(numFrames, 10, 0));
            ui->currentFrameNumLine->setText("0");
            ui->fpsLine->setText(QString::number(fps, 10, 0));
            ui->frameWidthLine->setText(QString::number(frameW, 10, 0));
            ui->frameHeightLine->setText(QString::number(frameH, 10, 0));

            int h = ui->scrollArea->size().height();    // scollArea Height
            Top_y = (h - frameH) / 2;    //the height from the top of scollArea to the frame

            video >> img_original;    //read video
            img_original.copyTo(img_drawing);
            defaultImage = QImage(img_original.data,img_original.cols,img_original.rows,QImage::Format_RGB888);
                //ui->label->clear();
            imageLabel->setPixmap(QPixmap::fromImage(defaultImage));

            //create a label directory if it is not exist
            QDir dir;
            QString dirPath = path.section('/',0,-2) + "/labels";
            if(!dir.exists(dirPath)){
                    bool ok = dir.mkdir(dirPath);
                    if(ok){
                        ui->textEdit->append("Create sucessful!:" + dirPath);
                    }else{
                        ui->textEdit->append("Create failed.");
                    }
                }
           filePath = dirPath + "/" + videoName.split('.')[0] + ".txt";
           //QString filePath = path.split('.')[0] + ".txt";

           //create an '.txt' file of the video if it is not exist
           f = new QFile(filePath, this);
           if(!f->open(QIODevice::WriteOnly | QIODevice::Text))
           {
              ui->textEdit->append("Open failed.");
           }

    }


}

/******************** next_frame shortcut ********************/
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_N)
        on_n_f_Button_clicked();
}


/******************** next_frame button ********************/
void MainWindow::on_n_f_Button_clicked()
{
    //read the next frame
    ++frame_counter;
    ui->currentFrameNumLine->setText(QString::number(frame_counter, 10, 0));
    video >> img_original;

    if (img_original.empty()){
        ui->textEdit->append("\nVideo Finished!");
        ui->n_f_Button->setEnabled(false);
        imageLabel->clear();
         f->close();
    }

    //update current frame
    img_original.copyTo(img_drawing);
    defaultImage = QImage(img_drawing.data,img_drawing.cols,img_drawing.rows,QImage::Format_RGB888);
    imageLabel->setPixmap(QPixmap::fromImage(defaultImage));

    // write the label.txt file
    if (!isempty(imageLabel))
    {

       QPoint startP = imageLabel->getStartPoint();
       QPoint endP = imageLabel->getEndPoint();

       //compute the coordinate of points in frame
       int start_x = startP.x();
       int end_x = endP.x();
       int start_y = startP.y()-Top_y;
       int end_y = endP.y()-Top_y;

       //print the coordinate of points
       ui->textEdit->append("frame:" +  QString::number(frame_counter));
       ui->textEdit->append(tr(" startx: ") + QString::number(start_x) +tr(" starty: ") + QString::number(start_y));
       ui->textEdit->append(tr(" endx:") + QString::number(end_x) + tr(" endy: ") + QString::number(end_y) );

       QTextStream txtOutput(f);

       //save the information like "* frame_number startPoint_x startPoint_y,endPoint_x endPoint_y"
       txtOutput << "* " << frame_counter << " "<< start_x << " "<< start_y << ","
                << end_x << " "<< end_y  << " "<<endl;



    }
    else {
        ui->textEdit->append("no points");
    }
}

/******************** function isempty() ********************/
int MainWindow::isempty(myLabel *label)
{
    for (int i = 0 ; i < 2; i++)
    {
        if (label->getStartPoint() != QPoint(0,0) || label->getEndPoint() != QPoint(0,0) )
        {
            return 0;
        }
    }
    return 1;
}

/******************** clear_frame button ********************/
void MainWindow::on_c_f_Button_clicked()
{
    imageLabel->clear();
}
