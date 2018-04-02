#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QSize gridDimensions, size_t frameCount);
    ~MainWidget();
    void save();
    void saveAs();
    
signals:
    void nameChanged(QString newName);
    
private slots:
    void onTimeSliderChanged(int newValue);
    
private:
    Ui::MainWidget *ui;
    QSize gridDimensions;
    size_t frameCount;
    QString currentFilePath;
    bool hasFilename;
};

#endif // MAINWIDGET_H
