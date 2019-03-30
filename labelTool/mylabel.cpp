#include "mylabel.h"
#include <QPainter>

myLabel::myLabel(QWidget *parent) : QLabel(parent)
{

    this->lineStartPoint = QPoint(0,0);
    this->lineEndPoint = QPoint(0,0);
   this->lineColor = QColor(Qt::black);
   this->lineSize = 3;
}

/******************** draw the rectangle ********************/
void myLabel::paintEvent(QPaintEvent *event)
{
   QLabel::paintEvent(event);//必须有，才能让背景图片显示出来
   QPainter painter(this);
   QPen pen;
   pen.setColor(lineColor);
   pen.setWidth(lineSize);
   painter.setPen(pen);
   painter.drawRect(lineStartPoint.x(),lineStartPoint.y(),lineEndPoint.x()-lineStartPoint.x(),lineEndPoint.y()-lineStartPoint.y());
}

/******************** Mouse Press Event ********************/
void myLabel::mousePressEvent(QMouseEvent *e)
{
   lineStartPoint = e->pos();
   lineEndPoint = e->pos();
   isPressed = true;
}

/******************** Mouse Move Event ********************/
void myLabel::mouseMoveEvent(QMouseEvent *e)
{
   if(isPressed)
   {
       lineEndPoint=e->pos();
       update();
   }
}

/******************** Mouse Release Event ********************/
void myLabel::mouseReleaseEvent(QMouseEvent *e)
{
   isPressed=false;
   update();
}

/******************** Set Line Color ********************/
void myLabel::setLineColor(const QColor lineColor)
{
   this->lineColor = lineColor;
}

/******************** Set Line size ********************/
void myLabel::setLineSize(const int lineSize)
{
   this->lineSize = lineSize;
}

/******************** Get Start Point ********************/
QPoint myLabel::getStartPoint()
{
   return lineStartPoint;
}

/******************** Get End Point ********************/
QPoint myLabel::getEndPoint()
{
   return lineEndPoint;
}

/******************** Clear Points ********************/
void myLabel::clear()
{
   lineStartPoint = QPoint(0,0);
   lineEndPoint = QPoint(0,0);
   update();
}
