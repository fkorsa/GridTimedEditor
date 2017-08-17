#ifndef GRID_H
#define GRID_H

#include <vector>
#include <QGraphicsScene>

class Grid : public QGraphicsScene
{
public:
    Grid(QSize size);
    
    void setCell(QPointF position);
    void unsetCell(QPointF position);
    bool isCellSet(QPoint position);
    
private:
    struct Cell
    {
        bool isSet;
        QGraphicsRectItem *rectItem;
        
        Cell() : isSet(false), rectItem(nullptr) {}
    };
    
    std::vector<Cell> grid;
    QSize size;
    const int unitSize;
};

#endif // GRID_H
