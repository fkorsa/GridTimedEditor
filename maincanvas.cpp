#include "maincanvas.h"

#include <QDebug>
#include <QResizeEvent>

MainCanvas::MainCanvas(QWidget *parent)
    : QGraphicsView(parent),
      gridSize(5, 5),
      gridCount(5),
      isLeftButtonPressed(false),
      isRightButtonPressed(false),
      unitSize(100),
      borderSpacing(10)
{
    grids.push_back(new Grid(gridSize));
    setScene(grids[0]);
    setSceneRect(-borderSpacing, -borderSpacing, unitSize * gridSize.width() + 2 * borderSpacing, unitSize * gridSize.height() + 2 * borderSpacing);
    QSize fixedSize(unitSize * gridSize.width() + 5 * borderSpacing, unitSize * gridSize.height() + 5 * borderSpacing);
    //setMinimumSize(fixedSize);
    setMaximumSize(fixedSize);
}

void MainCanvas::resizeEvent(QResizeEvent *event)
{
    /*
    qreal newX = (qreal)event->size().width() / ((qreal)gridSize.width() * 100.0);
    scale((qreal)event->size().width() / ((qreal)gridSize.width() * 100.0), 
          (qreal)event->size().height() / ((qreal)gridSize.height() * 100.0));*/
    QGraphicsView::resizeEvent(event);
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
    repaint();
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
    repaint();
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
