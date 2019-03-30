#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>
#include <QPoint>
#include <QColor>
#include <QPaintEvent>
#include <QImage>
#include <QPixmap>
#include <QMouseEvent>


class myLabel : public QLabel
{
    Q_OBJECT
public:
    explicit myLabel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) ;
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

    void setLineColor(const QColor lineColor);
    void setLineSize(const int lineSize);
    void clear();

    QPoint getStartPoint();
    QPoint getEndPoint();



private:

        QColor lineColor;
        int lineSize;
        bool isPressed;
        QPoint lineStartPoint;
        QPoint lineEndPoint;

};

#endif // MYLABEL_H
