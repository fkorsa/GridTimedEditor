#include "maincanvas.h"

#include <QDebug>
#include <QResizeEvent>

#define TMG_VERSION 1

MainCanvas::MainCanvas(QWidget *parent)
    : QGraphicsView(parent),
      gridSize(0, 0),
      gridCount(5),
      isLeftButtonPressed(false),
      isRightButtonPressed(false),
      unitSize(100),
      borderSpacing(10),
      currentTime(0)
{
}

void MainCanvas::setTime(size_t time)
{
    currentTime = time;
    setScene(grids[currentTime]);
}

void MainCanvas::setFrameCount(size_t frameCount)
{
    if(frameCount == 0)
    {
        Q_ASSERT(false);
        return;
    }
    if(frameCount < grids.size())
    {
        if(currentTime > frameCount)
        {
            setTime(frameCount - 1);
        }
        for(size_t i = frameCount; i < grids.size(); i++)
        {
            delete grids[i];
        }
        grids.resize(frameCount);
    }
    else if(frameCount > grids.size())
    {
        size_t oldGridSize = grids.size();
        grids.resize(frameCount);
        for(size_t i = oldGridSize; i < frameCount; i++)
        {
            grids[i] = new Grid(gridSize);
        }
    }
}

void MainCanvas::initialize(QSize gridSize, size_t frameCount)
{
    this->gridSize = gridSize;
    setFrameCount(frameCount);
    setScene(grids[0]);
    setSceneRect(-borderSpacing, -borderSpacing, unitSize * gridSize.width() + 2 * borderSpacing, unitSize * gridSize.height() + 2 * borderSpacing);
    QSize fixedSize(unitSize * gridSize.width() + 5 * borderSpacing, unitSize * gridSize.height() + 5 * borderSpacing);
    setMaximumSize(fixedSize);
}

void MainCanvas::saveTo(QString path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        Q_ASSERT(false);
        return;
    }
    
    QTextStream out(&file);
    out << TMG_VERSION << endl;
    out << gridSize.width() << " " << gridSize.height() << endl;
    out << grids.size() << endl;
    
    for(size_t t = 0; t < grids.size(); t++)
    {
        for(size_t y = 0; y < gridSize.height(); y++)
        {
            for(size_t x = 0; x < gridSize.width(); x++)
            {
                out << grids[t]->isCellSet(QPoint(x, y)) << " ";
            }
            out << endl;
        }
        out << endl;
    }
    
    file.close();
}

void MainCanvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        grids[currentTime]->setCell(mapToScene(event->pos()));
        isLeftButtonPressed = true;
    }
    else if (event->button() == Qt::RightButton)
    {
        grids[currentTime]->unsetCell(mapToScene(event->pos()));
        isRightButtonPressed = true;
    }
    repaint();
}

void MainCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if (isLeftButtonPressed)
    {
        grids[currentTime]->setCell(mapToScene(event->pos()));
    }
    else if (isRightButtonPressed)
    {
        grids[currentTime]->unsetCell(mapToScene(event->pos()));
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
