#ifndef MAINCANVAS_H
#define MAINCANVAS_H

#include <QGraphicsView>
#include "grid.h"

class MainCanvas : public QGraphicsView
{
public:
    MainCanvas(QWidget* parent);
    void setTime(size_t time);
    void setFramesCount(size_t framesCount);
    
protected:
    void resizeEvent(QResizeEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    
private:
    QSize gridSize;
    const int unitSize;
    const int borderSpacing;
    bool isLeftButtonPressed;
    bool isRightButtonPressed;
    int gridCount;
    size_t currentTime;
    std::vector<Grid*> grids;
};

#endif // MAINCANVAS_H
