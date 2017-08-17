#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QSize gridDimensions, size_t frameCount) :
    ui(new Ui::MainWidget),
    gridDimensions(gridDimensions),
    frameCount(frameCount)
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

void MainWidget::saveTo(QString path)
{
    ui->graphicsView->saveTo(path);
}

void MainWidget::onTimeSliderChanged(int newValue)
{
    ui->graphicsView->setTime(newValue);
}
