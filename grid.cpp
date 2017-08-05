#include "grid.h"

#include <QGraphicsRectItem>

Grid::Grid(QSize size)
    : size(size),
    unitSize(100)
{
    grid.resize(size.width() * size.height());
}

void Grid::setCell(QPointF position)
{
    QPoint gridPosition(position.x() / unitSize, position.y() / unitSize);
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
    QPoint gridPosition(position.x() / unitSize, position.y() / unitSize);
    size_t offset = gridPosition.y() * size.width() + gridPosition.x();
    if (grid[offset].isSet)
    {
        grid[offset].isSet = false;
        removeItem(grid[offset].rectItem);
        delete grid[offset].rectItem;
        grid[offset].rectItem = nullptr;
    }
}
