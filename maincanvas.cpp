#include "maincanvas.h"

#include <QDebug>
#include <QResizeEvent>

MainCanvas::MainCanvas(QWidget *parent)
    : QGraphicsView(parent),
      grid(QSize(10, 10)),
      gridSize(10, 10),
      isLeftButtonPressed(false),
      isRightButtonPressed(false),
      unitSize(100)
{
    setScene(&grid);
    setSceneRect(0, 0, unitSize * gridSize.width(), unitSize * gridSize.height());
}

void MainCanvas::resizeEvent(QResizeEvent *event)
{
    /*
    qreal newX = (qreal)event->size().width() / ((qreal)gridSize.width() * 100.0);
    scale((qreal)event->size().width() / ((qreal)gridSize.width() * 100.0), 
          (qreal)event->size().height() / ((qreal)gridSize.height() * 100.0));*/
}

void MainCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        grid.setCell(mapToScene(event->pos()));
        isLeftButtonPressed = true;
    }
    else if (event->button() == Qt::RightButton)
    {
        grid.unsetCell(mapToScene(event->pos()));
        isRightButtonPressed = true;
    }
}

void MainCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (isLeftButtonPressed)
    {
        grid.setCell(mapToScene(event->pos()));
    }
    else if (isRightButtonPressed)
    {
        grid.unsetCell(mapToScene(event->pos()));
    }
}

void MainCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        isLeftButtonPressed = false;
    }
    else if (event->button() == Qt::RightButton)
    {
        isRightButtonPressed = false;
    }
}
