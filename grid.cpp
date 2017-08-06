#include "grid.h"

#include <QGraphicsRectItem>
#include <qmath.h>

Grid::Grid(QSize size)
    : size(size),
    unitSize(100)
{
    grid.resize(size.width() * size.height());
    for(int i = 0; i <= size.width(); i++)
    {
        addLine(i * unitSize, 0, i * unitSize, size.height() * unitSize);
    }
    for(int i = 0; i <= size.height(); i++)
    {
        addLine(0, i * unitSize, size.width() * unitSize, i * unitSize);
    }
}

void Grid::setCell(QPointF position)
{
    QPoint gridPosition(qFloor(position.x() / (qreal)unitSize), qFloor(position.y() / (qreal)unitSize));
    if (gridPosition.x() >= size.width() 
            || gridPosition.y() >= size.height()
            || gridPosition.x() < 0
            || gridPosition.y() < 0)
    {
        return;
    }
    size_t offset = gridPosition.y() * size.width() + gridPosition.x();
    if (!grid[offset].isSet)
    {
        grid[offset].isSet = true;
        grid[offset].rectItem = addRect(gridPosition.x() * unitSize, 
                  gridPosition.y() * unitSize, 
                  unitSize, 
                  unitSize, 
                  QPen(Qt::blue), 
                  QBrush(Qt::SolidPattern));
    }
}

void Grid::unsetCell(QPointF position)
{
    QPoint gridPosition(qFloor(position.x() / (qreal)unitSize), qFloor(position.y() / (qreal)unitSize));
    if (gridPosition.x() >= size.width() 
            || gridPosition.y() >= size.height()
            || gridPosition.x() < 0
            || gridPosition.y() < 0)
    {
        return;
    }
    size_t offset = gridPosition.y() * size.width() + gridPosition.x();
    if (grid[offset].isSet)
    {
        grid[offset].isSet = false;
        removeItem(grid[offset].rectItem);
        delete grid[offset].rectItem;
        grid[offset].rectItem = nullptr;
    }
}
