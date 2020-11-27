#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMouseEvent>

class MainWindow : public QWidget
{
    Q_OBJECT

    bool isDrawing = false;
    QCursor *spi;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;
};
#endif // MAINWINDOW_H
