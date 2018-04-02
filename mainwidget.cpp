#include "mainwidget.h"
#include "ui_mainwidget.h"

#include <QFileDialog>

MainWidget::MainWidget(QSize gridDimensions, size_t frameCount) :
    ui(new Ui::MainWidget),
    gridDimensions(gridDimensions),
    frameCount(frameCount),
    hasFilename(false)
{
    ui->setupUi(this);
    ui->timeSlider->setRange(0, (int)frameCount - 1);
    ui->graphicsView->initialize(gridDimensions, frameCount);
    
    connect(ui->timeSlider, SIGNAL(sliderMoved(int)), this, SLOT(onTimeSliderChanged(int)));
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::save()
{
    QString filePath;
    if (hasFilename)
    {
        filePath = currentFilePath;
    }
    else
    {
        
        filePath = QFileDialog::getSaveFileName(this, tr("Save File"),
                                   QString(),
                                   tr("TimedGrid (*.tmg)"));
        if (filePath.isEmpty())
        {
            return;
        }
    }
    hasFilename = true;
    currentFilePath = filePath;
    ui->graphicsView->saveTo(filePath);
    QFileInfo fileInfo(filePath);
    emit nameChanged(fileInfo.baseName());
}

void MainWidget::saveAs()
{
    hasFilename = false;
    save();
}

void MainWidget::onTimeSliderChanged(int newValue)
{
    ui->graphicsView->setTime(newValue);
}
