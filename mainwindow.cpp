#include "mainwindow.h"
#include <QDebug>
#include <QToolTip>
#include <QPainter>
#include <QVector>
#include <QBitmap>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    QPixmap pix("./Images_lab2/cursor1.cur");
    pix.setMask(QBitmap("./Images_lab2/cursor1.cur"));
    spi = new QCursor(pix);


    setCursor(Qt::CursorShape::PointingHandCursor);




    show();
}

MainWindow::~MainWindow()
{
    delete spi;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

    if (event->button() == Qt::MouseButton::RightButton &&
            (event->modifiers() == Qt::ControlModifier) )
    {
        QString posX = QString::number(event->pos().x());
        QString posY = QString::number(event->pos().y());
        QString posStr = "(X: " + posX + " Y: " + posY + ")";
        QToolTip::showText( QPoint( this -> pos().x(), this -> pos().y() ),
                            posStr, this);
    }
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        isDrawing = true;
        setCursor(*spi);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        isDrawing = false;
        setCursor(Qt::CursorShape::PointingHandCursor);
    }

    setWindowTitle("Web");
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isDrawing) {
        QWidget::update();
    }

    if ( !rect().contains( event->pos() ) ) {
        QCursor::setPos( mapToGlobal( rect().center() ) );
    }


}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if (isDrawing) {
        QPainter painter(this);
        painter.setPen(QPen(Qt::black));
        QRect rect = this -> rect();
        QPoint curPos = mapFromGlobal( QCursor::pos() );

        size_t webInterval = 4;
        QVector <QPoint> vf;
        QVector <QPoint> vc;
        QVector <QPoint> vl;

        for (int x = rect.x() + rect.width()/webInterval; x < rect.width(); x += rect.width()/webInterval) {
            painter.drawLine(QPoint(x, 0), curPos);

            int xc = ( x+curPos.x() ) / 2;
            int yc = ( 0+curPos.y() ) / 2;
            vc.push_back( QPoint(xc, yc) );
        }

        for (int y = rect.y() + rect.height()/webInterval; y < rect.height(); y += rect.height()/webInterval) {
            painter.drawLine(QPoint(rect.width(), y), curPos);

            int xc = ( rect.width()+curPos.x() ) / 2;
            int yc = ( y+curPos.y() ) / 2;
            vc.push_back( QPoint(xc, yc) );
        }

        for (int x = rect.width() - rect.width()/webInterval; x > rect.x(); x -= rect.width()/webInterval) {
            painter.drawLine(QPoint(x, rect.height()), curPos);

            int xc = ( x+curPos.x() ) / 2;
            int yc = ( rect.height()+curPos.y() ) / 2;
            vc.push_back( QPoint(xc, yc) );
        }

        for(int y = rect.height() - rect.height()/webInterval; y > rect.y(); y -= rect.height()/webInterval) {
            painter.drawLine(QPoint(0, y), curPos);

            int xc = ( 0+curPos.x() ) / 2;
            int yc = ( y+curPos.y() ) / 2;
            vc.push_back( QPoint(xc, yc) );
        }
        vc.push_back(vc[0]);



        painter.drawPolyline(vc.constData(), vc.size());


    }
}


void MainWindow::resizeEvent(QResizeEvent *event)
{
    QString title = "Width: " + QString::number( rect().width() ) +
                  " Height: " + QString::number( rect().height() );
    setWindowTitle(title);
}
