#ifndef MYQTIMAGEWIDGET_H
#define MYQTIMAGEWIDGET_H

#include <QWidget>
#include <opencv2/core/core.hpp>

class MyQTImageWidget : public QWidget
{
public:
    int x;
    int y;
    cv::Mat Im;
    MyQTImageWidget();
    explicit MyQTImageWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event);
    void paintBitmap(cv::Mat Im);

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent * event);
signals:
    void on_mousePressed(QPoint point, int butPressed);
    void on_mouseMove(QPoint point, int butPressed);
    void on_KeyPressed(int key);
public slots:

};

#endif // MYQTIMAGEWIDGET_H
