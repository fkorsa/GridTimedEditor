#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <QGraphicsView>
#include "grid.h"

class MainCanvas : public QGraphicsView
{
public:
    MainCanvas(QWidget* parent);
    
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    
private:
    Grid grid;
    QSize gridSize;
    const int unitSize;
    bool isLeftButtonPressed;
    bool isRightButtonPressed;
};

#endif // MAINCANVAS_H
